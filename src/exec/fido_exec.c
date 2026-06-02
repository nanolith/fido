/**
 * \file exec/fido_exec.c
 *
 * \brief Execute the command.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/exec.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * \brief Execute a binary using the given options.
 *
 * \param opts          The options to use for this binary.
 * \param env           The environment to pass to this binary.
 *
 * \returns 0 on success and non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_exec(const fido_options* opts, const char** env)
{
    int retval;
    const char** child_argv;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_exec, opts, env);

    /* Create a new argument vector for the child process. */
    size_t child_argc = opts->arguments_count + 1;
    child_argv = (const char**)malloc((child_argc + 1) * sizeof(const char*));
    if (NULL == child_argv)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }

    /* initialize the argument vector. */
    child_argv[0] = opts->original_binary_name;
    for (size_t i = 0; i < opts->arguments_count; ++i)
    {
        child_argv[1 + i] = opts->arguments[i];
    }

    /* execve requires the argument list to be NULL terminated. */
    child_argv[child_argc] = NULL;

    /* execute. */
    (void)execve(opts->binary_name, (char**)child_argv, (char**)env);

    /* if we get this far, something went wrong. */
    retval = FIDO_ERROR_EXEC;
    goto cleanup_child_argv;

cleanup_child_argv:
    free(child_argv);

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_exec, retval, opts, env);

    return retval;
}
