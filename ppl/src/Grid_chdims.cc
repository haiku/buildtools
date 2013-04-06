/* Grid class implementation
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

#include "Grid.defs.hh"
#include "Variables_Set.defs.hh"
#include "assert.hh"

namespace PPL = Parma_Polyhedra_Library;

// Used for add_space_dimensions_and_embed.
void
PPL::Grid::add_space_dimensions(Congruence_System& cgs,
				Grid_Generator_System& gs,
				const dimension_type dims) {
  PPL_ASSERT(cgs.num_columns() - 1 == gs.space_dimension() + 1);
  PPL_ASSERT(dims > 0);

  const dimension_type old_modulus_index = cgs.num_columns() - 1;
  cgs.add_zero_columns(dims);
  // Move the moduli.
  cgs.swap_columns(old_modulus_index, old_modulus_index + dims);

  if (congruences_are_minimized() || generators_are_minimized())
    dim_kinds.resize(old_modulus_index + dims, CON_VIRTUAL /* a.k.a. LINE */);

  gs.add_universe_rows_and_columns(dims);
}

// Used for add_space_dimensions_and_project.
void
PPL::Grid::add_space_dimensions(Grid_Generator_System& gs,
				Congruence_System& cgs,
				const dimension_type dims) {
  PPL_ASSERT(cgs.num_columns() - 1 == gs.space_dimension() + 1);
  PPL_ASSERT(dims > 0);

  cgs.add_unit_rows_and_columns(dims);

  // Add `dims' zero columns onto gs.
  gs.insert(parameter(0*Variable(space_dim + dims - 1)));

  normalize_divisors(gs);

  dim_kinds.resize(cgs.num_columns() - 1, EQUALITY /* a.k.a GEN_VIRTUAL */);
}

// (o is a point)       y
//
//                      |   |   |
//                 =>   |   |   |
//                      |   |   |
// o---o---o-- x        |---|---|-- x
// 0 1 2 3 4 5          0 1 2 3 4 5
//     R^1                   R^2
void
PPL::Grid::add_space_dimensions_and_embed(dimension_type m) {
  if (m == 0)
    return;

  // The space dimension of the resulting grid must be at most the
  // maximum allowed space dimension.
  if (m > max_space_dimension() - space_dimension())
    throw_space_dimension_overflow("add_space_dimensions_and_embed(m)",
				   "adding m new space dimensions exceeds "
				   "the maximum allowed space dimension");

  // Adding dimensions to an empty grid is obtained by adjusting
  // `space_dim' and clearing `con_sys' (since it can contain the
  // integrality congruence of the current dimension).
  if (marked_empty()) {
    space_dim += m;
    set_empty();
    return;
  }

  // The case of a zero-dimension space grid.
  if (space_dim == 0) {
    // Since it is not empty, it has to be the universe grid.
    PPL_ASSERT(status.test_zero_dim_univ());
    // Swap *this with a newly created `m'-dimensional universe grid.
    Grid gr(m, UNIVERSE);
    swap(gr);
    return;
  }

  // To embed an n-dimension space grid in a (n+m)-dimension space, we
  // add `m' zero-columns to the rows in the system of congruences; in
  // contrast, the system of generators needs additional rows,
  // corresponding to the vectors of the canonical basis for the added
  // dimensions. That is, for each new dimension we add the line
  // having that direction. This is done by invoking the function
  // add_space_dimensions().
  if (congruences_are_up_to_date())
    if (generators_are_up_to_date())
      // Adds rows and/or columns to both matrices.
      add_space_dimensions(con_sys, gen_sys, m);
    else {
      // Only congruences are up-to-date, so modify only them.
      con_sys.add_zero_columns(m);
      dimension_type size = con_sys.num_columns() - 1;
      // Move the moduli.
      con_sys.swap_columns(size - m, size);
      if (congruences_are_minimized())
	dim_kinds.resize(size, CON_VIRTUAL);
    }
  else {
    // Only generators are up-to-date, so modify only them.
    PPL_ASSERT(generators_are_up_to_date());
    gen_sys.add_universe_rows_and_columns(m);
    if (generators_are_minimized())
      dim_kinds.resize(gen_sys.space_dimension() + 1, LINE);
  }
  // Update the space dimension.
  space_dim += m;

  // Note: we do not check for satisfiability, because the system of
  // congruences may be unsatisfiable.
  PPL_ASSERT(OK());
}

