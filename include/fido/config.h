/**
 * \file fido/config.h
 *
 * \brief Config tree for fido.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <fido/function_contracts.h>
#include <fido/function_decl.h>
#include <stddef.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief Identifier type.
 */
enum fido_config_identifier_type
{
    /** \brief Group identifier. */
    FIDO_CONFIG_IDENTIFIER_TYPE_GROUP = 1,
};

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
