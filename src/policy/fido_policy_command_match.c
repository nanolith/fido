/**
 * \file policy/fido_policy_command_match.c
 *
 * \brief Check to see if a given command matches command-line options.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/policy.h>
#include <string.h>

/**
 * \brief Check to see if a given command matches the provided options.
 *
 * \param cmd           The command to match.
 * \param opts          The options for this match.
 *
 * \returns 0 on success (matched) and non-zero on failure (not matched).
 */
int FN_DECL_MUST_CHECK
fido_policy_command_match(
    const fido_config_command* cmd, const fido_options* opts)
{
    int retval;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_policy_command_match, cmd, opts);

    /* the options binary and command binary must match. */
    if (strcmp(cmd->binary, opts->binary_name))
    {
        retval = FIDO_ERROR_POLICY_MATCH;
        goto done;
    }

    /* get the first command argument. */
    fido_config_command_argument* arg = cmd->head;

    /* if the first argument matcher is a wildcard, and the argument count is 0,
     * then this matches. */
    if (
        NULL != arg && FIDO_CONFIG_ARGUMENT_TYPE_WILDCARD == arg->argument_type 
     && 0 == opts->arguments_count)
    {
        retval = 0;
        goto done;
    }

    /* loop over arguments. */
    for (size_t i = 0; i < opts->arguments_count; ++i, arg = arg->next)
    {
        /* we ran out of argument matchers. */
        if (NULL == arg)
        {
            retval = FIDO_ERROR_POLICY_MATCH;
            goto done;
        }

        /* do the arguments match? */
        retval = fido_policy_command_argument_match(arg, opts->arguments[i]);
        if (0 != retval)
        {
            goto done;
        }

        /* if this is a wildcard argument, the match succeeds. */
        if (FIDO_CONFIG_ARGUMENT_TYPE_WILDCARD == arg->argument_type)
        {
            retval = 0;
            goto done;
        }
    }

    /* if there are still arguments to match, this fails. */
    if (NULL != arg)
    {
        retval = FIDO_ERROR_POLICY_MATCH;
        goto done;
    }

    /* if all arguments and matchers are exhausted, this command matches. */
    retval = 0;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_policy_command_match, retval, cmd, opts);

    return retval;
}