// (o is a point)       y
//
//
//                 =>
//
// o---o---o-- x        o---o---o-- x
// 0 1 2 3 4 5          0 1 2 3 4 5
//     R^1                   R^2
void
PPL::Grid::add_space_dimensions_and_project(dimension_type m) {
  if (m == 0)
    return;

  // The space dimension of the resulting grid should be at most the
  // maximum allowed space dimension.
  if (m > max_space_dimension() - space_dimension())
    throw_space_dimension_overflow("add_space_dimensions_and_project(m)",
				   "adding m new space dimensions exceeds "
				   "the maximum allowed space dimension");

  // Adding dimensions to an empty grid is obtained by merely
  // adjusting `space_dim'.
  if (marked_empty()) {
    space_dim += m;
    set_empty();
    return;
  }

  if (space_dim == 0) {
    PPL_ASSERT(status.test_zero_dim_univ());
    // Swap *this with a newly created `n'-dimensional universe grid.
    Grid gr(m, UNIVERSE);
    swap(gr);
    return;
  }

  // To project an n-dimension space grid in a (n+m)-dimension space,
  // we just add to the system of generators `m' zero-columns; in
  // contrast, in the system of congruences, new rows are needed in
  // order to avoid embedding the old grid in the new space.  Thus,
  // for each new dimensions `x[k]', we add the constraint x[k] = 0;
  // this is done by invoking the function add_space_dimensions()
  // giving the system of constraints as the second argument.
  if (congruences_are_up_to_date())
    if (generators_are_up_to_date())
      // Add rows and/or columns to both matrices.
      add_space_dimensions(gen_sys, con_sys, m);
    else {
      // Only congruences are up-to-date so modify only them.
      con_sys.add_unit_rows_and_columns(m);
      if (congruences_are_minimized())
	dim_kinds.resize(con_sys.num_columns() - 1, EQUALITY);
    }
  else {
    // Only generators are up-to-date so modify only them.
    PPL_ASSERT(generators_are_up_to_date());

    // Add m zero columns onto gs.
    gen_sys.insert(parameter(0*Variable(space_dim + m - 1)));

    normalize_divisors(gen_sys);

    if (generators_are_minimized())
      dim_kinds.resize(gen_sys.space_dimension() + 1, EQUALITY);
  }
  // Now update the space dimension.
  space_dim += m;

  // Note: we do not check for satisfiability, because the system of
  // congruences may be unsatisfiable.
  PPL_ASSERT(OK());
}

void
PPL::Grid::concatenate_assign(const Grid& y) {
  // The space dimension of the resulting grid must be at most the
  // maximum allowed space dimension.
  if (y.space_dim > max_space_dimension() - space_dimension())
    throw_space_dimension_overflow("concatenate_assign(y)",
				   "concatenation exceeds the maximum "
				   "allowed space dimension");

  const dimension_type added_columns = y.space_dim;

  // If `*this' or `y' are empty grids just adjust the space
  // dimension.
  if (marked_empty() || y.marked_empty()) {
    space_dim += added_columns;
    set_empty();
    return;
  }

  // If `y' is a universe 0-dim grid, the result is `*this'.
  if (added_columns == 0)
    return;

  // If `*this' is a universe 0-dim space grid, the result is `y'.
  if (space_dim == 0) {
    *this = y;
    return;
  }

  if (!congruences_are_up_to_date())
    update_congruences();

  con_sys.concatenate(y.congruences());

  space_dim += added_columns;

  clear_congruences_minimized();
  clear_generators_up_to_date();

  // Check that the system is OK, taking into account that the system
  // of congruences may now be empty.
  PPL_ASSERT(OK());
}

