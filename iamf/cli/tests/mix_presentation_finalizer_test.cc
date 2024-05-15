/*
 * Copyright (c) 2023, Alliance for Open Media. All rights reserved
 *
 * This source code is subject to the terms of the BSD 3-Clause Clear
 * License and the Alliance for Open Media Patent License 1.0. If the BSD
 * 3-Clause Clear License was not distributed with this source code in the
 * LICENSE file, you can obtain it at
 * www.aomedia.org/license/software-license/bsd-3-c-c. If the Alliance for
 * Open Media Patent License 1.0 was not distributed with this source code
 * in the PATENTS file, you can obtain it at www.aomedia.org/license/patent.
 */
#include "iamf/cli/mix_presentation_finalizer.h"

#include <list>
#include <vector>

#include "absl/status/status.h"
#include "gtest/gtest.h"
#include "iamf/cli/tests/cli_test_utils.h"
#include "iamf/obu/mix_presentation.h"
#include "src/google/protobuf/repeated_ptr_field.h"
#include "src/google/protobuf/text_format.h"

namespace iamf_tools {
namespace {

class MeasureLoudnessOrFallbackToUserLoudnessMixPresentationFinalizerTest
    : public ::testing::Test {
 public:
  MeasureLoudnessOrFallbackToUserLoudnessMixPresentationFinalizerTest() {
    // Initialize the input OBUs which will have loudness finalized.
    AddMixPresentationObuWithAudioElementIds(
        /*mix_presentation_id=*/42, /*audio_element_id=*/300,
        /*common_parameter_id=*/999,
        /*common_parameter_rate=*/16000, obus_to_finalize_);

    // Initialize the expected output OBUs.
    AddMixPresentationObuWithAudioElementIds(
        /*mix_presentation_id=*/42, /*audio_element_id=*/300,
        /*common_parameter_id=*/999,
        /*common_parameter_rate=*/16000, expected_obus_);
  }

  void InitAndTestGenerate(
      absl::StatusCode expected_finalize_status_code = absl::StatusCode::kOk) {
    MeasureLoudnessOrFallbackToUserLoudnessMixPresentationFinalizer finalizer(
        mix_presentation_metadata_);

    // `Finalize()` ignores most of the arguments.
    EXPECT_EQ(finalizer.Finalize({}, {}, {}, obus_to_finalize_).code(),
              expected_finalize_status_code);

    if (expected_finalize_status_code == absl::StatusCode::kOk) {
      EXPECT_EQ(obus_to_finalize_, expected_obus_);
    }
  }

 protected:
  std::list<MixPresentationObu> obus_to_finalize_;
  ::google::protobuf::RepeatedPtrField<
      iamf_tools_cli_proto::MixPresentationObuMetadata>
      mix_presentation_metadata_;
  std::list<MixPresentationObu> expected_obus_;
};

TEST_F(MeasureLoudnessOrFallbackToUserLoudnessMixPresentationFinalizerTest,
       NoMixPresentationObus) {
  obus_to_finalize_.clear();
  expected_obus_.clear();
  InitAndTestGenerate();
}

TEST_F(MeasureLoudnessOrFallbackToUserLoudnessMixPresentationFinalizerTest,
       CopiesIntegratedLoudnessAndDigitalPeak) {
  // Omit unused user metadata.
  ASSERT_TRUE(google::protobuf::TextFormat::ParseFromString(
      R"pb(
        num_sub_mixes: 1
        sub_mixes {
          num_layouts: 1
          layouts {
            loudness {
              info_type_bit_masks: []
              integrated_loudness: 99
              digital_peak: 100
            }
          }
        }
      )pb",
      mix_presentation_metadata_.Add()));

  // `info_type` must be configured as a prerequisite.
  ASSERT_EQ(
      obus_to_finalize_.front().sub_mixes_[0].layouts[0].loudness.info_type, 0);

  expected_obus_.front().sub_mixes_[0].layouts[0].loudness = {
      .info_type = 0, .integrated_loudness = 99, .digital_peak = 100};

  InitAndTestGenerate();
}

TEST_F(MeasureLoudnessOrFallbackToUserLoudnessMixPresentationFinalizerTest,
       CopiesTruePeak) {
  // Omit unused user metadata.
  ASSERT_TRUE(google::protobuf::TextFormat::ParseFromString(
      R"pb(
        num_sub_mixes: 1
        sub_mixes {
          num_layouts: 1
          layouts {
            loudness {
              info_type_bit_masks: [ LOUDNESS_INFO_TYPE_TRUE_PEAK ]
              integrated_loudness: 99
              digital_peak: 100
              true_peak: 101
            }
          }
        }
      )pb",
      mix_presentation_metadata_.Add()));

  // `info_type` must be configured as a prerequisite.
  obus_to_finalize_.front().sub_mixes_[0].layouts[0].loudness.info_type =
      LoudnessInfo::kTruePeak;

  expected_obus_.front().sub_mixes_[0].layouts[0].loudness = {
      .info_type = LoudnessInfo::kTruePeak,
      .integrated_loudness = 99,
      .digital_peak = 100,
      .true_peak = 101};

  InitAndTestGenerate();
}

