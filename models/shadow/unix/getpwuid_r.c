/**
 * \file models/shadow/unix/getpwuid_r.c
 *
 * \brief Fido specific shadow method for getpwuid_r.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/model_assert.h>
#include <pwd.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

int nondet_retval();
uid_t nondet_uid();

uid_t choose_uid()
{
    uid_t val = nondet_uid();
    MODEL_ASSUME(val >= 0 && val < INT16_MAX);

    return val;
}

char name[8];
char home[8];
char shell[8];

int
getpwuid_r(
    gid_t gid, struct passwd *pwd, char *buffer, size_t bufsize,
    struct passwd **result)
{
    int retval = nondet_retval();

    if (0 == retval)
    {
        if (0 == nondet_retval())
        {
            __CPROVER_havoc_object(name);
            name[sizeof(name)-1] = 0;
            __CPROVER_havoc_object(home);
            home[sizeof(home)-1] = 0;
            __CPROVER_havoc_object(shell);
            shell[sizeof(shell)-1] = 0;

            *result = pwd;
            memset(pwd, 0, sizeof(*pwd));
            pwd->pw_uid = choose_uid();
            pwd->pw_name = name;
            pwd->pw_shell = shell;
            pwd->pw_dir = home;
        }
        else
        {
            *result = NULL;
        }
    }

    return retval;
}
