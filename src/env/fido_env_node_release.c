/**
 * \file env/fido_env_node_release.c
 *
 * \brief Release a \ref fido_env_node instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/env.h>
#include <stdlib.h>

/**
 * \brief Release a \ref fido_node_env instance.
 *
 * \param node          The instance to release.
 */
void fido_env_node_release(fido_env_node* node)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_env_node_release, node);

    /* free key if set. */
    if (NULL != node->key)
    {
        free(node->key);
    }

    /* free value if set. */
    if (NULL != node->value)
    {
        free(node->value);
    }

    free(node);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(fido_env_node_release, node);
}
