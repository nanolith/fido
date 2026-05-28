/**
 * \file fido/main.c
 *
 * \brief Entry point for fido.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/options.h>
#include <fido/user.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* forward decls. */
static int setup_process(void);

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

    printf("Not yet implemented.\n");
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
    closefrom(STDERR_FILENO + 1);

    return 0;
}
