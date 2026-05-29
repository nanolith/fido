/**
 * \file models/sandbox/sandbox_enter/main.c
 *
 * \brief Model checks for \ref sandbox_enter.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/sandbox.h>

int main(int argc, char* argv[])
{
    int retval;

    /* enter sandbox. */
    retval = sandbox_enter();
    if (0 != retval)
    {
        goto done;
    }

done:
    return retval;
}
