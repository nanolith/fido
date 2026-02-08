/**
 * \file fido/scanner.h
 *
 * \brief Scanner for fido.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <fido/function_contracts.h>
#include <fido/function_decl.h>
#include <stdbool.h>
#include <stddef.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief Token types.
 */
enum fido_scanner_token_type
{
    /** \brief Role keyword. */
    FIDO_SCANNER_TOKEN_TYPE_KEYWORD_ROLE = 1,
    /** \brief Command keyword. */
    FIDO_SCANNER_TOKEN_TYPE_KEYWORD_CMD,
    /** \brief As keyword. */
    FIDO_SCANNER_TOKEN_TYPE_KEYWORD_AS,
    /** \brief Environment keyword. */
    FIDO_SCANNER_TOKEN_TYPE_KEYWORD_ENV,
    /** \brief Permit keyword. */
    FIDO_SCANNER_TOKEN_TYPE_KEYWORD_PERMIT,
    /** \brief Deny keyword. */
    FIDO_SCANNER_TOKEN_TYPE_KEYWORD_DENY,
    /** \brief Open brace. */
    FIDO_SCANNER_TOKEN_TYPE_OPEN_BRACE,
    /** \brief Close brace. */
    FIDO_SCANNER_TOKEN_TYPE_CLOSE_BRACE,
    /** \brief String. */
    FIDO_SCANNER_TOKEN_TYPE_STRING,
    /** \brief Add environment variable. */
    FIDO_SCANNER_TOKEN_TYPE_ADD_VARIABLE,
    /** \brief Username. */
    FIDO_SCANNER_TOKEN_TYPE_USERNAME,
    /** \brief Group. */
    FIDO_SCANNER_TOKEN_TYPE_GROUP,
};

/**
 * \brief Token details.
 */
typedef struct fido_token_details fido_token_details;
struct fido_token_details
{
    int type;
    size_t begin_index;
    size_t end_index;
    size_t begin_line;
    size_t end_line;
    size_t begin_col;
    size_t end_col;
};

/**
 * \brief fido_scanner implementation.
 */
typedef struct fido_scanner fido_scanner;
struct fido_scanner
{
    const char* input;
    size_t index;
    size_t line;
    size_t col;
};

/******************************************************************************/
/* Start of model checking properties.                                        */
/******************************************************************************/

/**
 * \brief Valid scanner property.
 *
 * \param alloc         The scanner instance to be verified.
 *
 * \returns true if the scanner instance is valid.
 */
bool
property_fido_scanner_valid(
    const fido_scanner* scanner);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Create a \ref fido_scanner instance.
 *
 * \param scanner           Pointer to the scanner pointer to be set to this
 *                          created scanner instance on success.
 * \param input             The input string to scan.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
fido_scanner_create(fido_scanner** scanner, const char* input);

/**
 * \brief Release a \ref fido_scanner instance.
 *
 * \param scanner           The scanner to release.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
fido_scanner_release(fido_scanner* scanner);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
