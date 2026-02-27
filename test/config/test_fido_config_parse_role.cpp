/**
 * \file test/config/test_fido_config_parse_role.cpp
 *
 * \brief Test that we can parse roles from the config.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/scanner.h>
#include <minunit/minunit.h>
#include <stdlib.h>
#include <string.h>

#include "../src/config/parser_internal.h"

TEST_SUITE(fido_config_parse_role);

/**
 * \brief Reading from an empty string results in an error.
 */
TEST(empty_string_error)
{
    fido_scanner* scanner = nullptr;
    fido_config_role* role = nullptr;
    const char* TEST_INPUT = "";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* attempt to parse an as expression. */
    TEST_ASSERT(
        FIDO_ERROR_UNEXPECTED_EOF == fido_config_parse_role(&role, scanner));
    TEST_ASSERT(nullptr == role);

    /* clean up. */
    fido_scanner_release(scanner);
}

/**
 * \brief Parsing an incomplete role results in an error.
 */
TEST(incomplete_role_1)
{
    fido_scanner* scanner = nullptr;
    fido_config_role* role = nullptr;
    const char* TEST_INPUT = "role";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* attempt to parse an as expression. */
    TEST_ASSERT(
        FIDO_ERROR_UNEXPECTED_EOF == fido_config_parse_role(&role, scanner));
    TEST_ASSERT(nullptr == role);

    /* clean up. */
    fido_scanner_release(scanner);
}

/**
 * \brief Parsing an incomplete role results in an error.
 */
TEST(incomplete_role_2)
{
    fido_scanner* scanner = nullptr;
    fido_config_role* role = nullptr;
    const char* TEST_INPUT = R"(role "foo")";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* attempt to parse an as expression. */
    TEST_ASSERT(
        FIDO_ERROR_UNEXPECTED_EOF == fido_config_parse_role(&role, scanner));
    TEST_ASSERT(nullptr == role);

    /* clean up. */
    fido_scanner_release(scanner);
}

/**
 * \brief Parsing an incomplete role results in an error.
 */
TEST(incomplete_role_3)
{
    fido_scanner* scanner = nullptr;
    fido_config_role* role = nullptr;
    const char* TEST_INPUT = R"(role "foo" {)";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* attempt to parse an as expression. */
    TEST_ASSERT(
        FIDO_ERROR_UNEXPECTED_EOF == fido_config_parse_role(&role, scanner));
    TEST_ASSERT(nullptr == role);

    /* clean up. */
    fido_scanner_release(scanner);
}

/**
 * \brief Simplest possible role, with no statements.
 */
TEST(simple_role)
{
    fido_scanner* scanner = nullptr;
    fido_config_role* role = nullptr;
    const char* TEST_INPUT = R"(role "foo" { })";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* attempt to parse an as expression. */
    TEST_ASSERT(0 == fido_config_parse_role(&role, scanner));
    TEST_ASSERT(nullptr != role);

    /* there is no next role. */
    TEST_EXPECT(nullptr == role->next);
    /* permissions have been finalized. */
    TEST_EXPECT(role->permissions_finalized);
    /* the name matches. */
    TEST_ASSERT(nullptr != role->name);
    TEST_EXPECT(!strcmp("foo", role->name));
    /* the default username is root. */
    TEST_ASSERT(nullptr != role->as_user);
    TEST_EXPECT(!strcmp("root", role->as_user));
    /* the default group is wheel. */
    TEST_ASSERT(nullptr != role->as_group);
    TEST_EXPECT(!strcmp("wheel", role->as_group));
    /* command head is null. */
    TEST_ASSERT(nullptr == role->command_head);
    /* variable head is null. */
    TEST_ASSERT(nullptr == role->variable_head);
    /* permission head is NULL. */
    TEST_ASSERT(nullptr == role->permission_head);

    /* clean up. */
    fido_config_role_release(role);
    fido_scanner_release(scanner);
}

/**
 * \brief Permissions are ordered sequentially.
 */
TEST(ordered_permissions)
{
    fido_scanner* scanner = nullptr;
    fido_config_role* role = nullptr;
    const char* TEST_INPUT = R"(role "foo" {
        permit :wheel
        deny george })";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* attempt to parse an as expression. */
    TEST_ASSERT(0 == fido_config_parse_role(&role, scanner));
    TEST_ASSERT(nullptr != role);

    /* permissions have been finalized. */
    TEST_EXPECT(role->permissions_finalized);
    /* permission head is not NULL. */
    TEST_ASSERT(nullptr != role->permission_head);
    /* the first entry is "permit :wheel". */
    TEST_ASSERT(nullptr != role->permission_head->identifier);
    TEST_EXPECT(!strcmp("wheel", role->permission_head->identifier));
    TEST_EXPECT(
        FIDO_CONFIG_IDENTIFIER_TYPE_GROUP
            == role->permission_head->identifier_type);
    TEST_EXPECT(
        FIDO_CONFIG_PERMISSION_TYPE_PERMIT
            == role->permission_head->permission_type);
    /* the second entry is "deny george" */
    TEST_ASSERT(nullptr != role->permission_head->next);
    TEST_ASSERT(nullptr != role->permission_head->next->identifier);
    TEST_EXPECT(!strcmp("george", role->permission_head->next->identifier));
    TEST_EXPECT(
        FIDO_CONFIG_IDENTIFIER_TYPE_USERNAME
            == role->permission_head->next->identifier_type);
    TEST_EXPECT(
        FIDO_CONFIG_PERMISSION_TYPE_DENY
            == role->permission_head->next->permission_type);

    /* clean up. */
    fido_config_role_release(role);
    fido_scanner_release(scanner);
}

/**
 * \brief Test that we can parse environment variables.
 */
TEST(add_variable_expressions)
{
    fido_scanner* scanner = nullptr;
    fido_config_role* role = nullptr;
    const char* TEST_INPUT = R"(role "foo" {
        env +PATH })";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* attempt to parse an as expression. */
    TEST_ASSERT(0 == fido_config_parse_role(&role, scanner));
    TEST_ASSERT(nullptr != role);

    /* verify that there is an environment variable set. */
    TEST_ASSERT(nullptr != role->variable_head);
    /* This environment variable matches PATH. */
    TEST_EXPECT(!strcmp("PATH", role->variable_head->name));
    /* there are no other variables. */
    TEST_ASSERT(nullptr == role->variable_head->next);

    /* clean up. */
    fido_config_role_release(role);
    fido_scanner_release(scanner);
}
