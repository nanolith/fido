/**
 * \file models/sandbox/sandbox_enter/main.c
 *
 * \brief Model checks for \ref sandbox_enter.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fcntl.h>
#include <fido/sandbox.h>

int main(int argc, char* argv[])
{
    int retval;
    int fd = -1;
    char filename[8];

    /* set the filename. */
    __CPROVER_havoc_object(filename);
    filename[sizeof(filename)-1] = 0;

    /* open a file. */
    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        goto done;
    }

    /* enter sandbox. */
    retval = sandbox_enter(fd);
    if (0 != retval)
    {
        goto done;
    }

done:
    if (fd >= 0)
    {
        close(fd);
    }

    return retval;
}
