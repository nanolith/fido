/**
 * \file models/shadow/config/fido_config_parse_role_shadow_sink.c
 *
 * \brief Shadow and sink impl of \ref fido_config_parse_role.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "../../helpers/config/config_helpers.h"
#include "config/parser_internal.h"

/**
 * \brief Parse a role instance from a config stream.
 *
 * \param role          Pointer to the pointer to store the role instance on
 *                      success.
 * \param scanner       The scanner to use to parse this as expression.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
fido_config_parse_role(
    fido_config_role** role, fido_scanner* scanner)
{
    int retval, token;
    fido_token_details details;
    fido_config_role* tmp_role = NULL;
    char* name = NULL;
    bool done_parsing = false;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_config_parse_role, role, scanner);

    retval = fido_config_role_create_random(role);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_parse_role, retval, role, scanner);

    return retval;
}
