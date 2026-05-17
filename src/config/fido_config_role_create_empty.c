/**
 * \file config/fido_config_role_create_empty.c
 *
 * \brief Create an empty \ref fido_config_role instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>
#include <string.h>

#include "parser_internal.h"

/**
 * \brief Create an empty \ref fido_config_role instance.
 *
 * \param role              Pointer to the role pointer to set to this
 *                          created instance on success.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_config_role_create_empty(fido_config_role** role)
{
    int retval;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_config_role_create_empty, role);

    /* create an "empty" role. */
    retval = fido_config_role_create(role, "(empty)", NULL, NULL);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_role_create_empty, retval, role);

    return retval;
}
