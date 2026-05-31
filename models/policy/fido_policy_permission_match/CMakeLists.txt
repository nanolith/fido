SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/helpers/config/fido_config_permission_create_random.c
    ${CMAKE_SOURCE_DIR}/models/helpers/user/fido_user_create_random.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/property_fido_config_permission_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/user/property_fido_user_valid.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_permission_create.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_permission_release.c
    ${CMAKE_SOURCE_DIR}/src/policy/fido_policy_permission_match.c
    ${CMAKE_SOURCE_DIR}/src/user/fido_user_release.c
    main.c)

ADD_EXECUTABLE(model_policy_fido_policy_permission_match ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_policy_fido_policy_permission_match PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_policy_fido_policy_permission_match
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_policy_fido_policy_permission_match
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_policy_fido_policy_permission_match
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS}
                 --unwindset fido_user_release.0:4,match_group_permission.0:4,fido_user_create_random.0:4
                 model_policy_fido_policy_permission_match
    USES_TERMINAL)
