/**
 * \file env/fido_env_vararray_create.c
 *
 * \brief Create a vararray instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/env.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * \brief Create an variable array from an environment instance.
 *
 * \param varr          Pointer to the variable array pointer to receive the
 *                      created variable array on success.
 * \param env           The \ref fido_env instance for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_env_vararray_create(void** varr, const fido_env* env)
{
    int retval;
    char** tmp;
    fido_env_node* node;
    size_t i = 0;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_env_vararray_create, varr, env);

    /* allocate memory for this variable array. */
    size_t varr_size = (env->count + 1) * sizeof(char*);
    tmp = (char**)malloc(varr_size);
    if (NULL == tmp)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }
    memset(tmp, 0, varr_size);

    /* assign each variable. */
    RB_FOREACH(node, fido_env_tree, (struct fido_env_tree*)&env->root) {
        retval = asprintf(&tmp[i], "%s=%s", node->key, node->value);
        if (retval < 0)
        {
            retval = FIDO_ERROR_OUT_OF_MEMORY;
            goto cleanup_tmp;
        }

        ++i;
    }
    tmp[i] = NULL;

    /* success. */
    retval = 0;
    *varr = tmp;
    goto done;

cleanup_tmp:
    fido_env_vararray_release(tmp);

done:
    return retval;
}
