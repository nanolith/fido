/**
 * \file test/config/test_fido_scanner_read_token_keyword_as.c
 *
 * \brief Test that we can read the "as" keyword.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/scanner.h>
#include <minunit/minunit.h>

TEST_SUITE(fido_scanner_read_token_keyword_as);

/**
 * \brief Basic test of the happy path.
 */
TEST(basics)
{
    fido_scanner* scanner = nullptr;
    fido_token_details details;
    const char* TEST_INPUT = "as";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* read the as keyword. */
    TEST_ASSERT(
        FIDO_SCANNER_TOKEN_TYPE_KEYWORD_AS ==
            fido_scanner_read_token_keyword_as(&details, scanner));

    /* the details are correct. */
    TEST_EXPECT(FIDO_SCANNER_TOKEN_TYPE_KEYWORD_AS == details.type);
    TEST_EXPECT(0 == details.begin_index);
    TEST_EXPECT(1 == details.end_index);
    TEST_EXPECT(1 == details.begin_line);
    TEST_EXPECT(1 == details.end_line);
    TEST_EXPECT(1 == details.begin_col);
    TEST_EXPECT(2 == details.end_col);

    /* clean up. */
    fido_scanner_release(scanner);
}
