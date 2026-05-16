SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/helpers/config/fido_config_command_create_random.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/fido_config_command_arguments_finalize.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/property_fido_config_command_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/property_fido_config_command_argument_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/string/strsep.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_command_add_argument.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_command_argument_create.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_command_argument_release.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_command_create.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_command_release.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_parse_command_arguments.c
    main.c)

ADD_EXECUTABLE(
    model_config_fido_config_parse_command_arguments ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_config_fido_config_parse_command_arguments PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_config_fido_config_parse_command_arguments
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_config_fido_config_parse_command_arguments
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_config_fido_config_parse_command_arguments
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS}
                 --unwindset fido_config_parse_command_arguments.0:4
                 model_config_fido_config_parse_command_arguments
    USES_TERMINAL)
