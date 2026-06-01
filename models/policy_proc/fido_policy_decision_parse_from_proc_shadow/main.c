/**
 * \file models/policy_proc/fido_policy_decision_parse_from_proc_shadow/main.c
 *
 * \brief Model checks for shadow implementation of
 * \ref fido_policy_decision_parse_from_proc.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/policy_proc.h>
#include <fcntl.h>

#include "../../helpers/options/options_helpers.h"
#include "../../shadow/unix/unix_shadow.h"

int main(int argc, char* argv[])
{
    int retval;
    fido_options* opts;
    fido_policy_decision* dec;

    unix_init();

    /* create options. */
    retval = fido_options_create_random(&opts);
    if (0 != retval)
    {
        /* trim this decision branch. */
        MODEL_ASSUME(0);
    }

    /* parse a policy decsion from a process. */
    retval = fido_policy_decision_parse_from_proc(&dec, opts);
    if (0 != retval)
    {
        goto cleanup_opts;
    }

    retval = 0;
    goto cleanup_dec;

cleanup_dec:
    fido_policy_decision_release(dec);

cleanup_opts:
    fido_options_release(opts);

done:
    return retval;
}
