SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/helpers/config/fido_config_command_argument_create_random.c
    ${CMAKE_SOURCE_DIR}/models/shadow/policy/fido_policy_command_argument_match.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/property_fido_config_command_argument_valid.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_command_argument_create.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_command_argument_release.c
    main.c)

ADD_EXECUTABLE(
    model_policy_fido_policy_command_argument_match_shadow ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_policy_fido_policy_command_argument_match_shadow PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_policy_fido_policy_command_argument_match_shadow
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_policy_fido_policy_command_argument_match_shadow
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_policy_fido_policy_command_argument_match_shadow
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS}
                 #--unwindset
                 model_policy_fido_policy_command_argument_match_shadow
    USES_TERMINAL)
