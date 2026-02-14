/**
 * \file fido/scanner.h
 *
 * \brief Scanner for fido.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <fido/error_codes.h>
#include <fido/function_contracts.h>
#include <fido/function_decl.h>
#include <fido/model_assert.h>
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

    /** \brief End of input. */
    FIDO_SCANNER_TOKEN_TYPE_EOF = 0xFFFF,

    /** \brief Bad input token. */
    FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT,
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
    const char* original_input;
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
 * \param scanner       The scanner instance to be verified.
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

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_scanner_create, fido_scanner** scanner, const char* input)
        /* the scanner pointer is valid. */
        MODEL_CHECK_OBJECT_RW(scanner, sizeof(*scanner));
        /* the input is not NULL. */
        MODEL_ASSERT(NULL != input);
MODEL_CONTRACT_PRECONDITIONS_END(fido_scanner_create)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_scanner_create, int retval, fido_scanner** scanner, const char* input)
        /* on success... */
        if (0 == retval)
        {
            /* the scanner is valid. */
            MODEL_ASSERT(property_fido_scanner_valid(*scanner));
            /* the index starts at 0. */
            MODEL_ASSERT(0 == (*scanner)->index);
            /* the line starts at 1. */
            MODEL_ASSERT(1 == (*scanner)->line);
            /* the column starts at 1. */
            MODEL_ASSERT(1 == (*scanner)->col);
            /* the input string matches our input. */
            MODEL_ASSERT(input == (*scanner)->input);
            /* the input string matches our original_input. */
            MODEL_ASSERT(input == (*scanner)->original_input);
        }
        else
        {
            /* this is a defined error code. */
            enum fido_error_code error = (enum fido_error_code)retval;
            MODEL_ASSERT(__CPROVER_enum_is_in_range(error));
            /* scanner is set to NULL. */
            MODEL_ASSERT(NULL == *scanner);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_scanner_create)

/**
 * \brief Release a \ref fido_scanner instance.
 *
 * \param scanner           The scanner to release.
 */
void
fido_scanner_release(fido_scanner* scanner);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_scanner_release, fido_scanner* scanner)
        /* the scanner points to a region of memory large enough to hold it. */
        MODEL_CHECK_OBJECT_RW(scanner, sizeof(*scanner));
MODEL_CONTRACT_PRECONDITIONS_END(fido_scanner_release)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_scanner_release, fido_scanner* scanner)
MODEL_CONTRACT_POSTCONDITIONS_END(fido_scanner_release)

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Read a token from the scanner instance, populating the provided token
 * structure with details.
 *
 * \param details           Pointer to the token structure to receive additional
 *                          details.
 * \param scanner           The scanner instance for this operation.
 *
 * \returns a token from the scanner.
 *      - FIDO_SCANNER_TOKEN_TYPE_EOF at the end of input.
 *      - FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT if the scanner encounters bad
 *        input.
 *      - a value belonging to the \ref fido_scanner_token_type enumeration.
 */
int FN_DECL_MUST_CHECK
fido_scanner_read_token(
    fido_token_details* details, fido_scanner* scanner);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_scanner_read_token, fido_token_details* details, fido_scanner* scanner)
        /* token details point to a valid region of memory. */
        MODEL_CHECK_OBJECT_RW(details, sizeof(*details));
        /* scanner is valid. */
        MODEL_ASSERT(property_fido_scanner_valid(scanner));
MODEL_CONTRACT_PRECONDITIONS_END(fido_scanner_read_token)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_scanner_read_token, int retval, fido_token_details* details,
    fido_scanner* scanner)
        enum fido_scanner_token_type type =
            (enum fido_scanner_token_type)retval;
        MODEL_ASSERT(__CPROVER_enum_is_in_range(type));
        /* on success... */
        if (FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT != type
         && FIDO_SCANNER_TOKEN_TYPE_EOF != type)
        {
            /* the details type matches. */
            MODEL_ASSERT(type == details->type);
            /* end index is strictly >= begin index. */
            MODEL_ASSERT(details->end_index >= details->begin_index);
            /* the indices are within the bounds of the input. */
            MODEL_CHECK_OBJECT_READ(
                scanner->original_input + details->begin_index,
                details->end_index - details->begin_index + 1);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_scanner_read_token)

