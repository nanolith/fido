/**
 * \file fido/env.h
 *
 * \brief Methods for interfacing with the environment.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <sys/tree.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

typedef struct fido_env_node fido_env_node;
struct fido_env_node
{
    RB_ENTRY(fido_env_node) node;
    char* key;
    char* value;
};

typedef struct fido_env fido_env;
struct fido_env
{
    RB_HEAD(fido_env_tree, fido_env_node) head;
    size_t count;
};

/******************************************************************************/
/* Start of model checking properties.                                        */
/******************************************************************************/

/**
 * \brief Valid \ref fido_env_node property.
 *
 * \param node          The node to check.
 *
 * \returns true if the node is valid.
 */
bool
property_fido_env_node_valid(
    const fido_env_node* node);

/**
 * \brief Valid \ref fido_env property.
 *
 * \param env           The env to check.
 *
 * \returns true if the env is valid.
 */
bool
property_fido_env_valid(
    const fido_env* env);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
