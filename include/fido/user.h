/**
 * \file fido/user.h
 *
 * \brief Data structures and methods relating to a user.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <fido/error_codes.h>
#include <fido/function_contracts.h>
#include <fido/function_decl.h>
#include <fido/model_assert.h>
#include <stdbool.h>
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
    char* home;
    char* shell;
    size_t group_count;
    gid_t* gids;
    char** groupnames;
};

/******************************************************************************/
/* Start of model checking properties.                                        */
/******************************************************************************/

/**
 * \brief Valid user record property.
 *
 * \param user          The user record to check.
 *
 * \returns true if the user record is valid.
 */
bool
property_fido_user_valid(
    const fido_user* user);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Create a \ref fido_user instance by examining the system.
 *
 * \param user          Pointer to the user record pointer to populate with
 *                      the created user record on success.
 *
 * \returns 0 on success and non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_user_create(fido_user** user);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_user_create, fido_user** user)
        /* the user pointer is valid. */
        MODEL_CHECK_OBJECT_RW(user, sizeof(*user));
MODEL_CONTRACT_PRECONDITIONS_END(fido_user_create)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_user_create, int retval, fido_user** user)
        /* on success... */
        if (0 == retval)
        {
            /* the user is valid. */
            MODEL_ASSERT(property_fido_user_valid(*user));
        }
        else
        {
            /* this is a defined error code. */
            enum fido_error_code error = (enum fido_error_code)retval;
            MODEL_ASSERT(__CPROVER_enum_is_in_range(error));
            /* user is set to NULL. */
            MODEL_ASSERT(NULL == *user);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_user_create)

/**
 * \brief Release a \ref fido_user instance.
 *
 * \param user          The user record to release.
 */
void fido_user_release(fido_user* user);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_user_release, fido_user* user)
        /* user points to a region of memory large enough to hold it. */
        MODEL_CHECK_OBJECT_RW(user, sizeof(*user));
MODEL_CONTRACT_PRECONDITIONS_END(fido_user_release)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(fido_user_release, fido_user* user)
MODEL_CONTRACT_POSTCONDITIONS_END(fido_user_release)

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
