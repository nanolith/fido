SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/helpers/config/fido_config_role_create_random.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/property_fido_config_role_valid.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_role_create.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_role_create_empty.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_role_release.c
    main.c)

ADD_EXECUTABLE(model_config_fido_config_role_create_empty_release ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_config_fido_config_role_create_empty_release PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_config_fido_config_role_create_empty_release
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_config_fido_config_role_create_empty_release
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_config_fido_config_role_create_empty_release
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS}
                 --unwindset fido_config_role_release.0:1,fido_config_role_release.1:1,fido_config_role_release.2:1,property_fido_config_role_valid.0:1,property_fido_config_role_valid.1:1,property_fido_config_role_valid.2:1
                 model_config_fido_config_role_create_empty_release
    USES_TERMINAL)
