/**
 * \file config/fido_config_parse_command_arguments.c
 *
 * \brief Parse command arguments from the command string.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>
#include <string.h>

#include "parser_internal.h"

/* forward decls. */
static int parse_argument(
    fido_config_command* cmd, char* arg);
static bool argument_matches_prefix_wildcard(const char* arg);
static bool argument_matches_postfix_wildcard(const char* arg);
static bool argument_has_unbalanced_wildcards(const char* arg);

/**
 * \brief Parse command arguments, adding them to the given command.
 *
 * \param cmd           The command for this operation.
 * \param str           The string containing command arguments, separated by
 *                      spaces.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
fido_config_parse_command_arguments(
    fido_config_command* cmd, char* str)
{
    int retval;
    char* arg;
    bool has_wildcard = false;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_config_parse_command_arguments, cmd, str);

    while (NULL != str)
    {
        arg = strsep(&str, " ");
        if (NULL != arg && 0 != arg[0])
        {
            retval = parse_argument(cmd, arg);
            if (0 != retval)
            {
                goto done;
            }

            /* if this argument is a wildcard... */
            if (FIDO_CONFIG_ARGUMENT_TYPE_WILDCARD
                    == cmd->head->argument_type)
            {
                /* multiple wildcards aren't supported. */
                if (has_wildcard)
                {
                    retval = FIDO_ERROR_MULTIPLE_WILDCARD_ARGUMENTS;
                    goto done;
                }
                else
                {
                    has_wildcard = true;
                }
            }
            /* if a wildcard already exists. */
            else if (has_wildcard)
            {
                retval = FIDO_ERROR_ARGUMENT_AFTER_WILDCARD;
                goto done;
            }
        }
    }

    /* finalize command. */
    fido_config_command_arguments_finalize(cmd);
    retval = 0;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_parse_command_arguments, retval, cmd, str);

    return retval;
}

/**
 * \brief Parse an argument, adding it to the command.
 *
 * \param cmd                   The command to which this argument is added.
 * \param arg                   The argument to resolve.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
static int parse_argument(
    fido_config_command* cmd, char* arg)
{
    int retval;
    fido_config_command_argument* tmp;

    /* general wildcard. */
    if (!strcmp(arg, "\001"))
    {
        retval =
            fido_config_command_argument_create(
                &tmp, FIDO_CONFIG_ARGUMENT_TYPE_WILDCARD, "");
    }
    /* argument prefix wildcard. */
    else if (argument_matches_prefix_wildcard(arg))
    {
        retval =
            fido_config_command_argument_create(
                &tmp, FIDO_CONFIG_ARGUMENT_TYPE_PREFIX_WILDCARD, arg+1);
    }
    /* argument postfix wildcard. */
    else if (argument_matches_postfix_wildcard(arg))
    {
        /* calculate the postfix location. */
        size_t len = strlen(arg);
        if (len <= 1)
        {
            retval = FIDO_ERROR_INVALID_STRING;
            goto done;
        }

        /* truncate this postfix. */
        arg[len - 1] = 0;

        retval =
            fido_config_command_argument_create(
                &tmp, FIDO_CONFIG_ARGUMENT_TYPE_POSTFIX_WILDCARD, arg);
    }
    /* argument has unbalanced wildcards. */
    else if (argument_has_unbalanced_wildcards(arg))
    {
        retval = FIDO_ERROR_BAD_WILDCARD;
    }
    /* verbatim argument. */
    else
    {
        retval =
            fido_config_command_argument_create(
                &tmp, FIDO_CONFIG_ARGUMENT_TYPE_VERBATIM, arg);
    }

    /* exit if argument creation failed. */
    if (0 != retval)
    {
        goto done;
    }

    /* success. */
    fido_config_command_add_argument(cmd, tmp);
    retval = 0;
    goto done;

done:
    return retval;
}

/**
 * \brief Return true if the first character matches the argument wildcard and
 * no other characters match either wildcard.
 *
 * \param arg           The argument to check.
 *
 * \returns true if the first character is the argument wildcard.
 */
static bool argument_matches_prefix_wildcard(const char* arg)
{
    /* only continue if the first character is the prefix. */
    if (2 != *arg)
        return false;

    /* skip past the prefix. */
    ++arg;

    /* verify this is the only wildcard character. */
    while (0 != *arg)
    {
        if (1 == *arg || 2 == *arg)
            return false;

        ++arg;
    }

    return true;
}

/**
 * \brief Return true if the last character matches the argument wildcard and
 * no other characters match either wildcard.
 *
 * \param arg           The argument to check.
 *
 * \returns true if the last character is the argument wildcard.
 */
static bool argument_matches_postfix_wildcard(const char* arg)
{
    size_t arg_wildcard_count = 0;

    /* iterate over the string. */
    while (0 != *arg)
    {
        if (1 == *arg)
            return false;

        if (2 == *arg)
            ++arg_wildcard_count;

        ++arg;
    }

    /* if the arg wildcard count isn't 1, this is an invalid string. */
    if (arg_wildcard_count != 1)
        return false;

    /* verify that the last character is the arg wildcard. */
    if (2 != *(arg - 1))
        return false;

    /* all checks pass. */
    return true;
}

/**
 * \brief Return true if any wildcard characters are detected.
 *
 * This is a catch-all for cases where there are unbalanced argument wildcards.
 *
 * \param arg           The argument to check.
 *
 * \returns true if any wildcard characters are detected and false otherwise.
 */
static bool argument_has_unbalanced_wildcards(const char* arg)
{
    while (0 != *arg)
    {
        if (1 == *arg || 2 == *arg)
            return true;

        ++arg;
    }

    return false;
}
