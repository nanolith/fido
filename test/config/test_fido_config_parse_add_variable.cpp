/**
 * \file test/config/test_fido_config_parse_add_variable.cpp
 *
 * \brief Test that we can parse add variable statements from the config.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/scanner.h>
#include <minunit/minunit.h>
#include <string.h>

#include "../src/config/parser_internal.h"

TEST_SUITE(fido_config_parse_add_variable);

/**
 * \brief Reading from an empty string results in an error.
 */
TEST(empty_string_error)
{
    fido_scanner* scanner = nullptr;
    fido_config_add_variable* var = nullptr;
    const char* TEST_INPUT = "";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* attempt to parse an add variable. */
    TEST_ASSERT(
        FIDO_ERROR_UNEXPECTED_EOF
            == fido_config_parse_add_variable(&var, scanner));
    TEST_ASSERT(nullptr == var);

    /* clean up. */
    fido_scanner_release(scanner);
}

/**
 * \brief An incomplete add variable statement results in an error.
 */
TEST(incomplete_env)
{
    fido_scanner* scanner = nullptr;
    fido_config_add_variable* var = nullptr;
    const char* TEST_INPUT = "env ";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* attempt to parse an add variable. */
    TEST_ASSERT(
        FIDO_ERROR_UNEXPECTED_EOF
            == fido_config_parse_add_variable(&var, scanner));
    TEST_ASSERT(nullptr == var);

    /* clean up. */
    fido_scanner_release(scanner);
}

/**
 * \brief Any other token read will result in an error.
 */
TEST(bad_start_token)
{
    fido_scanner* scanner = nullptr;
    fido_config_add_variable* var = nullptr;
    const char* TEST_INPUT = "{";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* attempt to parse an add variable. */
    TEST_ASSERT(
        FIDO_ERROR_UNEXPECTED_TOKEN
            == fido_config_parse_add_variable(&var, scanner));
    TEST_ASSERT(nullptr == var);

    /* clean up. */
    fido_scanner_release(scanner);
}
