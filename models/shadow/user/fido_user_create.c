/**
 * \file models/shadow/user/fido_user_create.c
 *
 * \brief Shadow implementation of \ref fido_user_create.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "../../helpers/user/user_helpers.h"

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

    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_user_create, user);

    retval = fido_user_create_random(user);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(fido_user_create, retval, user);

    return retval;    
}
