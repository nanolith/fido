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

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief Policy decision type enumeration.
 */
enum policy_decision_type
{
    /** \brief Deny is the default. Don't allow this action. */
    FIDO_POLICY_DECISION_DENY,
    /** \brief Permit the action. */
    FIDO_POLICY_DECISION_PERMIT,
};

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
