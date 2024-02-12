/*
 * Copyright (c) 2023, Alliance for Open Media. All rights reserved
 *
 * This source code is subject to the terms of the BSD 3-Clause Clear License
 * and the Alliance for Open Media Patent License 1.0. If the BSD 3-Clause Clear
 * License was not distributed with this source code in the LICENSE file, you
 * can obtain it at www.aomedia.org/license/software-license/bsd-3-c-c. If the
 * Alliance for Open Media Patent License 1.0 was not distributed with this
 * source code in the PATENTS file, you can obtain it at
 * www.aomedia.org/license/patent.
 */
#ifndef OPUS_DECODER_CONFIG_H_
#define OPUS_DECODER_CONFIG_H_

#include <cstdint>

#include "absl/status/status.h"
#include "iamf/write_bit_buffer.h"

namespace iamf_tools {

/*!\brief The `CodecConfig` `decoder_config` field for Opus.*/
class OpusDecoderConfig {
 public:
  static constexpr uint8_t kOutputChannelCount = 2;
  static constexpr int16_t kOutputGain = 0;
  static constexpr uint8_t kMappingFamily = 0;

  friend bool operator==(const OpusDecoderConfig& lhs,
                         const OpusDecoderConfig& rhs) = default;

  /*!\brief Validates and writes the `OpusDecoderConfig` to a buffer.
   *
   * \param num_samples_per_frame `num_samples_per_frame` in the associated
   *     Codec Config OBU.
   * \param audio_roll_distance `audio_roll_distance` in the associated Codec
   *     Config OBU.
   * \param wb Buffer to write to.
   * \return `absl::OkStatus()` if the decoder config is valid. A specific error
   *     code on failure.
   */
  absl::Status ValidateAndWrite(uint32_t num_samples_per_frame,
                                int16_t audio_roll_distance,
                                WriteBitBuffer& wb) const;

  /*\!brief Gets the output sample rate represented within the decoder config.
   *
   * IAMF Spec requires the output to be 48,000 Hz.
   *
   * \return Output sample rate.
   */
  uint32_t GetOutputSampleRate() const { return 48000; }

  /*\!brief Gets the input sample rate represented within the decoder config.
   *
   * Opus explicitly has this value in the Codec Config OBU.
   *
   * \return Input sample rate.
   */
  uint32_t GetInputSampleRate() const { return input_sample_rate_; }

  /*!\brief Gets the bit-depth of the PCM to be used to measure loudness.
   *
   * This typically is the highest bit-depth associated substreams should be
   * decoded to. The encoder provides data to `libopus::opus_encoder_float()` as
   * a `float` in the range [-1, +1].
   *
   * \return Bit-depth of the PCM which will be used to measure loudness if the
   *     OBU was initialized successfully.
   */
  static constexpr uint8_t GetBitDepthToMeasureLoudness() { return 32; }

  /*\!brief Prints logging information about the decoder config.
   */
  void Print() const;

  uint8_t version_;
  // Must be set to 2. This field is ignored.
  uint8_t output_channel_count_ = kOutputChannelCount;
  uint16_t pre_skip_;
  uint32_t input_sample_rate_;
  int16_t output_gain_ = kOutputGain;
  uint8_t mapping_family_ = kMappingFamily;
};

}  // namespace iamf_tools

#endif  // OPUS_DECODER_CONFIG_H_
