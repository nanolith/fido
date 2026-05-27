/**
 * \file test/policy/test_fido_policy_permission_match.cpp
 *
 * \brief Test that we can match permissions with a user.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/config.h>
#include <fido/policy.h>
#include <minunit/minunit.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"

TEST_SUITE(fido_policy_permission_match);

/**
 * \brief Test that we can match a permit user permission.
 */
TEST(match_permit_user)
{
    fido_user* user = nullptr;
    fido_config* config = nullptr;
    const char* TEST_INPUT = R"(
        role "foo" {
            permit bob
        }
    )";

    TEST_ASSERT(0 == fido_user_create_test(&user, "bob", "wheel", "bob"));
    TEST_ASSERT(0 == fido_config_parse(&config, TEST_INPUT));
    TEST_ASSERT(nullptr != config);
    TEST_ASSERT(nullptr != config->head);
    TEST_ASSERT(nullptr != config->head->permission_head);

    fido_config_permission* perm = config->head->permission_head;

    /* test that we can match a permit user. */
    TEST_ASSERT(0 == fido_policy_permission_match(perm, user));

    /* clean up. */
    fido_config_release(config);
    fido_user_release(user);
}

/**
 * \brief Test that we can match a deny user permission.
 */
TEST(match_deny_user)
{
    fido_user* user = nullptr;
    fido_config* config = nullptr;
    const char* TEST_INPUT = R"(
        role "foo" {
            deny bob
        }
    )";

    TEST_ASSERT(0 == fido_user_create_test(&user, "bob", "wheel", "bob"));
    TEST_ASSERT(0 == fido_config_parse(&config, TEST_INPUT));
    TEST_ASSERT(nullptr != config);
    TEST_ASSERT(nullptr != config->head);
    TEST_ASSERT(nullptr != config->head->permission_head);

    fido_config_permission* perm = config->head->permission_head;

    /* test that we can match a permit user. */
    TEST_ASSERT(0 == fido_policy_permission_match(perm, user));

    /* clean up. */
    fido_config_release(config);
    fido_user_release(user);
}

/**
 * \brief Test that a mismatched permit user permission fails.
 */
TEST(nomatch_permit_user)
{
    fido_user* user = nullptr;
    fido_config* config = nullptr;
    const char* TEST_INPUT = R"(
        role "foo" {
            permit alice
        }
    )";

    TEST_ASSERT(0 == fido_user_create_test(&user, "bob", "wheel", "bob"));
    TEST_ASSERT(0 == fido_config_parse(&config, TEST_INPUT));
    TEST_ASSERT(nullptr != config);
    TEST_ASSERT(nullptr != config->head);
    TEST_ASSERT(nullptr != config->head->permission_head);

    fido_config_permission* perm = config->head->permission_head;

    /* test that we don't match. */
    TEST_ASSERT(0 != fido_policy_permission_match(perm, user));

    /* clean up. */
    fido_config_release(config);
    fido_user_release(user);
}

/**
 * \brief Test that a mismatched deny user permission fails.
 */
TEST(nomatch_deny_user)
{
    fido_user* user = nullptr;
    fido_config* config = nullptr;
    const char* TEST_INPUT = R"(
        role "foo" {
            deny alice
        }
    )";

    TEST_ASSERT(0 == fido_user_create_test(&user, "bob", "wheel", "bob"));
    TEST_ASSERT(0 == fido_config_parse(&config, TEST_INPUT));
    TEST_ASSERT(nullptr != config);
    TEST_ASSERT(nullptr != config->head);
    TEST_ASSERT(nullptr != config->head->permission_head);

    fido_config_permission* perm = config->head->permission_head;

    /* test that we don't match. */
    TEST_ASSERT(0 != fido_policy_permission_match(perm, user));

    /* clean up. */
    fido_config_release(config);
    fido_user_release(user);
}

/**
 * \brief Test that we can match a permit group permission.
 */
TEST(match_permit_group)
{
    fido_user* user = nullptr;
    fido_config* config = nullptr;
    const char* TEST_INPUT = R"(
        role "foo" {
            permit :wheel
        }
    )";

    TEST_ASSERT(0 == fido_user_create_test(&user, "bob", "wheel", "bob"));
    TEST_ASSERT(0 == fido_config_parse(&config, TEST_INPUT));
    TEST_ASSERT(nullptr != config);
    TEST_ASSERT(nullptr != config->head);
    TEST_ASSERT(nullptr != config->head->permission_head);

    fido_config_permission* perm = config->head->permission_head;

    /* test that we can match a permit user. */
    TEST_ASSERT(0 == fido_policy_permission_match(perm, user));

    /* clean up. */
    fido_config_release(config);
    fido_user_release(user);
}

