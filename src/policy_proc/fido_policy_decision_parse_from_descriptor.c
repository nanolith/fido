/**
 * \file policy_proc/fido_policy_decision_parse_from_descriptor.c
 *
 * \brief Parse a policy decision from the policy decision process.
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

#define MAX_BUFFER_SIZE (64 * 1024)

/* forward decls. */
static int read_policy_string(char* buffer, size_t buffer_size, int fd);

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
fido_policy_decision_parse_from_descriptor(fido_policy_decision** dec, int fd)
{
    int retval;
    char buffer[MAX_BUFFER_SIZE];

    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        fido_policy_decision_parse_from_descriptor, dec, fd);

    /* read the decision. */
    retval = read_policy_string(buffer, sizeof(buffer), fd);
    if (0 != retval)
    {
        goto done;
    }

    /* parse this string. */
    retval = fido_policy_decision_parse_from_string(dec, buffer);
    if (0 != retval)
    {
        goto done;
    }

    /* goto done. */
    retval = 0;
    goto done;

done:
    if (0 != retval)
    {
        *dec = NULL;
    }

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_policy_decision_parse_from_descriptor, retval, dec, fd);

    return retval;
}

/**
 * \brief Read a policy string into the buffer.
 *
 * \param buffer            The buffer into which this string is read.
 * \param buffer_size       The maximum buffer size.
 * \param fd                The file descriptor for this read.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - a non-zero error code on failure.
 */
static int read_policy_string(char* buffer, size_t buffer_size, int fd)
{
    /* read the policy decision string. */
    errno = 0;
    ssize_t bytes_read = read(fd, buffer, buffer_size - 1);
    if (bytes_read < 0 && errno == EINTR)
    {
        fprintf(stderr, "error: fido interrupted.\n");
        return FIDO_ERROR_INTERRUPTED;
    }
    else if (bytes_read <= 0)
    {
        fprintf(stderr, "error: fido policy read.\n");
        return FIDO_ERROR_POLICY_READ;
    }

    /* null terminate the read bytes. */
    buffer[buffer_size] = 0;

    /* make sure the buffer is a complete line. */
    char* eol = strchr(buffer, '\n');
    if (NULL == eol)
    {
        fprintf(stderr, "error: fido policy truncated\n");
        return FIDO_ERROR_POLICY_READ;
    }

    /* strip the newline. */
    *eol = 0;

    /* success. */
    return 0;
}
