SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/helpers/config/fido_config_role_create_random.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/property_fido_config_role_valid.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_role_create.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_role_as_user_set.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_role_release.c
    main.c)

ADD_EXECUTABLE(model_config_fido_config_role_as_user_set ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_config_fido_config_role_as_user_set PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_config_fido_config_role_as_user_set
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_config_fido_config_role_as_user_set
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_config_fido_config_role_as_user_set
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS}
                 model_config_fido_config_role_as_user_set
    USES_TERMINAL)
