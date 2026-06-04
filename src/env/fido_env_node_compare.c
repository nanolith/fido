/**
 * \file env/fido_env_node_compare.c
 *
 * \brief Comparison function for fido env red-black tree.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/env.h>
#include <string.h>

/**
 * \brief Compare two nodes.
 *
 * \param lhs           The left-hand-side of the comparison.
 * \param rhs           The right-hand-side of the comparison.
 *
 * \returns a comparison result
 *      - < 0 if lhs < rhs
 *      - > 0 if lhs > rhs
 *      - 0 if lhs == rhs
 */
int fido_env_node_compare(const fido_env_node* lhs, const fido_env_node* rhs)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_env_node_compare, lhs, rhs);

    int retval = strcmp(lhs->key, rhs->key);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_env_node_compare, retval, lhs, rhs);

    return retval;
}
