/**
 * \file fido/function_contracts.h
 *
 * \brief Function contract macros for handling preconditions, postconditions,
 * and model checks.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <fido/macro_tricks.h>

/**
 * \brief Begin a contract helper section.
 */
#define BEGIN_CONTRACT_HELPER \
    _Pragma("GCC diagnostic push") \
    _Pragma("GCC diagnostic ignored \"-Wunused-parameter\"")

/**
 * \brief End a contract helper section.
 */
#define END_CONTRACT_HELPER \
    _Pragma("GCC diagnostic pop")

/**
 * \brief Expansion of the begin preconditions variadic macro.
 */
#define MODEL_CONTRACT_PRECONDITIONS_BEGIN1(function, ...) \
    BEGIN_CONTRACT_HELPER \
    inline void fido_model_check_ ## function ## _preconditions(__VA_ARGS__) {

/**
 * \brief Variadic macro describing function contract preconditions.
 */
#define MODEL_CONTRACT_PRECONDITIONS_BEGIN(function, ...) \
    MODEL_CONTRACT_PRECONDITIONS_BEGIN1(function, __VA_ARGS__)

/**
 * \brief End of function contract preconditions.
 */
#define MODEL_CONTRACT_PRECONDITIONS_END(function) \
    } \
    END_CONTRACT_HELPER

/**
 * \brief Expansion of the begin postconditions variadic macro.
 */
#define MODEL_CONTRACT_POSTCONDITIONS_BEGIN1(function, ...) \
    BEGIN_CONTRACT_HELPER \
    inline void fido_model_check_ ## function ## _postconditions(__VA_ARGS__) {

/**
 * \brief Variadic macro describing function contract postconditions.
 */
#define MODEL_CONTRACT_POSTCONDITIONS_BEGIN(function, ...) \
    MODEL_CONTRACT_POSTCONDITIONS_BEGIN1(function, __VA_ARGS__)

/**
 * \brief End of function contract postconditions.
 */
#define MODEL_CONTRACT_POSTCONDITIONS_END(function) \
    } \
    END_CONTRACT_HELPER

#ifdef CBMC
# define MODEL_CONTRACT_CHECK_PRECONDITIONS1(function, ...) \
    fido_model_check_ ## function ## _preconditions(__VA_ARGS__)
# define MODEL_CONTRACT_CHECK_PRECONDITIONS(function, ...) \
    MODEL_CONTRACT_CHECK_PRECONDITIONS1(function, __VA_ARGS__)
# define MODEL_CONTRACT_CHECK_POSTCONDITIONS1(function, ...) \
    fido_model_check_ ## function ## _postconditions(__VA_ARGS__)
# define MODEL_CONTRACT_CHECK_POSTCONDITIONS(function, ...) \
    MODEL_CONTRACT_CHECK_POSTCONDITIONS1(function, __VA_ARGS__)
#else
# define MODEL_CONTRACT_CHECK_PRECONDITIONS(function, ...) \
    ; \
    REQUIRE_SEMICOLON_HERE
# define MODEL_CONTRACT_CHECK_POSTCONDITIONS(function, ...) \
    ; \
    REQUIRE_SEMICOLON_HERE
#endif
