/**
 * \file user_context/fido_set_user_context.c
 *
 * \brief Set the user context to the given username and groupname.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/user_context.h>
#include <sys/types.h>
#include <login_cap.h>
#include <pwd.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * \brief Look up the password entry for a given user and group, and set the
 * group and user context.
 *
 * \note For now, we don't respect group override. TODO we will need to visit
 * this.
 *
 * \param username      The username for this operation.
 * \param groupname     The groupname for this operation.
 *
 * \returns 0 on success and non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_set_user_context(const char* username, const char* groupname)
{
    int retval;
    char* pwbuffer = NULL;
    struct passwd pwd;
    struct passwd* pw_result;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_set_user_context, username, groupname);

    /* TODO - ignore groupname for now. */
    (void)groupname;

    /* get the maximum password buffer size. */
    long getpw_size_max = sysconf(_SC_GETPW_R_SIZE_MAX);
    if (getpw_size_max < 0)
    {
        getpw_size_max = 16384;
    }

    /* allocate the passwd buffer. */
    pwbuffer = (char*)malloc(getpw_size_max);
    if (NULL == pwbuffer)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }

    /* get the password entry. */
    retval = getpwnam_r(username, &pwd, pwbuffer, getpw_size_max, &pw_result);
    if (0 != retval || NULL == pw_result)
    {
        retval = FIDO_ERROR_BAD_GETPWD;
        goto cleanup_pwbuffer;
    }

    /* switch to the user. */
    retval = setusercontext(
        NULL, pw_result, pw_result->pw_uid,
        LOGIN_SETGROUP | LOGIN_SETPATH | LOGIN_SETPRIORITY |
        LOGIN_SETRESOURCES | LOGIN_SETUMASK | LOGIN_SETUSER | LOGIN_SETENV);
    if (0 != retval)
    {
        retval = FIDO_ERROR_SET_USER_CONTEXT;
        goto cleanup_pwbuffer;
    }

    /* success. */
    retval = 0;
    goto cleanup_pwbuffer;

cleanup_pwbuffer:
    free(pwbuffer);

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_set_user_context, retval, username, groupname);

    return retval;
}
