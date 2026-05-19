SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/helpers/config/fido_config_role_create_random.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/fido_config_add_role_shadow_sink.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/fido_config_parse_role_shadow_sink.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/fido_config_roles_finalize.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/fido_scanner_peek_token.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/property_fido_config_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/property_fido_config_role_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/property_fido_scanner_valid.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_create.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_release.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_parse.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_role_create.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_role_release.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_scanner_create.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_scanner_next_character.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_scanner_release.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_scanner_token_details_begin.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_scanner_token_details_end.c
    main.c)

ADD_EXECUTABLE(
    model_config_fido_config_parse ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_config_fido_config_parse PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_config_fido_config_parse
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_config_fido_config_parse
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_config_fido_config_parse
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS}
                 --unwindset fido_config_parse.0:3
                 model_config_fido_config_parse
    USES_TERMINAL)
