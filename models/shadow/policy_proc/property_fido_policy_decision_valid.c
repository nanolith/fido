/**
 * \file models/shadow/policy_proc/property_fido_policy_decision_valid.c
 *
 * \brief Verify that a policy decision is valid.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/policy_proc.h>

/**
 * \brief Valid policy decision record property.
 *
 * \param dec           The policy decision record to check.
 *
 * \returns true if the policy decision record is valid.
 */
bool
property_fido_policy_decision_valid(
    const fido_policy_decision* dec)
{
    MODEL_CHECK_OBJECT_READ(dec, sizeof(*dec));
    if (FIDO_POLICY_DECISION_DENY == dec->policy_decision)
    {
        MODEL_ASSERT(NULL == dec->as_user);
        MODEL_ASSERT(NULL == dec->as_group);
        MODEL_ASSERT(NULL == dec->variable_head);

        return true;
    }
    else if (FIDO_POLICY_DECISION_PERMIT == dec->policy_decision)
    {
        MODEL_ASSERT(NULL != dec->as_user);
        MODEL_ASSERT(NULL != dec->as_group);

        fido_config_add_variable* x = dec->variable_head;
        while (NULL != x)
        {
            MODEL_ASSERT(property_fido_config_add_variable_valid(x));
            x = x->next;
        }

        return true;
    }

    return false;
}
