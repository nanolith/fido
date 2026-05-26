/**
 * \file user/fido_user_release.c
 *
 * \brief Release a user instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/user.h>
#include <stdlib.h>

/**
 * \brief Release a \ref fido_user instance.
 *
 * \param user          The user record to release.
 */
void fido_user_release(fido_user* user)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_user_release, user);

    /* free username if set. */
    if (NULL != user->username)
    {
        free(user->username);
    }

    /* free gids if set. */
    if (NULL != user->gids)
    {
        free(user->gids);
    }

    /* free groupnames if set. */
    if (NULL != user->groupnames)
    {
        for (size_t i = 0; i < user->group_count; ++i)
        {
            if (NULL != user->groupnames[i])
            {
                free(user->groupnames[i]);
            }
        }

        free(user->groupnames);
    }

    /* free user instance. */
    free(user);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(fido_user_release, NULL);
}
