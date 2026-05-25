/**
 * \file models/shadow/options/fido_options_parse.c
 *
 * \brief Shadow implementation of \ref fido_options_parse.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/options.h>

#include "../../helpers/options/options_helpers.h"

int FN_DECL_MUST_CHECK
fido_options_parse(fido_options** opts, int argc, const char** argv)
{
    return fido_options_create_random(opts);
}
