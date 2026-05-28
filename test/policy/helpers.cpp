/**
 * \file test/policy/helpers.cpp
 *
 * \brief Helper methods for policy unit tests.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>
#include <string.h>

#include "helpers.h"

int fido_options_create_test(
    fido_options** opts, const char* binary_name, size_t arguments_count,
    const char** arguments)
{
    int retval;
    fido_options* tmp;

    tmp = (fido_options*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }

    /* set up tmp. */
    memset(tmp, 0, sizeof(*tmp));
    tmp->binary_name = strdup(binary_name);
    tmp->arguments_count = arguments_count;
    tmp->arguments = arguments;

    /* success. */
    retval = 0;
    *opts = tmp;
    goto done;

done:
    return retval;
}

int fido_user_create_test(
    fido_user** user, const char* username, const char* group1,
    const char* group2)
{
    int retval;
    fido_user* tmp;
    size_t gid_size, groupnames_size;

    tmp = (fido_user*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }

    memset(tmp, 0, sizeof(*tmp));

    tmp->username = strdup(username);
    if (NULL == tmp->username)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto cleanup_tmp;
    }

    tmp->group_count = 2;

    gid_size = tmp->group_count * sizeof(gid_t);
    tmp->gids = (gid_t*)malloc(gid_size);
    if (NULL == tmp->gids)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto cleanup_tmp;
    }
    tmp->gids[0] = 0;
    tmp->gids[1] = 1;

    groupnames_size = tmp->group_count * sizeof(char*);
    tmp->groupnames = (char**)malloc(groupnames_size);
    if (NULL == tmp->groupnames)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto cleanup_tmp;
    }
    tmp->groupnames[0] = NULL;
    tmp->groupnames[1] = NULL;

    tmp->groupnames[0] = strdup(group1);
    if (NULL == tmp->groupnames[0])
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto cleanup_tmp;
    }

    tmp->groupnames[1] = strdup(group2);
    if (NULL == tmp->groupnames[1])
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto cleanup_tmp;
    }

    retval = 0;
    *user = tmp;
    goto done;

cleanup_tmp:
    fido_user_release(tmp);

done:
    return retval;
}
