package(default_visibility = ["//iamf/cli/tests:__subpackages__"])

cc_test(
    name = "channel_label_test",
    srcs = ["channel_label_test.cc"],
    deps = [
        "//iamf/cli:channel_label",
        "//iamf/cli/proto:obu_header_cc_proto",
        "//iamf/cli/proto:parameter_data_cc_proto",
        "//iamf/cli/proto:temporal_delimiter_cc_proto",
        "//iamf/cli/proto:user_metadata_cc_proto",
        "//iamf/obu:audio_element",
        "@com_google_absl//absl/container:flat_hash_set",
        "@com_google_absl//absl/status:status_matchers",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_library(
    name = "cli_test_utils",
    testonly = True,
    srcs = ["cli_test_utils.cc"],
    hdrs = ["cli_test_utils.h"],
    visibility = [
        "//iamf:__subpackages__",
    ],
    deps = [
        "//iamf/cli:audio_element_with_data",
        "//iamf/cli:wav_reader",
        "//iamf/cli/proto_to_obu:audio_element_generator",
        "//iamf/obu:audio_element",
        "//iamf/obu:codec_config",
        "//iamf/obu:demixing_info_param_data",
        "//iamf/obu:leb128",
        "//iamf/obu:mix_presentation",
        "//iamf/obu:obu_header",
        "//iamf/obu:param_definitions",
        "//iamf/obu/decoder_config:aac_decoder_config",
        "//iamf/obu/decoder_config:lpcm_decoder_config",
        "//iamf/obu/decoder_config:opus_decoder_config",
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/status:status_matchers",
        "@com_google_absl//absl/strings",
        "@com_google_googletest//:gtest",
    ],
)

cc_test(
    name = "audio_frame_decoder_test",
    srcs = ["audio_frame_decoder_test.cc"],
    deps = [
        ":cli_test_utils",
        "//iamf/cli:audio_element_with_data",
        "//iamf/cli:audio_frame_decoder",
        "//iamf/cli:audio_frame_with_data",
        "//iamf/cli:channel_label",
        "//iamf/obu:audio_frame",
        "//iamf/obu:codec_config",
        "//iamf/obu:demixing_info_param_data",
        "//iamf/obu:leb128",
        "//iamf/obu:obu_header",
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/status:status_matchers",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "cli_util_test",
    size = "small",
    srcs = ["cli_util_test.cc"],
    deps = [
        ":cli_test_utils",
        "//iamf/cli:audio_element_with_data",
        "//iamf/cli:audio_frame_with_data",
        "//iamf/cli:cli_util",
        "//iamf/cli/proto:obu_header_cc_proto",
        "//iamf/cli/proto:parameter_data_cc_proto",
        "//iamf/cli/proto:temporal_delimiter_cc_proto",
        "//iamf/cli/proto:user_metadata_cc_proto",
        "//iamf/cli/proto_to_obu:audio_element_generator",
        "//iamf/obu:audio_element",
        "//iamf/obu:audio_frame",
        "//iamf/obu:codec_config",
        "//iamf/obu:demixing_info_param_data",
        "//iamf/obu:ia_sequence_header",
        "//iamf/obu:leb128",
        "//iamf/obu:mix_presentation",
        "//iamf/obu:obu_header",
        "//iamf/obu:param_definitions",
        "//iamf/obu:parameter_block",
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/container:flat_hash_set",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:status_matchers",
        "@com_google_googletest//:gtest_main",
        "@com_google_protobuf//:protobuf",
    ],
)

cc_test(
    name = "demixing_module_test",
    srcs = ["demixing_module_test.cc"],
    deps = [
        ":cli_test_utils",
        "//iamf/cli:audio_element_with_data",
        "//iamf/cli:audio_frame_decoder",
        "//iamf/cli:audio_frame_with_data",
        "//iamf/cli:channel_label",
        "//iamf/cli:demixing_module",
        "//iamf/cli/proto:user_metadata_cc_proto",
        "//iamf/obu:audio_element",
        "//iamf/obu:audio_frame",
        "//iamf/obu:codec_config",
        "//iamf/obu:demixing_info_param_data",
        "//iamf/obu:leb128",
        "//iamf/obu:obu_header",
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:status_matchers",
        "@com_google_absl//absl/strings:string_view",
        "@com_google_googletest//:gtest_main",
        "@com_google_protobuf//:protobuf",
    ],
)

cc_test(
    name = "encoder_main_lib_test",
    srcs = ["encoder_main_lib_test.cc"],
    deps = [
        "//iamf/cli:encoder_main_lib",
        "//iamf/cli/proto:codec_config_cc_proto",
        "//iamf/cli/proto:ia_sequence_header_cc_proto",
        "//iamf/cli/proto:test_vector_metadata_cc_proto",
        "//iamf/cli/proto:user_metadata_cc_proto",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:status_matchers",
        "@com_google_googletest//:gtest_main",
        "@com_google_protobuf//:protobuf",
    ],
)

cc_test(
    name = "global_timing_module_test",
    srcs = ["global_timing_module_test.cc"],
    deps = [
        ":cli_test_utils",
        "//iamf/cli:audio_element_with_data",
        "//iamf/cli:global_timing_module",
        "//iamf/cli/proto:parameter_block_cc_proto",
        "//iamf/cli/proto:user_metadata_cc_proto",
        "//iamf/obu:codec_config",
        "//iamf/obu:leb128",
        "//iamf/obu:param_definitions",
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:status_matchers",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "iamf_components_test",
    srcs = ["iamf_components_test.cc"],
    deps = [
        "//iamf/cli:iamf_components",
        "//iamf/cli/proto:test_vector_metadata_cc_proto",
        "//iamf/cli/proto:user_metadata_cc_proto",
        "@com_google_googletest//:gtest_main",
        "@com_google_protobuf//:protobuf",
    ],
)

cc_test(
    name = "iamf_encoder_test",
    srcs = ["iamf_encoder_test.cc"],
    deps = [
        "//iamf/cli:audio_element_with_data",
        "//iamf/cli:audio_frame_with_data",
        "//iamf/cli:channel_label",
        "//iamf/cli:demixing_module",
        "//iamf/cli:iamf_encoder",
        "//iamf/cli:parameter_block_with_data",
        "//iamf/cli/proto:audio_element_cc_proto",
        "//iamf/cli/proto:codec_config_cc_proto",
        "//iamf/cli/proto:ia_sequence_header_cc_proto",
        "//iamf/cli/proto:mix_presentation_cc_proto",
        "//iamf/cli/proto:test_vector_metadata_cc_proto",
        "//iamf/cli/proto:user_metadata_cc_proto",
        "//iamf/obu:codec_config",
        "//iamf/obu:ia_sequence_header",
        "//iamf/obu:leb128",
        "//iamf/obu:mix_presentation",
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/log",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:status_matchers",
        "@com_google_googletest//:gtest_main",
        "@com_google_protobuf//:protobuf",
    ],
)

cc_test(
    name = "leb_generator_test",
    srcs = ["leb_generator_test.cc"],
    deps = [
        "//iamf/cli:leb_generator",
        "//iamf/cli/proto:test_vector_metadata_cc_proto",
        "//iamf/cli/proto:user_metadata_cc_proto",
        "//iamf/obu:leb128",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:status_matchers",
        "@com_google_googletest//:gtest_main",
        "@com_google_protobuf//:protobuf",
    ],
)

cc_test(
    name = "loudness_calculator_factory_test",
    srcs = ["loudness_calculator_factory_test.cc"],
    deps = [
        "//iamf/cli:loudness_calculator_factory",
        "//iamf/cli/proto:obu_header_cc_proto",
        "//iamf/cli/proto:parameter_data_cc_proto",
        "//iamf/cli/proto:temporal_delimiter_cc_proto",
        "//iamf/cli/proto:user_metadata_cc_proto",
        "//iamf/obu:mix_presentation",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "loudness_calculator_test",
    srcs = ["loudness_calculator_test.cc"],
    deps = [
        "//iamf/cli:loudness_calculator",
        "//iamf/obu:mix_presentation",
        "@com_google_absl//absl/status:status_matchers",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "mix_presentation_finalizer_test",
    srcs = ["mix_presentation_finalizer_test.cc"],
    deps = [
        ":cli_test_utils",
        "//iamf/cli:mix_presentation_finalizer",
        "//iamf/cli:wav_writer",
        "//iamf/obu:leb128",
        "//iamf/obu:mix_presentation",
        "@com_google_absl//absl/status:status_matchers",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "obu_sequencer_test",
    srcs = ["obu_sequencer_test.cc"],
    deps = [
        ":cli_test_utils",
        "//iamf/cli:audio_element_with_data",
        "//iamf/cli:audio_frame_with_data",
        "//iamf/cli:obu_sequencer",
        "//iamf/cli:parameter_block_with_data",
        "//iamf/common:write_bit_buffer",
        "//iamf/obu:arbitrary_obu",
        "//iamf/obu:audio_frame",
        "//iamf/obu:codec_config",
        "//iamf/obu:demixing_info_param_data",
        "//iamf/obu:ia_sequence_header",
        "//iamf/obu:leb128",
        "//iamf/obu:mix_presentation",
        "//iamf/obu:obu_base",
        "//iamf/obu:obu_header",
        "//iamf/obu:param_definitions",
        "//iamf/obu:parameter_block",
        "//iamf/obu:temporal_delimiter",
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/status:status_matchers",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "parameter_block_partitioner_test",
    size = "small",
    srcs = ["parameter_block_partitioner_test.cc"],
    deps = [
        "//iamf/cli:parameter_block_partitioner",
        "//iamf/cli/proto:parameter_block_cc_proto",
        "//iamf/cli/proto:parameter_data_cc_proto",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:status_matchers",
        "@com_google_googletest//:gtest_main",
        "@com_google_protobuf//:protobuf",
    ],
)

cc_test(
    name = "parameters_manager_test",
    size = "small",
    srcs = ["parameters_manager_test.cc"],
    deps = [
        ":cli_test_utils",
        "//iamf/cli:audio_element_with_data",
        "//iamf/cli:parameter_block_with_data",
        "//iamf/cli:parameters_manager",
        "//iamf/obu:audio_element",
        "//iamf/obu:codec_config",
        "//iamf/obu:demixing_info_param_data",
        "//iamf/obu:leb128",
        "//iamf/obu:obu_header",
        "//iamf/obu:param_definitions",
        "//iamf/obu:parameter_block",
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:status_matchers",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "profile_filter_test",
    srcs = ["profile_filter_test.cc"],
    deps = [
        ":cli_test_utils",
        "//iamf/cli:audio_element_with_data",
        "//iamf/cli:profile_filter",
        "//iamf/cli/proto:ia_sequence_header_cc_proto",
        "//iamf/cli/proto:obu_header_cc_proto",
        "//iamf/cli/proto:user_metadata_cc_proto",
        "//iamf/obu:audio_element",
        "//iamf/obu:codec_config",
        "//iamf/obu:ia_sequence_header",
        "//iamf/obu:leb128",
        "//iamf/obu:mix_presentation",
        "//iamf/obu:obu_header",
        "//iamf/obu:param_definitions",
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/container:flat_hash_set",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:status_matchers",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "recon_gain_generator_test",
    srcs = ["recon_gain_generator_test.cc"],
    deps = [
        "//iamf/cli:channel_label",
        "//iamf/cli:demixing_module",
        "//iamf/cli:recon_gain_generator",
        "//iamf/cli/proto:user_metadata_cc_proto",
        "@com_google_absl//absl/status:status_matchers",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "renderer_factory_test",
    srcs = ["renderer_factory_test.cc"],
    deps = [
        "//iamf/cli:channel_label",
        "//iamf/cli:renderer_factory",
        "//iamf/cli/proto:obu_header_cc_proto",
        "//iamf/cli/proto:parameter_data_cc_proto",
        "//iamf/cli/proto:temporal_delimiter_cc_proto",
        "//iamf/cli/proto:user_metadata_cc_proto",
        "//iamf/obu:audio_element",
        "//iamf/obu:mix_presentation",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "wav_reader_test",
    srcs = ["wav_reader_test.cc"],
    data = [
        "//iamf/cli/testdata:input_wav_files",
    ],
    deps = [
        ":cli_test_utils",
        "//iamf/cli:wav_reader",
        "@com_google_absl//absl/status:status_matchers",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "wav_sample_provider_test",
    srcs = ["wav_sample_provider_test.cc"],
    data = [
        "//iamf/cli/testdata:input_wav_files",
    ],
    deps = [
        ":cli_test_utils",
        "//iamf/cli:audio_element_with_data",
        "//iamf/cli:channel_label",
        "//iamf/cli:demixing_module",
        "//iamf/cli:wav_sample_provider",
        "//iamf/cli/proto:user_metadata_cc_proto",
        "//iamf/obu:codec_config",
        "//iamf/obu:leb128",
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/status:status_matchers",
        "@com_google_absl//absl/strings:string_view",
        "@com_google_googletest//:gtest_main",
        "@com_google_protobuf//:protobuf",
    ],
)

cc_test(
    name = "wav_writer_test",
    srcs = ["wav_writer_test.cc"],
    deps = [
        ":cli_test_utils",
        "//iamf/cli:wav_reader",
        "//iamf/cli:wav_writer",
        "@com_google_googletest//:gtest_main",
    ],
)