void
PPL::Grid::remove_space_dimensions(const Variables_Set& vars) {
  // The removal of no dimensions from any grid is a no-op.  This case
  // also captures the only legal removal of dimensions from a grid in
  // a 0-dim space.
  if (vars.empty()) {
    PPL_ASSERT(OK());
    return;
  }

  // Dimension-compatibility check.
  const dimension_type min_space_dim = vars.space_dimension();
  if (space_dim < min_space_dim)
    throw_dimension_incompatible("remove_space_dimensions(vs)", min_space_dim);

  const dimension_type new_space_dim = space_dim - vars.size();

  if (marked_empty()
      || (!generators_are_up_to_date() && !update_generators())) {
    // Update the space dimension.
    space_dim = new_space_dim;
    set_empty();
    PPL_ASSERT(OK());
    return;
  }

  // Removing _all_ dimensions from a non-empty grid obtains the
  // zero-dimensional universe grid.
  if (new_space_dim == 0) {
    set_zero_dim_univ();
    return;
  }

  gen_sys.remove_space_dimensions(vars);

  clear_congruences_up_to_date();
  clear_generators_minimized();

  // Update the space dimension.
  space_dim = new_space_dim;

  PPL_ASSERT(OK(true));
}

void
PPL::Grid::remove_higher_space_dimensions(const dimension_type new_dimension) {
  // Dimension-compatibility check.
  if (new_dimension > space_dim)
    throw_dimension_incompatible("remove_higher_space_dimensions(nd)",
				 new_dimension);

  // The removal of no dimensions from any grid is a no-op.
  // Note that this case also captures the only legal removal of
  // dimensions from a grid in a 0-dim space.
  if (new_dimension == space_dim) {
    PPL_ASSERT(OK());
    return;
  }

  if (is_empty()) {
    // Removing dimensions from the empty grid just updates the space
    // dimension.
    space_dim = new_dimension;
    set_empty();
    PPL_ASSERT(OK());
    return;
  }

  if (new_dimension == 0) {
    // Removing all dimensions from a non-empty grid just returns the
    // zero-dimensional universe grid.
    set_zero_dim_univ();
    return;
  }

  // Favor the generators, as is done by is_empty().
  if (generators_are_up_to_date()) {
    gen_sys.remove_higher_space_dimensions(new_dimension);
    if (generators_are_minimized()) {
      // Count the actual number of rows that are now redundant.
      dimension_type num_redundant = 0;
      const dimension_type num_old_gs = space_dim - new_dimension;
      for (dimension_type row = 0; row < num_old_gs; ++row)
	dim_kinds[row] == GEN_VIRTUAL || ++num_redundant;
      if (num_redundant > 0) {
	// Chop zero rows from end of system, to keep minimal form.
	gen_sys.erase_to_end(gen_sys.num_rows() - num_redundant);
	gen_sys.unset_pending_rows();
      }
      dim_kinds.erase(dim_kinds.begin() + new_dimension + 1, dim_kinds.end());
      // TODO: Consider if it is worth also preserving the congruences
      //       if they are also in minimal form.
    }
    clear_congruences_up_to_date();
    // Extend the zero dim false congruence system to the appropriate
    // dimension and then swap it with `con_sys'.
    Congruence_System cgs(Congruence::zero_dim_false());
    // Extra 2 columns for inhomogeneous term and modulus.
    cgs.increase_space_dimension(new_dimension + 2);
    con_sys.swap(cgs);
  }
  else {
    PPL_ASSERT(congruences_are_minimized());
    con_sys.remove_higher_space_dimensions(new_dimension);
    // Count the actual number of rows that are now redundant.
    dimension_type num_redundant = 0;
    for (dimension_type row = space_dim; row > new_dimension; --row)
      dim_kinds[row] == CON_VIRTUAL || ++num_redundant;
    if (num_redundant > 0) {
      dimension_type rows = con_sys.num_rows();
      // Shuffle the remaining rows upwards.
      for (dimension_type low = 0, high = num_redundant;
	   high < rows;
	   ++high, ++low)
	std::swap(con_sys[low], con_sys[high]);
      // Chop newly redundant rows from end of system, to keep minimal
      // form.
      con_sys.erase_to_end(rows - num_redundant);
    }
    dim_kinds.erase(dim_kinds.begin() + new_dimension + 1, dim_kinds.end());
    clear_generators_up_to_date();
    // Replace gen_sys with an empty system of the right dimension.
    // Extra 2 columns for inhomogeneous term and modulus.
    Grid_Generator_System gs(new_dimension + 2);
    gen_sys.swap(gs);
  }

  // Update the space dimension.
  space_dim = new_dimension;

  PPL_ASSERT(OK(true));
}

