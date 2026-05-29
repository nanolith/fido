SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/helpers/config/fido_config_create_random.c
    ${CMAKE_SOURCE_DIR}/models/helpers/options/fido_options_create_random.c
    ${CMAKE_SOURCE_DIR}/models/helpers/user/fido_user_create_random.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/fido_config_parse.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/property_fido_config_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/options/property_fido_options_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/policy/fido_policy_check.c
    ${CMAKE_SOURCE_DIR}/models/shadow/user/property_fido_user_valid.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_create.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_release.c
    ${CMAKE_SOURCE_DIR}/src/options/fido_options_release.c
    ${CMAKE_SOURCE_DIR}/src/policy/fido_policy_check_from_string.c
    ${CMAKE_SOURCE_DIR}/src/user/fido_user_release.c
    main.c)

ADD_EXECUTABLE(model_policy_fido_policy_check_from_string ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_policy_fido_policy_check_from_string PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_policy_fido_policy_check_from_string
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_policy_fido_policy_check_from_string
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_policy_fido_policy_check_from_string
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS}
                 --unwindset fido_config_release.0:1,property_fido_config_valid.0:1,fido_user_release.0:4
                 model_policy_fido_policy_check_from_string
    USES_TERMINAL)
