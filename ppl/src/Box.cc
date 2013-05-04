/* Box class implementation (non-inline functions).
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
#include "Box.defs.hh"

namespace PPL = Parma_Polyhedra_Library;

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
/*! \relates Parma_Polyhedra_Library::BD_Shape */
#endif // defined(PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS)
bool
PPL::extract_interval_constraint(const Constraint& c,
				 const dimension_type c_space_dim,
				 dimension_type& c_num_vars,
				 dimension_type& c_only_var) {
  // Check for preconditions.
  PPL_ASSERT(c.space_dimension() == c_space_dim);
  PPL_ASSERT(c_num_vars == 0 && c_only_var == 0);
  // Collect the non-zero components of `c'.
  for (dimension_type i = c_space_dim; i-- > 0; )
    if (c.coefficient(Variable(i)) != 0) {
      if (c_num_vars == 0) {
	c_only_var = i;
	++c_num_vars;
      }
      else
	// Constraint `c' is not an interval constraint.
	return false;
    }
  return true;
}

bool
PPL::extract_interval_congruence(const Congruence& cg,
			 	 const dimension_type cg_space_dim,
				 dimension_type& cg_num_vars,
				 dimension_type& cg_only_var) {
  // Check for preconditions.
  PPL_ASSERT(cg.space_dimension() == cg_space_dim);
  PPL_ASSERT(cg_num_vars == 0 && cg_only_var == 0);
  // Only equality congruences can be intervals.
  PPL_ASSERT(cg.is_equality());

  // Collect the non-zero components of `cg'.
  for (dimension_type i = cg_space_dim; i-- > 0; )
    if (cg.coefficient(Variable(i)) != 0) {
      if (cg_num_vars == 0) {
	cg_only_var = i;
	++cg_num_vars;
      }
      else
	// Congruence `cg' is not an interval congruence.
	return false;
    }
  return true;
}
