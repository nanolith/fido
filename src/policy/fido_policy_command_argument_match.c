/**
 * \file policy/fido_policy_command_argument_match.c
 *
 * \brief Check to see if a given argument matches its
 * \ref fido_config_command_argument counterpart.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/policy.h>
#include <string.h>

/* forward decls. */
static int match_prefix_wildcard_argument(
    const fido_config_command_argument* cmd_arg, const char* arg);
static int match_postfix_wildcard_argument(
    const fido_config_command_argument* cmd_arg, const char* arg);
static int match_argument(
    const fido_config_command_argument* cmd_arg, const char* arg);

/**
 * \brief Check to see if a given command argument matches the provided
 * argument.
 *
 * \param cmd_arg       The command argument to match.
 * \param arg           The argument for this match.
 *
 * \returns 0 on success (matched) and non-zero on failure (not matched).
 */
int FN_DECL_MUST_CHECK
fido_policy_command_argument_match(
    const fido_config_command_argument* cmd_arg, const char* arg)
{
    int retval;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_policy_command_argument_match, cmd_arg, arg);

    /* decode command argument. */
    switch (cmd_arg->argument_type)
    {
        case FIDO_CONFIG_ARGUMENT_TYPE_WILDCARD:
            retval = 0;
            break;

        case FIDO_CONFIG_ARGUMENT_TYPE_PREFIX_WILDCARD:
            retval = match_prefix_wildcard_argument(cmd_arg, arg);
            break;

        case FIDO_CONFIG_ARGUMENT_TYPE_POSTFIX_WILDCARD:
            retval = match_postfix_wildcard_argument(cmd_arg, arg);
            break;

        case FIDO_CONFIG_ARGUMENT_TYPE_VERBATIM:
            retval = match_argument(cmd_arg, arg);
            break;

        default:
            retval = FIDO_ERROR_POLICY_MATCH;
            break;
    }

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_policy_command_argument_match, retval, cmd_arg, arg);

    return retval;
}

/**
 * \brief Perform a basic exact match on an argument.
 *
 * \param cmd_arg       The command argument to match.
 * \param arg           The argument for this match.
 *
 * \returns 0 on success (matched) and non-zero on failure (not matched).
 */
static int match_argument(
    const fido_config_command_argument* cmd_arg, const char* arg)
{
    if (0 != strcmp(cmd_arg->argument_match, arg))
    {
        return FIDO_ERROR_POLICY_MATCH;
    }

    return 0;
}

/**
 * \brief Match the end of an argument with a matcher.
 *
 * \param cmd_arg       The command argument to match.
 * \param arg           The argument for this match.
 *
 * \returns 0 on success (matched) and non-zero on failure (not matched).
 */
static int match_prefix_wildcard_argument(
    const fido_config_command_argument* cmd_arg, const char* arg)
{
    size_t arglen = strlen(arg);
    size_t matchlen = strlen(cmd_arg->argument_match);

    /* if the arg length is less than the match length, they can't match. */
    if (arglen < matchlen)
    {
        return FIDO_ERROR_POLICY_MATCH;
    }

    /* calculate the argument offset. */
    size_t offset = arglen - matchlen;

    /* If the ends of these strings don't match, then the match fails. */
    if (strcmp(arg + offset, cmd_arg->argument_match))
    {
        return FIDO_ERROR_POLICY_MATCH;
    }

    return 0;
}

/**
 * \brief Match the beginning of an argument with a matcher.
 *
 * \param cmd_arg       The command argument to match.
 * \param arg           The argument for this match.
 *
 * \returns 0 on success (matched) and non-zero on failure (not matched).
 */
static int match_postfix_wildcard_argument(
    const fido_config_command_argument* cmd_arg, const char* arg)
{
    size_t matchlen = strlen(cmd_arg->argument_match);

    /* if the beginnings of these strings don't match, then the match fails. */
    if (strncmp(arg, cmd_arg->argument_match, matchlen))
    {
        return FIDO_ERROR_POLICY_MATCH;
    }

    return 0;
}
