/**
 * \file models/user/fido_user_release/main.c
 *
 * \brief Model checks for \ref fido_user_release.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/options.h>

#include "../../helpers/user/user_helpers.h"

int main(int argc, char* argv[])
{
    int retval;
    fido_user* user;

    /* create the user instance. */
    retval = fido_user_create_random(&user);
    if (0 != retval)
    {
        goto done;
    }

    /* release the user instance. */
    fido_user_release(user);
    retval = 0;

done:
    return retval;
}
