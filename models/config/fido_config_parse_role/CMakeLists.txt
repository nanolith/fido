SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/shadow/config/fido_scanner_peek_token.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/fido_scanner_read_token.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/fido_config_parse_role_as_clause_shadow_sink.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/fido_config_parse_role_command_shadow_sink.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/fido_config_parse_role_permission_shadow_sink.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/fido_config_parse_role_variable_shadow_sink.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/fido_config_role_permissions_finalize.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/property_fido_config_role_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/property_fido_scanner_valid.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_parse_role.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_role_as_group_set.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_role_as_user_set.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_role_create.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_role_release.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_scanner_create.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_scanner_next_character.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_scanner_release.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_scanner_token_details_begin.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_scanner_token_details_end.c
    main.c)

ADD_EXECUTABLE(
    model_config_fido_config_parse_role ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_config_fido_config_parse_role PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_config_fido_config_parse_role
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_config_fido_config_parse_role
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_config_fido_config_parse_role
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS}
                 --unwindset fido_config_parse_role.0:6
                 model_config_fido_config_parse_role
    USES_TERMINAL)
