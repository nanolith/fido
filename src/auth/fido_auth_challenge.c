/**
 * \file auth/fido_auth_challenge.c
 *
 * \brief Issue an authentication challenge to the user.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/auth.h>
#include <fcntl.h>
#include <stdio.h>

#ifdef   __FreeBSD__
#include <security/pam_appl.h>
#include <security/openpam.h>
#endif /*__FreeBSD__*/

#ifdef __OpenBSD__
#include <bsd_auth.h>
#endif /*__OpenBSD__*/

/* forward decls. */
#ifdef   __FreeBSD__
static int open_pam_auth_challenge(const fido_user* user);
static void try_set_tty(pam_handle_t* pam);
#endif /*__FreeBSD__*/

/**
 * \brief Provide an authentication challenge, read the response, and verify it
 * using either BSD Auth (OpenBSD) or PAM (FreeBSD / etc).
 *
 * \param user          The user for this challenge.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_auth_challenge(const fido_user* user)
{
    int retval;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_auth_challenge, user);

#if   defined(__FreeBSD__)
    retval = open_pam_auth_challenge(user);
#elif defined(__OpenBSD__)
    retval = auth_userokay(user->username, NULL, NULL, NULL);
    if (0 == retval)
    {
        retval = FIDO_ERROR_AUTH;
    }
    else
    {
        retval = 0;
    }
#else
    #error "Authentication Unsupported!"
#endif

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(fido_auth_challenge, retval, user);

    return retval;
}

#ifdef   __FreeBSD__
/**
 * \brief Use FreeBSD's OpenPAM implementation to issue a user challenge.
 *
 * \param user              The user details for the challenge.
 *
 * \returns a status code indicating success or failure.
 *      - 0 on success.
 *      - non-zero on failure.
 */
static int open_pam_auth_challenge(const fido_user* user)
{
    int retval;
    pam_handle_t* pam;
    struct pam_conv ttyconv = {
        .conv = openpam_ttyconv,
        .appdata_ptr = NULL
    };

    /* start the PAM transaction. */
    retval = pam_start("fido", user->username, &ttyconv, &pam);
    if (PAM_SUCCESS != retval)
    {
        fprintf(stderr, "error: PAM initialization failed: %s\n",
                pam_strerror(pam, retval));
        retval = FIDO_ERROR_PAM;
        goto done;
    }

    /* Set the tty. */
    try_set_tty(pam);

    /* issue the user challenge. */
    retval = pam_authenticate(pam, 0);
    if (PAM_SUCCESS != retval)
    {
        fprintf(stderr, "error: authentication failed: %s\n",
                pam_strerror(pam, retval));
        pam_end(pam, retval);
        retval = FIDO_ERROR_AUTH;
        goto done;
    }

    /* verify account status. */
    retval = pam_acct_mgmt(pam, 0);
    if (PAM_SUCCESS != retval)
    {
        fprintf(stderr, "error: user rejected: %s\n",
                pam_strerror(pam, retval));
        pam_end(pam, retval);
        retval = FIDO_ERROR_BAD_USER;
        goto done;
    }

    /* success. */
    pam_end(pam, PAM_SUCCESS);
    retval = 0;
    goto done;

done:
    return retval;
}

/**
 * \brief Attempt to set the PAM TTY.
 *
 * \param pam           The PAM handle.
 */
static void try_set_tty(pam_handle_t* pam)
{
    /* attempt to get the current tty. */
    int fd = open("/dev/tty", O_RDONLY | O_NONBLOCK | O_NOCTTY | O_CLOEXEC);
    if (fd >= 0)
    {
        const char* tty = ttyname(fd);
        if (NULL != tty)
        {
            pam_set_item(pam, PAM_TTY, tty);
        }
        close(fd);
    }
    /* fall back to stderr. */
    else
    {
        const char* tty = ttyname(STDERR_FILENO);
        if (NULL != tty)
        {
            pam_set_item(pam, PAM_TTY, tty);
        }
    }
}
#endif /*__FreeBSD__*/
