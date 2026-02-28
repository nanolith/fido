/**
 * \file test/config/test_fido_config_parse.cpp
 *
 * \brief Test that we can parse config data.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/config.h>
#include <minunit/minunit.h>
#include <stdlib.h>
#include <string.h>

TEST_SUITE(fido_config_parse);

/**
 * \brief An empty string results in an empty config.
 */
TEST(empty_string_empty_config)
{
    fido_config* config = nullptr;
    const char* TEST_INPUT = "";

    /* parsing succeeds. */
    TEST_ASSERT(0 == fido_config_parse(&config, TEST_INPUT));

    /* The config is valid. */
    TEST_ASSERT(nullptr != config);
    /* the config is empty. */
    TEST_EXPECT(nullptr == config->head);

    /* clean up. */
    fido_config_release(config);
}
