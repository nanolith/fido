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

TEST_SUITE(fido_policy_permission_match);

static int fido_user_create_test(
    fido_user** user, const char* username, const char* group1,
    const char* group2)
{
    int retval;
    fido_user* tmp;
    size_t gid_size, groupnames_size;

    tmp = (fido_user*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }

    memset(tmp, 0, sizeof(*tmp));

    tmp->username = strdup(username);
    if (NULL == tmp->username)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto cleanup_tmp;
    }

    tmp->group_count = 2;

    gid_size = tmp->group_count * sizeof(gid_t);
    tmp->gids = (gid_t*)malloc(gid_size);
    if (NULL == tmp->gids)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto cleanup_tmp;
    }
    tmp->gids[0] = 0;
    tmp->gids[1] = 1;

    groupnames_size = tmp->group_count * sizeof(char*);
    tmp->groupnames = (char**)malloc(groupnames_size);
    if (NULL == tmp->groupnames)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto cleanup_tmp;
    }
    tmp->groupnames[0] = NULL;
    tmp->groupnames[1] = NULL;

    tmp->groupnames[0] = strdup(group1);
    if (NULL == tmp->groupnames[0])
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto cleanup_tmp;
    }

    tmp->groupnames[1] = strdup(group2);
    if (NULL == tmp->groupnames[1])
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto cleanup_tmp;
    }

    retval = 0;
    *user = tmp;
    goto done;

cleanup_tmp:
    fido_user_release(tmp);

done:
    return retval;
}

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
