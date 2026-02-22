/**
 * \file test/config/test_fido_config_parse_command.cpp
 *
 * \brief Test that we can parse command statements from the config.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/scanner.h>
#include <minunit/minunit.h>
#include <string.h>

#include "../src/config/parser_internal.h"

TEST_SUITE(fido_config_parse_command);

/**
 * \brief Reading from an empty string results in an error.
 */
TEST(empty_string_error)
{
    fido_scanner* scanner = nullptr;
    fido_config_command* cmd = nullptr;
    const char* TEST_INPUT = "";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* attempt to parse a permission. */
    TEST_ASSERT(
        FIDO_ERROR_UNEXPECTED_EOF
            == fido_config_parse_command(&cmd, scanner));
    TEST_ASSERT(nullptr == cmd);

    /* clean up. */
    fido_scanner_release(scanner);
}

/**
 * \brief Reading an incomplete command statement results in an error.
 */
TEST(incomplete_cmd)
{
    fido_scanner* scanner = nullptr;
    fido_config_command* cmd = nullptr;
    const char* TEST_INPUT = "cmd ";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* attempt to parse a permission. */
    TEST_ASSERT(
        FIDO_ERROR_UNEXPECTED_EOF
            == fido_config_parse_command(&cmd, scanner));
    TEST_ASSERT(nullptr == cmd);

    /* clean up. */
    fido_scanner_release(scanner);
}

/**
 * \brief A command with an empty string results in an error.
 */
TEST(cmd_empty_string)
{
    fido_scanner* scanner = nullptr;
    fido_config_command* cmd = nullptr;
    const char* TEST_INPUT = R"(cmd "")";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* attempt to parse a permission. */
    TEST_ASSERT(
        FIDO_ERROR_INVALID_COMMAND
            == fido_config_parse_command(&cmd, scanner));
    TEST_ASSERT(nullptr == cmd);

    /* clean up. */
    fido_scanner_release(scanner);
}

/**
 * \brief We can parse a command with no arguments.
 */
TEST(cmd_no_arguments)
{
    fido_scanner* scanner = nullptr;
    fido_config_command* cmd = nullptr;
    const char* TEST_INPUT = R"(cmd "/sbin/halt")";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* attempt to parse a command. */
    TEST_ASSERT(0 == fido_config_parse_command(&cmd, scanner));
    TEST_ASSERT(nullptr != cmd);
    TEST_EXPECT(nullptr == cmd->next);
    TEST_EXPECT(nullptr == cmd->head);
    TEST_EXPECT(cmd->arguments_finalized);
    TEST_ASSERT(nullptr != cmd->binary);
    TEST_EXPECT(!strcmp("/sbin/halt", cmd->binary));

    /* clean up. */
    fido_config_command_release(cmd);
    fido_scanner_release(scanner);
}

/**
 * \brief We can parse a command with a wildcard argument.
 */
TEST(cmd_wildcard_argument)
{
    fido_scanner* scanner = nullptr;
    fido_config_command* cmd = nullptr;
    const char* TEST_INPUT = R"(cmd "/sbin/mount *")";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* attempt to parse a command. */
    TEST_ASSERT(0 == fido_config_parse_command(&cmd, scanner));
    TEST_ASSERT(nullptr != cmd);
    TEST_EXPECT(nullptr == cmd->next);
    TEST_EXPECT(cmd->arguments_finalized);
    TEST_ASSERT(nullptr != cmd->binary);
    TEST_EXPECT(!strcmp("/sbin/mount", cmd->binary));
    TEST_ASSERT(nullptr != cmd->head);
    TEST_EXPECT(nullptr == cmd->head->next);
    TEST_EXPECT(FIDO_CONFIG_ARGUMENT_TYPE_WILDCARD == cmd->head->argument_type);

    /* clean up. */
    fido_config_command_release(cmd);
    fido_scanner_release(scanner);
}

/**
 * \brief We can parse a command with a prefix wildcard argument.
 */
TEST(cmd_prefix_wildcard_argument)
{
    fido_scanner* scanner = nullptr;
    fido_config_command* cmd = nullptr;
    const char* TEST_INPUT = R"(cmd "/sbin/mount %c")";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* attempt to parse a command. */
    TEST_ASSERT(0 == fido_config_parse_command(&cmd, scanner));
    TEST_ASSERT(nullptr != cmd);
    TEST_EXPECT(nullptr == cmd->next);
    TEST_EXPECT(cmd->arguments_finalized);
    TEST_ASSERT(nullptr != cmd->binary);
    TEST_EXPECT(!strcmp("/sbin/mount", cmd->binary));
    TEST_ASSERT(nullptr != cmd->head);
    TEST_EXPECT(nullptr == cmd->head->next);
    TEST_EXPECT(
        FIDO_CONFIG_ARGUMENT_TYPE_PREFIX_WILDCARD == cmd->head->argument_type);
    TEST_EXPECT(!strcmp("c", cmd->head->argument_match));

    /* clean up. */
    fido_config_command_release(cmd);
    fido_scanner_release(scanner);
}

/**
 * \brief We can parse a command with a postfix wildcard argument.
 */
TEST(cmd_postfix_wildcard_argument)
{
    fido_scanner* scanner = nullptr;
    fido_config_command* cmd = nullptr;
    const char* TEST_INPUT = R"(cmd "/sbin/mount /dev/sd%")";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* attempt to parse a command. */
    TEST_ASSERT(0 == fido_config_parse_command(&cmd, scanner));
    TEST_ASSERT(nullptr != cmd);
    TEST_EXPECT(nullptr == cmd->next);
    TEST_EXPECT(cmd->arguments_finalized);
    TEST_ASSERT(nullptr != cmd->binary);
    TEST_EXPECT(!strcmp("/sbin/mount", cmd->binary));
    TEST_ASSERT(nullptr != cmd->head);
    TEST_EXPECT(nullptr == cmd->head->next);
    TEST_EXPECT(
        FIDO_CONFIG_ARGUMENT_TYPE_POSTFIX_WILDCARD == cmd->head->argument_type);
    TEST_EXPECT(!strcmp("/dev/sd", cmd->head->argument_match));

    /* clean up. */
    fido_config_command_release(cmd);
    fido_scanner_release(scanner);
}

/**
 * \brief We can only have a single wildcard argument.
 */
TEST(cmd_single_wildcard)
{
    fido_scanner* scanner = nullptr;
    fido_config_command* cmd = nullptr;
    const char* TEST_INPUT = R"(cmd "/sbin/mount * *")";

    /* Create the scanner instance. */
    TEST_ASSERT(0 == fido_scanner_create(&scanner, TEST_INPUT));

    /* attempt to parse a command. */
    TEST_ASSERT(
        FIDO_ERROR_MULTIPLE_WILDCARD_ARGUMENTS
            == fido_config_parse_command(&cmd, scanner));

    /* clean up. */
    fido_scanner_release(scanner);
}
