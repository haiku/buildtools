/* Definitions of global objects.
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

#include <ppl-config.h>

#include "globals.defs.hh"
#include "Constraint.defs.hh"
#include "Generator.defs.hh"

namespace Parma_Polyhedra_Library {

const Throwable* volatile abandon_expensive_computations = 0;

// Initialize Weightwatch_Traits static data members.
Weightwatch_Traits::Threshold Weightwatch_Traits::weight = 0;
void (*Weightwatch_Traits::check_function)(void) = 0;

#ifndef NDEBUG
namespace Implementation {
unsigned int in_assert = 0;
}
#endif

} // namespace Parma_Polyhedra_Library
