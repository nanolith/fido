/**
 * \file env/rb_impl.c
 *
 * \brief Implementation of red-black tree for fido env.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/env.h>

RB_GENERATE(fido_env_tree, fido_env_node, node, fido_env_node_compare)
