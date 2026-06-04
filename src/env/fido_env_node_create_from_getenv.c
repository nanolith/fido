/**
 * \file env/fido_env_node_create_from_getenv.c
 *
 * \brief Create a \ref fido_env_node instance by reading the environment.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/env.h>
#include <stdlib.h>

/**
 * \brief Create a \ref fido_env_node instance from the current environment.
 *
 * \param node          Pointer to the \ref fido_env_node pointer to
 *                      receive the created node instance on success.
 * \param key           The key for this node.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - FIDO_ERROR_ENV_VAR_NOT_FOUND
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_env_node_create_from_getenv(fido_env_node** node, const char* key)
{
    int retval;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_env_node_create_from_getenv, node, key);

    /* attempt to read this variable from the environment. */
    const char* value = getenv(key);
    if (NULL == value)
    {
        retval = FIDO_ERROR_ENV_VAR_NOT_FOUND;
        goto done;
    }

    /* attempt to create a node entry from this value. */
    retval = fido_env_node_create(node, key, value);
    goto done;

done:
    if (0 != retval)
    {
        *node = NULL;
    }

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_env_node_create_from_getenv, retval, node, key);

    return retval;
}
