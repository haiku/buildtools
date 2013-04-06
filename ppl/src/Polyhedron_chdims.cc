/* Polyhedron class implementation
   (non-inline operators that may change the dimension of the vector space).
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

#include "Polyhedron.defs.hh"
#include "Variables_Set.defs.hh"
#include "assert.hh"

#define BE_LAZY 1

namespace PPL = Parma_Polyhedra_Library;

void
PPL::Polyhedron::add_space_dimensions(Linear_System& sys1,
				      Linear_System& sys2,
				      Bit_Matrix& sat1,
				      Bit_Matrix& sat2,
				      dimension_type add_dim) {
  PPL_ASSERT(sys1.topology() == sys2.topology());
  PPL_ASSERT(sys1.num_columns() == sys2.num_columns());
  PPL_ASSERT(add_dim != 0);

  sys1.add_zero_columns(add_dim);
  dimension_type old_index = sys2.first_pending_row();
  sys2.add_rows_and_columns(add_dim);
  // The added rows are in the non-pending part.
  sys2.set_index_first_pending_row(old_index + add_dim);

  // The resulting saturation matrix will be as follows:
  // from row    0    to      add_dim-1       : only zeroes
  //          add_dim     add_dim+num_rows-1  : old saturation matrix

  // In fact all the old generators saturate all the new constraints
  // because the polyhedron has not been embedded in the new space.
  sat1.resize(sat1.num_rows() + add_dim, sat1.num_columns());
  // The old matrix is moved to the end of the new matrix.
  for (dimension_type i = sat1.num_rows() - add_dim; i-- > 0; )
    std::swap(sat1[i], sat1[i+add_dim]);
  // Computes the "sat_c", too.
  sat2.transpose_assign(sat1);

  if (!sys1.is_necessarily_closed()) {
    // Moving the epsilon coefficients to the new last column.
    dimension_type new_eps_index = sys1.num_columns() - 1;
    dimension_type old_eps_index = new_eps_index - add_dim;
    // This swap preserves sortedness of `sys1'.
    sys1.swap_columns(old_eps_index, new_eps_index);

    // Try to preserve sortedness of `sys2'.
    if (!sys2.is_sorted())
      sys2.swap_columns(old_eps_index, new_eps_index);
    else {
      for (dimension_type i = sys2.num_rows(); i-- > add_dim; ) {
	Linear_Row& r = sys2[i];
	std::swap(r[old_eps_index], r[new_eps_index]);
      }
      // The upper-right corner of `sys2' contains the J matrix:
      // swap coefficients to preserve sortedness.
      for (dimension_type i = add_dim; i-- > 0; ++old_eps_index) {
	Linear_Row& r = sys2[i];
	std::swap(r[old_eps_index], r[old_eps_index + 1]);
      }
    }
    // NOTE: since we swapped columns in both `sys1' and `sys2',
    // no swapping is required for `sat1' and `sat2'.
  }
}

void
PPL::Polyhedron::add_space_dimensions_and_embed(dimension_type m) {
  // The space dimension of the resulting polyhedron should not
  // overflow the maximum allowed space dimension.
  if (m > max_space_dimension() - space_dimension())
    throw_space_dimension_overflow(topology(),
				   "add_space_dimensions_and_embed(m)",
				   "adding m new space dimensions exceeds "
				   "the maximum allowed space dimension");

  // Adding no dimensions to any polyhedron is a no-op.
  if (m == 0)
    return;

  // Adding dimensions to an empty polyhedron is obtained by adjusting
  // `space_dim' and clearing `con_sys' (since it can contain the
  // unsatisfiable constraint system of the wrong dimension).
  if (marked_empty()) {
    space_dim += m;
    con_sys.clear();
    return;
  }

  // The case of a zero-dimensional space polyhedron.
  if (space_dim == 0) {
    // Since it is not empty, it has to be the universe polyhedron.
    PPL_ASSERT(status.test_zero_dim_univ());
    // We swap `*this' with a newly created
    // universe polyhedron of dimension `m'.
    Polyhedron ph(topology(), m, UNIVERSE);
    swap(ph);
    return;
  }

  // To embed an n-dimension space polyhedron in a (n+m)-dimension space,
  // we just add `m' zero-columns to the rows in the system of constraints;
  // in contrast, the system of generators needs additional rows,
  // corresponding to the vectors of the canonical basis
  // for the added dimensions. That is, for each new dimension `x[k]'
  // we add the line having that direction. This is done by invoking
  // the function add_space_dimensions() giving the system of generators
  // as the second argument.
  if (constraints_are_up_to_date())
    if (generators_are_up_to_date()) {
      // `sat_c' must be up to date for add_space_dimensions().
      if (!sat_c_is_up_to_date())
	update_sat_c();
      // Adds rows and/or columns to both matrices.
      // `add_space_dimensions' correctly handles pending constraints
      // or generators.
      add_space_dimensions(con_sys, gen_sys, sat_c, sat_g, m);
    }
    else {
      // Only constraints are up-to-date: no need to modify the generators.
      con_sys.add_zero_columns(m);
      // If the polyhedron is not necessarily closed,
      // move the epsilon coefficients to the last column.
      if (!is_necessarily_closed())
	con_sys.swap_columns(space_dim + 1, space_dim + 1 + m);
    }
  else {
    // Only generators are up-to-date: no need to modify the constraints.
    PPL_ASSERT(generators_are_up_to_date());
    gen_sys.add_rows_and_columns(m);
    // The polyhedron does not support pending generators.
    gen_sys.unset_pending_rows();
    // If the polyhedron is not necessarily closed,
    // move the epsilon coefficients to the last column.
    if (!is_necessarily_closed()) {
      // Try to preserve sortedness of `gen_sys'.
      if (!gen_sys.is_sorted())
	gen_sys.swap_columns(space_dim + 1, space_dim + 1 + m);
      else {
	dimension_type old_eps_index = space_dim + 1;
	dimension_type new_eps_index = old_eps_index + m;
	for (dimension_type i = gen_sys.num_rows(); i-- > m; ) {
	  Generator& r = gen_sys[i];
	  std::swap(r[old_eps_index], r[new_eps_index]);
	}
	// The upper-right corner of `gen_sys' contains the J matrix:
	// swap coefficients to preserve sortedness.
	for (dimension_type i = m; i-- > 0; ++old_eps_index) {
	  Generator& r = gen_sys[i];
	  std::swap(r[old_eps_index], r[old_eps_index + 1]);
	}
      }
    }
  }
  // Update the space dimension.
  space_dim += m;

  // Note: we do not check for satisfiability, because the system of
  // constraints may be unsatisfiable.
  PPL_ASSERT_HEAVY(OK());
}

void
PPL::Polyhedron::add_space_dimensions_and_project(dimension_type m) {
  // The space dimension of the resulting polyhedron should not
  // overflow the maximum allowed space dimension.
  if (m > max_space_dimension() - space_dimension())
    throw_space_dimension_overflow(topology(),
				   "add_space_dimensions_and_project(m)",
				   "adding m new space dimensions exceeds "
				   "the maximum allowed space dimension");

  // Adding no dimensions to any polyhedron is a no-op.
  if (m == 0)
    return;

  // Adding dimensions to an empty polyhedron is obtained
  // by merely adjusting `space_dim'.
  if (marked_empty()) {
    space_dim += m;
    con_sys.clear();
    return;
  }

  if (space_dim == 0) {
    PPL_ASSERT(status.test_zero_dim_univ() && gen_sys.has_no_rows());
    // The system of generators for this polyhedron has only
    // the origin as a point.
    // In an NNC polyhedron, all points have to be accompanied
    // by the corresponding closure points
    // (this time, dimensions are automatically adjusted).
    if (!is_necessarily_closed())
      gen_sys.insert(Generator::zero_dim_closure_point());
    gen_sys.insert(Generator::zero_dim_point());
    gen_sys.adjust_topology_and_space_dimension(topology(), m);
    set_generators_minimized();
    space_dim = m;
    PPL_ASSERT_HEAVY(OK());
    return;
  }

  // To project an n-dimension space polyhedron in a (n+m)-dimension space,
  // we just add to the system of generators `m' zero-columns;
  // In contrast, in the system of constraints, new rows are needed
  // in order to avoid embedding the old polyhedron in the new space.
  // Thus, for each new dimensions `x[k]', we add the constraint
  // x[k] = 0; this is done by invoking the function add_space_dimensions()
  // giving the system of constraints as the second argument.
  if (constraints_are_up_to_date())
    if (generators_are_up_to_date()) {
      // `sat_g' must be up to date for add_space_dimensions().
      if (!sat_g_is_up_to_date())
	update_sat_g();
      // Adds rows and/or columns to both matrices.
      // `add_space_dimensions' correctly handles pending constraints
      // or generators.
      add_space_dimensions(gen_sys, con_sys, sat_g, sat_c, m);
    }
    else {
      // Only constraints are up-to-date: no need to modify the generators.
      con_sys.add_rows_and_columns(m);
      // The polyhedron does not support pending constraints.
      con_sys.unset_pending_rows();
      // If the polyhedron is not necessarily closed,
      // move the epsilon coefficients to the last column.
      if (!is_necessarily_closed()) {
	// Try to preserve sortedness of `con_sys'.
	if (!con_sys.is_sorted())
	  con_sys.swap_columns(space_dim + 1, space_dim + 1 + m);
	else {
	  dimension_type old_eps_index = space_dim + 1;
	  dimension_type new_eps_index = old_eps_index + m;
	  for (dimension_type i = con_sys.num_rows(); i-- > m; ) {
	    Constraint& r = con_sys[i];
	    std::swap(r[old_eps_index], r[new_eps_index]);
	  }
	  // The upper-right corner of `con_sys' contains the J matrix:
	  // swap coefficients to preserve sortedness.
	  for (dimension_type i = m; i-- > 0; ++old_eps_index) {
	    Constraint& r = con_sys[i];
	    std::swap(r[old_eps_index], r[old_eps_index + 1]);
	  }
	}
      }
    }
  else {
    // Only generators are up-to-date: no need to modify the constraints.
    PPL_ASSERT(generators_are_up_to_date());
    gen_sys.add_zero_columns(m);
    // If the polyhedron is not necessarily closed,
    // move the epsilon coefficients to the last column.
    if (!is_necessarily_closed())
      gen_sys.swap_columns(space_dim + 1, space_dim + 1 + m);
  }
  // Now we update the space dimension.
  space_dim += m;

  // Note: we do not check for satisfiability, because the system of
  // constraints may be unsatisfiable.
  PPL_ASSERT_HEAVY(OK());
}

void
PPL::Polyhedron::concatenate_assign(const Polyhedron& y) {
  if (topology() != y.topology())
    throw_topology_incompatible("concatenate_assign(y)", "y", y);

  // The space dimension of the resulting polyhedron should not
  // overflow the maximum allowed space dimension.
  const dimension_type added_columns = y.space_dim;
  if (added_columns > max_space_dimension() - space_dim)
    throw_space_dimension_overflow(topology(),
				   "concatenate_assign(y)",
				   "concatenation exceeds the maximum "
				   "allowed space dimension");

  // If `*this' or `y' are empty polyhedra, it is sufficient to adjust
  // the dimension of the space.
  if (marked_empty() || y.marked_empty()) {
    space_dim += added_columns;
    set_empty();
    return;
  }

  // If `y' is a non-empty 0-dim space polyhedron, the result is `*this'.
  if (added_columns == 0)
    return;

  // If `*this' is a non-empty 0-dim space polyhedron, the result is `y'.
  if (space_dim == 0) {
    *this = y;
    return;
  }

  // TODO: this implementation is just an executable specification.
  Constraint_System cs = y.constraints();

  // The constraints of `x' (possibly with pending rows) are required.
  if (has_pending_generators())
    process_pending_generators();
  else if (!constraints_are_up_to_date())
    update_constraints();

  // The matrix for the new system of constraints is obtained
  // by leaving the old system of constraints in the upper left-hand side
  // and placing the constraints of `cs' in the lower right-hand side.
  // NOTE: here topologies agree, whereas dimensions may not agree.
  dimension_type old_num_rows = con_sys.num_rows();
  dimension_type old_num_columns = con_sys.num_columns();
  dimension_type added_rows = cs.num_rows();

  // We already dealt with the cases of an empty or zero-dim `y' polyhedron;
  // also, `cs' contains the low-level constraints, at least.
  PPL_ASSERT(added_rows > 0 && added_columns > 0);

  con_sys.add_zero_rows_and_columns(added_rows, added_columns,
				    Linear_Row::Flags(topology(),
						      Linear_Row::RAY_OR_POINT_OR_INEQUALITY));
  // Move the epsilon coefficient to the last column, if needed.
  if (!is_necessarily_closed())
    con_sys.swap_columns(old_num_columns - 1,
			 old_num_columns - 1 + added_columns);
  dimension_type cs_num_columns = cs.num_columns();
  // Steal the constraints from `cs' and put them in `con_sys'
  // using the right displacement for coefficients.
  for (dimension_type i = added_rows; i-- > 0; ) {
    Constraint& c_old = cs[i];
    Constraint& c_new = con_sys[old_num_rows + i];
    // Method `add_zero_rows_and_columns', by default, added inequalities.
    if (c_old.is_equality())
      c_new.set_is_equality();
    // The inhomogeneous term is not displaced.
    std::swap(c_new[0], c_old[0]);
    // All homogeneous terms (included the epsilon coefficient,
    // if present) are displaced by `space_dim' columns.
    for (dimension_type j = 1; j < cs_num_columns; ++j)
      std::swap(c_old[j], c_new[space_dim + j]);
  }

  if (can_have_something_pending()) {
    // If `*this' can support pending constraints, then, since we have
    // resized the system of constraints, we must also add to the generator
    // system those lines corresponding to the newly added dimensions,
    // because the non-pending parts of `con_sys' and `gen_sys' must still
    // be a DD pair in minimal form.
    gen_sys.add_rows_and_columns(added_columns);
    gen_sys.set_sorted(false);
    if (!is_necessarily_closed())
      gen_sys.swap_columns(old_num_columns - 1,
			   old_num_columns - 1 + added_columns);
    // The added lines are not pending.
    gen_sys.unset_pending_rows();
    // Since we added new lines at the beginning of `x.gen_sys',
    // we also have to adjust the saturation matrix `sat_c'.
    // FIXME: if `sat_c' is not up-to-date, couldn't we directly update
    // `sat_g' by resizing it and shifting its columns?
    if (!sat_c_is_up_to_date()) {
      sat_c.transpose_assign(sat_g);
      set_sat_c_up_to_date();
    }
    clear_sat_g_up_to_date();
    sat_c.resize(sat_c.num_rows() + added_columns, sat_c.num_columns());
    // The old saturation rows are copied at the end of the matrix.
    // The newly introduced lines saturate all the non-pending constraints,
    // thus their saturation rows are made of zeroes.
    for (dimension_type i = sat_c.num_rows() - added_columns; i-- > 0; )
      std::swap(sat_c[i], sat_c[i+added_columns]);
    // Since `added_rows > 0', we now have pending constraints.
    set_constraints_pending();
  }
  else {
    // The polyhedron cannot have pending constraints.
    con_sys.unset_pending_rows();
#if BE_LAZY
    con_sys.set_sorted(false);
#else
    con_sys.sort_rows();
#endif
    clear_constraints_minimized();
    clear_generators_up_to_date();
    clear_sat_g_up_to_date();
    clear_sat_c_up_to_date();
  }
  // Update space dimension.
  space_dim += added_columns;

  // The system of constraints may be unsatisfiable,
  // thus we do not check for satisfiability.
  PPL_ASSERT_HEAVY(OK());
}

void
PPL::Polyhedron::remove_space_dimensions(const Variables_Set& vars) {
  // The removal of no dimensions from any polyhedron is a no-op.
  // Note that this case also captures the only legal removal of
  // dimensions from a polyhedron in a 0-dim space.
  if (vars.empty()) {
    PPL_ASSERT_HEAVY(OK());
    return;
  }

  // Dimension-compatibility check.
  const dimension_type min_space_dim = vars.space_dimension();
  if (space_dim < min_space_dim)
    throw_dimension_incompatible("remove_space_dimensions(vs)", min_space_dim);

  const dimension_type new_space_dim = space_dim - vars.size();

  // We need updated generators; note that keeping pending generators
  // is useless because the constraints will be dropped anyway.
  if (marked_empty()
      || (has_something_pending() && !remove_pending_to_obtain_generators())
      || (!generators_are_up_to_date() && !update_generators())) {
    // Removing dimensions from the empty polyhedron:
    // we clear `con_sys' since it could have contained the
    // unsatisfiable constraint of the wrong dimension.
    con_sys.clear();
    // Update the space dimension.
    space_dim = new_space_dim;
    PPL_ASSERT_HEAVY(OK());
    return;
  }

  // When removing _all_ dimensions from a non-empty polyhedron,
  // we obtain the zero-dimensional universe polyhedron.
  if (new_space_dim == 0) {
    set_zero_dim_univ();
    return;
  }

  // For each variable to be removed, we fill the corresponding column
  // by shifting left those columns that will not be removed.
  Variables_Set::const_iterator vsi = vars.begin();
  Variables_Set::const_iterator vsi_end = vars.end();
  dimension_type dst_col = *vsi + 1;
  dimension_type src_col = dst_col + 1;
  for (++vsi; vsi != vsi_end; ++vsi) {
    const dimension_type vsi_col = *vsi + 1;
    // All columns in between are moved to the left.
    while (src_col < vsi_col)
      gen_sys.Matrix::swap_columns(dst_col++, src_col++);
    ++src_col;
  }
  // Moving the remaining columns.
  const dimension_type gen_sys_num_columns = gen_sys.num_columns();
  while (src_col < gen_sys_num_columns)
    gen_sys.Matrix::swap_columns(dst_col++, src_col++);

  // The number of remaining columns is `dst_col'.
  // Note that resizing also calls `set_sorted(false)'.
  gen_sys.remove_trailing_columns(gen_sys_num_columns - dst_col);
  // We may have invalid lines and rays now.
  gen_sys.remove_invalid_lines_and_rays();

  // Constraints are not up-to-date and generators are not minimized.
  clear_constraints_up_to_date();
  clear_generators_minimized();

  // Update the space dimension.
  space_dim = new_space_dim;

  PPL_ASSERT_HEAVY(OK(true));
}

void
PPL::Polyhedron::remove_higher_space_dimensions(dimension_type new_dimension) {
  // Dimension-compatibility check.
  if (new_dimension > space_dim)
    throw_dimension_incompatible("remove_higher_space_dimensions(nd)",
				 new_dimension);

  // The removal of no dimensions from any polyhedron is a no-op.
  // Note that this case also captures the only legal removal of
  // dimensions from a polyhedron in a 0-dim space.
  if (new_dimension == space_dim) {
    PPL_ASSERT_HEAVY(OK());
    return;
  }

  // We need updated generators; note that keeping pending generators
  // is useless because constraints will be dropped anyway.
  if (marked_empty()
      || (has_something_pending() && !remove_pending_to_obtain_generators())
      || (!generators_are_up_to_date() && !update_generators())) {
    // Removing dimensions from the empty polyhedron:
    // just updates the space dimension.
    space_dim = new_dimension;
    con_sys.clear();
    PPL_ASSERT_HEAVY(OK());
    return;
  }

  if (new_dimension == 0) {
    // Removing all dimensions from a non-empty polyhedron:
    // just return the zero-dimensional universe polyhedron.
    set_zero_dim_univ();
    return;
  }

  dimension_type new_num_cols = new_dimension + 1;
  if (!is_necessarily_closed()) {
    // The polyhedron is not necessarily closed: move the column
    // of the epsilon coefficients to its new place.
    gen_sys.swap_columns(gen_sys.num_columns() - 1, new_num_cols);
    // The number of remaining columns is `new_dimension + 2'.
    ++new_num_cols;
  }
  // Note that resizing also calls `set_sorted(false)'.
  gen_sys.remove_trailing_columns(space_dim - new_dimension);
  // We may have invalid lines and rays now.
  gen_sys.remove_invalid_lines_and_rays();

  // Constraints are not up-to-date and generators are not minimized.
  clear_constraints_up_to_date();
  clear_generators_minimized();

  // Update the space dimension.
  space_dim = new_dimension;

  PPL_ASSERT_HEAVY(OK(true));
}

void
PPL::Polyhedron::expand_space_dimension(Variable var, dimension_type m) {
  // TODO: this implementation is _really_ an executable specification.

  // `var' should be one of the dimensions of the vector space.
  if (var.space_dimension() > space_dim)
    throw_dimension_incompatible("expand_space_dimension(v, m)", "v", var);

  // The space dimension of the resulting polyhedron should not
  // overflow the maximum allowed space dimension.
  if (m > max_space_dimension() - space_dimension())
    throw_space_dimension_overflow(topology(),
				   "expand_dimension(v, m)",
				   "adding m new space dimensions exceeds "
				   "the maximum allowed space dimension");

  // Nothing to do, if no dimensions must be added.
  if (m == 0)
    return;

  // Keep track of the dimension before adding the new ones.
  dimension_type old_dim = space_dim;

  // Add the required new dimensions.
  add_space_dimensions_and_embed(m);

  const dimension_type src_d = var.id();
  const Constraint_System& cs = constraints();
  Constraint_System new_constraints;
  for (Constraint_System::const_iterator i = cs.begin(),
	 cs_end = cs.end(); i != cs_end; ++i) {
    const Constraint& c = *i;

    // If `c' does not constrain `var', skip it.
    if (c.coefficient(var) == 0)
      continue;

    // Each relevant constraint results in `m' new constraints.
    for (dimension_type dst_d = old_dim; dst_d < old_dim+m; ++dst_d) {
      Linear_Expression e;
      for (dimension_type j = old_dim; j-- > 0; )
	e +=
	  c.coefficient(Variable(j))
	  * (j == src_d ? Variable(dst_d) : Variable(j));
      e += c.inhomogeneous_term();
      new_constraints.insert(c.is_equality()
			     ? (e == 0)
			     : (c.is_nonstrict_inequality()
				? (e >= 0)
				: (e > 0)));
    }
  }
  add_recycled_constraints(new_constraints);
  PPL_ASSERT_HEAVY(OK());
}

void
PPL::Polyhedron::fold_space_dimensions(const Variables_Set& vars,
				       Variable dest) {
  // TODO: this implementation is _really_ an executable specification.

  // `dest' should be one of the dimensions of the polyhedron.
  if (dest.space_dimension() > space_dim)
    throw_dimension_incompatible("fold_space_dimensions(vs, v)", "v", dest);

  // The folding of no dimensions is a no-op.
  if (vars.empty())
    return;

  // All variables in `vars' should be dimensions of the polyhedron.
  if (vars.space_dimension() > space_dim)
    throw_dimension_incompatible("fold_space_dimensions(vs, v)",
				 "vs.space_dimension()",
				 vars.space_dimension());

  // Moreover, `dest.id()' should not occur in `vars'.
  if (vars.find(dest.id()) != vars.end())
    throw_invalid_argument("fold_space_dimensions(vs, v)",
			   "v should not occur in vs");

  // All of the affine images we are going to compute are not invertible,
  // hence we will need to compute the generators of the polyehdron.
  // Since we keep taking copies, make sure that a single conversion
  // from constraints to generators is computed.
  (void) generators();
  // Having generators, we now know if the polyhedron is empty:
  // in that case, folding is equivalent to just removing space dimensions.
  if (!marked_empty()) {
    for (Variables_Set::const_iterator i = vars.begin(),
           vs_end = vars.end(); i != vs_end; ++i) {
      Polyhedron copy = *this;
      copy.affine_image(dest, Linear_Expression(Variable(*i)));
      poly_hull_assign(copy);
    }
  }
  remove_space_dimensions(vars);
  PPL_ASSERT_HEAVY(OK());
}
