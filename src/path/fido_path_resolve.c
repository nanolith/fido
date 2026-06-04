/**
 * \file path/fido_path_resolve.c
 *
 * \brief Resolve a command with the given path.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/path.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

/**
 * \brief Resolve a command given the following path; copy the current command
 * if the provided path includes a slash in it already.
 *
 * \param resolved      On success, this holds a copy of the resolved path.
 * \param input_path    The input path to consider.
 * \param command       The command to resolve.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_path_resolve(char** resolved, const char* input_path, const char* command)
{
    int retval;
    char* path = NULL;
    char buffer[PATH_MAX];
    struct stat st;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_path_resolve, resolved, input_path, command);

    /* don't resolve the path further if it has a path element already. */
    if (NULL != strchr(command, '/'))
    {
        *resolved = realpath(command, NULL);
        if (NULL == *resolved)
        {
            retval = FIDO_ERROR_OUT_OF_MEMORY;
            goto done;
        }

        retval = 0;
        goto done;
    }

    /* if the input path is NULL, we can't resolve this command. */
    if (NULL == input_path)
    {
        retval = FIDO_ERROR_PATH_RESOLUTION;
        goto done;
    }

    path = strdup(input_path);
    if (NULL == path)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }

    for (char* p = path; NULL != p && 0 != p[0];)
    {
        char* path_entry = strsep(&p, ":");

        if (NULL != path_entry && 0 != path_entry[0])
        {
            int sz =
                snprintf(buffer, sizeof(buffer), "%s/%s", path_entry, command);
            if (sz > 0 && (size_t)sz < sizeof(buffer))
            {
                /* skip if the file doesn't exist. */
                retval = stat(buffer, &st);
                if (retval < 0)
                {
                    continue;
                }

                /* skip if the file isn't executable. */
                if (0 == (st.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)))
                {
                    continue;
                }

                /* copy the resolved file. */
                *resolved = realpath(buffer, NULL);
                if (NULL == *resolved)
                {
                    retval = FIDO_ERROR_OUT_OF_MEMORY;
                    goto done;
                }

                /* success. */
                retval = 0;
                goto done;
            }
        }
    }

    /* file not found. */
    retval = FIDO_ERROR_PATH_RESOLUTION;
    goto done;

done:
    if (NULL != path)
    {
        free(path);
    }

    if (0 != retval)
    {
        *resolved = NULL;
    }

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_path_resolve, retval, resolved, input_path, command);

    return retval;
}
