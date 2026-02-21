/**
 * \file test/config/test_fido_config_parse_permission.cpp
 *
 * \brief Test that we can parse permission statements from the config.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/scanner.h>
#include <minunit/minunit.h>

#include "../src/config/parser_internal.h"

TEST_SUITE(fido_config_parse_permission);

/**
 * \brief Reading from an empty string results in an error.
 */
TEST(empty_string_error)
{
    fido_scanner* scanner = nullptr;
    fido_config_permission* perm = nullptr;
    const char* TEST_INPUT = "";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* attempt to parse a permission. */
    TEST_ASSERT(
        FIDO_ERROR_UNEXPECTED_EOF
            == fido_config_parse_permission(&perm, scanner));
    TEST_ASSERT(nullptr == perm);

    /* clean up. */
    fido_scanner_release(scanner);
}

/**
 * \brief An incomplete permit statement is an error.
 */
TEST(incomplete_permit)
{
    fido_scanner* scanner = nullptr;
    fido_config_permission* perm = nullptr;
    const char* TEST_INPUT = "permit";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* attempt to parse a permission. */
    TEST_ASSERT(
        FIDO_ERROR_UNEXPECTED_EOF
            == fido_config_parse_permission(&perm, scanner));
    TEST_ASSERT(nullptr == perm);

    /* clean up. */
    fido_scanner_release(scanner);
}

/**
 * \brief An incomplete deny statement is an error.
 */
TEST(incomplete_deny)
{
    fido_scanner* scanner = nullptr;
    fido_config_permission* perm = nullptr;
    const char* TEST_INPUT = "deny";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* attempt to parse a permission. */
    TEST_ASSERT(
        FIDO_ERROR_UNEXPECTED_EOF
            == fido_config_parse_permission(&perm, scanner));
    TEST_ASSERT(nullptr == perm);

    /* clean up. */
    fido_scanner_release(scanner);
}

/**
 * \brief Any other token read will result in an error.
 */
TEST(bad_start_token)
{
    fido_scanner* scanner = nullptr;
    fido_config_permission* perm = nullptr;
    const char* TEST_INPUT = "{";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* attempt to parse a permission. */
    TEST_ASSERT(
        FIDO_ERROR_UNEXPECTED_TOKEN
            == fido_config_parse_permission(&perm, scanner));
    TEST_ASSERT(nullptr == perm);

    /* clean up. */
    fido_scanner_release(scanner);
}

/**
 * \brief Any other token after permit is an error.
 */
TEST(bad_token_after_permit)
{
    fido_scanner* scanner = nullptr;
    fido_config_permission* perm = nullptr;
    const char* TEST_INPUT = "permit {";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* attempt to parse a permission. */
    TEST_ASSERT(
        FIDO_ERROR_UNEXPECTED_TOKEN
            == fido_config_parse_permission(&perm, scanner));
    TEST_ASSERT(nullptr == perm);

    /* clean up. */
    fido_scanner_release(scanner);
}
