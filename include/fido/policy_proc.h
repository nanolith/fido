/**
 * \file fido/policy_proc.h
 *
 * \brief Methods for interfacing with the policy process.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <fido/config.h>
#include <fido/function_contracts.h>
#include <fido/function_decl.h>
#include <fido/model_assert.h>
#include <fido/options.h>
#include <fido/properties/unix.h>
#include <stdbool.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief Policy decision type enumeration.
 */
enum fido_policy_decision_type
{
    /** \brief Deny is the default. Don't allow this action. */
    FIDO_POLICY_DECISION_DENY,
    /** \brief Permit the action. */
    FIDO_POLICY_DECISION_PERMIT,
};

/**
 * \brief Policy decision.
 */
typedef struct fido_policy_decision fido_policy_decision;
struct fido_policy_decision
{
    int policy_decision;
    char* as_user;
    char* as_group;
    fido_config_add_variable* variable_head;
};

/******************************************************************************/
/* Start of model checking properties.                                        */
/******************************************************************************/

/**
 * \brief Valid policy decision record property.
 *
 * \param dec           The policy decision record to check.
 *
 * \returns true if the policy decision record is valid.
 */
bool
property_fido_policy_decision_valid(
    const fido_policy_decision* dec);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Spawn a fido policy process to get a decision about the given options.
 *
 * \param dec           Pointer to the \ref fido_policy_decision pointer to
 *                      receive the created policy decision on success.
 * \param opts          The options used for this decision process.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_policy_decision_parse_from_proc(
    fido_policy_decision** dec, const fido_options* opts);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_policy_decision_parse_from_proc, fido_policy_decision** dec,
    const fido_options* opts)
        /* the decision pointer is valid. */
        MODEL_CHECK_OBJECT_RW(dec, sizeof(*dec));
        /* the options record is valid. */
        MODEL_ASSERT(property_fido_options_valid(opts));
MODEL_CONTRACT_PRECONDITIONS_END(fido_policy_decision_parse_from_proc)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_policy_decision_parse_from_proc, int retval,
    fido_policy_decision** dec, const fido_options* opts)
        /* on success... */
        if (0 == retval)
        {
            /* the decision is valid. */
            MODEL_ASSERT(property_fido_policy_decision_valid(*dec));
        }
        else
        {
            /* this is a defined error code. */
            enum fido_error_code error = (enum fido_error_code)retval;
            MODEL_ASSERT(__CPROVER_enum_is_in_range(error));
            /* dec is set to NULL. */
            MODEL_ASSERT(NULL == *dec);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_policy_decision_parse_from_proc)

/**
 * \brief Parse a \ref fido_policy_decision instance from a descriptor.
 *
 * \param dec           Pointer to the \ref fido_policy_decision pointer to
 *                      receive the created policy decision on success.
 * \param fd            The descriptor from which the policy decision is read.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_policy_decision_parse_from_descriptor(fido_policy_decision** dec, int fd);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_policy_decision_parse_from_descriptor, fido_policy_decision** dec,
    int fd)
        /* the decision pointer is valid. */
        MODEL_CHECK_OBJECT_RW(dec, sizeof(*dec));
        /* the descriptor is open. */
        MODEL_ASSERT(property_file_descriptor_open(fd));
MODEL_CONTRACT_PRECONDITIONS_END(fido_policy_decision_parse_from_descriptor)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_policy_decision_parse_from_descriptor, int retval,
    fido_policy_decision** dec, int fd)
        /* on success... */
        if (0 == retval)
        {
            /* the decision is valid. */
            MODEL_ASSERT(property_fido_policy_decision_valid(*dec));
        }
        else
        {
            /* this is a defined error code. */
            enum fido_error_code error = (enum fido_error_code)retval;
            MODEL_ASSERT(__CPROVER_enum_is_in_range(error));
            /* dec is set to NULL. */
            MODEL_ASSERT(NULL == *dec);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_policy_decision_parse_from_descriptor)

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
    fido_policy_decision** dec, char* dec_str);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_policy_decision_parse_from_string, fido_policy_decision** dec,
    char* dec_str)
        /* the decision pointer is valid. */
        MODEL_CHECK_OBJECT_RW(dec, sizeof(*dec));
        /* the decision string is valid. */
        MODEL_ASSERT(NULL != dec_str);
MODEL_CONTRACT_PRECONDITIONS_END(fido_policy_decision_parse_from_string)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_policy_decision_parse_from_string, int retval,
    fido_policy_decision** dec, char* dec_str)
        /* on success... */
        if (0 == retval)
        {
            /* the decision is valid. */
            MODEL_ASSERT(property_fido_policy_decision_valid(*dec));
        }
        else
        {
            /* this is a defined error code. */
            enum fido_error_code error = (enum fido_error_code)retval;
            MODEL_ASSERT(__CPROVER_enum_is_in_range(error));
            /* dec is set to NULL. */
            MODEL_ASSERT(NULL == *dec);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_policy_decision_parse_from_string)

/**
 * \brief Release a \ref fido_policy_decision instance.
 *
 * \param dec           The policy decision record to release.
 */
void
fido_policy_decision_release(fido_policy_decision* dec);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_policy_decision_release, fido_policy_decision* dec)
        /* dec points to a region of memory large enough to hold it. */
        MODEL_CHECK_OBJECT_RW(dec, sizeof(*dec));
MODEL_CONTRACT_PRECONDITIONS_END(fido_policy_decision_release)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_policy_decision_release, fido_policy_decision* dec)
MODEL_CONTRACT_POSTCONDITIONS_END(fido_policy_decision_release)

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
