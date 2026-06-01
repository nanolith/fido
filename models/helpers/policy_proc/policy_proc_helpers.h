/**
 * \file models/helpers/policy_proc/policy_proc_helpers.h
 *
 * \brief Helpers for exercising policy_proc data structures.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <fido/policy_proc.h>

int FN_DECL_MUST_CHECK
fido_policy_decision_create_random(fido_policy_decision** dec);
