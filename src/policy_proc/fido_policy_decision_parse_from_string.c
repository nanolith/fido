/**
 * \file policy_proc/fido_policy_decision_parse_from_string.c
 *
 * \brief Parse a policy decision from a policy decision string.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <errno.h>
#include <fido/policy_proc.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static const char *USER_GROUP_CHARSET =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_-";
static const char *VARIABLE_CHARSET =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_";

/* forward decls. */
static int validate_string(const char* str, const char* allowed_set);

/**
 * \brief Parse a \ref fido_policy_decision instance from a string.
 *
 * \note The parsing process is modifies the decision string. The caller is
 * still responsible for freeing it if necessary.
 *
 * \param dec           Pointer to the \ref fido_policy_decision pointer to
 *                      receive the created policy decision on success.
 * \param dec_str       The string from which this decision is parsed.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_policy_decision_parse_from_string(
    fido_policy_decision** dec, char* dec_str)
{
    int retval;
    fido_policy_decision* tmp;
    char* str = dec_str;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_policy_decision_parse_from_string, dec, dec_str);

    /* allocate memory for this policy decision. */
    tmp = (fido_policy_decision*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }
    memset(tmp, 0, sizeof(*tmp));

    /* decode the action. */
    const char* action = strsep(&str, ":");

    /* short circuit a denial. */
    if (!strcmp(action, "deny"))
    {
        tmp->policy_decision = FIDO_POLICY_DECISION_DENY;
        *dec = tmp;
        retval = 0;
        goto done;
    }

    /* if this is NOT a permit, then we've hit a parse error. */
    if (strcmp(action, "permit"))
    {
        fprintf(stderr, "error: fido policy read.\n");
        retval = FIDO_ERROR_POLICY_READ;
        goto cleanup_tmp;
    }

    /* proceed with permit. */
    tmp->policy_decision = FIDO_POLICY_DECISION_PERMIT;

    /* parse the as user. */
    const char* as_user = strsep(&str, ":");
    retval = validate_string(as_user, USER_GROUP_CHARSET);
    if (0 != retval || '-' == as_user[0])
    {
        fprintf(stderr, "error: invalid user.\n");
        retval = FIDO_ERROR_INVALID_INPUT;
        goto cleanup_tmp;
    }

    /* save this value. */
    tmp->as_user = strdup(as_user);
    if (NULL == tmp->as_user)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto cleanup_tmp;
    }

    /* parse the group. */
    const char* as_group = strsep(&str, ":");
    retval = validate_string(as_group, USER_GROUP_CHARSET);
    if (0 != retval || '-' == as_group[0])
    {
        fprintf(stderr, "error: invalid group.\n");
        retval = FIDO_ERROR_INVALID_INPUT;
        goto cleanup_tmp;
    }

    /* save this value. */
    tmp->as_group = strdup(as_group);
    if (NULL == tmp->as_group)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto cleanup_tmp;
    }

    /* parse any add variables. */
    char* add_variable_list = strsep(&str, ":");
    while (NULL != add_variable_list)
    {
        const char* var = strsep(&add_variable_list, ",");
        retval = validate_string(var, VARIABLE_CHARSET);
        if (0 != retval)
        {
            fprintf(stderr, "error: invalid variable.\n");
            retval = FIDO_ERROR_INVALID_INPUT;
            goto cleanup_tmp;
        }

        fido_config_add_variable* vtmp;
        retval = fido_config_add_variable_create(&vtmp, var);
        if (0 != retval)
        {
            retval = FIDO_ERROR_OUT_OF_MEMORY;
            goto cleanup_tmp;
        }

        vtmp->next = tmp->variable_head;
        tmp->variable_head = vtmp;
    }

    /* success. */
    *dec = tmp;
    retval = 0;
    goto done;

cleanup_tmp:
    fido_policy_decision_release(tmp);

done:
    if (0 != retval)
    {
        *dec = NULL;
    }

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_policy_decision_parse_from_string, retval, dec, dec_str);

    return retval;
}

/**
 * \brief Validate a parsed string.
 *
 * \param str           The string to validate.
 * \param allowed_set   The allowed set of characters.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - a non-zero error code on failure.
 */
static int validate_string(const char* str, const char* allowed_set)
{
    /* return error if this string couldn't be parsed or is empty. */
    if (NULL == str || 0 == str[0])
    {
        return FIDO_ERROR_INVALID_INPUT;
    }

    /* if a non-matching character is found, this is an error. */
    if (strlen(str) != strspn(str, allowed_set))
    {
        return FIDO_ERROR_INVALID_INPUT;
    }

    return 0;
}
