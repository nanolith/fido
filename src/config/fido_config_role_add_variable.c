/**
 * \file config/fido_config_role_add_variable.c
 *
 * \brief Add a variable to the \ref fido_config_role instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>

#include "parser_internal.h"

/**
 * \brief Add a variable to a role instance.
 *
 * \param role              The role instance for this operation.
 * \param var               The variable to add.
 */
void
fido_config_role_add_variable(
    fido_config_role* role, fido_config_add_variable* var)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_config_role_add_variable, role, var);

    var->next = role->variable_head;
    role->variable_head = var;

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_role_add_variable, role, var);
}
