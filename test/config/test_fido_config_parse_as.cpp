/**
 * \file test/config/test_fido_config_parse_as.cpp
 *
 * \brief Test that we can parse as statements from the config.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/scanner.h>
#include <minunit/minunit.h>
#include <string.h>

#include "../src/config/parser_internal.h"

TEST_SUITE(fido_config_parse_as);

/**
 * \brief Reading from an empty string results in an error.
 */
TEST(empty_string_error)
{
    fido_scanner* scanner = nullptr;
    char* name = nullptr;
    int type = 0;
    const char* TEST_INPUT = "";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* attempt to parse an as expression. */
    TEST_ASSERT(
        FIDO_ERROR_UNEXPECTED_EOF
            == fido_config_parse_as(&name, &type, scanner));
    TEST_ASSERT(nullptr == name);
    TEST_ASSERT(0 == type);

    /* clean up. */
    fido_scanner_release(scanner);
}

/**
 * \brief Parsing an as expression without an identifier results in an error.
 */
TEST(as_without_identifier)
{
    fido_scanner* scanner = nullptr;
    char* name = nullptr;
    int type = 0;
    const char* TEST_INPUT = "as";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* attempt to parse an as expression. */
    TEST_ASSERT(
        FIDO_ERROR_UNEXPECTED_EOF
            == fido_config_parse_as(&name, &type, scanner));
    TEST_ASSERT(nullptr == name);
    TEST_ASSERT(0 == type);

    /* clean up. */
    fido_scanner_release(scanner);
}
