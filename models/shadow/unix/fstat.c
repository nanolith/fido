/**
 * \file models/shadow/unix/fstat.c
 *
 * \brief fstat shadow implementation.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/model_assert.h>
#include <fido/properties/unix.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/stat.h>

#include "unix_shadow.h"

dev_t nondet_dev();
ino_t nondet_inode();
nlink_t nondet_nlink();
mode_t nondet_mode();
uid_t nondet_uid();
gid_t nondet_gid();

int nondet_retval();

int fstat(int fd, struct stat *sb)
{
    MODEL_ASSERT(property_file_descriptor_open(fd));
    MODEL_CHECK_OBJECT_RW(sb, sizeof(struct stat));

    int retval = nondet_retval();
    MODEL_ASSUME(0 == retval || -1 == retval);

    if (0 == retval)
    {
        __CPROVER_havoc_object(sb);
        sb->st_dev = nondet_dev();
        sb->st_ino = nondet_inode();
        sb->st_nlink = nondet_nlink();
        sb->st_mode = nondet_mode();
        sb->st_uid = nondet_uid();
        sb->st_gid = nondet_gid();
    }

    return retval;
}
