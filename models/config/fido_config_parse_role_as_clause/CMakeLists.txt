SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/helpers/config/fido_config_role_create_random.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/fido_config_parse_as.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/property_fido_scanner_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/property_fido_config_role_valid.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_parse_role_as_clause.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_role_create.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_role_as_group_set.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_role_as_user_set.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_role_release.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_scanner_create.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_scanner_release.c
    main.c)

ADD_EXECUTABLE(
    model_config_fido_config_parse_role_as_clause ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_config_fido_config_parse_role_as_clause PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_config_fido_config_parse_role_as_clause
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_config_fido_config_parse_role_as_clause
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_config_fido_config_parse_role_as_clause
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS}
                 --unwindset fido_config_role_release.0:1,fido_config_role_release.1:1,fido_config_role_release.2:1,property_fido_config_role_valid.0:1,property_fido_config_role_valid.1:1,property_fido_config_role_valid.2:1
                 model_config_fido_config_parse_role_as_clause
    USES_TERMINAL)
