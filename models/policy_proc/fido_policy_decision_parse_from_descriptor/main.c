/**
 * \file models/policy_proc/fido_policy_decision_parse_from_descriptor/main.c
 *
 * \brief Model checks for \ref fido_policy_decision_parse_from_descriptor.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/policy_proc.h>
#include <fcntl.h>

#include "../../shadow/unix/unix_shadow.h"

int main(int argc, char* argv[])
{
    int retval, fd;
    fido_policy_decision* dec;

    unix_init();

    /* open descriptor. */
    fd = open("foo.txt", O_RDONLY);
    if (fd < 0)
    {
        /* trim this decision branch. */
        MODEL_ASSUME(0);
    }

    /* parse a policy decsion from a descriptor. */
    retval = fido_policy_decision_parse_from_descriptor(&dec, fd);
    if (0 != retval)
    {
        goto done;
    }

    retval = 0;
    goto cleanup_dec;

cleanup_dec:
    fido_policy_decision_release(dec);

done:
    close(fd);

    return retval;
}
