/**
 * \file models/options/fido_options_release/main.c
 *
 * \brief Model checks for \ref fido_options_release.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/options.h>

#include "../../helpers/options/options_helpers.h"

int main(int argc, char* argv[])
{
    int retval;
    fido_options* opts;

    /* create the options instance. */
    retval = fido_options_create_random(&opts);
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
