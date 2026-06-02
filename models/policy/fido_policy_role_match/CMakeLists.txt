SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/helpers/config/fido_config_command_create_random.c
    ${CMAKE_SOURCE_DIR}/models/helpers/config/fido_config_permission_create_random.c
    ${CMAKE_SOURCE_DIR}/models/helpers/config/fido_config_role_create_random.c
    ${CMAKE_SOURCE_DIR}/models/helpers/options/fido_options_create_random.c
    ${CMAKE_SOURCE_DIR}/models/helpers/user/fido_user_create_random.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/property_fido_config_command_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/property_fido_config_role_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/property_fido_config_permission_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/options/property_fido_options_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/policy/fido_policy_command_match.c
    ${CMAKE_SOURCE_DIR}/models/shadow/policy/fido_policy_permission_match.c
    ${CMAKE_SOURCE_DIR}/models/shadow/user/property_fido_user_valid.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_command_create.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_command_release.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_permission_create.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_permission_release.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_role_add_command.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_role_add_permission.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_role_create.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_role_release.c
    ${CMAKE_SOURCE_DIR}/src/options/fido_options_release.c
    ${CMAKE_SOURCE_DIR}/src/policy/fido_policy_role_match.c
    ${CMAKE_SOURCE_DIR}/src/user/fido_user_release.c
    main.c)

ADD_EXECUTABLE(model_policy_fido_policy_role_match ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_policy_fido_policy_role_match PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_policy_fido_policy_role_match
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_policy_fido_policy_role_match
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_policy_fido_policy_role_match
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS}
                --unwindset main.0:4,fido_user_release.0:4,role_permission_match.0:4,match_group_by_name.0:4,role_command_match.0:4,fido_config_role_release.0:3,fido_config_role_release.1:1,fido_config_role_release.2:3,fido_config_command_release.0:1,property_fido_config_role_valid.0:4,property_fido_config_role_valid.1:4,property_fido_config_role_valid.2:4,property_fido_config_command_valid.0:1,fido_user_create_random.0:4
                model_policy_fido_policy_role_match
    USES_TERMINAL)
