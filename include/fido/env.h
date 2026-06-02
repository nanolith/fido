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

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
