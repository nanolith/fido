/**
 * \file models/shadow/config/property_fido_config_permission_valid.c
 *
 * \brief Model checking property to ensure that a fido config permission is
 * valid.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/config.h>

/**
 * \brief Valid permission record property.
 *
 * \param perm          The permission record to check.
 *
 * \returns true if the permission record is valid.
 */
bool
property_fido_config_permission_valid(
    const fido_config_permission* perm)
{
    MODEL_CHECK_OBJECT_READ(perm, sizeof(*perm));

    MODEL_ASSERT(NULL != perm->identifier);

    enum fido_config_identifier_type it =
        (enum fido_config_identifier_type)perm->identifier_type;
    MODEL_ASSERT(__CPROVER_enum_is_in_range(it));

    enum fido_config_permission_type pt =
        (enum fido_config_permission_type)perm->permission_type;
    MODEL_ASSERT(__CPROVER_enum_is_in_range(pt));

    return true;
}
