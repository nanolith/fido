SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/helpers/options/fido_options_create_random.c
    ${CMAKE_SOURCE_DIR}/models/shadow/options/property_fido_options_valid.c
    ${CMAKE_SOURCE_DIR}/src/options/fido_options_release.c
    main.c)

ADD_EXECUTABLE(model_options_fido_options_release ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_options_fido_options_release PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_options_fido_options_release
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_options_fido_options_release
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_options_fido_options_release
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS}
                 #--unwindset
                 model_options_fido_options_release
    USES_TERMINAL)
