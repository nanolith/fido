/**
 * \file policy/fido_policy_role_match.c
 *
 * \brief Check to see if a given role matches command-line options and user
 * details.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/policy.h>
#include <string.h>

/* forward decls. */
static int role_permission_match(
    const fido_config_role* role, const fido_user* user);
static int match_group_by_name(
    const fido_user* user, const char* groupname);
static int role_command_match(
    const fido_config_role* role, const fido_options* opts);

/**
 * \brief Check to see if a given role matches the command and user details.
 *
 * \param as_user       String pointer pointer updated to the user name who
 *                      should execute this command.
 * \param as_group      String pointer pointer updated to the group group name
 *                      who should execute this command.
 * \param env_head      Pointer to pointer to head of environment variables list
 *                      to be copied from the user's environment on success.
 * \param role          The role to match.
 * \param opts          The options for this match.
 * \param user          The user for this match.
 *
 * \returns 0 on success (matched) and non-zero on failure (not matched).
 */
int FN_DECL_MUST_CHECK
fido_policy_role_match(
    const char** as_user, const char** as_group,
    const fido_config_add_variable** env_head, const fido_config_role* role,
    const fido_options* opts, const fido_user* user)
{
    int retval;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_policy_role_match, as_user, as_group, env_head, role, opts, user);

    /* do the permissions match? */
    retval = role_permission_match(role, user);
    if (0 != retval)
    {
        goto done;
    }

    /* does the command match? */
    retval = role_command_match(role, opts);
    if (0 != retval)
    {
        goto done;
    }

    /* the role matches, so set the as_user, as_group, and env_head. */
    *as_user = role->as_user;
    *as_group = role->as_group;
    *env_head = role->variable_head;
    retval = 0;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_policy_role_match, retval, as_user, as_group, env_head, role,
        opts, user);

    return retval;
}

/**
 * \brief Match role permissions against the user using latest-match-wins.
 *
 * \param role              The role for permission matching.
 * \param user              The user for this match.
 *
 * \returns 0 on success (matched) and non-zero on failure (not matched).
 */
static int role_permission_match(
    const fido_config_role* role, const fido_user* user)
{
    fido_config_permission* latest = NULL;

    /* edge case: if no permissions are specified, check user for wheel
     * membership. */
    if (NULL == role->permission_head)
    {
        return match_group_by_name(user, "wheel");
    }

    /* get the latest match. */
    for(
        fido_config_permission* perm = role->permission_head;
        NULL != perm;
        perm = perm->next)
    {
        if (0 == fido_policy_permission_match(perm, user))
        {
            latest = perm;
        }
    }

    /* no match if nothing found. */
    if (NULL == latest)
    {
        return FIDO_ERROR_POLICY_MATCH;
    }

    /* no match if deny. */
    if (FIDO_CONFIG_PERMISSION_TYPE_DENY == latest->permission_type)
    {
        return FIDO_ERROR_POLICY_MATCH;
    }

    /* permission found and it's not a deny. So, we match. */
    return 0;
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

/**
 * \brief Attempt to match a role against a list of commands, on a first match
 * wins basis.
 *
 * \param role              The role to match.
 * \param opts              The command-line options to match.
 *
 * \returns 0 on success (matched) and non-zero on failure (not matched).
 */
static int role_command_match(
    const fido_config_role* role, const fido_options* opts)
{
    /* edge case: if no commands are specified, then any command matches. */
    if (NULL == role->command_head)
    {
        return 0;
    }

    /* otherwise, a matching command must be found. */
    for (
        fido_config_command* cmd = role->command_head;
        NULL != cmd;
        cmd = cmd->next)
    {
        if (0 == fido_policy_command_match(cmd, opts))
        {
            return 0;
        }
    }

    return FIDO_ERROR_POLICY_MATCH;
}
