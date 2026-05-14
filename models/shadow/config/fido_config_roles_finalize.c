/**
 * \file models/shadow/config/fido_config_roles_finalize.c
 *
 * \brief This shadow form of \ref fido_config_roles_finalize is a no-op.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>

#include "config/parser_internal.h"

void
fido_config_roles_finalize(fido_config* config)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_config_roles_finalize, config);

    config->roles_finalized = true;

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(fido_config_roles_finalize, config);
}
