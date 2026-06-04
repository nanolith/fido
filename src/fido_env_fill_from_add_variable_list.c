/**
 * \file env/fido_env_fill_from_add_variable_list.c
 *
 * \brief Fill the environment using an add variable list.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/env.h>
#include <stdio.h>

/**
 * \brief Fill environment entries from an add variable list.
 *
 * \param env           The env instance to fill.
 * \param var_head      The head of the add variable list.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_env_fill_from_add_variable_list(
    fido_env* env, const fido_config_add_variable* var_head)
{
    int retval;
    fido_env_node* tmp;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_env_fill_from_add_variable_list, env, var_head);

    for (; NULL != var_head; var_head = var_head->next)
    {
        /* create the variable from the environment. */
        retval = fido_env_node_create_from_getenv(&tmp, var_head->name);
        if (0 != retval)
        {
            fprintf(
                stderr, "error: environment variable %s not found.\n",
                var_head->name);
            goto done;
        }

        /* add this variable to the environment. */
        retval = fido_env_node_add_or_replace(env, tmp);
        if (0 != retval)
        {
            goto cleanup_tmp;
        }
    }

    /* success. */
    retval = 0;
    goto done;

cleanup_tmp:
    fido_env_node_release(tmp);

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_env_fill_from_add_variable_list, retval, env, var_head);

    return retval;
}
