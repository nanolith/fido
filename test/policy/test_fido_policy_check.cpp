/**
 * \file test/policy/test_fido_policy_check.cpp
 *
 * \brief Unit tests for \ref fido_policy_check.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/config.h>
#include <fido/options.h>
#include <fido/policy.h>
#include <fido/user.h>
#include <minunit/minunit.h>
#include <string.h>

#include "helpers.h"

TEST_SUITE(fido_policy_check);

/**
 * \brief Test that with an empty config, a user belonging to wheel can run any
 * command.
 */
TEST(empty_config)
{
    fido_config* config = nullptr;
    fido_options* opts = nullptr;
    fido_user* user = nullptr;
    const char* as_user = nullptr;
    const char* as_group = nullptr;
    const fido_config_add_variable* env_head = nullptr;
    const char* TEST_INPUT = R"()";
    const char** ARGS = nullptr;
    size_t ARGS_COUNT = 0;

    TEST_ASSERT(0 == fido_user_create_test(&user, "bob", "wheel", "bob"));
    TEST_ASSERT(
        0
            == fido_options_create_test(
                    &opts, "/sbin/shutdown", ARGS_COUNT, ARGS));
    TEST_ASSERT(0 == fido_config_parse(&config, TEST_INPUT));

    /* the policy check should succeed. */
    TEST_ASSERT(
        0
            == fido_policy_check(
                    &as_user, &as_group, &env_head, config, opts, user));
    TEST_ASSERT(!strcmp("root", as_user));
    TEST_ASSERT(!strcmp("wheel", as_group));
    TEST_ASSERT(nullptr == env_head);

    /* clean up. */
    fido_config_release(config);
    fido_options_release(opts);
    fido_user_release(user);
}

/**
 * \brief Test that the last role wins.
 */
TEST(last_role_wins)
{
    fido_config* config = nullptr;
    fido_options* opts = nullptr;
    fido_user* user = nullptr;
    const char* as_user = nullptr;
    const char* as_group = nullptr;
    const fido_config_add_variable* env_head = nullptr;
    const char* TEST_INPUT = R"(
        role "foo" {
        }

        role "bar" {
            as operator
        }
    )";
    const char** ARGS = nullptr;
    size_t ARGS_COUNT = 0;

    TEST_ASSERT(0 == fido_user_create_test(&user, "bob", "wheel", "bob"));
    TEST_ASSERT(
        0
            == fido_options_create_test(
                    &opts, "/sbin/shutdown", ARGS_COUNT, ARGS));
    TEST_ASSERT(0 == fido_config_parse(&config, TEST_INPUT));

    /* the policy check should succeed. */
    TEST_ASSERT(
        0
            == fido_policy_check(
                    &as_user, &as_group, &env_head, config, opts, user));
    TEST_ASSERT(!strcmp("operator", as_user));
    TEST_ASSERT(!strcmp("wheel", as_group));
    TEST_ASSERT(nullptr == env_head);

    /* clean up. */
    fido_config_release(config);
    fido_options_release(opts);
    fido_user_release(user);
}
