/**
 * \file fido/policy.h
 *
 * \brief Policy check methods.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <fido/config.h>
#include <fido/options.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief Check the given options against the given configuration file to return
 * a policy decision about whether this command should be executed, and as which
 * user and group
 *
 * \param as_user       String pointer pointer updated to the user name who
 *                      should execute this command.
 * \param as_group      String pointer pointer updated to the group group name
 *                      who should execute this command.
 * \param config        The configuration used for making policy decisions.
 * \param opts          The options for this policy check.
 *
 * \returns 0 on success (authorized) and non-zero on failure (not authorized).
 */
int FN_DECL_MUST_CHECK
fido_policy_check(
    const char** as_user, const char** as_group, const fido_config* config,
    const fido_options* opts);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_policy_check, const char** as_user, const char** as_group,
    const fido_config* config, const fido_options* opts)
        /* the as_user pointer is valid. */
        MODEL_CHECK_OBJECT_RW(as_user, sizeof(*as_user));
        /* the as_group pointer is valid. */
        MODEL_CHECK_OBJECT_RW(as_group, sizeof(*as_group));
        /* config is valid. */
        MODEL_ASSERT(property_fido_config_valid(config));
        /* options is valid. */
        MODEL_ASSERT(property_fido_options_valid(options));
MODEL_CONTRACT_PRECONDITIONS_END(fido_policy_check)

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
