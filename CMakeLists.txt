cmake_minimum_required(VERSION 3.22)
cmake_policy(SET CMP0048 NEW)
PROJECT(fido VERSION 0.0.1 LANGUAGES C CXX)

INCLUDE(CheckSymbolExists)

option(MODEL_CHECKING_ENABLED "Enable Model Checking")

#pkgconfig
find_package(PkgConfig REQUIRED)
#minunit package
pkg_search_module(minunit REQUIRED IMPORTED_TARGET minunit)

#chooser helpers
SET(COMPILER_CHOOSER ${CMAKE_SOURCE_DIR}/scripts/compiler-chooser.sh)
SET(LINKER_CHOOSER ${CMAKE_SOURCE_DIR}/scripts/linker-chooser.sh)

#source files
file(GLOB_RECURSE FIDO_SOURCES src/*.c)
list(FILTER FIDO_SOURCES EXCLUDE REGEX ".*/main[.]c")
file(GLOB FIDO_SOURCES_MAIN src/fido/main.c)

#test files
file(GLOB_RECURSE FIDO_TEST_SOURCES test/*.cpp)

include_directories(include)
include_directories(${CMAKE_BINARY_DIR}/include)

ADD_EXECUTABLE(fido ${FIDO_SOURCES} ${FIDO_SOURCES_MAIN})
TARGET_COMPILE_OPTIONS(
    fido PRIVATE -fPIC -O2
    -Wall -Werror -Wextra -Wpedantic)
TARGET_LINK_LIBRARIES(fido -static)

ADD_EXECUTABLE(testfido
    ${FIDO_SOURCES} ${FIDO_TEST_SOURCES})
TARGET_COMPILE_OPTIONS(
    testfido PRIVATE -g -O0 --coverage ${minunit_CFLAGS}
                       -Wall -Werror -Wextra -Wpedantic)
TARGET_LINK_OPTIONS(testfido PRIVATE --coverage)
TARGET_LINK_LIBRARIES(
    testfido PRIVATE -g -O0 --coverage PkgConfig::minunit)
SET_SOURCE_FILES_PROPERTIES(
    ${FIDO_TEST_SOURCES} PROPERTIES
    COMPILE_FLAGS "${STD_CXX_20}")

ADD_CUSTOM_TARGET(
    test
    COMMAND testfido
    DEPENDS testfido
    USES_TERMINAL)

#model checks
if (MODEL_CHECKING_ENABLED)
    ADD_SUBDIRECTORY(models)
endif ()
