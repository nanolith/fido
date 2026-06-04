/**
 * \file env/fido_env_node_add_or_replace.c
 *
 * \brief Add an env node to the environment or replace it.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/env.h>

/**
 * \brief Add or replace an environment variable node in an environment
 * instance.
 *
 * \note On success, \p env takes ownership of \p node.
 *
 * \param env           The env to which this node is added.
 * \param node          The node to add or replace.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_env_node_add_or_replace(fido_env* env, fido_env_node* node)
{
    int retval;
    fido_env_node* tmp;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_env_node_add_or_replace, node);

    /* first, remove the node if it already exists. */
    tmp = RB_FIND(fido_env_tree, &env->root, node);
    if (NULL != tmp)
    {
        RB_REMOVE(fido_env_tree, &env->root, tmp);
        fido_env_node_release(tmp);
        env->count -= 1;
    }

    /* insert this node. */
    RB_INSERT(fido_env_tree, &env->root, node);
    env->count += 1;

    /* success. */
    retval = 0;

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_env_node_add_or_replace, retval, node);

    return retval;
}
