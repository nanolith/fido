/**
 * \file test/policy/test_fido_policy_command_argument_match.cpp
 *
 * \brief Test that we can match command arguments with a policy matcher.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/config.h>
#include <fido/policy.h>
#include <minunit/minunit.h>

TEST_SUITE(fido_policy_command_argument_match);

/**
 * \brief Test that we can match an exact argument.
 */
TEST(exact_argument)
{
    fido_config* config = nullptr;
    const char* TEST_INPUT = R"(
        role "foo" {
            cmd "/sbin/mount /dev/sd1c /mnt"
        }
    )";

    TEST_ASSERT(0 == fido_config_parse(&config, TEST_INPUT));
    TEST_ASSERT(nullptr != config);
    TEST_ASSERT(nullptr != config->head);
    TEST_ASSERT(nullptr != config->head->command_head);
    TEST_ASSERT(nullptr != config->head->command_head->head);

    fido_config_command_argument* arg = config->head->command_head->head;

    /* test that an exact match passes. */
    TEST_ASSERT(0 == fido_policy_command_argument_match(arg, "/dev/sd1c"));
    /* test that anything else fails. */
    TEST_ASSERT(0 != fido_policy_command_argument_match(arg, "/dev/sd2a"));

    /* clean up. */
    fido_config_release(config);
}

/**
 * \brief Test that we can match a wildcard argument.
 */
TEST(wildcard_argument)
{
    fido_config* config = nullptr;
    const char* TEST_INPUT = R"(
        role "foo" {
            cmd "/sbin/mount *"
        }
    )";

    TEST_ASSERT(0 == fido_config_parse(&config, TEST_INPUT));
    TEST_ASSERT(nullptr != config);
    TEST_ASSERT(nullptr != config->head);
    TEST_ASSERT(nullptr != config->head->command_head);
    TEST_ASSERT(nullptr != config->head->command_head->head);

    fido_config_command_argument* arg = config->head->command_head->head;

    /* test that anything matches. */
    TEST_ASSERT(0 == fido_policy_command_argument_match(arg, "anything"));

    /* clean up. */
    fido_config_release(config);
}

/**
 * \brief Test that we can match a prefix wildcard argument.
 */
TEST(prefix_wildcard_argument)
{
    fido_config* config = nullptr;
    const char* TEST_INPUT = R"(
        role "foo" {
            cmd "/sbin/mount %sd1c"
        }
    )";

    TEST_ASSERT(0 == fido_config_parse(&config, TEST_INPUT));
    TEST_ASSERT(nullptr != config);
    TEST_ASSERT(nullptr != config->head);
    TEST_ASSERT(nullptr != config->head->command_head);
    TEST_ASSERT(nullptr != config->head->command_head->head);

    fido_config_command_argument* arg = config->head->command_head->head;

    /* test a match. */
    TEST_ASSERT(0 == fido_policy_command_argument_match(arg, "/dev/sd1c"));
    /* test non-matches. */
    TEST_ASSERT(0 != fido_policy_command_argument_match(arg, "/dev/sd2c"));
    TEST_ASSERT(0 != fido_policy_command_argument_match(arg, "/dev/sd1"));
    TEST_ASSERT(0 != fido_policy_command_argument_match(arg, "/dev/sd1ca"));
    TEST_ASSERT(0 != fido_policy_command_argument_match(arg, "d1c"));

    /* clean up. */
    fido_config_release(config);
}

/**
 * \brief Test that we can match a postfix wildcard argument.
 */
TEST(postfix_wildcard_argument)
{
    fido_config* config = nullptr;
    const char* TEST_INPUT = R"(
        role "foo" {
            cmd "/sbin/mount /dev/%"
        }
    )";

    TEST_ASSERT(0 == fido_config_parse(&config, TEST_INPUT));
    TEST_ASSERT(nullptr != config);
    TEST_ASSERT(nullptr != config->head);
    TEST_ASSERT(nullptr != config->head->command_head);
    TEST_ASSERT(nullptr != config->head->command_head->head);

    fido_config_command_argument* arg = config->head->command_head->head;

    /* test a match. */
    TEST_ASSERT(0 == fido_policy_command_argument_match(arg, "/dev/sd1c"));
    /* test non-matches. */
    TEST_ASSERT(0 != fido_policy_command_argument_match(arg, "/var/sd2c"));
    TEST_ASSERT(0 != fido_policy_command_argument_match(arg, "/etc/sd1"));
    TEST_ASSERT(0 != fido_policy_command_argument_match(arg, "/dev"));

    /* clean up. */
    fido_config_release(config);
}
