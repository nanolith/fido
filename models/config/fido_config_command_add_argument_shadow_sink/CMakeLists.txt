SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/helpers/config/fido_config_command_argument_create_random.c
    ${CMAKE_SOURCE_DIR}/models/helpers/config/fido_config_command_create_random.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/fido_config_command_add_argument_shadow_sink.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/property_fido_config_command_argument_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/property_fido_config_command_valid.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_command_argument_create.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_command_argument_release.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_command_create.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_command_release.c
    main.c)

ADD_EXECUTABLE(
    model_config_fido_config_command_add_argument_shadow_sink ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_config_fido_config_command_add_argument_shadow_sink PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_config_fido_config_command_add_argument_shadow_sink
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_config_fido_config_command_add_argument_shadow_sink
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_config_fido_config_command_add_argument_shadow_sink
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS}
                 model_config_fido_config_command_add_argument_shadow_sink
    USES_TERMINAL)
