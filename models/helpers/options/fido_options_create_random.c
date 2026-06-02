/**
 * \file models/helpers/options/fido_options_create_random.c
 *
 * \brief Non-deterministic \ref fido_options create helper.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <string.h>

#include "options_helpers.h"

bool nondet_bool();
int nondet_int();

static char binary_name[8];
static char argument0[8];
static char argument1[8];
static char argument2[8];

static char* argv[3] = { argument0, argument1, argument2 };

char* choose_config_file_override()
{
    int retval = 0;
    char config_data[8];

    __CPROVER_havoc_object(config_data);
    config_data[sizeof(config_data)-1] = 0;

    retval = nondet_int();
    if (0 == retval)
    {
        return strdup(config_data);
    }
    else
    {
        return NULL;
    }
}

size_t nondet_size();

size_t choose_arguments_count()
{
    size_t size = nondet_size();
    if (size > 3)
        size = 3;
    return size;
}

int FN_DECL_MUST_CHECK
fido_options_create_random(fido_options** opts)
{
    char name[8];
    fido_options* tmp = NULL;

    tmp = (fido_options*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        *opts = NULL;
        return FIDO_ERROR_OUT_OF_MEMORY;
    }

    __CPROVER_havoc_object(binary_name);
    binary_name[sizeof(binary_name)-1] = 0;
    __CPROVER_havoc_object(argument0);
    argument0[sizeof(argument0)-1] = 0;
    __CPROVER_havoc_object(argument1);
    argument1[sizeof(argument1)-1] = 0;
    __CPROVER_havoc_object(argument2);
    argument2[sizeof(argument2)-1] = 0;

    char* bin = strdup(binary_name);
    if (NULL == bin)
    {
        free(tmp);
        *opts = NULL;
        return FIDO_ERROR_OUT_OF_MEMORY;
    }

    char* orig_bin = strdup(binary_name);
    if (NULL == orig_bin)
    {
        /* trim this branch of the decision tree. */
        MODEL_ASSUME(0);
    }

    tmp->dry_run = nondet_bool();
    tmp->config_file_override = choose_config_file_override();
    tmp->original_binary_name = orig_bin;
    tmp->binary_name = bin;
    tmp->arguments_count = choose_arguments_count();
    if (tmp->arguments_count > 0)
    {
        tmp->arguments = argv;
    }
    else
    {
        tmp->arguments = NULL;
    }

    *opts = tmp;
    return 0;
}
