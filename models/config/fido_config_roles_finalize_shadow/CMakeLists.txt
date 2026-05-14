SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/helpers/config/fido_config_create_random.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/fido_config_roles_finalize.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/property_fido_config_role_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/property_fido_config_valid.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_add_role.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_create.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_release.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_role_create.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_role_release.c
    main.c)

ADD_EXECUTABLE(
    model_config_fido_config_roles_finalize_shadow ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_config_fido_config_roles_finalize_shadow PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_config_fido_config_roles_finalize_shadow
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_config_fido_config_roles_finalize_shadow
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_config_fido_config_roles_finalize_shadow
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS} model_config_fido_config_roles_finalize_shadow
    USES_TERMINAL)
