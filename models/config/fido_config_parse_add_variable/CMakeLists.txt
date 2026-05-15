SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/shadow/config/fido_scanner_read_token.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/property_fido_config_add_variable_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/property_fido_scanner_valid.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_add_variable_create.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_add_variable_release.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_parse_add_variable.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_scanner_create.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_scanner_next_character.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_scanner_release.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_scanner_token_details_begin.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_scanner_token_details_end.c
    main.c)

ADD_EXECUTABLE(
    fido_config_parse_add_variable ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    fido_config_parse_add_variable PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    fido_config_parse_add_variable
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET fido_config_parse_add_variable
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET fido_config_parse_add_variable
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS} fido_config_parse_add_variable
    USES_TERMINAL)
