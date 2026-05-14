SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/helpers/config/fido_config_command_argument_create_random.c
    ${CMAKE_SOURCE_DIR}/models/helpers/config/fido_config_command_create_random.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/property_fido_config_command_argument_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/property_fido_config_command_valid.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_command_argument_create.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_command_argument_release.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_command_arguments_finalize.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_command_add_argument.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_command_create.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_command_release.c
    main.c)

ADD_EXECUTABLE(
    model_config_fido_config_command_aguments_finalize ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_config_fido_config_command_aguments_finalize PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_config_fido_config_command_aguments_finalize
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_config_fido_config_command_aguments_finalize
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_config_fido_config_command_aguments_finalize
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS}
                 model_config_fido_config_command_aguments_finalize
    USES_TERMINAL)
