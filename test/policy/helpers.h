/**
 * \file test/policy/helpers.h
 *
 * \brief Helper methods for policy unit tests.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <fido/config.h>
#include <fido/options.h>
#include <fido/policy.h>

int fido_options_create_test(
    fido_options** opts, const char* binary_name, size_t arguments_count,
    const char** arguments);
int fido_user_create_test(
    fido_user** user, const char* username, const char* group1,
    const char* group2);