/**
 * \brief Peek a token from the scanner instance, populating the provided token
 * structure with details.
 *
 * \param details           Pointer to the token structure to receive additional
 *                          details.
 * \param scanner           The scanner instance for this operation.
 *
 * \returns a token from the scanner.
 *      - FIDO_SCANNER_TOKEN_TYPE_EOF at the end of input.
 *      - FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT if the scanner encounters bad
 *        input.
 *      - a value belonging to the \ref fido_scanner_token_type enumeration.
 */
int FN_DECL_MUST_CHECK
fido_scanner_peek_token(
    fido_token_details* details, fido_scanner* scanner);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_scanner_peek_token, fido_token_details* details, fido_scanner* scanner)
        /* token details point to a valid region of memory. */
        MODEL_CHECK_OBJECT_RW(details, sizeof(*details));
        /* scanner is valid. */
        MODEL_ASSERT(property_fido_scanner_valid(scanner));
MODEL_CONTRACT_PRECONDITIONS_END(fido_scanner_peek_token)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_scanner_peek_token, int retval, fido_token_details* details,
    fido_scanner* scanner)
        enum fido_scanner_token_type type =
            (enum fido_scanner_token_type)retval;
        MODEL_ASSERT(__CPROVER_enum_is_in_range(type));
        /* on success... */
        if (FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT != type
         && FIDO_SCANNER_TOKEN_TYPE_EOF != type)
        {
            /* the details type matches. */
            MODEL_ASSERT(type == details->type);
            /* end index is strictly >= begin index. */
            MODEL_ASSERT(details->end_index >= details->begin_index);
            /* the indices are within the bounds of the input. */
            MODEL_CHECK_OBJECT_READ(
                scanner->original_input + details->begin_index,
                details->end_index - details->begin_index + 1);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_scanner_peek_token)

/**
 * \brief Attempt to read a role keyword token.
 *
 * \note This function exists mainly for verification purposes. The function,
 * \ref fido_scanner_complete_token_keyword_role is used by the scanner proper,
 * and called by this function.
 *
 * \param details           Pointer to the token structure to receive additional
 *                          details.
 * \param scanner           The scanner instance for this operation.
 *
 * \returns a token from the scanner.
 *      - FIDO_SCANNER_TOKEN_TYPE_KEYWORD_ROLE or
 *        FIDO_SCANNER_TOKEN_TYPE_USERNAME on success.
 *      - FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT if the scanner encounters bad
 *        input.
 */
int FN_DECL_MUST_CHECK
fido_scanner_read_token_keyword_role(
    fido_token_details* details, fido_scanner* scanner);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_scanner_read_token_keyword_role, fido_token_details* details,
    fido_scanner* scanner)
        /* token details point to a valid region of memory. */
        MODEL_CHECK_OBJECT_RW(details, sizeof(*details));
        /* scanner is valid. */
        MODEL_ASSERT(property_fido_scanner_valid(scanner));
MODEL_CONTRACT_PRECONDITIONS_END(fido_scanner_read_token_keyword_role)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_scanner_read_token_keyword_role, int retval,
    fido_token_details* details, fido_scanner* scanner)
        /* on success... */
        if (FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT != retval
         && FIDO_SCANNER_TOKEN_TYPE_EOF != retval)
        {
            /* the returned token type matches our expected token. */
            MODEL_ASSERT(
                FIDO_SCANNER_TOKEN_TYPE_KEYWORD_ROLE == retval
             || FIDO_SCANNER_TOKEN_TYPE_USERNAME == retval);
            /* the details type matches. */
            MODEL_ASSERT(retval == details->type);
            /* end index is strictly >= begin index. */
            MODEL_ASSERT(details->end_index >= details->begin_index);
            /* the indices are within the bounds of the input. */
            MODEL_CHECK_OBJECT_READ(
                scanner->original_input + details->begin_index,
                details->end_index - details->begin_index + 1);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_scanner_read_token_keyword_role)

/**
 * \brief Attempt to read a cmd keyword token.
 *
 * \note This function exists mainly for verification purposes. The function,
 * \ref fido_scanner_complete_token_keyword_cmd is used by the scanner proper,
 * and called by this function.
 *
 * \param details           Pointer to the token structure to receive additional
 *                          details.
 * \param scanner           The scanner instance for this operation.
 *
 * \returns a token from the scanner.
 *      - FIDO_SCANNER_TOKEN_TYPE_KEYWORD_CMD or
 *        FIDO_SCANNER_TOKEN_TYPE_USERNAME on success.
 *      - FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT if the scanner encounters bad
 *        input.
 */
