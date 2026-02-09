/**
 * \file test/config/test_fido_scanner_read_token_keyword_deny.c
 *
 * \brief Test that we can read the "deny" keyword.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/scanner.h>
#include <minunit/minunit.h>

TEST_SUITE(fido_scanner_read_token_keyword_deny);

/**
 * \brief Basic test of the happy path.
 */
TEST(basics)
{
    fido_scanner* scanner = nullptr;
    fido_token_details details;
    const char* TEST_INPUT = "deny";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* read the deny keyword. */
    TEST_ASSERT(
        FIDO_SCANNER_TOKEN_TYPE_KEYWORD_DENY ==
            fido_scanner_read_token_keyword_deny(&details, scanner));

    /* the details are correct. */
    TEST_EXPECT(FIDO_SCANNER_TOKEN_TYPE_KEYWORD_DENY == details.type);
    TEST_EXPECT(0 == details.begin_index);
    TEST_EXPECT(3 == details.end_index);
    TEST_EXPECT(1 == details.begin_line);
    TEST_EXPECT(1 == details.end_line);
    TEST_EXPECT(1 == details.begin_col);
    TEST_EXPECT(4 == details.end_col);

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
    const char* TEST_INPUT = "devo";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* read a username token. */
    TEST_ASSERT(
        FIDO_SCANNER_TOKEN_TYPE_USERNAME ==
            fido_scanner_read_token_keyword_deny(&details, scanner));

    /* the details are correct. */
    TEST_EXPECT(FIDO_SCANNER_TOKEN_TYPE_USERNAME == details.type);
    TEST_EXPECT(0 == details.begin_index);
    TEST_EXPECT(3 == details.end_index);
    TEST_EXPECT(1 == details.begin_line);
    TEST_EXPECT(1 == details.end_line);
    TEST_EXPECT(1 == details.begin_col);
    TEST_EXPECT(4 == details.end_col);

    /* clean up. */
    fido_scanner_release(scanner);
}

/**
 * \brief If this doesn't start with 'd', it's a failure.
 */
TEST(not_deny)
{
    fido_scanner* scanner = nullptr;
    fido_token_details details;
    const char* TEST_INPUT = "alpha";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* read fails. */
    TEST_ASSERT(
        FIDO_SCANNER_TOKEN_TYPE_BAD_INPUT ==
            fido_scanner_read_token_keyword_deny(&details, scanner));

    /* clean up. */
    fido_scanner_release(scanner);
}
