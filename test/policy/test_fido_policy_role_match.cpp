/**
 * \file test/policy/test_fido_policy_role_match.cpp
 *
 * \brief Test that we can match roles with command-line options and a user.
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

TEST_SUITE(fido_policy_role_match);

/**
 * \brief Test that with an empty role, a user belonging to wheel can run any
 * command.
 */
TEST(match_empty_role)
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
    )";
    const char** ARGS = nullptr;
    size_t ARGS_COUNT = 0;

    TEST_ASSERT(0 == fido_user_create_test(&user, "bob", "wheel", "bob"));
    TEST_ASSERT(
        0
            == fido_options_create_test(
                    &opts, "/sbin/shutdown", ARGS_COUNT, ARGS));
    TEST_ASSERT(0 == fido_config_parse(&config, TEST_INPUT));
    TEST_ASSERT(nullptr != config);
    TEST_ASSERT(nullptr != config->head);

    fido_config_role* role = config->head;

    /* test that we can match this role. */
    TEST_ASSERT(
        0
            == fido_policy_role_match(
                    &as_user, &as_group, &env_head, role, opts, user));
    TEST_ASSERT(!strcmp("root", as_user));
    TEST_ASSERT(!strcmp("wheel", as_group));
    TEST_ASSERT(nullptr == env_head);

    /* clean up. */
    fido_config_release(config);
    fido_options_release(opts);
    fido_user_release(user);
}

/**
 * \brief Test that users can be authorized with permit.
 */
