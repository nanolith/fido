/**
 * \file env/fido_env_fill_from_current_and_target_users.c
 *
 * \brief Fill the environment using the current and target users.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/env.h>

/**
 * \brief Fill environment entries from the current and target user.
 *
 * \param env           The env instance to fill.
 * \param curr          The current user.
 * \param target        The target user.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_env_fill_from_current_and_target_users(
    fido_env* env, const fido_user* curr, const fido_user* target)
{
    int retval;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_env_fill_from_current_and_target_users, curr, target);

    /* preserve the original username. */
    retval = fido_env_node_add_or_replace_kvp(env, "FIDO_USER", curr->username);
    if (0 != retval)
    {
        goto done;
    }

    /* set HOME to the target user's home. */
    retval = fido_env_node_add_or_replace_kvp(env, "HOME", target->home);
    if (0 != retval)
    {
        goto done;
    }

    /* set LOGNAME to the target user's name. */
    retval = fido_env_node_add_or_replace_kvp(env, "LOGNAME", target->username);
    if (0 != retval)
    {
        goto done;
    }

    /* set SHELL to the target user's shell. */
    retval = fido_env_node_add_or_replace_kvp(env, "SHELL", target->shell);
    if (0 != retval)
    {
        goto done;
    }

    /* set USER to the target user's name. */
    retval = fido_env_node_add_or_replace_kvp(env, "USER", target->username);
    if (0 != retval)
    {
        goto done;
    }

    /* success. */
    retval = 0;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_env_fill_from_current_and_target_users, retval, env, curr, target);

    return retval;
}