int FN_DECL_MUST_CHECK
fido_scanner_read_token_keyword_cmd(
    fido_token_details* details, fido_scanner* scanner);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_scanner_read_token_keyword_cmd, fido_token_details* details,
    fido_scanner* scanner)
        /* token details point to a valid region of memory. */
        MODEL_CHECK_OBJECT_RW(details, sizeof(*details));
        /* scanner is valid. */
        MODEL_ASSERT(property_fido_scanner_valid(scanner));
MODEL_CONTRACT_PRECONDITIONS_END(fido_scanner_read_token_keyword_cmd)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_scanner_read_token_keyword_cmd, int retval,
    fido_token_details* details, fido_scanner* scanner)
        /* on success... */
        if (FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT != retval
         && FIDO_SCANNER_TOKEN_TYPE_EOF != retval)
        {
            /* the returned token type matches our expected token. */
            MODEL_ASSERT(
                FIDO_SCANNER_TOKEN_TYPE_KEYWORD_CMD == retval
             || FIDO_SCANNER_TOKEN_TYPE_USERNAME == retval);
            /* the details type matches. */
            MODEL_ASSERT(retval == details->type);
            /* end index is strictly >= begin index. */
            MODEL_ASSERT(details->end_index >= details->begin_index);
            /* the indices are within the bounds of the input. */
            MODEL_CHECK_OBJECT_READ(
                scanner->original_input + details->begin_index,
                details->end_index - details->begin_index + 1);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_scanner_read_token_keyword_cmd)

/**
 * \brief Attempt to read an "as" keyword token.
 *
 * \note This function exists mainly for verification purposes. The function,
 * \ref fido_scanner_complete_token_keyword_as is used by the scanner proper,
 * and called by this function.
 *
 * \param details           Pointer to the token structure to receive additional
 *                          details.
 * \param scanner           The scanner instance for this operation.
 *
 * \returns a token from the scanner.
 *      - FIDO_SCANNER_TOKEN_TYPE_KEYWORD_AS or
 *        FIDO_SCANNER_TOKEN_TYPE_USERNAME on success.
 *      - FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT if the scanner encounters bad
 *        input.
 */
int FN_DECL_MUST_CHECK
fido_scanner_read_token_keyword_as(
    fido_token_details* details, fido_scanner* scanner);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_scanner_read_token_keyword_as, fido_token_details* details,
    fido_scanner* scanner)
        /* token details point to a valid region of memory. */
        MODEL_CHECK_OBJECT_RW(details, sizeof(*details));
        /* scanner is valid. */
        MODEL_ASSERT(property_fido_scanner_valid(scanner));
MODEL_CONTRACT_PRECONDITIONS_END(fido_scanner_read_token_keyword_as)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_scanner_read_token_keyword_as, int retval,
    fido_token_details* details, fido_scanner* scanner)
        /* on success... */
        if (FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT != retval
         && FIDO_SCANNER_TOKEN_TYPE_EOF != retval)
        {
            /* the returned token type matches our expected token. */
            MODEL_ASSERT(
                FIDO_SCANNER_TOKEN_TYPE_KEYWORD_AS == retval
             || FIDO_SCANNER_TOKEN_TYPE_USERNAME == retval);
            /* the details type matches. */
            MODEL_ASSERT(retval == details->type);
            /* end index is strictly >= begin index. */
            MODEL_ASSERT(details->end_index >= details->begin_index);
            /* the indices are within the bounds of the input. */
            MODEL_CHECK_OBJECT_READ(
                scanner->original_input + details->begin_index,
                details->end_index - details->begin_index + 1);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_scanner_read_token_keyword_as)

/**
 * \brief Attempt to read an env keyword token.
 *
 * \note This function exists mainly for verification purposes. The function,
 * \ref fido_scanner_complete_token_keyword_env is used by the scanner proper,
 * and called by this function.
 *
 * \param details           Pointer to the token structure to receive additional
 *                          details.
 * \param scanner           The scanner instance for this operation.
 *
 * \returns a token from the scanner.
 *      - FIDO_SCANNER_TOKEN_TYPE_KEYWORD_ENV or
 *        FIDO_SCANNER_TOKEN_TYPE_USERNAME on success.
 *      - FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT if the scanner encounters bad
 *        input.
 */
