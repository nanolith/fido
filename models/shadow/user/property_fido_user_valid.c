/**
 * \file models/shadow/user/property_fido_user_valid.c
 *
 * \brief Model checking property to ensure that a fido user instance is valid.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/user.h>

/**
 * \brief Valid user record property.
 *
 * \param user          The user record to check.
 *
 * \returns true if the user record is valid.
 */
bool
property_fido_user_valid(
    const fido_user* user)
{
    MODEL_CHECK_OBJECT_READ(user, sizeof(*user));

    MODEL_ASSERT(NULL != user->username);
    MODEL_ASSERT(user->group_count > 0);
    MODEL_ASSERT(NULL != user->gids);
    MODEL_CHECK_OBJECT_READ(
        user->gids,
        user->group_count * sizeof(gid_t));
    MODEL_ASSERT(NULL != user->groupnames);
    MODEL_CHECK_OBJECT_READ(
        user->groupnames,
        user->group_count * sizeof(char*));
    size_t offset;
    MODEL_ASSUME(offset < user->group_count);
    MODEL_ASSERT(user->gids[offset] >= 0);
    MODEL_ASSERT(NULL != user->groupnames[offset]);

    return true;
}
