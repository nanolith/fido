/**
 * \file config/scanner_internal.h
 *
 * \brief Internal functions and types for the fido scanner.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <fido/scanner.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/******************************************************************************/
/* Start of private methods.                                                  */
/******************************************************************************/

/**
 * \brief Skip to the next character.
 *
 * \param scanner           The scanner instance for this operation.
 */
void fido_scanner_next_character(fido_scanner* scanner);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_scanner_next_character, fido_scanner* scanner)
        /* scanner is valid. */
        MODEL_ASSERT(property_fido_scanner_valid(scanner));
        /* the scanner is not at end of input. */
        MODEL_ASSERT(0 != *(scanner->input));
MODEL_CONTRACT_PRECONDITIONS_END(fido_scanner_next_character)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_scanner_next_character, fido_scanner* scanner)
        /* scanner is valid. */
        MODEL_ASSERT(property_fido_scanner_valid(scanner));
MODEL_CONTRACT_POSTCONDITIONS_END(fido_scanner_next_character)

/**
 * \brief End the current input token, populating token details.
 *
 * \param details           The details to populate with the end token data.
 * \param scanner           The scanner instance.
 * \param type              The token type.
 *
 * \returns the token type.
 */
int fido_scanner_token_details_end(
    fido_token_details* details, fido_scanner* scanner, int type);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_scanner_token_details_end, fido_token_details* details,
    fido_scanner* scanner, int type)
        /* details are writable. */
        MODEL_CHECK_OBJECT_RW(details, sizeof(*details));
        /* scanner is valid. */
        MODEL_ASSERT(property_fido_scanner_valid(scanner));
        /* the type is valid. */
        enum fido_scanner_token_type t = (enum fido_scanner_token_type)type;
        MODEL_ASSERT(__CPROVER_enum_is_in_range(t));
MODEL_CONTRACT_PRECONDITIONS_END(fido_scanner_token_details_end)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_scanner_token_details_end, int retval, fido_token_details* details,
    fido_scanner* scanner, int type)
        /* the type is returned. */
        MODEL_ASSERT(retval == type);
MODEL_CONTRACT_POSTCONDITIONS_END(fido_scanner_token_details_end)

/**
 * \brief Skip whitespace to get the start of the next token.
 *
 * \param scanner       The scanner instance for this operation.
 *
 * \returns the start of the next token.
 */
int fido_scanner_skip_whitespace(fido_scanner* scanner);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_scanner_skip_whitespace, fido_scanner* scanner)
        /* scanner is valid. */
        MODEL_ASSERT(property_fido_scanner_valid(scanner));
MODEL_CONTRACT_PRECONDITIONS_END(fido_scanner_skip_whitespace)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_scanner_skip_whitespace, int retval, fido_scanner* scanner)
        /* scanner is valid. */
        MODEL_ASSERT(property_fido_scanner_valid(scanner));
MODEL_CONTRACT_POSTCONDITIONS_END(fido_scanner_skip_whitespace)

/**
 * \brief Attempt to complete a role keyword token.
 *
 * \param details           Pointer to the token structure to receive additional
 *                          details.
 * \param scanner           The scanner instance for this operation.
 *
 * \returns a token from the scanner.
 *      - FIDO_SCANNER_TOKEN_TYPE_KEYWORD_ROLE on success.
 *      - FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT if the scanner encounteres bad
 *        input.
 *      - FIDO_SCANNER_TOKEN_TYPE_EOF if the scanner encounters an EOF
 *        condition.
 */
int FN_DECL_MUST_CHECK
fido_scanner_complete_token_keyword_role(
    fido_token_details* details, fido_scanner* scanner);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_scanner_complete_token_keyword_role, fido_token_details* details,
    fido_scanner* scanner)
        /* token details point to a valid region of memory. */
        MODEL_CHECK_OBJECT_RW(details, sizeof(*details));
        /* scanner is valid. */
        MODEL_ASSERT(property_fido_scanner_valid(scanner));
MODEL_CONTRACT_PRECONDITIONS_END(fido_scanner_complete_token_keyword_role)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_scanner_complete_token_keyword_role, int retval,
    fido_token_details* details, fido_scanner* scanner)
        /* on success... */
        if (FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT != retval
         && FIDO_SCANNER_TOKEN_TYPE_EOF != retval)
        {
            /* the returned token type matches our expected token. */
            MODEL_ASSERT(FIDO_SCANNER_TOKEN_TYPE_KEYWORD_ROLE == retval);
            /* the details type matches. */
            MODEL_ASSERT(retval == details->type);
            /* end index is strictly >= begin index. */
            MODEL_ASSERT(details->end_index >= details->begin_index);
            /* the indices are within the bounds of the input. */
            MODEL_CHECK_OBJECT_READ(
                scanner->original_input + details->begin_index,
                details->end_index - details->begin_index);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_scanner_complete_token_keyword_role)

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
