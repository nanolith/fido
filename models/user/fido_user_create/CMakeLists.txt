SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/getgid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/getgrgid_r.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/getgroups.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/getpwuid_r.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/getuid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/unix/sysconf.c
    ${CMAKE_SOURCE_DIR}/models/shadow/user/property_fido_user_valid.c
    ${CMAKE_SOURCE_DIR}/src/user/fido_user_create.c
    ${CMAKE_SOURCE_DIR}/src/user/fido_user_release.c
    main.c)

ADD_EXECUTABLE(model_user_fido_user_create ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_user_fido_user_create PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_user_fido_user_create
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_user_fido_user_create
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_user_fido_user_create
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS}
                 --unwindset fido_user_release.0:5,fido_user_create.0:5,fido_user_create.1:5
                 model_user_fido_user_create
    USES_TERMINAL)
