/**
 * \file models/helpers/user/user_helpers.h
 *
 * \brief Helpers for exercising user data structures.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <fido/user.h>

int FN_DECL_MUST_CHECK
fido_user_create_random(fido_user** user);
