/**
 * \file policy_proc/fido_policy_decision_release.c
 *
 * \brief Release a \ref fido_policy_decision instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/policy_proc.h>
#include <stdlib.h>

/**
 * \brief Release a \ref fido_policy_decision instance.
 *
 * \param dec           The policy decision record to release.
 */
void
fido_policy_decision_release(fido_policy_decision* dec)
{
    fido_config_add_variable* tmp;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_policy_decision_release, dec);

    /* free as_user if set. */
    if (NULL != dec->as_user)
    {
        free(dec->as_user);
    }

    /* free as_group if set. */
    if (NULL != dec->as_group)
    {
        free(dec->as_group);
    }

    /* clean up all variables. */
    while (NULL != dec->variable_head)
    {
        tmp = dec->variable_head->next;
        fido_config_add_variable_release(dec->variable_head);
        dec->variable_head = tmp;
    }

    free(dec);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(fido_policy_decision_release, dec);
}
