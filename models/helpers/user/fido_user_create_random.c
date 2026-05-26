/**
 * \file models/helpers/user/fido_user_create_random.c
 *
 * \brief Non-deterministic \ref fido_user create helper.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>
#include <string.h>

#include "user_helpers.h"

uid_t nondet_uid();
gid_t nondet_gid();
size_t nondet_size();

static uid_t choose_uid()
{
    uid_t val = nondet_uid();
    MODEL_ASSUME(val >= 0);

    return val;
}

static gid_t choose_gid()
{
    gid_t val = nondet_gid();
    MODEL_ASSUME(val >= 0);

    return val;
}

static size_t choose_group_count()
{
    size_t val = nondet_size();
    MODEL_ASSUME(val > 0 && val <= 3);

    return val; 
}

int FN_DECL_MUST_CHECK
fido_user_create_random(fido_user** user)
{
    int retval;
    char username[8];
    char group0[8];
    char group1[8];
    char group2[8];
    fido_user* tmp = NULL;

    /* initialize string fields. */
    __CPROVER_havoc_object(username);
    username[sizeof(username)-1] = 0;
    __CPROVER_havoc_object(group0);
    group0[sizeof(group0)-1] = 0;
    __CPROVER_havoc_object(group1);
    group1[sizeof(group1)-1] = 0;
    __CPROVER_havoc_object(group2);
    group2[sizeof(group2)-1] = 0;

    tmp = (fido_user*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }
    memset(tmp, 0, sizeof(*tmp));

    tmp->uid = choose_uid();
    tmp->username = strdup(username);
    if (NULL == tmp->username)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }

    tmp->group_count = choose_group_count();

    tmp->gids = (gid_t*)malloc(tmp->group_count * sizeof(gid_t));
    if (NULL == tmp->gids)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }

    for (size_t i = 0; i < tmp->group_count; ++i)
    {
        tmp->gids[i] = choose_gid();
    }

    tmp->groupnames = (char**)malloc(tmp->group_count * sizeof(char*));
    if (NULL == tmp->groupnames)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }
    memset(tmp->groupnames, 0, tmp->group_count * sizeof(char*));
    if (tmp->group_count > 0)
    {
        tmp->groupnames[0] = strdup(group0);
        MODEL_ASSUME(NULL != tmp->groupnames[0]);
    }
    if (tmp->group_count > 1)
    {
        tmp->groupnames[1] = strdup(group1);
        MODEL_ASSUME(NULL != tmp->groupnames[1]);
    }
    if (tmp->group_count > 2)
    {
        tmp->groupnames[2] = strdup(group2);
        MODEL_ASSUME(NULL != tmp->groupnames[2]);
    }

    *user = tmp;
    tmp = NULL;
    retval = 0;
    goto done;

done:
    if (NULL != tmp)
    {
        fido_user_release(tmp);
    }

    if (0 != retval)
    {
        *user = NULL;
    }

    return retval;
}