int FN_DECL_MUST_CHECK
fido_scanner_read_token_keyword_env(
    fido_token_details* details, fido_scanner* scanner);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_scanner_read_token_keyword_env, fido_token_details* details,
    fido_scanner* scanner)
        /* token details point to a valid region of memory. */
        MODEL_CHECK_OBJECT_RW(details, sizeof(*details));
        /* scanner is valid. */
        MODEL_ASSERT(property_fido_scanner_valid(scanner));
MODEL_CONTRACT_PRECONDITIONS_END(fido_scanner_read_token_keyword_env)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_scanner_read_token_keyword_env, int retval,
    fido_token_details* details, fido_scanner* scanner)
        /* on success... */
        if (FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT != retval
         && FIDO_SCANNER_TOKEN_TYPE_EOF != retval)
        {
            /* the returned token type matches our expected token. */
            MODEL_ASSERT(
                FIDO_SCANNER_TOKEN_TYPE_KEYWORD_ENV == retval
             || FIDO_SCANNER_TOKEN_TYPE_USERNAME == retval);
            /* the details type matches. */
            MODEL_ASSERT(retval == details->type);
            /* end index is strictly >= begin index. */
            MODEL_ASSERT(details->end_index >= details->begin_index);
            /* the indices are within the bounds of the input. */
            MODEL_CHECK_OBJECT_READ(
                scanner->original_input + details->begin_index,
                details->end_index - details->begin_index + 1);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_scanner_read_token_keyword_env)

/**
 * \brief Attempt to read a permit keyword token.
 *
 * \note This function exists mainly for verification purposes. The function,
 * \ref fido_scanner_complete_token_keyword_permit is used by the scanner
 * proper, and called by this function.
 *
 * \param details           Pointer to the token structure to receive additional
 *                          details.
 * \param scanner           The scanner instance for this operation.
 *
 * \returns a token from the scanner.
 *      - FIDO_SCANNER_TOKEN_TYPE_KEYWORD_PERMIT or
 *        FIDO_SCANNER_TOKEN_TYPE_USERNAME on success.
 *      - FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT if the scanner encounters bad
 *        input.
 */
int FN_DECL_MUST_CHECK
fido_scanner_read_token_keyword_permit(
    fido_token_details* details, fido_scanner* scanner);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_scanner_read_token_keyword_permit, fido_token_details* details,
    fido_scanner* scanner)
        /* token details point to a valid region of memory. */
        MODEL_CHECK_OBJECT_RW(details, sizeof(*details));
        /* scanner is valid. */
        MODEL_ASSERT(property_fido_scanner_valid(scanner));
MODEL_CONTRACT_PRECONDITIONS_END(fido_scanner_read_token_keyword_permit)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_scanner_read_token_keyword_permit, int retval,
    fido_token_details* details, fido_scanner* scanner)
        /* on success... */
        if (FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT != retval
         && FIDO_SCANNER_TOKEN_TYPE_EOF != retval)
        {
            /* the returned token type matches our expected token. */
            MODEL_ASSERT(
                FIDO_SCANNER_TOKEN_TYPE_KEYWORD_PERMIT == retval
             || FIDO_SCANNER_TOKEN_TYPE_USERNAME == retval);
            /* the details type matches. */
            MODEL_ASSERT(retval == details->type);
            /* end index is strictly >= begin index. */
            MODEL_ASSERT(details->end_index >= details->begin_index);
            /* the indices are within the bounds of the input. */
            MODEL_CHECK_OBJECT_READ(
                scanner->original_input + details->begin_index,
                details->end_index - details->begin_index + 1);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_scanner_read_token_keyword_permit)

/**
 * \brief Attempt to read a deny keyword token.
 *
 * \note This function exists mainly for verification purposes. The function,
 * \ref fido_scanner_complete_token_keyword_deny is used by the scanner
 * proper, and called by this function.
 *
 * \param details           Pointer to the token structure to receive additional
 *                          details.
 * \param scanner           The scanner instance for this operation.
 *
 * \returns a token from the scanner.
 *      - FIDO_SCANNER_TOKEN_TYPE_KEYWORD_DENY or
 *        FIDO_SCANNER_TOKEN_TYPE_USERNAME on success.
 *      - FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT if the scanner encounters bad
 *        input.
 */
