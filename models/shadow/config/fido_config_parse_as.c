/**
 * \file models/shadow/config/fido_config_parse_as.c
 *
 * \brief fido_config_parse_as shadow impl.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>
#include <string.h>

#include "config/parser_internal.h"

int nondet_retval();

int random_as_type()
{
    int val = nondet_retval();
    enum fido_config_as_type ty = (enum fido_config_as_type)val;
    MODEL_ASSUME(__CPROVER_enum_is_in_range(ty));

    return val;
}

char* random_str()
{
    char str[10];
    __CPROVER_havoc_object(str);
    str[sizeof(str)-1] = 0;

    return strdup(str);
};

int FN_DECL_MUST_CHECK
fido_config_parse_as(
    char** str, int* type, fido_scanner* scanner)
{
    int retval;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_config_parse_as, str, type, scanner);

    *str = NULL;
    *type = 0;

    retval = nondet_retval();
    if (0 != retval)
    {
        enum fido_error_code ec = (enum fido_error_code)retval;
        MODEL_ASSUME(__CPROVER_enum_is_in_range(ec));
        goto done;
    }

    char* tmp_str = random_str();
    if (NULL == tmp_str)
    {
        retval = nondet_retval();
        enum fido_error_code ec = (enum fido_error_code)retval;
        MODEL_ASSUME(0 != retval && __CPROVER_enum_is_in_range(ec));
        goto done;
    }

    /* success. */
    retval = 0;
    *str = tmp_str;
    *type = random_as_type();
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_config_parse_as, retval, str, type, scanner);

    return retval;
}
