/**
 * \file policy/fido_policy_permission_match.c
 *
 * \brief Check to see if a given premission matches user details.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/policy.h>
#include <string.h>

/* forward decls. */
static int match_username_permission(
    const fido_config_permission* perm, const fido_user* user);
static int match_group_permission(
    const fido_config_permission* perm, const fido_user* user);

/**
 * \brief Check to see if a given permission matches the user details.
 *
 * \note This does NOT evaluate whether this permission is a PERMIT or DENY, but
 * only whether the user matches. The caller must make the appropriate policy
 * decision based on the match and the permission type.
 *
 * \param perm          The permission to match.
 * \param user          The user for this match.
 *
 * \returns 0 on success (matched) and non-zero on failure (not matched).
 */
int FN_DECL_MUST_CHECK
fido_policy_permission_match(
    const fido_config_permission* perm, const fido_user* user)
{
    int retval;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_policy_permission_match, perm, user);

    /* decode identifier type. */
    switch (perm->identifier_type)
    {
        case FIDO_CONFIG_IDENTIFIER_TYPE_USERNAME:
            retval = match_username_permission(perm, user);
            break;

        case FIDO_CONFIG_IDENTIFIER_TYPE_GROUP:
            retval = match_group_permission(perm, user);
            break;

        default:
            retval = FIDO_ERROR_POLICY_MATCH;
            break;
    }

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_policy_permission_match, retval, perm, user);

    return retval;
}

/**
 * \brief Match a username permission.
 *
 * \param perm          The permission to match.
 * \param user          The user for this match.
 *
 * \returns 0 on success (matched) and non-zero on failure (not matched).
 */
static int match_username_permission(
    const fido_config_permission* perm, const fido_user* user)
{
    if (strcmp(perm->identifier, user->username))
    {
        return FIDO_ERROR_POLICY_MATCH;
    }

    return 0;
}

/**
 * \brief Match a group permission.
 *
 * \param perm          The permission to match.
 * \param user          The user for this match.
 *
 * \returns 0 on success (matched) and non-zero on failure (not matched).
 */
static int match_group_permission(
    const fido_config_permission* perm, const fido_user* user)
{
    for (size_t i = 0; i < user->group_count; ++i)
    {
        if (!strcmp(perm->identifier, user->groupnames[i]))
        {
            return 0;
        }
    }

    return FIDO_ERROR_POLICY_MATCH;
}
