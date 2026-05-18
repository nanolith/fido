SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/helpers/config/fido_config_add_variable_create_random.c
    ${CMAKE_SOURCE_DIR}/models/helpers/config/fido_config_role_create_random.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/fido_config_parse_add_variable.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/fido_config_role_add_variable_shadow_sink.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/property_fido_config_add_variable_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/property_fido_config_role_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/property_fido_scanner_valid.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_add_variable_create.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_add_variable_release.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_parse_role_variable.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_role_create.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_role_release.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_scanner_create.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_scanner_release.c
    main.c)

ADD_EXECUTABLE(
    model_config_fido_config_parse_role_variable ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_config_fido_config_parse_role_variable PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_config_fido_config_parse_role_variable
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_config_fido_config_parse_role_variable
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_config_fido_config_parse_role_variable
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS} model_config_fido_config_parse_role_variable
    USES_TERMINAL)
