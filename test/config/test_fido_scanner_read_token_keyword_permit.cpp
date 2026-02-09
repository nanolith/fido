/**
 * \file test/config/test_fido_scanner_read_token_keyword_permit.c
 *
 * \brief Test that we can read the "permit" keyword.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/scanner.h>
#include <minunit/minunit.h>

TEST_SUITE(fido_scanner_read_token_keyword_permit);

/**
 * \brief Basic test of the happy path.
 */
TEST(basics)
{
    fido_scanner* scanner = nullptr;
    fido_token_details details;
    const char* TEST_INPUT = "permit";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* read the role keyword. */
    TEST_ASSERT(
        FIDO_SCANNER_TOKEN_TYPE_KEYWORD_PERMIT ==
            fido_scanner_read_token_keyword_permit(&details, scanner));

    /* the details are correct. */
    TEST_EXPECT(FIDO_SCANNER_TOKEN_TYPE_KEYWORD_PERMIT == details.type);
    TEST_EXPECT(0 == details.begin_index);
    TEST_EXPECT(5 == details.end_index);
    TEST_EXPECT(1 == details.begin_line);
    TEST_EXPECT(1 == details.end_line);
    TEST_EXPECT(1 == details.begin_col);
    TEST_EXPECT(6 == details.end_col);

    /* clean up. */
    fido_scanner_release(scanner);
}

/**
 * \brief Fall back to a username.
 */
TEST(username_fallback)
{
    fido_scanner* scanner = nullptr;
    fido_token_details details;
    const char* TEST_INPUT = "permie";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* read a username token. */
    TEST_ASSERT(
        FIDO_SCANNER_TOKEN_TYPE_USERNAME ==
            fido_scanner_read_token_keyword_permit(&details, scanner));

    /* the details are correct. */
    TEST_EXPECT(FIDO_SCANNER_TOKEN_TYPE_USERNAME == details.type);
    TEST_EXPECT(0 == details.begin_index);
    TEST_EXPECT(5 == details.end_index);
    TEST_EXPECT(1 == details.begin_line);
    TEST_EXPECT(1 == details.end_line);
    TEST_EXPECT(1 == details.begin_col);
    TEST_EXPECT(6 == details.end_col);

    /* clean up. */
    fido_scanner_release(scanner);
}

/**
 * \brief If this doesn't start with 'p', it's a failure.
 */
TEST(not_permit)
{
    fido_scanner* scanner = nullptr;
    fido_token_details details;
    const char* TEST_INPUT = "alpha";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* read fails. */
    TEST_ASSERT(
        FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT ==
            fido_scanner_read_token_keyword_permit(&details, scanner));

    /* clean up. */
    fido_scanner_release(scanner);
}
