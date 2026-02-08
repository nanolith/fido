/**
 * \file test/config/test_fido_scanner_create_release.c
 *
 * \brief Test that we can create and release a \ref fido_scanner instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/scanner.h>
#include <minunit/minunit.h>

TEST_SUITE(fido_scanner_create_release);

/**
 * \brief Basic test.
 */
TEST(basics)
{
    fido_scanner* scanner = nullptr;
    const char* TEST_INPUT = "Test input";

    /* verify that we can create a scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* the scanner variable is updated with the created instance. */
    TEST_ASSERT(nullptr != scanner);
    TEST_EXPECT(TEST_INPUT == scanner->original_input);
    TEST_EXPECT(TEST_INPUT == scanner->input);
    TEST_EXPECT(0 == scanner->index);
    TEST_EXPECT(1 == scanner->line);
    TEST_EXPECT(1 == scanner->col);

    /* clean up. */
    fido_scanner_release(scanner);
}
