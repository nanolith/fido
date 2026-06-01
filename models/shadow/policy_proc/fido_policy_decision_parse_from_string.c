/**
 * \file models/shadow/policy_proc/fido_policy_decision_parse_from_string.c
 *
 * \brief Shadow implementation of \ref fido_policy_decision_parse_from_string.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/policy_proc.h>
#include <string.h>

int nondet_retval();

int choose_decision()
{
    int retval = nondet_retval();
    enum fido_policy_decision_type dt = (enum fido_policy_decision_type)retval;
    MODEL_ASSUME(__CPROVER_enum_is_in_range(dt));

    return retval;
}

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
    char str[8];

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_policy_decision_parse_from_string, dec, dec_str);

    retval = nondet_retval();
    enum fido_error_code ec = (enum fido_error_code)retval;
    MODEL_ASSUME(0 == retval || __CPROVER_enum_is_in_range(ec));

    if (0 != retval)
    {
        goto done;
    }

    tmp = (fido_policy_decision*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        /* skip this decision leaf. */
        MODEL_ASSUME(0);
    }

    memset(tmp, 0, sizeof(*tmp));
    tmp->policy_decision = choose_decision();

    /* short circuit deny. */
    if (FIDO_POLICY_DECISION_DENY == tmp->policy_decision)
    {
        retval = 0;
        *dec = tmp;
        goto done;
    }

    __CPROVER_havoc_object(str);
    str[sizeof(str)-1] = 0;
    MODEL_ASSUME(str[0] != 0);

    tmp->as_user = strdup(str);
    if (NULL == tmp->as_user)
    {
        /* skip this decision leaf. */
        MODEL_ASSUME(0);
    }

    __CPROVER_havoc_object(str);
    str[sizeof(str)-1] = 0;
    MODEL_ASSUME(str[0] != 0);

    tmp->as_group = strdup(str);
    if (NULL == tmp->as_group)
    {
        /* skip this decision leaf. */
        MODEL_ASSUME(0);
    }

    int vars = nondet_retval();
    MODEL_ASSUME(vars >= 0 && vars <= 2);
    for (int i = 0; i < vars; ++i)
    {
        fido_config_add_variable* var;
        retval = fido_config_add_variable_create_random(&var);
        if (0 != retval)
        {
            /* skip this decision leaf. */
            MODEL_ASSUME(0);
        }

        var->next = tmp->variable_head;
        tmp->variable_head = var;
    }

    /* success. */
    *dec = tmp;
    retval = 0;
    goto done;

done:
    if (0 != retval)
    {
        *dec = NULL;
    }

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_policy_decision_parse_from_string, retval, dec, dec_str);

    return retval;
}