int FN_DECL_MUST_CHECK
fido_scanner_read_token_keyword_deny(
    fido_token_details* details, fido_scanner* scanner);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_scanner_read_token_keyword_deny, fido_token_details* details,
    fido_scanner* scanner)
        /* token details point to a valid region of memory. */
        MODEL_CHECK_OBJECT_RW(details, sizeof(*details));
        /* scanner is valid. */
        MODEL_ASSERT(property_fido_scanner_valid(scanner));
MODEL_CONTRACT_PRECONDITIONS_END(fido_scanner_read_token_keyword_deny)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_scanner_read_token_keyword_deny, int retval,
    fido_token_details* details, fido_scanner* scanner)
        /* on success... */
        if (FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT != retval
         && FIDO_SCANNER_TOKEN_TYPE_EOF != retval)
        {
            /* the returned token type matches our expected token. */
            MODEL_ASSERT(
                FIDO_SCANNER_TOKEN_TYPE_KEYWORD_DENY == retval
             || FIDO_SCANNER_TOKEN_TYPE_USERNAME == retval);
            /* the details type matches. */
            MODEL_ASSERT(retval == details->type);
            /* end index is strictly >= begin index. */
            MODEL_ASSERT(details->end_index >= details->begin_index);
            /* the indices are within the bounds of the input. */
            MODEL_CHECK_OBJECT_READ(
                scanner->original_input + details->begin_index,
                details->end_index - details->begin_index + 1);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_scanner_read_token_keyword_deny)

/**
 * \brief Attempt to read a username token.
 *
 * \note This function exists mainly for verification purposes. The function,
 * \ref fido_scanner_complete_token_identifier is used by the scanner
 * proper, and called by this function.
 *
 * \param details           Pointer to the token structure to receive additional
 *                          details.
 * \param scanner           The scanner instance for this operation.
 *
 * \returns a token from the scanner.
 *      - FIDO_SCANNER_TOKEN_TYPE_USERNAME on success.
 *      - FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT if the scanner encounters bad
 *        input.
 */
int FN_DECL_MUST_CHECK
fido_scanner_read_token_username(
    fido_token_details* details, fido_scanner* scanner);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_scanner_read_token_username, fido_token_details* details,
    fido_scanner* scanner)
        /* token details point to a valid region of memory. */
        MODEL_CHECK_OBJECT_RW(details, sizeof(*details));
        /* scanner is valid. */
        MODEL_ASSERT(property_fido_scanner_valid(scanner));
MODEL_CONTRACT_PRECONDITIONS_END(fido_scanner_read_token_username)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_scanner_read_token_username, int retval,
    fido_token_details* details, fido_scanner* scanner)
        /* on success... */
        if (FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT != retval
         && FIDO_SCANNER_TOKEN_TYPE_EOF != retval)
        {
            /* the returned token type matches our expected token. */
            MODEL_ASSERT(FIDO_SCANNER_TOKEN_TYPE_USERNAME == retval);
            /* the details type matches. */
            MODEL_ASSERT(retval == details->type);
            /* end index is strictly >= begin index. */
            MODEL_ASSERT(details->end_index >= details->begin_index);
            /* the indices are within the bounds of the input. */
            MODEL_CHECK_OBJECT_READ(
                scanner->original_input + details->begin_index,
                details->end_index - details->begin_index + 1);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_scanner_read_token_username)

/**
 * \brief Attempt to read a group token.
 *
 * \note This function exists mainly for verification purposes. The function,
 * \ref fido_scanner_complete_token_identifier is used by the scanner
 * proper, and called by this function.
 *
 * \param details           Pointer to the token structure to receive additional
 *                          details.
 * \param scanner           The scanner instance for this operation.
 *
 * \returns a token from the scanner.
 *      - FIDO_SCANNER_TOKEN_TYPE_GROUP on success.
 *      - FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT if the scanner encounters bad
 *        input.
 */
int FN_DECL_MUST_CHECK
fido_scanner_read_token_group(
    fido_token_details* details, fido_scanner* scanner);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_scanner_read_token_group, fido_token_details* details,
    fido_scanner* scanner)
        /* token details point to a valid region of memory. */
        MODEL_CHECK_OBJECT_RW(details, sizeof(*details));
        /* scanner is valid. */
        MODEL_ASSERT(property_fido_scanner_valid(scanner));
