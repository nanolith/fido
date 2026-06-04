/**
 * \file env/fido_env_release.c
 *
 * \brief Release a \ref fido_env instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/env.h>
#include <stdlib.h>

/**
 * \brief Release a \ref fido_env instance.
 *
 * \param env           The instance to release.
 */
void fido_env_release(fido_env* env)
{
    fido_env_node* node;
    fido_env_node* next_node;

    for (
        node = RB_MIN(fido_env_tree, &env->root);
        node != NULL;
        node = next_node)
    {
        next_node = RB_NEXT(fido_env_tree, &env->root, node);
        RB_REMOVE(fido_env_tree, &env->root, node);
        free(node);
    }

    free(env);
}
