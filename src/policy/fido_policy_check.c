/**
 * \file policy/fido_policy_check.c
 *
 * \brief Check the given user and command-line options against the given
 * configuration to make a policy decision about whether the given command is
 * authorized to execute, as well as which user/group and which environment
 * variables should be used to execute this command.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/policy.h>
#include <string.h>

/* forward decls. */
static int match_group_by_name(
    const fido_user* user, const char* groupname);

/**
 * \brief Check the given options against the given configuration file to return
 * a policy decision about whether this command should be executed, and as which
 * user and group
 *
 * \param as_user       String pointer pointer updated to the user name who
 *                      should execute this command.
 * \param as_group      String pointer pointer updated to the group group name
 *                      who should execute this command.
 * \param env_head      Head of the environment variable list to add from the
 *                      current environment to this one on success.
 * \param config        The configuration used for making policy decisions.
 * \param opts          The options for this policy check.
 * \param user          The user for this policy check.
 *
 * \returns 0 on success (authorized) and non-zero on failure (not authorized).
 */
int FN_DECL_MUST_CHECK
fido_policy_check(
    const char** as_user, const char** as_group,
    const fido_config_add_variable** env_head, const fido_config* config,
    const fido_options* opts, const fido_user* user)
{
    int retval;
    const char* as_user_tmp;
    const char* as_group_tmp;
    const fido_config_add_variable* env_head_tmp;
    bool role_found = false;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_policy_check, as_user, as_group, env_head, config, opts, user);

    /* edge case: is the role list empty? */
    if (NULL == config->head)
    {
        /* check that the user belongs to the wheel group. */
        retval = match_group_by_name(user, "wheel");
        if (0 != retval)
        {
            goto done;
        }

        *as_user = "root";
        *as_group = "wheel";
        *env_head = NULL;
        goto done;
    }

    /* find the last matching role. */
    for (fido_config_role* role = config->head; NULL != role; role = role->next)
    {
        retval =
            fido_policy_role_match(
                &as_user_tmp, &as_group_tmp, &env_head_tmp, role, opts, user);
        if (0 == retval)
        {
            role_found = true;
            *as_user = as_user_tmp;
            *as_group = as_group_tmp;
            *env_head = env_head_tmp;
        }
    }

    /* if a matching role wasn't found, then the policy check failed. */
    if (!role_found)
    {
        retval = FIDO_ERROR_POLICY_MATCH;
        goto done;
    }

    /* success. */
    retval = 0;
    goto done;

done:
    if (0 != retval)
    {
        *as_user = NULL;
        *as_group = NULL;
        *env_head = NULL;
    }

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_policy_check, retval, as_user, as_group, env_head, config, opts,
        user);

    return retval;
}

/**
 * \brief Attempt to match a user's group membership by name.
 *
 * \param user              The user to match.
 * \param groupname         The name of the group.
 *
 * \returns 0 on success (matched) and non-zero on failure (not matched).
 */
static int match_group_by_name(
    const fido_user* user, const char* groupname)
{
    for (size_t i = 0; i < user->group_count; ++i)
    {
        if (!strcmp(user->groupnames[i], groupname))
        {
            return 0;
        }
    }

    return FIDO_ERROR_POLICY_MATCH;
}
