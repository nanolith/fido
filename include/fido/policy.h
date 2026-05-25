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
#include <fido/user.h>

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
 * \param user          The user for this policy check.
 *
 * \returns 0 on success (authorized) and non-zero on failure (not authorized).
 */
int FN_DECL_MUST_CHECK
fido_policy_check(
    const char** as_user, const char** as_group, const fido_config* config,
    const fido_options* opts, const fido_user* user);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_policy_check, const char** as_user, const char** as_group,
    const fido_config* config, const fido_options* opts, const fido_user* user)
        /* the as_user pointer is valid. */
        MODEL_CHECK_OBJECT_RW(as_user, sizeof(*as_user));
        /* the as_group pointer is valid. */
        MODEL_CHECK_OBJECT_RW(as_group, sizeof(*as_group));
        /* config is valid. */
        MODEL_ASSERT(property_fido_config_valid(config));
        /* options is valid. */
        MODEL_ASSERT(property_fido_options_valid(options));
        /* user is valid. */
        MODEL_ASSERT(property_fido_user_valid(user));
MODEL_CONTRACT_PRECONDITIONS_END(fido_policy_check)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_policy_check, int retval, const char** as_user, const char** as_group,
    const fido_config* config, const fido_options* opts, const fido_user* user)
        /* on success... */
        if (0 == retval)
        {
            /* as_user is populated. */
            MODEL_ASSERT(NULL != *as_user);
            /* as_group is populated. */
            MODEL_ASSERT(NULL != *as_group);
        }
        else
        {
            /* this is a defined error code. */
            enum fido_error_code error = (enum fido_error_code)retval;
            MODEL_ASSERT(__CPROVER_enum_is_in_range(error));
            /* both as_user and as_group are NULL. */
            MODEL_ASSERT(NULL == *as_user);
            MODEL_ASSERT(NULL == *as_group);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_policy_check)

/**
 * \brief Check to see if a given role matches the command and user details.
 *
 * \param as_user       String pointer pointer updated to the user name who
 *                      should execute this command.
 * \param as_group      String pointer pointer updated to the group group name
 *                      who should execute this command.
 * \param role          The role to match.
 * \param opts          The options for this match.
 * \param user          The user for this match.
 *
 * \returns 0 on success (matched) and non-zero on failure (not matched).
 */
int FN_DECL_MUST_CHECK
fido_policy_role_match(
    const char** as_user, const char** as_group, const fido_config_role* role,
    const fido_options* opts, const fido_user* user);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_policy_role_match, const char** as_user, const char** as_group,
    const fido_config* config, const fido_options* opts, const fido_user* user)
        /* the as_user pointer is valid. */
        MODEL_CHECK_OBJECT_RW(as_user, sizeof(*as_user));
        /* the as_group pointer is valid. */
        MODEL_CHECK_OBJECT_RW(as_group, sizeof(*as_group));
        /* config is valid. */
        MODEL_ASSERT(property_fido_config_valid(config));
        /* options is valid. */
        MODEL_ASSERT(property_fido_options_valid(options));
        /* user is valid. */
        MODEL_ASSERT(property_fido_user_valid(user));
MODEL_CONTRACT_PRECONDITIONS_END(fido_policy_role_match)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_policy_role_match, int retval, const char** as_user,
    const char** as_group, const fido_config_role* role,
    const fido_options* opts, const fido_user* user)
        /* on success... */
        if (0 == retval)
        {
            /* as_user is populated. */
            MODEL_ASSERT(NULL != *as_user);
            /* as_group is populated. */
            MODEL_ASSERT(NULL != *as_group);
        }
        else
        {
            /* this is a defined error code. */
            enum fido_error_code error = (enum fido_error_code)retval;
            MODEL_ASSERT(__CPROVER_enum_is_in_range(error));
            /* both as_user and as_group are NULL. */
            MODEL_ASSERT(NULL == *as_user);
            MODEL_ASSERT(NULL == *as_group);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_policy_role_match)

/**
 * \brief Check to see if a given command matches the provided options.
 *
 * \param cmd           The command to match.
 * \param opts          The options for this match.
 *
 * \returns 0 on success (matched) and non-zero on failure (not matched).
 */
int FN_DECL_MUST_CHECK
fido_policy_command_match(
    const fido_config_command* cmd, const fido_options* opts);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_policy_command_match, const fido_config_command* cmd,
    const fido_options* opts)
        /* command is valid. */
        MODEL_ASSERT(property_fido_config_command_valid(cmd));
        /* options is valid. */
        MODEL_ASSERT(property_fido_options_valid(options));
MODEL_CONTRACT_PRECONDITIONS_END(fido_policy_command_match)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_policy_command_match, int retval, const fido_config_command* cmd,
    const fido_options* opts)
MODEL_CONTRACT_POSTCONDITIONS_END(fido_policy_command_match)

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
