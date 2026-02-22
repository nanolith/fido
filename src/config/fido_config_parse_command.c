/**
 * \file config/fido_config_parse_command.c
 *
 * \brief Parse a command from the input scanner.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>
#include <string.h>

#include "parser_internal.h"

/* forward decls. */
static int extract_command_string(
    char** command_string, fido_token_details* details, fido_scanner* scanner);
static int resolve_escape(char* resolved, char input);
static int parse_argument(
    fido_config_command* cmd, char* arg);
static bool argument_matches_prefix_wildcard(const char* arg);
static bool argument_matches_postfix_wildcard(const char* arg);
static bool argument_has_unbalanced_wildcards(const char* arg);

/**
 * \brief Parse a command statement into a \ref fido_config_command instance.
 *
 * \param cmd           Pointer to the command pointer to set to the created
 *                      instance on success.
 * \param scanner       The scanner to use to parse this command.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
fido_config_parse_command(
    fido_config_command** cmd, fido_scanner* scanner)
{
    int retval, token;
    fido_token_details details;
    char* arg;
    char* tmp;
    char* command_string = NULL;
    fido_config_command* tmp_cmd = NULL;
    bool has_wildcard = false;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_config_parse_command, cmd, scanner);

    /* read the cmd token. */
    token = fido_scanner_read_token(&details, scanner);
    if (FIDO_SCANNER_TOKEN_TYPE_EOF == token)
    {
        retval = FIDO_ERROR_UNEXPECTED_EOF;
        goto error_exit;
    }
    else if (FIDO_SCANNER_TOKEN_TYPE_KEYWORD_CMD != token)
    {
        retval = FIDO_ERROR_UNEXPECTED_TOKEN;
        goto error_exit;
    }

    /* read the command string. */
    token = fido_scanner_read_token(&details, scanner);
    if (FIDO_SCANNER_TOKEN_TYPE_EOF == token)
    {
        retval = FIDO_ERROR_UNEXPECTED_EOF;
        goto error_exit;
    }
    else if (FIDO_SCANNER_TOKEN_TYPE_STRING != token)
    {
        retval = FIDO_ERROR_UNEXPECTED_TOKEN;
        goto error_exit;
    }

    /* extract the command string. */
    retval = extract_command_string(&command_string, &details, scanner);
    if (0 != retval)
    {
        goto error_exit;
    }

    /* extract the binary from the string. */
    tmp = command_string;
    arg = strsep(&tmp, " ");
    if (NULL == arg || 0 == arg[0])
    {
        retval = FIDO_ERROR_INVALID_COMMAND;
        goto error_exit;
    }

    /* create command instance. */
    retval = fido_config_command_create(&tmp_cmd, arg);
    if (0 != retval)
    {
        goto error_exit;
    }

    /* read additional arguments. */
    while (NULL != tmp)
    {
        arg = strsep(&tmp, " ");
        if (NULL != arg && 0 != arg[0])
        {
            retval = parse_argument(tmp_cmd, arg);
            if (0 != retval)
            {
                goto error_exit;
            }

            if (FIDO_CONFIG_ARGUMENT_TYPE_WILDCARD
                    == tmp_cmd->head->argument_type)
            {
                if (has_wildcard)
                {
                    retval = FIDO_ERROR_MULTIPLE_WILDCARD_ARGUMENTS;
                    goto error_exit;
                }
                else
                {
                    has_wildcard = true;
                }
            }
            else if (has_wildcard)
            {
                retval = FIDO_ERROR_ARGUMENT_AFTER_WILDCARD;
                goto error_exit;
            }
        }
    }

    /* finalize command. */
    fido_config_command_arguments_finalize(tmp_cmd);

    /* success. */
    retval = 0;
    *cmd = tmp_cmd;
    tmp_cmd = NULL;
    goto done;

error_exit:
    *cmd = NULL;

done:
    if (NULL != command_string)
    {
        free(command_string);
    }

    if (NULL != tmp_cmd)
    {
        fido_config_command_release(tmp_cmd);
    }

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_parse_command, retval, cmd, scanner);

    return retval;
}

/**
 * \brief Extract a command string, and resolve any escape sequences.
 *
 * \param command_string            Pointer to the character pointer to hold the
 *                                  extracted command string on success.
 * \param details                   The token details used for extracting this
 *                                  string.
 * \param scanner                   The scanner used for extracting this string.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
static int extract_command_string(
    char** command_string, fido_token_details* details, fido_scanner* scanner)
{
    int retval;
    char ch;
    char* tmp;
    char* output;
    size_t string_len = (details->end_index - details->begin_index) + 2;
    const char* input = scanner->original_input;
    input += details->begin_index;

    /* The string length should include the two quotes at the beginning and
     * end. */
    if (string_len <= 2)
    {
        retval = FIDO_ERROR_BAD_LENGTH;
        goto done;
    }

    /* skip the begin quote. */
    input += 1;
    string_len -= 1;

    /* skip the end quote. */
    string_len -= 1;

    MODEL_ASSERT(string_len > 0);

    /* allocate memory for the string. */
    tmp = malloc(string_len);
    if (NULL == tmp)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }

    /* copy over the string. */
    size_t content_length = string_len - 1;
    output = tmp;
    for (size_t i = 0; i < content_length; ++i)
    {
        switch (input[i])
        {
            /* we reserve SOH and STX for full wildcard and partial wildcard. */
            case 1:
            case 2:
                retval = FIDO_ERROR_INVALID_STRING;
                goto cleanup_tmp;

            case '\\':
                if (i + 1 < content_length)
                {
                    retval = resolve_escape(&ch, input[i+1]);
                    if (0 != retval)
                    {
                        goto cleanup_tmp;
                    }

                    *output++ = ch;
                    ++i;
                }
                else
                {
                    retval = FIDO_ERROR_INVALID_STRING;
                    goto cleanup_tmp;
                }
                break;

            case '*':
                *output++ = 1;
                break;

            case '%':
                *output++ = 2;
                break;

            default:
                *output++ = input[i];
                break;
        }
    }

    /* ASCIIZ the string. */
    *output = 0;

    /* success. */
    *command_string = tmp;
    retval = 0;
    goto done;

cleanup_tmp:
    free(tmp);

done:
    return retval;
}

/**
 * \brief Resolve an escape character.
 *
 * \param resolved              Pointer to hold the resolved character on
 *                              success.
 * \param input                 Input character to resolve.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
static int resolve_escape(char* resolved, char input)
{
    switch (input)
    {
        /* these are all just literal escapes. */
        case '*':
        case '%':
        case '"':
        case '\\':
            *resolved = input;
            return 0;

        case 'f':
            *resolved = '\f';
            return 0;

        case 'n':
            *resolved = '\n';
            return 0;

        case 'r':
            *resolved = '\r';
            return 0;

        case 't':
            *resolved = '\t';
            return 0;

        case 'v':
            *resolved = '\v';
            return 0;

        default:
            return FIDO_ERROR_INVALID_STRING_ESCAPE;
    }
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
    /* argument hsa unbalanced wildcards. */
    else if (argument_has_unbalanced_wildcards(arg))
    {
        retval = FIDO_ERROR_INVALID_STRING;
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