void
PPL::Grid::expand_space_dimension(Variable var, dimension_type m) {
  // TODO: this implementation is _really_ an executable specification.

  // `var' must be one of the dimensions of the vector space.
  if (var.space_dimension() > space_dim)
    throw_dimension_incompatible("expand_space_dimension(v, m)", "v", var);

  // Adding 0 dimensions leaves the same grid.
  if (m == 0)
    return;

  // The resulting space dimension must be at most the maximum.
  if (m > max_space_dimension() - space_dimension())
    throw_space_dimension_overflow("expand_space_dimension(v, m)",
				   "adding m new space dimensions exceeds "
				   "the maximum allowed space dimension");

  // Save the number of dimensions before adding new ones.
  dimension_type old_dim = space_dim;

  // Add the required new dimensions.
  add_space_dimensions_and_embed(m);

  const dimension_type src_d = var.id();
  const Congruence_System& cgs = congruences();
  Congruence_System new_congruences;
  for (Congruence_System::const_iterator i = cgs.begin(),
	 cgs_end = cgs.end(); i != cgs_end; ++i) {
    const Congruence& cg = *i;

    // Only consider congruences that constrain `var'.
    if (cg.coefficient(var) == 0)
      continue;

    // Each relevant congruence results in `m' new congruences.
    for (dimension_type dst_d = old_dim; dst_d < old_dim+m; ++dst_d) {
      Linear_Expression e;
      for (dimension_type j = old_dim; j-- > 0; )
	e +=
	  cg.coefficient(Variable(j))
	  * (j == src_d ? Variable(dst_d) : Variable(j));
      new_congruences.insert_verbatim((e + cg.inhomogeneous_term() %= 0)
				      / cg.modulus());
    }
  }
  add_recycled_congruences(new_congruences);
  PPL_ASSERT(OK());
}

void
PPL::Grid::fold_space_dimensions(const Variables_Set& vars, Variable dest) {
  // TODO: this implementation is _really_ an executable specification.

  // `dest' should be one of the dimensions of the grid.
  if (dest.space_dimension() > space_dim)
    throw_dimension_incompatible("fold_space_dimensions(vs, v)", "v", dest);

  // Folding only has effect if dimensions are given.
  if (vars.empty())
    return;

  // All variables in `vars' must be dimensions of the grid.
  if (vars.space_dimension() > space_dim)
    throw_dimension_incompatible("fold_space_dimensions(vs, v)",
				 "vs.space_dimension()",
				 vars.space_dimension());

  // Moreover, `dest.id()' must not occur in `vars'.
  if (vars.find(dest.id()) != vars.end())
    throw_invalid_argument("fold_space_dimensions(vs, v)",
			   "v should not occur in vs");
  // All of the affine images we are going to compute are not invertible,
  // hence we will need to compute the grid generators of the polyhedron.
  // Since we keep taking copies, make sure that a single conversion
  // from congruences to grid generators is computed.
  (void) grid_generators();
  // Having grid generators, we now know if the grid is empty:
  // in that case, folding is equivalent to just removing space dimensions.
  if (!marked_empty()) {
    for (Variables_Set::const_iterator i = vars.begin(),
           vs_end = vars.end(); i != vs_end; ++i) {
      Grid copy = *this;
      copy.affine_image(dest, Linear_Expression(Variable(*i)));
      upper_bound_assign(copy);
    }
  }
  remove_space_dimensions(vars);
  PPL_ASSERT(OK());
}
