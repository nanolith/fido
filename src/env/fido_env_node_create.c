/**
 * \file env/fido_env_node_create.c
 *
 * \brief Create a \ref fido_env_node instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/env.h>
#include <stdlib.h>
#include <string.h>

/**
 * \brief Create a \ref fido_env_node instance.
 *
 * \param node          Pointer to the \ref fido_env_node pointer to
 *                      receive the created node instance on success.
 * \param key           The key for this node.
 * \param value         The optional value for this node (set to NULL if not
 *                      used).
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_env_node_create(fido_env_node** node, const char* key, const char* value)
{
    int retval;
    fido_env_node* tmp;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_env_node_create, node, key, value);

    /* allocate memory for this instance. */
    tmp = (fido_env_node*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }
    memset(tmp, 0, sizeof(*tmp));

    /* copy the key. */
    tmp->key = strdup(key);
    if (NULL == tmp->key)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto cleanup_tmp;
    }

    /* copy the value if the value is set. */
    if (NULL != value)
    {
        tmp->value = strdup(value);
        if (NULL == tmp->value)
        {
            retval = FIDO_ERROR_OUT_OF_MEMORY;
            goto cleanup_tmp;
        }
    }

    /* success. */
    *node = tmp;
    retval = 0;
    goto done;

cleanup_tmp:
    fido_env_node_release(tmp);

done:
    if (0 != retval)
    {
        *node = NULL;
    }

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_env_node_create, retval, node, key, value);

    return retval;
}
