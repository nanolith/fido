/**
 * \file test/policy/test_fido_policy_command_match.cpp
 *
 * \brief Test that we can match commands with command-line options.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/config.h>
#include <fido/policy.h>
#include <minunit/minunit.h>
#include <stdlib.h>
#include <string.h>

TEST_SUITE(fido_policy_command_match);

static int fido_options_create_test(
    fido_options** opts, const char* binary_name, size_t arguments_count,
    const char** arguments)
{
    int retval;
    fido_options* tmp;

    tmp = (fido_options*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }

    /* set up tmp. */
    memset(tmp, 0, sizeof(*tmp));
    tmp->binary_name = binary_name;
    tmp->arguments_count = arguments_count;
    tmp->arguments = arguments;

    /* success. */
    retval = 0;
    *opts = tmp;
    goto done;

done:
    return retval;
}

/**
 * \brief Test that we can match a command with no arguments.
 */
TEST(match_no_arguments)
{
    fido_options* opts = nullptr;
    fido_config* config = nullptr;
    const char* TEST_INPUT = R"(
        role "foo" {
            cmd "/sbin/mount"
        }
    )";
    const char** ARGS = nullptr;
    size_t ARGS_COUNT = 0;

    TEST_ASSERT(
        0 == fido_options_create_test(&opts, "/sbin/mount", ARGS_COUNT, ARGS));
    TEST_ASSERT(0 == fido_config_parse(&config, TEST_INPUT));
    TEST_ASSERT(nullptr != config);
    TEST_ASSERT(nullptr != config->head);
    TEST_ASSERT(nullptr != config->head->command_head);

    fido_config_command* cmd = config->head->command_head;

    /* test that we can match a command with no arguments. */
    TEST_ASSERT(0 == fido_policy_command_match(cmd, opts));

    /* clean up. */
    fido_config_release(config);
    fido_options_release(opts);
}

/**
 * \brief Test that we can match a command with an exact argument.
 */
TEST(match_one_exact_argument)
{
    fido_options* opts = nullptr;
    fido_config* config = nullptr;
    const char* TEST_INPUT = R"(
        role "foo" {
            cmd "/sbin/mount /dev/sd1c"
        }
    )";
    const char* ARGS[] = { "/dev/sd1c" };
    size_t ARGS_COUNT = sizeof(ARGS) / sizeof(ARGS[0]);

    TEST_ASSERT(
        0 == fido_options_create_test(&opts, "/sbin/mount", ARGS_COUNT, ARGS));
    TEST_ASSERT(0 == fido_config_parse(&config, TEST_INPUT));
    TEST_ASSERT(nullptr != config);
    TEST_ASSERT(nullptr != config->head);
    TEST_ASSERT(nullptr != config->head->command_head);

    fido_config_command* cmd = config->head->command_head;

    /* test that we can match a command with no arguments. */
    TEST_ASSERT(0 == fido_policy_command_match(cmd, opts));

    /* clean up. */
    fido_config_release(config);
    fido_options_release(opts);
}

/**
 * \brief Test that we can match a command with multiple exact arguments.
 */
TEST(match_multiple_exact_arguments)
{
    fido_options* opts = nullptr;
    fido_config* config = nullptr;
    const char* TEST_INPUT = R"(
        role "foo" {
            cmd "/sbin/mount -f /dev/sd1c /mnt"
        }
    )";
    const char* ARGS[] = { "-f", "/dev/sd1c", "/mnt" };
    size_t ARGS_COUNT = sizeof(ARGS) / sizeof(ARGS[0]);

    TEST_ASSERT(
        0 == fido_options_create_test(&opts, "/sbin/mount", ARGS_COUNT, ARGS));
    TEST_ASSERT(0 == fido_config_parse(&config, TEST_INPUT));
    TEST_ASSERT(nullptr != config);
    TEST_ASSERT(nullptr != config->head);
    TEST_ASSERT(nullptr != config->head->command_head);

    fido_config_command* cmd = config->head->command_head;

    /* test that we can match a command with no arguments. */
    TEST_ASSERT(0 == fido_policy_command_match(cmd, opts));

    /* clean up. */
    fido_config_release(config);
    fido_options_release(opts);
}