MODEL_CONTRACT_PRECONDITIONS_END(fido_scanner_read_token_group)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_scanner_read_token_group, int retval,
    fido_token_details* details, fido_scanner* scanner)
        /* on success... */
        if (FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT != retval
         && FIDO_SCANNER_TOKEN_TYPE_EOF != retval)
        {
            /* the returned token type matches our expected token. */
            MODEL_ASSERT(FIDO_SCANNER_TOKEN_TYPE_GROUP == retval);
            /* the details type matches. */
            MODEL_ASSERT(retval == details->type);
            /* end index is strictly >= begin index. */
            MODEL_ASSERT(details->end_index >= details->begin_index);
            /* the indices are within the bounds of the input. */
            MODEL_CHECK_OBJECT_READ(
                scanner->original_input + details->begin_index,
                details->end_index - details->begin_index + 1);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_scanner_read_token_group)

/**
 * \brief Attempt to read an add variable token.
 *
 * \note This function exists mainly for verification purposes. The function,
 * \ref fido_scanner_complete_token_identifier is used by the scanner
 * proper, and called by this function.
 *
 * \param details           Pointer to the token structure to receive additional
 *                          details.
 * \param scanner           The scanner instance for this operation.
 *
 * \returns a token from the scanner.
 *      - FIDO_SCANNER_TOKEN_TYPE_ADD_VARIABLE on success.
 *      - FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT if the scanner encounters bad
 *        input.
 */
int FN_DECL_MUST_CHECK
fido_scanner_read_token_add_variable(
    fido_token_details* details, fido_scanner* scanner);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_scanner_read_token_add_variable, fido_token_details* details,
    fido_scanner* scanner)
        /* token details point to a valid region of memory. */
        MODEL_CHECK_OBJECT_RW(details, sizeof(*details));
        /* scanner is valid. */
        MODEL_ASSERT(property_fido_scanner_valid(scanner));
MODEL_CONTRACT_PRECONDITIONS_END(fido_scanner_read_token_add_variable)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_scanner_read_token_add_variable, int retval,
    fido_token_details* details, fido_scanner* scanner)
        /* on success... */
        if (FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT != retval
         && FIDO_SCANNER_TOKEN_TYPE_EOF != retval)
        {
            /* the returned token type matches our expected token. */
            MODEL_ASSERT(FIDO_SCANNER_TOKEN_TYPE_ADD_VARIABLE == retval);
            /* the details type matches. */
            MODEL_ASSERT(retval == details->type);
            /* end index is strictly >= begin index. */
            MODEL_ASSERT(details->end_index >= details->begin_index);
            /* the indices are within the bounds of the input. */
            MODEL_CHECK_OBJECT_READ(
                scanner->original_input + details->begin_index,
                details->end_index - details->begin_index + 1);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_scanner_read_token_add_variable)

/**
 * \brief Attempt to read a string token.
 *
 * \note This function exists mainly for verification purposes. The function,
 * \ref fido_scanner_complete_token_string is used by the scanner
 * proper, and called by this function.
 *
 * \param details           Pointer to the token structure to receive additional
 *                          details.
 * \param scanner           The scanner instance for this operation.
 *
 * \returns a token from the scanner.
 *      - FIDO_SCANNER_TOKEN_TYPE_STRING on success.
 *      - FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT if the scanner encounters bad
 *        input.
 */
int FN_DECL_MUST_CHECK
fido_scanner_read_token_string(
    fido_token_details* details, fido_scanner* scanner);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_scanner_read_token_string, fido_token_details* details,
    fido_scanner* scanner)
        /* token details point to a valid region of memory. */
        MODEL_CHECK_OBJECT_RW(details, sizeof(*details));
        /* scanner is valid. */
        MODEL_ASSERT(property_fido_scanner_valid(scanner));
MODEL_CONTRACT_PRECONDITIONS_END(fido_scanner_read_token_string)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_scanner_read_token_string, int retval,
    fido_token_details* details, fido_scanner* scanner)
        /* on success... */
        if (FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT != retval
         && FIDO_SCANNER_TOKEN_TYPE_EOF != retval)
        {
            /* the returned token type matches our expected token. */
            MODEL_ASSERT(FIDO_SCANNER_TOKEN_TYPE_STRING == retval);
            /* the details type matches. */
            MODEL_ASSERT(retval == details->type);
            /* end index is strictly >= begin index. */
            MODEL_ASSERT(details->end_index >= details->begin_index);
            /* the indices are within the bounds of the input. */
            MODEL_CHECK_OBJECT_READ(
                scanner->original_input + details->begin_index,
                details->end_index - details->begin_index + 1);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_scanner_read_token_string)

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
