/**
 * \file fido/user.h
 *
 * \brief Data structures and methods relating to a user.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <stddef.h>
#include <unistd.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief A \ref fido_user record holds the user name, user id, group names, and
 * group ids associated with a user.
 */
typedef struct fido_user fido_user;
struct fido_user
{
    uid_t uid;
    char* username;
    size_t group_count;
    gid_t* gids;
    char** groupnames;
};

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
