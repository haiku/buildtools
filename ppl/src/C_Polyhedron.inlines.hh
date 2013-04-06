/* C_Polyhedron class implementation: inline functions.
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

#ifndef PPL_C_Polyhedron_inlines_hh
#define PPL_C_Polyhedron_inlines_hh 1

#include <algorithm>
#include <stdexcept>

namespace Parma_Polyhedra_Library {

inline
C_Polyhedron::~C_Polyhedron() {
}

inline
C_Polyhedron::C_Polyhedron(dimension_type num_dimensions,
			   Degenerate_Element kind)
  : Polyhedron(NECESSARILY_CLOSED,
	       num_dimensions <= max_space_dimension()
	       ? num_dimensions
	       : (throw_space_dimension_overflow(NECESSARILY_CLOSED,
						 "C_Polyhedron(n, k)",
						 "n exceeds the maximum "
						 "allowed space dimension"),
		  num_dimensions),
	       kind) {
}

inline
C_Polyhedron::C_Polyhedron(const Constraint_System& cs)
  : Polyhedron(NECESSARILY_CLOSED,
	       cs.space_dimension() <= max_space_dimension()
	       ? cs
	       : (throw_space_dimension_overflow(NECESSARILY_CLOSED,
						 "C_Polyhedron(cs)",
						 "the space dimension of cs "
						 "exceeds the maximum allowed "
						 "space dimension"), cs)) {
}

inline
C_Polyhedron::C_Polyhedron(Constraint_System& cs, Recycle_Input)
  : Polyhedron(NECESSARILY_CLOSED,
	       cs.space_dimension() <= max_space_dimension()
	       ? cs
	       : (throw_space_dimension_overflow(NECESSARILY_CLOSED,
						 "C_Polyhedron(cs, recycle)",
						 "the space dimension of cs "
						 "exceeds the maximum allowed "
						 "space dimension"), cs),
	       Recycle_Input()) {
}

inline
C_Polyhedron::C_Polyhedron(const Generator_System& gs)
  : Polyhedron(NECESSARILY_CLOSED,
	       gs.space_dimension() <= max_space_dimension()
	       ? gs
	       : (throw_space_dimension_overflow(NECESSARILY_CLOSED,
						 "C_Polyhedron(gs)",
						 "the space dimension of gs "
						 "exceeds the maximum allowed "
						 "space dimension"), gs)) {
}

inline
C_Polyhedron::C_Polyhedron(Generator_System& gs, Recycle_Input)
  : Polyhedron(NECESSARILY_CLOSED,
	       gs.space_dimension() <= max_space_dimension()
	       ? gs
	       : (throw_space_dimension_overflow(NECESSARILY_CLOSED,
						 "C_Polyhedron(gs, recycle)",
						 "the space dimension of gs "
						 "exceeds the maximum allowed "
						 "space dimension"), gs),
	       Recycle_Input()) {
}

template <typename Interval>
inline
C_Polyhedron::C_Polyhedron(const Box<Interval>& box, Complexity_Class)
  : Polyhedron(NECESSARILY_CLOSED,
	       box.space_dimension() <= max_space_dimension()
	       ? box
	       : (throw_space_dimension_overflow(NECESSARILY_CLOSED,
						 "C_Polyhedron(box): ",
						 "the space dimension of box "
						 "exceeds the maximum allowed "
						 "space dimension"), box)) {
}

template <typename U>
inline
C_Polyhedron::C_Polyhedron(const BD_Shape<U>& bd, Complexity_Class)
  : Polyhedron(NECESSARILY_CLOSED,
	       bd.space_dimension() <= max_space_dimension()
	       ? bd.space_dimension()
	       : (throw_space_dimension_overflow(NECESSARILY_CLOSED,
						 "C_Polyhedron(bd): ",
						 "the space dimension of bd "
						 "exceeds the maximum allowed "
						 "space dimension"), 0),
               UNIVERSE) {
  add_constraints(bd.constraints());
}

template <typename U>
inline
C_Polyhedron::C_Polyhedron(const Octagonal_Shape<U>& os, Complexity_Class)
  : Polyhedron(NECESSARILY_CLOSED,
	       os.space_dimension() <= max_space_dimension()
	       ? os.space_dimension()
	       : (throw_space_dimension_overflow(NECESSARILY_CLOSED,
						 "C_Polyhedron(os): ",
						 "the space dimension of os "
						 "exceeds the maximum allowed "
						 "space dimension"), 0),
               UNIVERSE) {
  add_constraints(os.constraints());
}

inline
C_Polyhedron::C_Polyhedron(const C_Polyhedron& y, Complexity_Class)
  : Polyhedron(y) {
}

inline C_Polyhedron&
C_Polyhedron::operator=(const C_Polyhedron& y) {
  Polyhedron::operator=(y);
  return *this;
}

inline C_Polyhedron&
C_Polyhedron::operator=(const NNC_Polyhedron& y) {
  C_Polyhedron c_y(y);
  swap(c_y);
  return *this;
}

inline bool
C_Polyhedron::upper_bound_assign_if_exact(const C_Polyhedron& y) {
  return poly_hull_assign_if_exact(y);
}

} // namespace Parma_Polyhedra_Library

#endif // !defined(PPL_C_Polyhedron_inlines_hh)
