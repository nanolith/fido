/**
 * \file models/shadow/unix/cap_rights_init.c
 *
 * \brief Shadow method for __cap_rights_init.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/model_assert.h>
#include <stdint.h>
#include <sys/capsicum.h>
#include <unistd.h>

int nondet_retval();

cap_rights_t* __cap_rights_init(int version, cap_rights_t* rights, ...)
{
    return rights;
}
