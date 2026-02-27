/**
 * \file test/config/test_fido_config_parse_role.cpp
 *
 * \brief Test that we can parse roles from the config.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/scanner.h>
#include <minunit/minunit.h>
#include <stdlib.h>
#include <string.h>

#include "../src/config/parser_internal.h"

TEST_SUITE(fido_config_parse_role);

/**
 * \brief Reading from an empty string results in an error.
 */
TEST(empty_string_error)
{
    fido_scanner* scanner = nullptr;
    fido_config_role* role = nullptr;
    const char* TEST_INPUT = "";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* attempt to parse an as expression. */
    TEST_ASSERT(
        FIDO_ERROR_UNEXPECTED_EOF == fido_config_parse_role(&role, scanner));
    TEST_ASSERT(nullptr == role);

    /* clean up. */
    fido_scanner_release(scanner);
}
