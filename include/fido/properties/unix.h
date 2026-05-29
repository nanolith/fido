/**
 * \file fido/properties/unix.h
 *
 * \brief Unix related properties.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <stdbool.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/******************************************************************************/
/* Start of model checking properties.                                        */
/******************************************************************************/

/**
 * \brief Open file descriptor property.
 *
 * \param fd            The file descriptor to check.
 *
 * \returns true if the file descriptor is open.
 */
bool property_file_descriptor_open(int fd);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
