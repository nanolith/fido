SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/helpers/options/fido_options_create_random.c
    ${CMAKE_SOURCE_DIR}/models/helpers/user/fido_user_create_random.c
    ${CMAKE_SOURCE_DIR}/models/shadow/options/property_fido_options_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/policy/fido_policy_check_from_descriptor.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/close.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/open.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/property_file_descriptor_open.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/unix_init.c
    ${CMAKE_SOURCE_DIR}/models/shadow/user/property_fido_user_valid.c
    ${CMAKE_SOURCE_DIR}/src/options/fido_options_release.c
    ${CMAKE_SOURCE_DIR}/src/user/fido_user_release.c
    main.c)

ADD_EXECUTABLE(
    model_policy_fido_policy_check_from_descriptor_shadow ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_policy_fido_policy_check_from_descriptor_shadow PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_policy_fido_policy_check_from_descriptor_shadow
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_policy_fido_policy_check_from_descriptor_shadow
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_policy_fido_policy_check_from_descriptor_shadow
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS}
                 --unwindset fido_user_release.0:4,fido_user_create_random.0:4
                 model_policy_fido_policy_check_from_descriptor_shadow
    USES_TERMINAL)
