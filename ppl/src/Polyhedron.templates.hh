/* Polyhedron class implementation: non-inline template functions.
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

#ifndef PPL_Polyhedron_templates_hh
#define PPL_Polyhedron_templates_hh 1

#include "Generator.defs.hh"
#include "MIP_Problem.defs.hh"
#include "Interval.defs.hh"
#include <algorithm>
#include <deque>

namespace Parma_Polyhedra_Library {

template <typename Interval>
Polyhedron::Polyhedron(Topology topol,
                       const Box<Interval>& box,
                       Complexity_Class)
  : con_sys(topol),
    gen_sys(topol),
    sat_c(),
    sat_g() {
  // Initialize the space dimension as indicated by the box.
  space_dim = box.space_dimension();

  // Check for emptiness.
  if (box.is_empty()) {
    set_empty();
    return;
  }

  // Zero-dim universe polyhedron.
  if (space_dim == 0) {
    set_zero_dim_univ();
    return;
  }

  // Insert a dummy constraint of the highest dimension to avoid the
  // need of resizing the matrix of constraints later;
  // this constraint will be removed at the end.
  con_sys.insert(Variable(space_dim - 1) >= 0);

  PPL_DIRTY_TEMP_COEFFICIENT(l_n);
  PPL_DIRTY_TEMP_COEFFICIENT(l_d);
  PPL_DIRTY_TEMP_COEFFICIENT(u_n);
  PPL_DIRTY_TEMP_COEFFICIENT(u_d);

  if (topol == NECESSARILY_CLOSED) {
    for (dimension_type k = space_dim; k-- > 0; ) {
      // See if we have a valid lower bound.
      bool l_closed = false;
      bool l_bounded = box.get_lower_bound(k, l_closed, l_n, l_d);
      // See if we have a valid upper bound.
      bool u_closed = false;
      bool u_bounded = box.get_upper_bound(k, u_closed, u_n, u_d);

      // See if we have an implicit equality constraint.
      if (l_bounded && u_bounded
          && l_closed && u_closed
          && l_n == u_n && l_d == u_d) {
        // Add the constraint `l_d*v_k == l_n'.
        con_sys.insert(l_d * Variable(k) == l_n);
      }
      else {
        if (l_bounded)
          // Add the constraint `l_d*v_k >= l_n'.
          con_sys.insert(l_d * Variable(k) >= l_n);
        if (u_bounded)
          // Add the constraint `u_d*v_k <= u_n'.
          con_sys.insert(u_d * Variable(k) <= u_n);
      }
    }
  }
  else {
    // topol == NOT_NECESSARILY_CLOSED
    for (dimension_type k = space_dim; k-- > 0; ) {
      // See if we have a valid lower bound.
      bool l_closed = false;
      bool l_bounded = box.get_lower_bound(k, l_closed, l_n, l_d);
      // See if we have a valid upper bound.
      bool u_closed = false;
      bool u_bounded = box.get_upper_bound(k, u_closed, u_n, u_d);

      // See if we have an implicit equality constraint.
      if (l_bounded && u_bounded
          && l_closed && u_closed
          && l_n == u_n && l_d == u_d) {
        // Add the constraint `l_d*v_k == l_n'.
        con_sys.insert(l_d * Variable(k) == l_n);
      }
      else {
        // Check if a lower bound constraint is required.
        if (l_bounded) {
          if (l_closed)
            // Add the constraint `l_d*v_k >= l_n'.
            con_sys.insert(l_d * Variable(k) >= l_n);
          else
            // Add the constraint `l_d*v_k > l_n'.
            con_sys.insert(l_d * Variable(k) > l_n);
        }
        // Check if an upper bound constraint is required.
        if (u_bounded) {
          if (u_closed)
            // Add the constraint `u_d*v_k <= u_n'.
            con_sys.insert(u_d * Variable(k) <= u_n);
          else
            // Add the constraint `u_d*v_k < u_n'.
            con_sys.insert(u_d * Variable(k) < u_n);
        }
      }
    }
  }

  // Adding the low-level constraints.
  con_sys.add_low_level_constraints();
  // Now removing the dummy constraint inserted before.
  dimension_type n_rows = con_sys.num_rows() - 1;
  con_sys[0].swap(con_sys[n_rows]);
  con_sys.set_sorted(false);
  // NOTE: here there are no pending constraints.
  con_sys.set_index_first_pending_row(n_rows);
  con_sys.erase_to_end(n_rows);

  // Constraints are up-to-date.
  set_constraints_up_to_date();
  PPL_ASSERT_HEAVY(OK());
}

template <typename Partial_Function>
void
Polyhedron::map_space_dimensions(const Partial_Function& pfunc) {
  if (space_dim == 0)
    return;

  if (pfunc.has_empty_codomain()) {
    // All dimensions vanish: the polyhedron becomes zero_dimensional.
    if (marked_empty()
	|| (has_pending_constraints()
	    && !remove_pending_to_obtain_generators())
	|| (!generators_are_up_to_date() && !update_generators())) {
      // Removing all dimensions from the empty polyhedron.
      space_dim = 0;
      con_sys.clear();
    }
    else
      // Removing all dimensions from a non-empty polyhedron.
      set_zero_dim_univ();

    PPL_ASSERT_HEAVY(OK());
    return;
  }

  const dimension_type new_space_dimension = pfunc.max_in_codomain() + 1;

  if (new_space_dimension == space_dim) {
    // The partial function `pfunc' is indeed total and thus specifies
    // a permutation, that is, a renaming of the dimensions.  For
    // maximum efficiency, we will simply permute the columns of the
    // constraint system and/or the generator system.

    // We first compute suitable permutation cycles for the columns of
    // the `con_sys' and `gen_sys' matrices.  We will represent them
    // with a linear array, using 0 as a terminator for each cycle
    // (notice that the columns with index 0 of `con_sys' and
    // `gen_sys' represent the inhomogeneous terms, and thus are
    // unaffected by the permutation of dimensions).
    // Cycles of length 1 will be omitted so that, in the worst case,
    // we will have `space_dim' elements organized in `space_dim/2'
    // cycles, which means we will have at most `space_dim/2'
    // terminators.
    std::vector<dimension_type> cycles;
    cycles.reserve(space_dim + space_dim/2);

    // Used to mark elements as soon as they are inserted in a cycle.
    std::deque<bool> visited(space_dim);

    for (dimension_type i = space_dim; i-- > 0; ) {
      if (!visited[i]) {
	dimension_type j = i;
	do {
	  visited[j] = true;
	  // The following initialization is only to make the compiler happy.
	  dimension_type k = 0;
	  if (!pfunc.maps(j, k))
	    throw_invalid_argument("map_space_dimensions(pfunc)",
				   " pfunc is inconsistent");
	  if (k == j)
	    // Cycle of length 1: skip it.
	    goto skip;

	  cycles.push_back(j+1);
	  // Go along the cycle.
	  j = k;
	} while (!visited[j]);
	// End of cycle: mark it.
	cycles.push_back(0);
      skip:
	;
      }
    }

    // If `cycles' is empty then `pfunc' is the identity.
    if (cycles.empty())
      return;

    // Permute all that is up-to-date.  Notice that the contents of
    // the saturation matrices is unaffected by the permutation of
    // columns: they remain valid, if they were so.
    if (constraints_are_up_to_date())
      con_sys.permute_columns(cycles);

    if (generators_are_up_to_date())
      gen_sys.permute_columns(cycles);

    PPL_ASSERT_HEAVY(OK());
    return;
  }

  // If control gets here, then `pfunc' is not a permutation and some
  // dimensions must be projected away.

  // If there are pending constraints, using `generators()' we process them.
  const Generator_System& old_gensys = generators();

  if (old_gensys.has_no_rows()) {
    // The polyhedron is empty.
    Polyhedron new_polyhedron(topology(), new_space_dimension, EMPTY);
    std::swap(*this, new_polyhedron);
    PPL_ASSERT_HEAVY(OK());
    return;
  }

  // Make a local copy of the partial function.
  std::vector<dimension_type> pfunc_maps(space_dim, not_a_dimension());
  for (dimension_type j = space_dim; j-- > 0; ) {
    dimension_type pfunc_j;
    if (pfunc.maps(j, pfunc_j))
      pfunc_maps[j] = pfunc_j;
  }

  Generator_System new_gensys;
  for (Generator_System::const_iterator i = old_gensys.begin(),
	 old_gensys_end = old_gensys.end(); i != old_gensys_end; ++i) {
    const Generator& old_g = *i;
    Linear_Expression e(0 * Variable(new_space_dimension-1));
    bool all_zeroes = true;
    for (dimension_type j = space_dim; j-- > 0; ) {
      if (old_g.coefficient(Variable(j)) != 0
	  && pfunc_maps[j] != not_a_dimension()) {
	e += Variable(pfunc_maps[j]) * old_g.coefficient(Variable(j));
	all_zeroes = false;
      }
    }
    switch (old_g.type()) {
    case Generator::LINE:
      if (!all_zeroes)
	new_gensys.insert(line(e));
      break;
    case Generator::RAY:
      if (!all_zeroes)
	new_gensys.insert(ray(e));
      break;
    case Generator::POINT:
      // A point in the origin has all zero homogeneous coefficients.
      new_gensys.insert(point(e, old_g.divisor()));
      break;
    case Generator::CLOSURE_POINT:
      // A closure point in the origin has all zero homogeneous coefficients.
      new_gensys.insert(closure_point(e, old_g.divisor()));
      break;
    }
  }
  Polyhedron new_polyhedron(topology(), new_gensys);
  std::swap(*this, new_polyhedron);
  PPL_ASSERT_HEAVY(OK(true));
}

} // namespace Parma_Polyhedra_Library

#endif // !defined(PPL_Polyhedron_templates_hh)
