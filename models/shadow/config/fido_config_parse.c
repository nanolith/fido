/**
 * \file models/shadow/config/fido_config_parse.c
 *
 * \brief Shadow implementation of \ref fido_config_parse.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "../../helpers/config/config_helpers.h"
#include "config/parser_internal.h"

int FN_DECL_MUST_CHECK
fido_config_parse(fido_config** config, const char* input)
{
    int retval;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_config_parse, config, input);

    retval = fido_config_create_random(config);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_parse, retval, config, input);

    return retval;
}
