/**
 * \file fido/policy_proc.h
 *
 * \brief Methods for interfacing with the policy process.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <fido/config.h>
#include <fido/function_contracts.h>
#include <fido/function_decl.h>
#include <fido/model_assert.h>
#include <stdbool.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief Policy decision type enumeration.
 */
enum fido_policy_decision_type
{
    /** \brief Deny is the default. Don't allow this action. */
    FIDO_POLICY_DECISION_DENY,
    /** \brief Permit the action. */
    FIDO_POLICY_DECISION_PERMIT,
};

/**
 * \brief Policy decision.
 */
typedef struct fido_policy_decision fido_policy_decision;
struct fido_policy_decision
{
    int policy_decision;
    char* as_user;
    char* as_group;
    fido_config_add_variable* variable_head;
};

/******************************************************************************/
/* Start of model checking properties.                                        */
/******************************************************************************/

/**
 * \brief Valid policy decision record property.
 *
 * \param dec           The policy decision record to check.
 *
 * \returns true if the policy decision record is valid.
 */
bool
property_fido_policy_decision_valid(
    const fido_policy_decision* dec);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Release a \ref fido_policy_decision instance.
 *
 * \param dec           The policy decision record to release.
 */
void
fido_policy_decision_release(fido_policy_decision* dec);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_policy_decision_release, fido_policy_decision* dec)
        /* dec points to a region of memory large enough to hold it. */
        MODEL_CHECK_OBJECT_RW(dec, sizeof(*dec));
MODEL_CONTRACT_PRECONDITIONS_END(fido_policy_decision_release)

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
