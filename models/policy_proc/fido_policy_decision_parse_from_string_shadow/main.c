 /**
 * \file models/policy_proc/fido_policy_decision_parse_from_string_shadow/main.c
 *
 * \brief Model checks for the shadow implementation of
 * \ref fido_policy_decision_parse_from_string.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/policy_proc.h>

static char decisionstr[8];

extern size_t strsep_max_runs;

const char* choose_decisionstr()
{
    __CPROVER_havoc_object(decisionstr);
    decisionstr[sizeof(decisionstr)-1]=0;

    return decisionstr;
}

int main(int argc, char* argv[])
{
    int retval;
    fido_policy_decision* dec;

    strsep_max_runs = 7;

    /* parse a policy string. */
    retval = fido_policy_decision_parse_from_string(&dec, choose_decisionstr());
    if (0 != retval)
    {
        goto done;
    }

    retval = 0;
    goto cleanup_dec;

cleanup_dec:
    fido_policy_decision_release(dec);

done:
    return retval;
}
