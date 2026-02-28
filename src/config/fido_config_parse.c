/**
 * \file config/fido_config_parse.c
 *
 * \brief Parse a fido config file.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>
#include <string.h>

#include "parser_internal.h"

/* forward decls. */
static int parse_role(fido_config* config, fido_scanner* scanner);

/**
 * \brief Parse config data into a \ref fido_config instance.
 *
 * \param config        Pointer to the config pointer to set to the created
 *                      instance on success.
 * \param input         The input string to parse.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
fido_config_parse(fido_config** config, const char* input)
{
    int retval, token;
    fido_token_details details;
    fido_config* tmp = NULL;
    fido_scanner* scanner = NULL;
    bool done_parsing = false;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_config_parse, config, input);

    /* create the config instance. */
    retval = fido_config_create(&tmp);
    if (0 != retval)
    {
        goto done;
    }

    /* create the scanner for input. */
    retval = fido_scanner_create(&scanner, input);
    if (0 != retval)
    {
        goto done;
    }

    /* begin parse loop. */
    while (!done_parsing)
    {
        token = fido_scanner_peek_token(&details, scanner);
        switch (token)
        {
            case FIDO_SCANNER_TOKEN_TYPE_EOF:
                done_parsing = true;
                break;

            case FIDO_SCANNER_TOKEN_TYPE_KEYWORD_ROLE:
                retval = parse_role(tmp, scanner);
                if (0 != retval)
                {
                    goto done;
                }
        }
    }

    /* finalize roles before continuing. */
    fido_config_roles_finalize(tmp);

    /* success. */
    retval = 0;
    *config = tmp;
    tmp = NULL;
    goto done;

done:
    if (NULL != scanner)
    {
        fido_scanner_release(scanner);
    }

    if (NULL != tmp)
    {
        fido_config_release(tmp);
    }

    if (0 != retval)
    {
        *config = NULL;
    }

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_parse, retval, config, input);

    return retval;
}

/**
 * \brief Parse a role, adding this role to the given config on success.
 *
 * \param config                The config to which this role is added on
 *                              success.
 * \param scanner               The scanner from which this role is read.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
static int parse_role(fido_config* config, fido_scanner* scanner)
{
    int retval;
    fido_config_role* tmp = NULL;

    /* attempt to parse a role. */
    retval = fido_config_parse_role(&tmp, scanner);
    if (0 != retval)
    {
        goto done;
    }

    /* Success: add this role to the config. */
    retval = 0;
    fido_config_add_role(config, tmp);
    goto done;

done:
    return retval;
}
