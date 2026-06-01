SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/helpers/config/fido_config_add_variable_create_random.c
    ${CMAKE_SOURCE_DIR}/models/helpers/options/fido_options_create_random.c
    ${CMAKE_SOURCE_DIR}/models/helpers/policy_proc/fido_policy_decision_create_random.c
    ${CMAKE_SOURCE_DIR}/models/shadow/config/property_fido_config_add_variable_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/options/property_fido_options_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/policy_proc/fido_policy_decision_parse_from_proc.c
    ${CMAKE_SOURCE_DIR}/models/shadow/policy_proc/property_fido_policy_decision_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/unix_init.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_add_variable_create.c
    ${CMAKE_SOURCE_DIR}/src/config/fido_config_add_variable_release.c
    ${CMAKE_SOURCE_DIR}/src/options/fido_options_release.c
    ${CMAKE_SOURCE_DIR}/src/policy_proc/fido_policy_decision_release.c
    main.c)

ADD_EXECUTABLE(
    model_policy_proc_fido_policy_decision_parse_from_proc_shadow ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_policy_proc_fido_policy_decision_parse_from_proc_shadow PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_policy_proc_fido_policy_decision_parse_from_proc_shadow
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_policy_proc_fido_policy_decision_parse_from_proc_shadow
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_policy_proc_fido_policy_decision_parse_from_proc_shadow
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS}
                 --unwindset fido_policy_decision_release.0:3,property_fido_policy_decision_valid.0:3,fido_policy_decision_create_random.0:3
                 model_policy_proc_fido_policy_decision_parse_from_proc_shadow
    USES_TERMINAL)
