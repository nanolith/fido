SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/helpers/user/fido_user_create_random.c
    ${CMAKE_SOURCE_DIR}/models/shadow/user/property_fido_user_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/user/fido_user_create.c
    ${CMAKE_SOURCE_DIR}/src/user/fido_user_release.c
    main.c)

ADD_EXECUTABLE(model_user_fido_user_create_shadow ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_user_fido_user_create_shadow PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_user_fido_user_create_shadow
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_user_fido_user_create_shadow
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_user_fido_user_create_shadow
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS} model_user_fido_user_create_shadow
    USES_TERMINAL)
