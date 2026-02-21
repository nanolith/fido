/**
 * \file fido/error_codes.h
 *
 * \brief Error codes for fido.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

enum fido_error_code
{
    /** \brief Out of memory error. */
    FIDO_ERROR_OUT_OF_MEMORY = 1,
    /** \brief Invalid input error. */
    FIDO_ERROR_INVALID_INPUT = 2,
    /** \brief Unexpected EOF while parsing config file. */
    FIDO_ERROR_UNEXPECTED_EOF = 3,
    /** \brief An unexpected token was encountered when parsing config file. */
    FIDO_ERROR_UNEXPECTED_TOKEN = 4,
    /** \brief The length of a string token was too long. */
    FIDO_ERROR_BAD_LENGTH = 5,
};

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