/**
 * \brief Test that we can match a permit second group permission.
 */
TEST(match_permit_second_group)
{
    fido_user* user = nullptr;
    fido_config* config = nullptr;
    const char* TEST_INPUT = R"(
        role "foo" {
            permit :bob
        }
    )";

    TEST_ASSERT(0 == fido_user_create_test(&user, "bob", "wheel", "bob"));
    TEST_ASSERT(0 == fido_config_parse(&config, TEST_INPUT));
    TEST_ASSERT(nullptr != config);
    TEST_ASSERT(nullptr != config->head);
    TEST_ASSERT(nullptr != config->head->permission_head);

    fido_config_permission* perm = config->head->permission_head;

    /* test that we can match a permit user. */
    TEST_ASSERT(0 == fido_policy_permission_match(perm, user));

    /* clean up. */
    fido_config_release(config);
    fido_user_release(user);
}

/**
 * \brief Test that we can match a deny group permission.
 */
TEST(match_deny_group)
{
    fido_user* user = nullptr;
    fido_config* config = nullptr;
    const char* TEST_INPUT = R"(
        role "foo" {
            deny :wheel
        }
    )";

    TEST_ASSERT(0 == fido_user_create_test(&user, "bob", "wheel", "bob"));
    TEST_ASSERT(0 == fido_config_parse(&config, TEST_INPUT));
    TEST_ASSERT(nullptr != config);
    TEST_ASSERT(nullptr != config->head);
    TEST_ASSERT(nullptr != config->head->permission_head);

    fido_config_permission* perm = config->head->permission_head;

    /* test that we can match a permit user. */
    TEST_ASSERT(0 == fido_policy_permission_match(perm, user));

    /* clean up. */
    fido_config_release(config);
    fido_user_release(user);
}

/**
 * \brief Test that we can match a deny second group permission.
 */
TEST(match_deny_second_group)
{
    fido_user* user = nullptr;
    fido_config* config = nullptr;
    const char* TEST_INPUT = R"(
        role "foo" {
            deny :bob
        }
    )";

    TEST_ASSERT(0 == fido_user_create_test(&user, "bob", "wheel", "bob"));
    TEST_ASSERT(0 == fido_config_parse(&config, TEST_INPUT));
    TEST_ASSERT(nullptr != config);
    TEST_ASSERT(nullptr != config->head);
    TEST_ASSERT(nullptr != config->head->permission_head);

    fido_config_permission* perm = config->head->permission_head;

    /* test that we can match a permit user. */
    TEST_ASSERT(0 == fido_policy_permission_match(perm, user));

    /* clean up. */
    fido_config_release(config);
    fido_user_release(user);
}

/**
 * \brief Test that we can fail to match a permit group permission.
 */
TEST(nomatch_permit_group)
{
    fido_user* user = nullptr;
    fido_config* config = nullptr;
    const char* TEST_INPUT = R"(
        role "foo" {
            permit :operator
        }
    )";

    TEST_ASSERT(0 == fido_user_create_test(&user, "bob", "wheel", "bob"));
    TEST_ASSERT(0 == fido_config_parse(&config, TEST_INPUT));
    TEST_ASSERT(nullptr != config);
    TEST_ASSERT(nullptr != config->head);
    TEST_ASSERT(nullptr != config->head->permission_head);

    fido_config_permission* perm = config->head->permission_head;

    /* test that we don't match. */
    TEST_ASSERT(0 != fido_policy_permission_match(perm, user));

    /* clean up. */
    fido_config_release(config);
    fido_user_release(user);
}

/**
 * \brief Test that we fail to match a deny group permission.
 */
TEST(nomatch_deny_group)
{
    fido_user* user = nullptr;
    fido_config* config = nullptr;
    const char* TEST_INPUT = R"(
        role "foo" {
            deny :operator
        }
    )";

    TEST_ASSERT(0 == fido_user_create_test(&user, "bob", "wheel", "bob"));
    TEST_ASSERT(0 == fido_config_parse(&config, TEST_INPUT));
    TEST_ASSERT(nullptr != config);
    TEST_ASSERT(nullptr != config->head);
    TEST_ASSERT(nullptr != config->head->permission_head);

    fido_config_permission* perm = config->head->permission_head;

    /* test that we don't match. */
    TEST_ASSERT(0 != fido_policy_permission_match(perm, user));

    /* clean up. */
    fido_config_release(config);
    fido_user_release(user);
}
