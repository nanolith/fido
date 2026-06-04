/**
 * \file fido/env.h
 *
 * \brief Methods for interfacing with the environment.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <sys/tree.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

typedef struct fido_env_node fido_env_node;
struct fido_env_node
{
    RB_ENTRY(fido_env_node) node;
    char* key;
    char* value;
};

typedef struct fido_env fido_env;
struct fido_env
{
    RB_HEAD(fido_env_tree, fido_env_node) head;
    size_t count;
};

/******************************************************************************/
/* Start of model checking properties.                                        */
/******************************************************************************/

/**
 * \brief Valid \ref fido_env_node property.
 *
 * \param node          The node to check.
 *
 * \returns true if the node is valid.
 */
bool
property_fido_env_node_valid(
    const fido_env_node* node);

/**
 * \brief Valid \ref fido_env property.
 *
 * \param env           The env to check.
 *
 * \returns true if the env is valid.
 */
bool
property_fido_env_valid(
    const fido_env* env);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Create an empty env instance.
 *
 * \param env           Pointer to the \ref fido_env pointer to
 *                      receive the created environment instance on success.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_env_create(fido_env** env);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_env_create, fido_env** env)
        /* the environment pointer is valid. */
        MODEL_CHECK_OBJECT_RW(env, sizeof(*env));
MODEL_CONTRACT_PRECONDITIONS_END(fido_env_create)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_env_create, int retval, fido_env** env)
        /* on success... */
        if (0 == retval)
        {
            /* the environment is valid. */
            MODEL_ASSERT(property_fido_env_valid(*env));
        }
        else
        {
            /* this is a defined error code. */
            enum fido_error_code error = (enum fido_error_code)retval;
            MODEL_ASSERT(__CPROVER_enum_is_in_range(error));
            /* env is set to NULL. */
            MODEL_ASSERT(NULL == *env);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_env_create)

/**
 * \brief Release a \ref fido_env instance.
 *
 * \param env           The instance to release.
 */
void fido_env_release(fido_env* env);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_env_release, fido_env* env)
        /* env points to a region of memory large enough to hold it. */
        MODEL_CHECK_OBJECT_RW(env, sizeof(*env));
MODEL_CONTRACT_PRECONDITIONS_END(fido_env_release)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_env_release, fido_env* env)
MODEL_CONTRACT_POSTCONDITIONS_END(fido_env_release)

/**
 * \brief Create a \ref fido_env_node instance.
 *
 * \param node          Pointer to the \ref fido_env_node pointer to
 *                      receive the created node instance on success.
 * \param key           The key for this node.
 * \param value         The optional value for this node (set to NULL if not
 *                      used).
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_env_node_create(fido_env_node** node, const char* key, const char* value);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_env_node_create, fido_env_node** node, const char* key,
    const char* value)
        /* the node pointer is valid. */
        MODEL_CHECK_OBJECT_RW(node, sizeof(*node));
        /* key is not NULL. */
        MODEL_ASSERT(NULL != key);
MODEL_CONTRACT_PRECONDITIONS_END(fido_env_node_create)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_env_node_create, int retval, fido_env_node** node, const char* key,
    const char* value)
        /* on success... */
        if (0 == retval)
        {
            /* the node is valid. */
            MODEL_ASSERT(property_fido_env_node_valid(*node));
        }
        else
        {
            /* this is a defined error code. */
            enum fido_error_code error = (enum fido_error_code)retval;
            MODEL_ASSERT(__CPROVER_enum_is_in_range(error));
            /* node is set to NULL. */
            MODEL_ASSERT(NULL == *node);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_env_node_create)

/**
 * \brief Release a \ref fido_node_env instance.
 *
 * \param node          The instance to release.
 */
void fido_env_node_release(fido_env_node* node);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_env_node_release, fido_env_node* node)
        /* node points to a region of memory large enough to hold it. */
        MODEL_CHECK_OBJECT_RW(node, sizeof(*node));
MODEL_CONTRACT_PRECONDITIONS_END(fido_env_node_release)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_env_node_release, fido_env_node* node)
MODEL_CONTRACT_POSTCONDITIONS_END(fido_env_node_release)

