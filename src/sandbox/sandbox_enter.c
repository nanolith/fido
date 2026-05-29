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
 * \returns 0 on success and non-zero on failure.
 */
int FN_DECL_MUST_CHECK sandbox_enter(void)
{
    int retval;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(sandbox_enter, );

#if defined(__FreeBSD__)
    /* enter capsicum; no other policy is set so only I/O on existing
     * descriptors is allowed. */
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
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(sandbox_enter, retval);

    return retval;
}
