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
};

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