TEST_F(MeasureLoudnessOrFallbackToUserLoudnessMixPresentationFinalizerTest,
       InvalidInconsistentInfoType) {
  // Omit unused user metadata.
  ASSERT_TRUE(google::protobuf::TextFormat::ParseFromString(
      R"pb(
        num_sub_mixes: 1
        sub_mixes {
          num_layouts: 1
          layouts {
            loudness {
              info_type_bit_masks: [ LOUDNESS_INFO_TYPE_TRUE_PEAK ]
              integrated_loudness: 99
              digital_peak: 100
              true_peak: 101
            }
          }
        }
      )pb",
      mix_presentation_metadata_.Add()));

  // The finalizer reports an error when `info_type` was not configured as a
  // prerequisite.
  ASSERT_NE(
      obus_to_finalize_.front().sub_mixes_[0].layouts[0].loudness.info_type,
      LoudnessInfo::kTruePeak);

  InitAndTestGenerate(absl::StatusCode::kInvalidArgument);
}

TEST_F(MeasureLoudnessOrFallbackToUserLoudnessMixPresentationFinalizerTest,
       CopiesAnchoredLoudness) {
  // Omit unused user metadata.
  ASSERT_TRUE(google::protobuf::TextFormat::ParseFromString(
      R"pb(
        num_sub_mixes: 1
        sub_mixes {
          num_layouts: 1
          layouts {
            loudness {
              info_type_bit_masks: [ LOUDNESS_INFO_TYPE_ANCHORED_LOUDNESS ]
              integrated_loudness: 99
              digital_peak: 100
              anchored_loudness {
                num_anchored_loudness: 2
                anchor_elements:
                [ {
                  anchor_element: ANCHOR_TYPE_DIALOGUE
                  anchored_loudness: 1000
                }
                  , {
                    anchor_element: ANCHOR_TYPE_DIALOGUE
                    anchored_loudness: 1001
                  }]
              }
            }
          }
        }
      )pb",
      mix_presentation_metadata_.Add()));

  // `info_type` must be configured as a prerequisite.
  obus_to_finalize_.front().sub_mixes_[0].layouts[0].loudness.info_type =
      LoudnessInfo::kAnchoredLoudness;

  expected_obus_.front().sub_mixes_[0].layouts[0].loudness = {
      .info_type = LoudnessInfo::kAnchoredLoudness,
      .integrated_loudness = 99,
      .digital_peak = 100,
      .anchored_loudness{
          .num_anchored_loudness = 2,
          .anchor_elements = {
              {.anchor_element =
                   AnchoredLoudnessElement::kAnchorElementDialogue,
               .anchored_loudness = 1000},
              {.anchor_element =
                   AnchoredLoudnessElement::kAnchorElementDialogue,
               .anchored_loudness = 1001}}}};

  InitAndTestGenerate();
}

TEST_F(MeasureLoudnessOrFallbackToUserLoudnessMixPresentationFinalizerTest,
       CopiesExtensionLoudness) {
  // Omit unused user metadata.
  ASSERT_TRUE(google::protobuf::TextFormat::ParseFromString(
      R"pb(
        num_sub_mixes: 1
        sub_mixes {
          num_layouts: 1
          layouts {
            loudness {
              # Using all reserved loudness types.
              info_type_bit_masks: [
                LOUDNESS_INFO_TYPE_RESERVED_4,
                LOUDNESS_INFO_TYPE_RESERVED_8,
                LOUDNESS_INFO_TYPE_RESERVED_16,
                LOUDNESS_INFO_TYPE_RESERVED_32,
                LOUDNESS_INFO_TYPE_RESERVED_64,
                LOUDNESS_INFO_TYPE_RESERVED_128
              ]
              integrated_loudness: 99
              digital_peak: 100
              info_type_size: 1
              info_type_bytes: "a"
            }
          }
        }
      )pb",
      mix_presentation_metadata_.Add()));

  // `info_type` must be configured as a prerequisite.
  obus_to_finalize_.front().sub_mixes_[0].layouts[0].loudness.info_type =
      LoudnessInfo::kAnyLayoutExtension;

  expected_obus_.front().sub_mixes_[0].layouts[0].loudness = {
      .info_type = LoudnessInfo::kAnyLayoutExtension,
      .integrated_loudness = 99,
      .digital_peak = 100,
      .layout_extension = {.info_type_size = 1, .info_type_bytes = {'a'}}};

  InitAndTestGenerate();
}

TEST_F(MeasureLoudnessOrFallbackToUserLoudnessMixPresentationFinalizerTest,
       CopiesMultipleObus) {
  expected_obus_.clear();
  obus_to_finalize_.clear();

  // Initialize two user OBUs and the corresponding OBUs.
  for (int i = 0; i < 2; i++) {
    ASSERT_TRUE(google::protobuf::TextFormat::ParseFromString(
        R"pb(
          num_sub_mixes: 1
          sub_mixes {
            num_layouts: 1
            layouts {
              loudness {
                info_type_bit_masks: []
                integrated_loudness: 99
                digital_peak: 100
              }
            }
          }
        )pb",
        mix_presentation_metadata_.Add()));

    AddMixPresentationObuWithAudioElementIds(
        /*mix_presentation_id=*/42, /*audio_element_id=*/300,
        /*common_parameter_id=*/999,
        /*common_parameter_rate=*/16000, obus_to_finalize_);

    // Expect the OBUs will have the loudness configured.
    AddMixPresentationObuWithAudioElementIds(
        /*mix_presentation_id=*/42, /*audio_element_id=*/300,
        /*common_parameter_id=*/999,
        /*common_parameter_rate=*/16000, expected_obus_);
    expected_obus_.back().sub_mixes_[0].layouts[0].loudness = {
        .info_type = 0, .integrated_loudness = 99, .digital_peak = 100};
  }

  InitAndTestGenerate();
}

}  // namespace
}  // namespace iamf_tools
