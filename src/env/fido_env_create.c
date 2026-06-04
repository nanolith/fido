/**
 * \file env/fido_env_create.c
 *
 * \brief Create a \ref fido_env instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/env.h>
#include <stdlib.h>
#include <string.h>

/**
 * \brief Create an empty env instance.
 *
 * \param env           Pointer to the \ref fido_env pointer to
 *                      receive the created environment instance on success.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_env_create(fido_env** env)
{
    int retval;
    fido_env* tmp;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_env_create, env);

    /* allocate memory for this instance. */
    tmp = (fido_env*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }
    memset(tmp, 0, sizeof(*tmp));

    /* initialize head. */
    RB_INIT(&tmp->root);

    /* success. */
    retval = 0;
    *env = tmp;
    tmp = NULL;
    goto done;

done:
    if (0 != retval)
    {
        *env = NULL;
    }

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(fido_env_create, retval, env);

    return retval;
}
