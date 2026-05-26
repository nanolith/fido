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
    /** \brief The provided command is invalid. */
    FIDO_ERROR_INVALID_COMMAND = 6,
    /** \brief An invalid string was encountered. */
    FIDO_ERROR_INVALID_STRING = 7,
    /** \brief An invalid escape sequence was encountered in a string. */
    FIDO_ERROR_INVALID_STRING_ESCAPE = 8,
    /** \brief Multiple wildcard (*) arguments aren't supported. */
    FIDO_ERROR_MULTIPLE_WILDCARD_ARGUMENTS = 9,
    /** \brief Argument encountered after wildcard. */
    FIDO_ERROR_ARGUMENT_AFTER_WILDCARD = 10,
    /** \brief A bad wildcard construction. */
    FIDO_ERROR_BAD_WILDCARD = 11,
    /** \brief as username was provided twice. */
    FIDO_ERROR_DUPLICATE_AS_USERNAME = 12,
    /** \brief as group was provided twice. */
    FIDO_ERROR_DUPLICATE_AS_GROUP = 13,
    /** \brief Unknown as type. */
    FIDO_ERROR_UNKNOWN_AS_TYPE = 14,
    /** \brief Invalid command-line option. */
    FIDO_ERROR_INVALID_OPTION = 15,
    /** \brief Missing command. */
    FIDO_ERROR_OPTION_MISSING_COMMAND = 16,
    /** \brief Bad system configuration. */
    FIDO_ERROR_BAD_SYSCONF = 17,
};

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
