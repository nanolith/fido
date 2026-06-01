/**
 * \file policy_proc/fido_policy_decision_parse_from_proc.c
 *
 * \brief Spawn a fido policy process and read a policy decision from this
 * process.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/error_codes.h>
#include <fido/policy_proc.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

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
    fido_policy_decision** dec, const fido_options* opts)
{
    int retval;
    int pipefd[2];
    const char** child_argv;
    char* empty_env[] = { NULL };
    pid_t child;
    fido_policy_decision* tmp = NULL;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_policy_decision_parse_from_proc, dec, opts);

    /* Create a new argument vector for the child process. */
    size_t child_argc = opts->arguments_count + 3;
    child_argv = (const char**)malloc((child_argc + 1)* sizeof(const char*));
    if (NULL == child_argv)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }

    /* initialize this argument vector. */
    child_argv[0] = "/usr/local/bin/fido";
    child_argv[1] = "-n";
    child_argv[2] = opts->binary_name;
    for (size_t i = 0; i < opts->arguments_count; ++i)
    {
        child_argv[3 + i] = opts->arguments[i];
    }

    /* execve requires the argument list to be NULL terminated. */
    child_argv[child_argc] = NULL;

    /* Set up a pipe for IPC. */
    retval = pipe(pipefd);
    if (retval < 0)
    {
        fprintf(stderr, "fido: pipe creation failed.\n");
        retval = FIDO_ERROR_PIPE;
        goto cleanup_child_argv;
    }

    /* fork the process. */
    child = fork();
    if (child < 0)
    {
        fprintf(stderr, "fido: fork failed.\n");
        retval = FIDO_ERROR_FORK;
        goto cleanup_pipe;
    }

    /* child. */
    if (0 == child)
    {
        close(pipefd[0]);
        pipefd[0] = -1;

        /* redirect standard output to our pipe. */
        retval = dup2(pipefd[1], STDOUT_FILENO);
        if (retval < 0)
        {
            _exit(1);
        }
        close(pipefd[1]);
        pipefd[1] = -1;

        /* execute the process. */
        execve("/usr/local/bin/fido", (char**)child_argv, empty_env);

        /* if execve returns, something went wrong. */
        _exit(1);
    }
    else
    {
        /* close the write end of the pipe. */
        close(pipefd[1]);
        pipefd[1] = -1;

        /* parse the decision. */
        retval = fido_policy_decision_parse_from_descriptor(&tmp, pipefd[0]);

        /* wait on the child to exit. */
        int status;
        if (waitpid(child, &status, 0) < 0)
        {
            fprintf(stderr, "error: waitpid failed.\n");
            retval = FIDO_ERROR_WAITPID;
            goto cleanup_tmp;
        }

        /* did the child exit normally? */
        if (!WIFEXITED(status))
        {
            fprintf(stderr, "error: policy process failed.\n");
            retval = FIDO_ERROR_CHILD;
            goto cleanup_tmp;
        }

        /* did the policy decision parse fail? */
        if (0 != retval)
        {
            goto cleanup_tmp;
        }

        /* success. */
        retval = 0;
        *dec = tmp;
        goto cleanup_pipe;
    }

cleanup_tmp:
    if (NULL != tmp)
    {
        fido_policy_decision_release(tmp);
    }

cleanup_pipe:
    if (pipefd[0] >= 0)
    {
        close(pipefd[0]);
    }

    if (pipefd[1] >= 0)
    {
        close(pipefd[1]);
    }

cleanup_child_argv:
    free(child_argv);

done:
    if (0 != retval)
    {
        *dec = NULL;
    }

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_policy_decision_parse_from_proc, retval, dec, opts);

    return retval;
}
