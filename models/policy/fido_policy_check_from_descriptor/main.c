/**
 * \file models/policy/fido_policy_check_from_string/main.c
 *
 * \brief Model checks for * \ref fido_policy_check_from_descriptor.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fcntl.h>
#include <fido/config.h>
#include <fido/options.h>
#include <fido/policy.h>
#include <unistd.h>

#include "../../helpers/config/config_helpers.h"
#include "../../helpers/options/options_helpers.h"
#include "../../shadow/unix/unix_shadow.h"

int nondet_retval();
bool nondet_bool();

bool choose_auth()
{
    return nondet_bool();
}

static char filename[8];

const char* choose_filename()
{
    __CPROVER_havoc_object(filename);
    filename[sizeof(filename)-1]=0;

    return filename;
}

int main(int argc, char* argv[])
{
    int retval, fd;
    fido_options* opts;
    fido_user* user;
    fido_config_role* role;

    /* initialize unix shadow subsystem. */
    unix_init();

    /* create options. */
    retval = fido_options_create_random(&opts);
    if (0 != retval)
    {
        goto done;
    }

    /* create user. */
    retval = fido_user_create_random(&user);
    if (0 != retval)
    {
        goto cleanup_opts;
    }

    /* open file descriptor. */
    fd = open(choose_filename(), O_RDONLY);
    if (fd < 0)
    {
        retval = FIDO_ERROR_CONFIG_FILE_OPEN;
        goto cleanup_user;
    }

    /* check to see if the policy matches. */
    retval =
        fido_policy_check_from_descriptor(
            user, opts, fd, choose_auth());
    if (0 != retval)
    {
        goto close_fd;
    }

    retval = 0;
    goto close_fd;

close_fd:
    close(fd);

cleanup_user:
    fido_user_release(user);

cleanup_opts:
    fido_options_release(opts);

done:
    return retval;
}
