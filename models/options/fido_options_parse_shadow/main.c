/**
 * \file models/options/fido_options_parse_shadow/main.c
 *
 * \brief Model checks for the \ref fido_options_parse shadow method.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/options.h>

#include "../../helpers/options/options_helpers.h"

static char argument0[8];
static char argument1[8];
static char argument2[8];

static char* argvec[3] = {argument0, argument1, argument2};

int main(int argc, char* argv[])
{
    int retval;
    fido_options* opts;

    __CPROVER_havoc_object(argument0);
    argument0[sizeof(argument0)-1] = 0;
    __CPROVER_havoc_object(argument1);
    argument1[sizeof(argument1)-1] = 0;
    __CPROVER_havoc_object(argument2);
    argument2[sizeof(argument2)-1] = 0;

    MODEL_ASSUME(argc >= 0 && argc <= 3);

    /* parse options. */
    retval = fido_options_parse(&opts, argc, argvec);
    if (0 != retval)
    {
        goto done;
    }

    /* release the options instance. */
    fido_options_release(opts);
    retval = 0;

done:
    return retval;
}
