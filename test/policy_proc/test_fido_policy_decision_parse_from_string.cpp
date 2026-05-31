/**
 * \file test/policy_proc/test_fido_policy_decision_parse_from_string.cpp
 *
 * \brief Unit tests for \ref fido_policy_decision_parse_from_string.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/policy_proc.h>
#include <minunit/minunit.h>
#include <string.h>

TEST_SUITE(fido_policy_decision_parse_from_string);

/**
 * \brief Test that we can parse a deny.
 */
TEST(deny)
{
    fido_policy_decision* dec = nullptr;
    char DECISION[] = "deny";

    TEST_ASSERT(0 == fido_policy_decision_parse_from_string(&dec, DECISION));
    TEST_ASSERT(nullptr != dec);
    TEST_ASSERT(FIDO_POLICY_DECISION_DENY == dec->policy_decision);
    TEST_ASSERT(nullptr == dec->as_user);
    TEST_ASSERT(nullptr == dec->as_group);
    TEST_ASSERT(nullptr == dec->variable_head);

    /* clean up */
    fido_policy_decision_release(dec);
}

/**
 * \brief Test that an asterisk deny causes a failure.
 */
TEST(deny_asterisk_failure)
{
    fido_policy_decision* dec = nullptr;
    char DECISION[] = "deny*";

    TEST_ASSERT(0 != fido_policy_decision_parse_from_string(&dec, DECISION));
}

/**
 * \brief Test that a permit without any additional information causes a
 * failure.
 */
TEST(permit_missing_data_failure1)
{
    fido_policy_decision* dec = nullptr;
    char DECISION[] = "permit";

    TEST_ASSERT(0 != fido_policy_decision_parse_from_string(&dec, DECISION));
}

/**
 * \brief Test that a permit with an empty username field cases an error.
 */
TEST(permit_missing_data_failure2)
{
    fido_policy_decision* dec = nullptr;
    char DECISION[] = "permit:";

    TEST_ASSERT(0 != fido_policy_decision_parse_from_string(&dec, DECISION));
}

/**
 * \brief Test that a permit with only a username field causes an error.
 */
TEST(permit_missing_data_failure3)
{
    fido_policy_decision* dec = nullptr;
    char DECISION[] = "permit:foo";

    TEST_ASSERT(0 != fido_policy_decision_parse_from_string(&dec, DECISION));
}

/**
 * \brief Test that a permit with an empty group field causes an error.
 */
TEST(permit_missing_data_failure4)
{
    fido_policy_decision* dec = nullptr;
    char DECISION[] = "permit:foo:";

    TEST_ASSERT(0 != fido_policy_decision_parse_from_string(&dec, DECISION));
}

/**
 * \brief Test that a permit with a missing variables field passes.
 */
TEST(permit_no_variables)
{
    fido_policy_decision* dec = nullptr;
    char DECISION[] = "permit:foo:bar";

    TEST_ASSERT(0 == fido_policy_decision_parse_from_string(&dec, DECISION));
    TEST_ASSERT(nullptr != dec);
    TEST_ASSERT(FIDO_POLICY_DECISION_PERMIT == dec->policy_decision);
    TEST_ASSERT(!strcmp("foo", dec->as_user));
    TEST_ASSERT(!strcmp("bar", dec->as_group));
    TEST_ASSERT(nullptr == dec->variable_head);

    /* clean up */
    fido_policy_decision_release(dec);
}

/**
 * \brief Test that a permit with an empty variables field passes.
 */
TEST(permit_empty_variables)
{
    fido_policy_decision* dec = nullptr;
    char DECISION[] = "permit:foo:bar:";

    TEST_ASSERT(0 == fido_policy_decision_parse_from_string(&dec, DECISION));
    TEST_ASSERT(nullptr != dec);
    TEST_ASSERT(FIDO_POLICY_DECISION_PERMIT == dec->policy_decision);
    TEST_ASSERT(!strcmp("foo", dec->as_user));
    TEST_ASSERT(!strcmp("bar", dec->as_group));
    TEST_ASSERT(nullptr == dec->variable_head);

    /* clean up */
    fido_policy_decision_release(dec);
}

/**
 * \brief Test that a permit with a single variable passes.
 */
TEST(permit_one_variable)
{
    fido_policy_decision* dec = nullptr;
    char DECISION[] = "permit:foo:bar:baz";

    TEST_ASSERT(0 == fido_policy_decision_parse_from_string(&dec, DECISION));
    TEST_ASSERT(nullptr != dec);
    TEST_ASSERT(FIDO_POLICY_DECISION_PERMIT == dec->policy_decision);
    TEST_ASSERT(!strcmp("foo", dec->as_user));
    TEST_ASSERT(!strcmp("bar", dec->as_group));
    TEST_ASSERT(nullptr != dec->variable_head);
    TEST_ASSERT(!strcmp("baz", dec->variable_head->name));
    TEST_ASSERT(nullptr == dec->variable_head->next);

    /* clean up */
    fido_policy_decision_release(dec);
}
