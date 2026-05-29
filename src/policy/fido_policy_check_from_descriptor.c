/**
 * \file policy/fido_policy_check_from_descriptor.c
 *
 * \brief Perform a policy check using the given config file descriptor.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/policy.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * \brief Perform a policy check from the given config file descriptor.
 *
 * \note Authoritative policy decisions will additionally check file ownership
 * and permission metadata to ensure that it is only root writeable; the policy
 * check automatically fails if the file backing this descriptor can be modified
 * by anyone other than root.
 *
 * \param user          The user for this policy check.
 * \param opts          The options for this policy check.
 * \param fd            The descriptor of the config file.
 * \param authoritative A flag to indicate whether the policy decision is
 *                      authoritative.
 *
 * \returns 0 on success and non-zero on error.
 */
int FN_DECL_MUST_CHECK
fido_policy_check_from_descriptor(
    const fido_user* user, const fido_options* opts, int fd,
    bool authoritative)
{
    int retval = 0;
    struct stat st;
    char* buffer = NULL;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_policy_check_from_descriptor, user, opts, fd, authoritative);

    /* stat the descriptor. */
    retval = fstat(fd, &st);
    if (0 != retval)
    {
        fprintf(stderr, "error: could not stat config file.\n");
        retval = FIDO_ERROR_CONFIG_FILE_STAT;
        goto done;
    }

    /* authoritative checks should verify config file permissions. */
    if (authoritative)
    {
        /* ensure that this file is owned by root. */
        if (0 != st.st_uid)
        {
            fprintf(stderr, "error: config file is not owned by root.\n");
            retval = FIDO_ERROR_CONFIG_FILE_PERMISSIONS;
            goto done;
        }

        /* ensure that this file is writeable only by root. */
        if (0 != (st.st_mode & (S_IWGRP | S_IWOTH)))
        {
            fprintf(stderr, "error: config file is writeable by non-root.\n");
            retval = FIDO_ERROR_CONFIG_FILE_PERMISSIONS;
            goto done;
        }
    }

    /* calculate file size. */
    ssize_t filesize = st.st_size;
    if (filesize < 0)
    {
        fprintf(stderr, "error: invalid config file size.\n");
        retval = FIDO_ERROR_CONFIG_FILE_READ;
        goto done;
    }

    /* allocate a buffer large enough to hold the config. */
    buffer = (char*)malloc(filesize + 1);
    if (NULL == buffer)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }
    memset(buffer, 0, filesize + 1);

    /* read config data. */
    ssize_t size = read(fd, buffer, filesize);
    if (size != filesize)
    {
        fprintf(stderr, "error: config file read failed.\n");
        retval = FIDO_ERROR_CONFIG_FILE_READ;
        goto cleanup_buffer;
    }
    buffer[filesize] = 0;

    /* perform the policy check. */
    retval = fido_policy_check_from_string(user, opts, buffer, authoritative);
    goto cleanup_buffer;

cleanup_buffer:
    free(buffer);

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_policy_check_from_descriptor, retval, user, opts, fd,
        authoritative);

    return retval;
}
