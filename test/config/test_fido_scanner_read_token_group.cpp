/**
 * \file test/config/test_fido_scanner_read_token_group.c
 *
 * \brief Test that we can read a group token.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/scanner.h>
#include <minunit/minunit.h>

TEST_SUITE(fido_scanner_read_token_group);

/**
 * \brief Basic test of the happy path.
 */
TEST(basics)
{
    fido_scanner* scanner = nullptr;
    fido_token_details details;
    const char* TEST_INPUT = ":abc_123";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* read this username. */
    TEST_ASSERT(
        FIDO_SCANNER_TOKEN_TYPE_GROUP ==
            fido_scanner_read_token_group(&details, scanner));

    /* the details are correct. */
    TEST_EXPECT(FIDO_SCANNER_TOKEN_TYPE_GROUP == details.type);
    TEST_EXPECT(0 == details.begin_index);
    TEST_EXPECT(7 == details.end_index);
    TEST_EXPECT(1 == details.begin_line);
    TEST_EXPECT(1 == details.end_line);
    TEST_EXPECT(1 == details.begin_col);
    TEST_EXPECT(8 == details.end_col);

    /* clean up. */
    fido_scanner_release(scanner);
}

/**
 * \brief Groups can begin with underscores.
 */
TEST(underscore)
{
    fido_scanner* scanner = nullptr;
    fido_token_details details;
    const char* TEST_INPUT = ":_www";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* read this username. */
    TEST_ASSERT(
        FIDO_SCANNER_TOKEN_TYPE_GROUP ==
            fido_scanner_read_token_group(&details, scanner));

    /* the details are correct. */
    TEST_EXPECT(FIDO_SCANNER_TOKEN_TYPE_GROUP == details.type);
    TEST_EXPECT(0 == details.begin_index);
    TEST_EXPECT(4 == details.end_index);
    TEST_EXPECT(1 == details.begin_line);
    TEST_EXPECT(1 == details.end_line);
    TEST_EXPECT(1 == details.begin_col);
    TEST_EXPECT(5 == details.end_col);

    /* clean up. */
    fido_scanner_release(scanner);
}
