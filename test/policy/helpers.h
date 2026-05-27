/**
 * \file test/policy/helpers.h
 *
 * \brief Helper methods for policy unit tests.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

int fido_options_create_test(
    fido_options** opts, const char* binary_name, size_t arguments_count,
    const char** arguments);
