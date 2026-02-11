/**
 * \file test/config/test_fido_scanner_read_token_string.c
 *
 * \brief Test that we can read string tokens from the scanner.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/scanner.h>
#include <minunit/minunit.h>

TEST_SUITE(fido_scanner_read_token_string);

/**
 * \brief A simple string can be read.
 */
TEST(basics)
{
    fido_scanner* scanner = nullptr;
    fido_token_details details;
    const char* TEST_INPUT = R"("test")";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* read a string token. */
    TEST_ASSERT(
        FIDO_SCANNER_TOKEN_TYPE_STRING ==
            fido_scanner_read_token_string(&details, scanner));

    /* clean up. */
    fido_scanner_release(scanner);
}
