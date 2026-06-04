/**
 * \file user/fido_user_create_from_username.c
 *
 * \brief Create a user instance from a username.
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
 * \brief Create a \ref fido_user instance by querying the password database for
 * a user by username.
 *
 * \param user          Pointer to the user record pointer to populate with
 *                      the created user record on success.
 * \param username      The username to use for the query.
 *
 * \returns 0 on success and non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_user_create_from_username(fido_user** user, const char* username)
{
    int retval;
    fido_user* tmp = NULL;
    char* pwbuffer = NULL;
    struct group grp;
    struct group* gr_result;
    struct passwd pwd;
    struct passwd* pw_result;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_user_create_from_username, user, username);

    /* get the maximum password buffer size. */
    long getpw_size_max = sysconf(_SC_GETPW_R_SIZE_MAX);
    if (getpw_size_max < 0)
    {
        getpw_size_max = 16384;
    }

    /* allocate the passwor buffer. */
    pwbuffer = (char*)malloc(getpw_size_max);
    if (NULL == pwbuffer)
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
    /* TODO - CBMC requires these redundant assignments. */
    tmp->username = NULL;
    tmp->groupnames = NULL;
    tmp->gids = NULL;

    /* get the password entry. */
    retval = getpwnam_r(username, &pwd, pwbuffer, getpw_size_max, &pw_result);
    if (0 != retval || NULL == pw_result)
    {
        retval = FIDO_ERROR_BAD_GETPWD;
        goto done;
    }

    /* save the uid. */
    tmp->uid = pw_result->pw_uid;

    /* save the username. */
    tmp->username = strdup(pw_result->pw_name);
    if (NULL == tmp->username)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }

    /* save the home directory. */
    tmp->home = strdup(pw_result->pw_dir);
    if (NULL == tmp->home)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }

    /* save the shell. */
    tmp->shell = strdup(pw_result->pw_shell);
    if (NULL == tmp->shell)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }

    /* allocate memory for the group ids. */
    size_t gids_size = sizeof(gid_t);
    tmp->gids = (gid_t*)malloc(gids_size);
    if (NULL == tmp->gids)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }
    memset(tmp->gids, 0, gids_size);

    /* save the primary group. */
    tmp->gids[0] = pw_result->pw_gid;

    /* save the group count. */
    tmp->group_count = 1;

    /* allocate memory for the group names. */
    size_t groupnames_size = sizeof(char*);
    tmp->groupnames = (char**)malloc(groupnames_size);
    if (NULL == tmp->groupnames)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }
    memset(tmp->groupnames, 0, groupnames_size);
    tmp->groupnames[0] = NULL;

    /* query the name of the primary group. */
    retval =
        getgrgid_r(tmp->gids[0], &grp, pwbuffer, getpw_size_max, &gr_result);
    if (0 != retval || NULL == gr_result)
    {
        retval = FIDO_ERROR_BAD_GETGROUPS;
        goto done;
    }

    /* set the group name. */
    char* groupname = strdup(gr_result->gr_name);
    if (NULL == groupname)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }
    tmp->groupnames[0] = groupname;

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

    if (NULL != pwbuffer)
    {
        free(pwbuffer);
    }

    if (0 != retval)
    {
        *user = NULL;
    }

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_user_create_from_username, retval, user, username);

    return retval;
}