TEST(match_role_permit)
{
    fido_config* config = nullptr;
    fido_options* opts = nullptr;
    fido_user* user = nullptr;
    const char* as_user = nullptr;
    const char* as_group = nullptr;
    const fido_config_add_variable* env_head = nullptr;
    const char* TEST_INPUT = R"(
        role "foo" {
            permit bob
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
    TEST_ASSERT(nullptr != config);
    TEST_ASSERT(nullptr != config->head);

    fido_config_role* role = config->head;

    /* test that we can match this role. */
    TEST_ASSERT(
        0
            == fido_policy_role_match(
                    &as_user, &as_group, &env_head, role, opts, user));
    TEST_ASSERT(!strcmp("root", as_user));
    TEST_ASSERT(!strcmp("wheel", as_group));
    TEST_ASSERT(nullptr == env_head);

    /* clean up. */
    fido_config_release(config);
    fido_options_release(opts);
    fido_user_release(user);
}

/**
 * \brief Test that users not explicitly authorized don't match.
 */
TEST(nomatch_role_permit)
{
    fido_config* config = nullptr;
    fido_options* opts = nullptr;
    fido_user* user = nullptr;
    const char* as_user = nullptr;
    const char* as_group = nullptr;
    const fido_config_add_variable* env_head = nullptr;
    const char* TEST_INPUT = R"(
        role "foo" {
            permit alice
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
    TEST_ASSERT(nullptr != config);
    TEST_ASSERT(nullptr != config->head);

    fido_config_role* role = config->head;

    /* test that we don't match this role. */
    TEST_ASSERT(
        0
            != fido_policy_role_match(
                    &as_user, &as_group, &env_head, role, opts, user));

    /* clean up. */
    fido_config_release(config);
    fido_options_release(opts);
    fido_user_release(user);
}

/**
 * \brief Test that users with group membership can be authorized.
 */
TEST(match_role_group_permit)
{
    fido_config* config = nullptr;
    fido_options* opts = nullptr;
    fido_user* user = nullptr;
    const char* as_user = nullptr;
    const char* as_group = nullptr;
    const fido_config_add_variable* env_head = nullptr;
    const char* TEST_INPUT = R"(
        role "foo" {
            permit :bob
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
    TEST_ASSERT(nullptr != config);
    TEST_ASSERT(nullptr != config->head);

    fido_config_role* role = config->head;

    /* test that we match this role. */
    TEST_ASSERT(
        0
            == fido_policy_role_match(
                    &as_user, &as_group, &env_head, role, opts, user));
    TEST_ASSERT(!strcmp("root", as_user));
    TEST_ASSERT(!strcmp("wheel", as_group));
    TEST_ASSERT(nullptr == env_head);

    /* clean up. */
    fido_config_release(config);
    fido_options_release(opts);
    fido_user_release(user);
}

/**
 * \brief Test that users without group membership aren't authorized.
 */
TEST(nomatch_role_group_permit)
{
    fido_config* config = nullptr;
    fido_options* opts = nullptr;
    fido_user* user = nullptr;
    const char* as_user = nullptr;
    const char* as_group = nullptr;
    const fido_config_add_variable* env_head = nullptr;
    const char* TEST_INPUT = R"(
        role "foo" {
            permit :alice
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

    fido_config_role* role = config->head;

    /* test that we don't match this role. */
    TEST_ASSERT(
        0
            != fido_policy_role_match(
                    &as_user, &as_group, &env_head, role, opts, user));

    /* clean up. */
    fido_config_release(config);
    fido_options_release(opts);
    fido_user_release(user);
}

/**
 * \brief Test that last permission wins.
 */
TEST(nomatch_role_last_permission_wins)
{
    fido_config* config = nullptr;
    fido_options* opts = nullptr;
    fido_user* user = nullptr;
    const char* as_user = nullptr;
    const char* as_group = nullptr;
    const fido_config_add_variable* env_head = nullptr;
    const char* TEST_INPUT = R"(
        role "foo" {
            permit :wheel
            deny bob
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

    fido_config_role* role = config->head;

    /* test that we don't match this role. */
    TEST_ASSERT(
        0
            != fido_policy_role_match(
                    &as_user, &as_group, &env_head, role, opts, user));

    /* clean up. */
    fido_config_release(config);
    fido_options_release(opts);
    fido_user_release(user);
}

/**
 * \brief Test that we can override the user.
 */
TEST(match_role_as_user_override)
{
    fido_config* config = nullptr;
    fido_options* opts = nullptr;
    fido_user* user = nullptr;
    const char* as_user = nullptr;
    const char* as_group = nullptr;
    const fido_config_add_variable* env_head = nullptr;
    const char* TEST_INPUT = R"(
        role "foo" {
            permit :wheel
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

    fido_config_role* role = config->head;

    /* test that we match this role. */
    TEST_ASSERT(
        0
            == fido_policy_role_match(
                    &as_user, &as_group, &env_head, role, opts, user));
    TEST_ASSERT(!strcmp("operator", as_user));

    /* clean up. */
    fido_config_release(config);
    fido_options_release(opts);
    fido_user_release(user);
}

/**
 * \brief Test that we can override the group.
 */
TEST(match_role_as_group_override)
{
    fido_config* config = nullptr;
    fido_options* opts = nullptr;
    fido_user* user = nullptr;
    const char* as_user = nullptr;
    const char* as_group = nullptr;
    const fido_config_add_variable* env_head = nullptr;
    const char* TEST_INPUT = R"(
        role "foo" {
            permit :wheel
            as :operator
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

    fido_config_role* role = config->head;

    /* test that we match this role. */
    TEST_ASSERT(
        0
            == fido_policy_role_match(
                    &as_user, &as_group, &env_head, role, opts, user));
    TEST_ASSERT(!strcmp("operator", as_group));

    /* clean up. */
    fido_config_release(config);
    fido_options_release(opts);
    fido_user_release(user);
}

/**
 * \brief Test that we can match on command.
 */
TEST(match_role_with_cmd)
{
    fido_config* config = nullptr;
    fido_options* opts = nullptr;
    fido_user* user = nullptr;
    const char* as_user = nullptr;
    const char* as_group = nullptr;
    const fido_config_add_variable* env_head = nullptr;
    const char* TEST_INPUT = R"(
        role "foo" {
            cmd "/sbin/shutdown *"
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

    fido_config_role* role = config->head;

    /* test that we match this role. */
    TEST_ASSERT(
        0
            == fido_policy_role_match(
                    &as_user, &as_group, &env_head, role, opts, user));

    /* clean up. */
    fido_config_release(config);
    fido_options_release(opts);
    fido_user_release(user);
}

/**
 * \brief Test that a match with a different command fails.
 */
TEST(nomatch_role_with_cmd)
{
    fido_config* config = nullptr;
    fido_options* opts = nullptr;
    fido_user* user = nullptr;
    const char* as_user = nullptr;
    const char* as_group = nullptr;
    const fido_config_add_variable* env_head = nullptr;
    const char* TEST_INPUT = R"(
        role "foo" {
            cmd "/sbin/shutdown *"
        }
    )";
    const char** ARGS = nullptr;
    size_t ARGS_COUNT = 0;

    TEST_ASSERT(0 == fido_user_create_test(&user, "bob", "wheel", "bob"));
    TEST_ASSERT(
        0
            == fido_options_create_test(
                    &opts, "/usr/bin/su", ARGS_COUNT, ARGS));
    TEST_ASSERT(0 == fido_config_parse(&config, TEST_INPUT));

    fido_config_role* role = config->head;

    /* test that we do not match. */
    TEST_ASSERT(
        0
            != fido_policy_role_match(
                    &as_user, &as_group, &env_head, role, opts, user));

    /* clean up. */
    fido_config_release(config);
    fido_options_release(opts);
    fido_user_release(user);
}
