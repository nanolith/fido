/**
 * \file fido/main.c
 *
 * \brief Entry point for fido.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <errno.h>
#include <fcntl.h>
#include <fido/auth.h>
#include <fido/config.h>
#include <fido/options.h>
#include <fido/policy.h>
#include <fido/policy_proc.h>
#include <fido/sandbox.h>
#include <fido/user.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/* forward decls. */
static int setup_process(void);
static int policy_check(const fido_user* user, const fido_options* opts);

/**
 * \brief Entry point for fido.
 *
 * \param argc          Argument count.
 * \param argv          Arguments.
 *
 * \returns 0 on success an non-zero on error.
 */
int main(int argc, char* argv[])
{
    int retval;
    fido_user* user = NULL;
    fido_options* opts = NULL;
    fido_policy_decision* dec = NULL;

    /* basic program setup. */
    retval = setup_process();
    if (0 != retval)
    {
        fprintf(stderr, "error: setup_process failed.\n");
        goto done;
    }

    /* get the user details. */
    retval = fido_user_create(&user);
    if (0 != retval)
    {
        fprintf(stderr, "error: could not get user details.\n");
        goto done;
    }

    /* parse the command line options. */
    retval = fido_options_parse(&opts, argc, (const char**)argv);
    if (0 != retval)
    {
        goto done;
    }

    /* should we perform a policy check? */
    if (opts->dry_run || NULL != opts->config_file_override)
    {
        retval = policy_check(user, opts);
        goto done;
    }

    /* make an authorization decision. */
    retval = fido_policy_decision_parse_from_proc(&dec, opts);
    if (0 != retval || FIDO_POLICY_DECISION_DENY == dec->policy_decision)
    {
        fprintf(stderr, "error: not authorized.\n");
        goto done;
    }

    /* from here on out, we must be running with an effective UID of root. */
    if (0 != geteuid())
    {
        fprintf(stderr, "error: fido binary is not setuid root.\n");
        goto done;
    }

    /* challenge the user. */
    retval = fido_auth_challenge(user);
    if (0 != retval)
    {
        goto done;
    }

    printf("Execution not yet implemented.\n");
    retval = 1;
    goto done;

done:
    if (NULL != opts)
    {
        fido_options_release(opts);
    }

    if (NULL != user)
    {
        fido_user_release(user);
    }

    if (NULL != dec)
    {
        fido_policy_decision_release(dec);
    }

    if (0 != retval)
        return 1;
    else
        return 0;
}

/**
 * \brief Set up the process by closing other file handles and setting the
 * process name.
 *
 * \returns 0 on success and non-zero on error.
 */
static int setup_process(void)
{
    setprogname("fido");

    /* make sure we aren't holding onto any other descriptors. */
    closefrom(STDERR_FILENO + 1);

    return 0;
}

/**
 * \brief Perform a policy check.
 *
 * \param user          The user for this policy check.
 * \param opts          The options for this policy check.
 *
 * \returns 0 on success and non-zero on error.
 */
static int policy_check(const fido_user* user, const fido_options* opts)
{
    int retval, fd;
    bool authoritative;
    const char* confname;

    /* are we testing a new configuration file? */
    if (NULL != opts->config_file_override)
    {
        confname = opts->config_file_override;
        authoritative = false;
    }
    else
    {
        confname = "/etc/fido.conf";
        authoritative = true;
    }

    /* open the file for reading. */
    errno = 0;
    fd = open(confname, O_RDONLY);
    int open_errno = errno;

    /* After opening the file, enter our sandbox. */
    retval = sandbox_enter();
    if (0 != retval)
    {
        fprintf(stderr, "error: could not enter sandbox.\n");
        goto done;
    }

    /* if the file does not exist, then fall back to our default policy. */
    if (fd < 0 && ENOENT == open_errno)
    {
        retval = fido_policy_check_from_string(user, opts, "", true);
        goto done;
    }
    /* if we failed to open the file for any other reason, report the error. */
    else if (fd < 0)
    {
        fprintf(stderr, "error: could not open config file.\n");
        retval = FIDO_ERROR_CONFIG_FILE_OPEN;
        goto done;
    }
    /* otherwise, use this file descriptor to derive our policy. */
    else
    {
        retval =
            fido_policy_check_from_descriptor(user, opts, fd, authoritative);
        goto cleanup_fd;
    }

cleanup_fd:
    close(fd);

done:
    return retval;
}
