/**
 * \file config/fido_config_roles_finalize.c
 *
 * \brief Finalize roles for a \ref fido_config instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>

#include "parser_internal.h"

/**
 * \brief Finalize roles for a \ref fido_config instance.
 *
 * \param config            The config instance for this operation.
 */
void
fido_config_roles_finalize(fido_config* config)
{
    fido_config_role* head = NULL;
    fido_config_role* tmp;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_config_roles_finalize, config);

    while (NULL != config->head)
    {
        /* cache next. */
        tmp = config->head->next;

        /* detach config->head from list and attach to new list. */
        config->head->next = head;

        /* update new list head to point to config->head. */
        head = config->head;

        /* move config->head to the next item in the original list. */
        config->head = tmp;
    }

    /* assign config->head to the reversed list. */
    config->head = head;

    /* the roles are now finalized. */
    config->roles_finalized = true;

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(fido_config_roles_finalize, config);
}
