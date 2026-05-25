/**
 * \file models/helpers/options/options_helpers.h
 *
 * \brief Helpers for exercising options data structures.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <fido/options.h>

int FN_DECL_MUST_CHECK
fido_options_create_random(fido_options** opts);
