SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/shadow/config/fido_scanner_read_token.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/property_fido_scanner_valid.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_parse_as.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_scanner_create.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_scanner_next_character.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_scanner_release.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_scanner_token_details_begin.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_scanner_token_details_end.c
    main.c)

ADD_EXECUTABLE(
    model_config_fido_config_parse_as ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_config_fido_config_parse_as PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_config_fido_config_parse_as
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_config_fido_config_parse_as
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_config_fido_config_parse_as
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS}
                 #--unwindset
                 model_config_fido_config_parse_as
    USES_TERMINAL)
