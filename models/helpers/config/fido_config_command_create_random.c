/**
 * \file models/helpers/config/fido_config_command_create_random.c
 *
 * \brief Create a non-deterministic command instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "config_helpers.h"

int FN_DECL_MUST_CHECK
fido_config_command_create_random(fido_config_command** cmd)
{
    char binary[8];

    /* randomize binary, and ensure it is ASCIIZ. */
    __CPROVER_havoc_object(binary);
    binary[sizeof(binary)-1] = 0;

    /* create the command instance. */
    return fido_config_command_create(cmd, binary);
}
