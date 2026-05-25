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
policy_check(
    const char** as_user, const char** as_group, fido_config* config,
    fido_options* opts);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
