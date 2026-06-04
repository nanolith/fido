/**
 * \file env/fido_env_node_add_or_replace_kvp.c
 *
 * \brief Add an env node to the environment or replace it.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/env.h>

/**
 * \brief Create an environment variable node with the given key and value, and
 * add it to the environment instance.
 *
 * \param env           The env to which this node is added.
 * \param key           The node key.
 * \param value         The node value.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_env_node_add_or_replace_kvp(
    fido_env* env, const char* key, const char* value)
{
    int retval;
    fido_env_node* tmp;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_env_add_or_replace_kvp, env, key, value);

    /* attempt to create the node. */
    retval = fido_env_node_create(&tmp, key, value);
    if (0 != retval)
    {
        goto done;
    }

    /* add this node to the environment. */
    retval = fido_env_node_add_or_replace(env, tmp);
    if (0 != retval)
    {
        goto cleanup_tmp;
    }

    /* success. */
    retval = 0;
    goto done;

cleanup_tmp:
    fido_env_node_release(tmp);

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_env_add_or_replace_kvp, retval, env, key, value);

    return retval;
}
