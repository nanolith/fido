/**
 * \file models/helpers/config/config_helpers.h
 *
 * \brief Helpers for exercising config data structures.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include "config/parser_internal.h"

int FN_DECL_MUST_CHECK
fido_config_permission_create_random(fido_config_permission** perm);

int FN_DECL_MUST_CHECK
fido_config_command_argument_create_random(fido_config_command_argument** arg);

int FN_DECL_MUST_CHECK
fido_config_command_create_random(fido_config_command** arg);

int FN_DECL_MUST_CHECK
fido_config_create_random(fido_config** conf);
