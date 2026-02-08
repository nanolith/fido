/**
 * \file fido/model_assert.h
 *
 * \brief Model checking assertions.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <fido/macro_tricks.h>

#if CBMC
# define MODEL_ASSERT(x) __CPROVER_assert((x), #x); REQUIRE_SEMICOLON_HERE
# define MODEL_ASSUME(x) __CPROVER_assume((x)); REQUIRE_SEMICOLON_HERE
# define MODEL_CHECK_OBJECT_READ(x, size) \
    __CPROVER_assert(__CPROVER_r_ok((x), (size)), #x " read " #size); \
    REQUIRE_SEMICOLON_HERE
# define MODEL_CHECK_OBJECT_WRITE(x, size) \
    __CPROVER_assert(__CPROVER_w_ok((x), (size)), #x " write " #size); \
    REQUIRE_SEMICOLON_HERE
# define MODEL_CHECK_OBJECT_RW(x, size) \
    __CPROVER_assert(__CPROVER_rw_ok((x), (size)), #x " r/w " #size); \
    REQUIRE_SEMICOLON_HERE
# define MODEL_CHECK_IS_STRING(x) \
    __CPROVER_assert(__CPROVER_is_zero_string((x)), #x " is string"); \
    REQUIRE_SEMICOLON_HERE
# define MODEL_CHECK_STRING_BUFFER_SIZE(x, size) \
    __CPROVER_assert(__CPROVER_buffer_size((x)) >= size); \
    REQUIRE_SEMICOLON_HERE
# define MODEL_EXEMPT(x)
# define MODEL_ONLY(x) (x)
#else
# define MODEL_ASSERT(x) REQUIRE_SEMICOLON_HERE
# define MODEL_ASSUME(x) REQUIRE_SEMICOLON_HERE
# define MODEL_CHECK_OBJECT_READ(x, size) REQUIRE_SEMICOLON_HERE
# define MODEL_CHECK_OBJECT_WRITE(x, size) REQUIRE_SEMICOLON_HERE
# define MODEL_CHECK_OBJECT_RW(x, size) REQUIRE_SEMICOLON_HERE
# define MODEL_CHECK_IS_STRING(x) REQUIRE_SEMICOLON_HERE
# define MODEL_CHECK_STRING_BUFFER_SIZE(x, size) REQUIRE_SEMICOLON_HERE
# define MODEL_EXEMPT(x) (x)
# define MODEL_ONLY(x)
#endif
