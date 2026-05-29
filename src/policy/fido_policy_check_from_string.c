/**
 * \file policy/fido_policy_check_from_string.c
 *
 * \brief Perform a policy check using the given policy string.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/policy.h>
#include <stdio.h>

/**
 * \brief Perform a policy check from the configuration stored in a string.
 *
 * \note The output for this check is written to standard output.
 *
 * \param user          The user for this policy check.
 * \param opts          The options for this policy check.
 * \param config_str    The configuration string for this policy check.
 * \param authoritative A flag to indicate whether the policy decision is
 *                      authoritative.
 *
 * \returns 0 on success (authorized) and non-zero on failure (not authorized).
 */
int FN_DECL_MUST_CHECK
fido_policy_check_from_string(
    const fido_user* user, const fido_options* opts, const char* config_str,
    bool authoritative)
{
    int retval;
    const char* as_user;
    const char* as_group;
    const fido_config_add_variable* env_head;
    fido_config* config;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_policy_check_from_string, user, opts, config_str, authoritative);

    /* parse config data. */
    retval = fido_config_parse(&config, config_str);
    if (0 != retval)
    {
        fprintf(stderr, "error: config file parse failed.\n");
        goto done;
    }

    /* perform policy check. */
    retval =
        fido_policy_check(
            &as_user, &as_group, &env_head, config, opts, user);
    if (0 != retval)
    {
        printf("deny%s\n", authoritative ? "" : "*");
        goto cleanup_config;
    }

    /* We are authorized; share details. */
    printf("permit%s:%s:%s:", authoritative ? "" : "*", as_user, as_group);

    /* print any variables. */
    size_t var_count = 0;
    while (NULL != env_head)
    {
        printf("%s%s", (var_count ? "," : ""), env_head->name);
        env_head = env_head->next;
    }

    /* complete auth line. */
    printf("\n");

    /* success. */
    retval = 0;
    goto cleanup_config;

cleanup_config:
    fido_config_release(config);

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_policy_check_from_string, retval, user, opts, config_str,
        authoritative);

    return retval;
}
