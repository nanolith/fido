/**
 * \file user/fido_user_create.c
 *
 * \brief Create a user instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/user.h>
#include <grp.h>
#include <limits.h>
#include <pwd.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * \brief Create a \ref fido_user instance by examining the system.
 *
 * \param user          Pointer to the user record pointer to populate with
 *                      the created user record on success.
 *
 * \returns 0 on success and non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_user_create(fido_user** user)
{
    int retval;
    fido_user* tmp = NULL;
    char* grbuffer = NULL;
    struct group grp;
    struct group* gr_result;
    struct passwd pwd;
    struct passwd* pw_result;

    /* get the max number of supplementary groups. */
    long ngroups_max = sysconf(_SC_NGROUPS_MAX);
    if (ngroups_max < 0 || ngroups_max > INT_MAX)
    {
        retval = FIDO_ERROR_BAD_SYSCONF;
        goto done;
    }

    /* get the maximum group buffer size. */
    long getgr_size_max = sysconf(_SC_GETGR_R_SIZE_MAX);
    if (getgr_size_max < 0)
    {
        getgr_size_max = 16384;
    }

    /* get the maximum password buffer size. */
    long getpw_size_max = sysconf(_SC_GETPW_R_SIZE_MAX);
    if (getpw_size_max < 0)
    {
        getpw_size_max = 16384;
    }

    /* if the password size is greater, use it. */
    if (getpw_size_max > getgr_size_max)
    {
        getgr_size_max = getpw_size_max;
    }

    /* allocate the group buffer. */
    grbuffer = (char*)malloc(getgr_size_max);
    if (NULL == grbuffer)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }

    /* allocate memory for the fido user instance. */
    tmp = (fido_user*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }
    memset(tmp, 0, sizeof(*tmp));

    /* get the user id. */
    tmp->uid = getuid();

    /* allocate memory for the group ids. */
    size_t gids_size = sizeof(gid_t) * (ngroups_max + 1);
    tmp->gids = (gid_t*)malloc(gids_size);
    if (NULL == tmp->gids)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }
    memset(tmp->gids, 0, gids_size);

    /* get the supplementary groups. */
    int ngroups = getgroups(ngroups_max, tmp->gids);
    if (ngroups < 0)
    {
        retval = FIDO_ERROR_BAD_GETGROUPS;
        goto done;
    }

    /* save the primary group. */
    tmp->gids[ngroups] = getgid();

    /* save the group count. */
    tmp->group_count = ngroups + 1;

    /* allocate memory for the group names. */
    size_t groupnames_size = sizeof(char*) * tmp->group_count;
    tmp->groupnames = (char**)malloc(groupnames_size);
    if (NULL == tmp->groupnames)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }
    memset(tmp->groupnames, 0, groupnames_size);

    /* get the group name for each group id. */
    for (size_t i = 0; i < tmp->group_count; ++i)
    {
        retval =
            getgrgid_r(
                tmp->gids[i], &grp, grbuffer, getgr_size_max, &gr_result);
        if (0 != retval || NULL == gr_result)
        {
            retval = FIDO_ERROR_BAD_GETGROUPS;
            goto done;
        }

        char* groupname = strdup(gr_result->gr_name);
        if (NULL == groupname)
        {
            retval = FIDO_ERROR_OUT_OF_MEMORY;
            goto done;
        }

        tmp->groupnames[i] = groupname;
    }

    /* get the password entry. */
    retval = getpwuid_r(tmp->uid, &pwd, grbuffer, getgr_size_max, &pw_result);
    if (0 != retval || NULL == pw_result)
    {
        retval = FIDO_ERROR_BAD_GETPWD;
        goto done;
    }

    /* save the username. */
    tmp->username = strdup(pw_result->pw_name);
    if (NULL == tmp->username)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }

    /* success. */
    retval = 0;
    *user = tmp;
    tmp = NULL;
    goto done;

done:
    if (NULL != tmp)
    {
        fido_user_release(tmp);
    }

    if (NULL != grbuffer)
    {
        free(grbuffer);
    }

    if (0 != retval)
    {
        *user = NULL;
    }

    return retval;
}
