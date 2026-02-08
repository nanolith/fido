/**
 * \file fido/scanner.h
 *
 * \brief Scanner for fido.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

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
    FIDO_SCANNER_TOKEN_TYPE_ROLE = 1,
    /** \brief Command keyword. */
    FIDO_SCANNER_TOKEN_TYPE_CMD,
    /** \brief As keyword. */
    FIDO_SCANNER_TOKEN_TYPE_AS,
};

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
