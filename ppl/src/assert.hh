/* Implementation of PPL_ASSERT macro.
   Copyright (C) 2001-2010 Roberto Bagnara <bagnara@cs.unipr.it>
   Copyright (C) 2010-2011 BUGSENG srl (http://bugseng.com)

This file is part of the Parma Polyhedra Library (PPL).

The PPL is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3 of the License, or (at your
option) any later version.

The PPL is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02111-1307, USA.

For the most up-to-date information see the Parma Polyhedra Library
site: http://www.cs.unipr.it/ppl/ . */

#ifndef PPL_assert_hh
#define PPL_assert_hh 1

#include <cassert>
#include "globals.defs.hh"

#if defined(NDEBUG)

#define PPL_ASSERT(cond__)
#define PPL_ASSERT_HEAVY(cond__)

#else

// Non zero to detect use of PPL_ASSERT instead of PPL_ASSERT_HEAVY
#define PPL_DEBUG_PPL_ASSERT 1
#if !PPL_DEBUG_PPL_ASSERT
#define PPL_ASSERT(cond__) assert(cond__)
#else
#define PPL_ASSERT(cond__)				       \
  do {							       \
    Parma_Polyhedra_Library::Weightwatch_Traits::Threshold     \
      old_weight__                                             \
        = Parma_Polyhedra_Library::Weightwatch_Traits::weight; \
    assert(cond__);					       \
    assert(old_weight__ == Parma_Polyhedra_Library::Weightwatch_Traits::weight &&   \
	   "PPL_ASSERT_HEAVY have to be used here");	   \
  } while(0)
#endif

// The evaluation of asserted conditions could have a non zero
// computational weight (i.e., the execution path could contain an
// invocation of WEIGHT_ADD).
#define PPL_ASSERT_HEAVY(cond__)				\
  do {								\
      ++Parma_Polyhedra_Library::Implementation::in_assert;	\
      assert(cond__);						\
      --Parma_Polyhedra_Library::Implementation::in_assert;	\
    } while (0)
#endif

#endif // !defined(PPL_assert_hh)
