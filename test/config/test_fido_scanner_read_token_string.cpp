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

    /* the details are correct. */
    TEST_EXPECT(FIDO_SCANNER_TOKEN_TYPE_STRING == details.type);
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
 * \brief A star character can be escaped.
 */
TEST(escape_star)
{
    fido_scanner* scanner = nullptr;
    fido_token_details details;
    const char* TEST_INPUT = R"("\*")";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* read a string token. */
    TEST_ASSERT(
        FIDO_SCANNER_TOKEN_TYPE_STRING ==
            fido_scanner_read_token_string(&details, scanner));

    /* the details are correct. */
    TEST_EXPECT(FIDO_SCANNER_TOKEN_TYPE_STRING == details.type);
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
 * \brief A percent character can be escaped.
 */
TEST(escape_percent)
{
    fido_scanner* scanner = nullptr;
    fido_token_details details;
    const char* TEST_INPUT = R"("\%")";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* read a string token. */
    TEST_ASSERT(
        FIDO_SCANNER_TOKEN_TYPE_STRING ==
            fido_scanner_read_token_string(&details, scanner));

    /* the details are correct. */
    TEST_EXPECT(FIDO_SCANNER_TOKEN_TYPE_STRING == details.type);
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
 * \brief A backslash character can be escaped.
 */
TEST(escape_backslash)
{
    fido_scanner* scanner = nullptr;
    fido_token_details details;
    const char* TEST_INPUT = R"("\\")";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* read a string token. */
    TEST_ASSERT(
        FIDO_SCANNER_TOKEN_TYPE_STRING ==
            fido_scanner_read_token_string(&details, scanner));

    /* the details are correct. */
    TEST_EXPECT(FIDO_SCANNER_TOKEN_TYPE_STRING == details.type);
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
 * \brief A double-quote character can be escaped.
 */
TEST(escape_double_quote)
{
    fido_scanner* scanner = nullptr;
    fido_token_details details;
    const char* TEST_INPUT = R"("\"")";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* read a string token. */
    TEST_ASSERT(
        FIDO_SCANNER_TOKEN_TYPE_STRING ==
            fido_scanner_read_token_string(&details, scanner));

    /* the details are correct. */
    TEST_EXPECT(FIDO_SCANNER_TOKEN_TYPE_STRING == details.type);
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
 * \brief A form feed can be escaped.
 */
TEST(escape_form_feed)
{
    fido_scanner* scanner = nullptr;
    fido_token_details details;
    const char* TEST_INPUT = R"("\f")";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* read a string token. */
    TEST_ASSERT(
        FIDO_SCANNER_TOKEN_TYPE_STRING ==
            fido_scanner_read_token_string(&details, scanner));

    /* the details are correct. */
    TEST_EXPECT(FIDO_SCANNER_TOKEN_TYPE_STRING == details.type);
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
 * \brief A newline can be escaped.
 */
TEST(escape_newline)
{
    fido_scanner* scanner = nullptr;
    fido_token_details details;
    const char* TEST_INPUT = R"("\n")";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* read a string token. */
    TEST_ASSERT(
        FIDO_SCANNER_TOKEN_TYPE_STRING ==
            fido_scanner_read_token_string(&details, scanner));

    /* the details are correct. */
    TEST_EXPECT(FIDO_SCANNER_TOKEN_TYPE_STRING == details.type);
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
 * \brief A carriage return can be escaped.
 */
TEST(escape_cr)
{
    fido_scanner* scanner = nullptr;
    fido_token_details details;
    const char* TEST_INPUT = R"("\r")";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* read a string token. */
    TEST_ASSERT(
        FIDO_SCANNER_TOKEN_TYPE_STRING ==
            fido_scanner_read_token_string(&details, scanner));

    /* the details are correct. */
    TEST_EXPECT(FIDO_SCANNER_TOKEN_TYPE_STRING == details.type);
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
 * \brief A tab can be escaped.
 */
TEST(escape_tab)
{
    fido_scanner* scanner = nullptr;
    fido_token_details details;
    const char* TEST_INPUT = R"("\t")";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* read a string token. */
    TEST_ASSERT(
        FIDO_SCANNER_TOKEN_TYPE_STRING ==
            fido_scanner_read_token_string(&details, scanner));

    /* the details are correct. */
    TEST_EXPECT(FIDO_SCANNER_TOKEN_TYPE_STRING == details.type);
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
 * \brief A vertical can be escaped.
 */
TEST(escape_vtab)
{
    fido_scanner* scanner = nullptr;
    fido_token_details details;
    const char* TEST_INPUT = R"("\v")";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* read a string token. */
    TEST_ASSERT(
        FIDO_SCANNER_TOKEN_TYPE_STRING ==
            fido_scanner_read_token_string(&details, scanner));

    /* the details are correct. */
    TEST_EXPECT(FIDO_SCANNER_TOKEN_TYPE_STRING == details.type);
    TEST_EXPECT(0 == details.begin_index);
    TEST_EXPECT(3 == details.end_index);
    TEST_EXPECT(1 == details.begin_line);
    TEST_EXPECT(1 == details.end_line);
    TEST_EXPECT(1 == details.begin_col);
    TEST_EXPECT(4 == details.end_col);

    /* clean up. */
    fido_scanner_release(scanner);
}
