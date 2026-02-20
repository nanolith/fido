/**
 * \file config/fido_config_add_role.c
 *
 * \brief Add a role to the \ref fido_config instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>

#include "parser_internal.h"

/**
 * \brief Add a role to a config instance.
 *
 * \param config            The config instance for this operation.
 * \param role              The role to add.
 */
void
fido_config_add_role(
    fido_config* config, fido_config_role* role)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_config_add_role, config, role);

    role->next = config->head;
    config->head = role;

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(fido_config_add_role, config, role);
}
