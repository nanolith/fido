/**
 * \file test/config/test_fido_scanner_read_token.c
 *
 * \brief Test that we can read tokens from the scanner.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/scanner.h>
#include <minunit/minunit.h>

TEST_SUITE(fido_scanner_read_token);

/**
 * \brief Reading from an empty string results in EOF.
 */
TEST(empty_string_eof)
{
    fido_scanner* scanner = nullptr;
    fido_token_details details;
    const char* TEST_INPUT = "";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* read a token. */
    TEST_ASSERT(
        FIDO_SCANNER_TOKEN_TYPE_EOF ==
            fido_scanner_read_token(&details, scanner));

    /* clean up. */
    fido_scanner_release(scanner);
}
