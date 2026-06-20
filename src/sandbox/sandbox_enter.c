/**
 * \file sandbox/sandbox_enter.c
 *
 * \brief Enter a restrictive sandbox.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/sandbox.h>
#include <unistd.h>

#ifdef __FreeBSD__
#include <sys/capsicum.h>
#endif

/**
 * \brief Enter sandbox mode via capsicum on FreeBSD or pledge / unveil on
 * OpenBSD.
 *
 * \param fd            The file descriptor for the input file to restrict.
 *
 * \returns 0 on success and non-zero on failure.
 */
int FN_DECL_MUST_CHECK sandbox_enter(int fd)
{
    int retval;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(sandbox_enter, fd);

#if defined(__FreeBSD__)
    if (fd >= 0)
    {
        cap_rights_t rights;

        /* Initialize a cap rights structure to allow reading and stat. */
        cap_rights_init(&rights, CAP_READ, CAP_FSTAT);

        /* restrict rights on the descriptor to read only. */
        retval = cap_rights_limit(fd, &rights);
        if (0 != retval)
        {
            retval = FIDO_ERROR_SANDBOX;
            goto done;
        }
    }

    /* enter capsicum; no other policy can be set after this point. */
    retval = cap_enter();
    if (0 != retval)
    {
        retval = FIDO_ERROR_SANDBOX;
        goto done;
    }

#elif defined(__OpenBSD__)
    /* Set a dummy unveil policy for /tmp. */
    retval = unveil("/tmp", "");
    if (0 != retval)
    {
        retval = FIDO_ERROR_SANDBOX;
        goto done;
    }

    /* lock down any future calls to unveil. */
    retval = unveil(NULL, NULL);
    if (0 != retval)
    {
        retval = FIDO_ERROR_SANDBOX;
        goto done;
    }

    /* pledge to only doing I/O on open descriptors. */
    retval = pledge("stdio", "stdio");
    if (0 != retval)
    {
        retval = FIDO_ERROR_SANDBOX;
        goto done;
    }
#else
#error "Unsupported platform."
#endif

    /* success. */
    retval = 0;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(sandbox_enter, retval, fd);

    return retval;
}