/**
 * \brief Create an variable array from an environment instance.
 *
 * \param varr          Pointer to the variable array pointer to receive the
 *                      created variable array on success.
 * \param env           The \ref fido_env instance for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_env_vararray_create(void** varr, const fido_env* env);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_env_vararray_create, void** varr, const fido_env* env)
        /* the node pointer is valid. */
        MODEL_CHECK_OBJECT_RW(varr, sizeof(*varr));
        /* the environment is valid. */
        MODEL_ASSERT(property_fido_env_valid(env));
MODEL_CONTRACT_PRECONDITIONS_END(fido_env_vararray_create)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_env_vararray_create, int retval, void** varr, const fido_env* env)
        /* on success... */
        if (0 == retval)
        {
            MODEL_ASSERT(NULL != varr);
        }
        else
        {
            /* this is a defined error code. */
            enum fido_error_code error = (enum fido_error_code)retval;
            MODEL_ASSERT(__CPROVER_enum_is_in_range(error));
            /* varr is set to NULL. */
            MODEL_ASSERT(NULL == varr);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_env_vararray_create)

/**
 * \brief Release a variable array instance.
 *
 * \param varr          The instance to release.
 */
int FN_DECL_MUST_CHECK
fido_env_vararray_release(char** varr);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_env_vararray_release, char** varr)
        /* the variable array is not NULL. */
        MODEL_ASSERT(NULL != varr);
        /* TODO - sample an entry to show that it is allocated. */
MODEL_CONTRACT_PRECONDITIONS_END(fido_env_vararray_release)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_env_vararray_release, char** varr)
MODEL_CONTRACT_POSTCONDITIONS_END(fido_env_vararray_release)

/******************************************************************************/
/* Public methods.                                                            */
/******************************************************************************/

/**
 * \brief Compare two nodes.
 *
 * \param lhs           The left-hand-side of the comparison.
 * \param rhs           The right-hand-side of the comparison.
 *
 * \returns a comparison result
 *      - < 0 if lhs < rhs
 *      - > 0 if lhs > rhs
 *      - 0 if lhs == rhs
 */
int fido_env_node_compare(const fido_env_node* lhs, const fido_env_node* rhs);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_env_node_compare, const fido_env_node* lhs, const fido_env_node* rhs)
        /* lhs and rhs are valid. */
        MODEL_ASSERT(property_fido_env_node_valid(lhs));
        MODEL_ASSERT(property_fido_env_node_valid(rhs));
MODEL_CONTRACT_PRECONDITIONS_END(fido_env_node_compare)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_env_node_compare, int retval, const fido_env_node* lhs,
    const fido_env_node* rhs)
MODEL_CONTRACT_POSTCONDITIONS_END(fido_env_node_compare)

/**
 * \brief Add or replace an environment variable node in an environment
 * instance.
 *
 * \note On success, \p env takes ownership of \p node.
 *
 * \param env           The env to which this node is added.
 * \param node          The node to add or replace.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_env_node_add_or_replace(fido_env* env, fido_env_node* node);

/* function contract preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    fido_env_node_add_or_replace, fido_env* env, fido_env_node* node)
        /* env is valid. */
        MODEL_ASSERT(property_fido_env_valid(env));
        /* node is valid. */
        MODEL_ASSERT(property_fido_env_node_valid(node));
MODEL_CONTRACT_PRECONDITIONS_END(fido_env_node_add_or_replace)

/* function contract postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    fido_env_node_add_or_replace, int retval, fido_env* env,
    fido_env_node* node)
        /* on failure... */
        if (0 != retval)
        {
            /* this is a defined error code. */
            enum fido_error_code error = (enum fido_error_code)retval;
            MODEL_ASSERT(__CPROVER_enum_is_in_range(error));
        }
MODEL_CONTRACT_POSTCONDITIONS_END(fido_env_node_add_or_replace)

/******************************************************************************/
/* Helper methods.                                                            */
/******************************************************************************/

/* Red-black tree declarations. */
RB_PROTOTYPE(fido_env_tree, fido_env_node, node, fido_env_node_compare)

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
