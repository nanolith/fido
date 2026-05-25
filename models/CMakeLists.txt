SET(CBMC_OPTIONS
    "--bounds-check" "--pointer-check" "--memory-leak-check"
    "--malloc-may-fail" "--malloc-fail-null" "--div-by-zero-check"
    "--pointer-overflow-check" "--trace" "--stop-on-fail"
    "--drop-unused-functions" "--unwind" "10" "--unwinding-assertions")

#CBMC build options
SET(CBMC_BUILD_OPTIONS "-D_ANSI_LIBRARY -DCBMC -I ${CMAKE_SOURCE_DIR}/models -I ${CMAKE_SOURCE_DIR}/src")

ADD_SUBDIRECTORY(config)
ADD_SUBDIRECTORY(options)
