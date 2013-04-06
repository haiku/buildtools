/* Grid class implementation: conversion().
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
#include <cstddef>

namespace Parma_Polyhedra_Library {

// X 0 0 0  upside down, so  x x x X
// x X 0 0                   x x X 0
// x x X 0                   x X 0 0
// x x x X                   X 0 0 0
//
// Where X is greater than zero and x is an integer.
bool
Grid::lower_triangular(const Congruence_System& sys,
		       const Dimension_Kinds& dim_kinds) {
  const dimension_type num_columns = sys.num_columns() - 1;

  // Check for easy square failure case.
  if (sys.num_rows() > num_columns)
    return false;

  // Check triangularity.

  dimension_type row = 0;
  for (dimension_type dim = num_columns; dim-- > 0; ) {
    if (dim_kinds[dim] == CON_VIRTUAL)
      continue;
    const Congruence& cg = sys[row];
    ++row;
    // Check diagonal.
    if (cg[dim] <= 0)
      return false;
    // Check elements following diagonal.
    dimension_type col = dim;
    while (++col < num_columns)
      if (cg[col] != 0)
	return false;
  }

  // Check squareness.
  return row == sys.num_rows();
}

// X x x x
// 0 X x x
// 0 0 X x
// 0 0 0 X
//
// Where X is greater than zero and x is an integer.
bool
Grid::upper_triangular(const Grid_Generator_System& sys,
		       const Dimension_Kinds& dim_kinds) {
  dimension_type num_columns = sys.space_dimension() + 1;
  dimension_type row = sys.num_rows();

  // Check for easy square fail case.
  if (row > num_columns)
    return false;

  // Check triangularity.
  while (num_columns > 0) {
    --num_columns;
    if (dim_kinds[num_columns] == GEN_VIRTUAL)
      continue;
    const Grid_Generator& gen = sys[--row];
    // Check diagonal.
    if (gen[num_columns] <= 0)
      return false;
    // Check elements preceding diagonal.
    dimension_type col = num_columns;
    while (col-- > 0)
      if (gen[col] != 0)
	return false;
  }

  // Check for squareness.
  return num_columns == row;
}

void
Grid::multiply_grid(const Coefficient& multiplier, Grid_Generator& gen,
		    Grid_Generator_System& dest, const dimension_type num_rows,
		    const dimension_type num_dims) {
  if (multiplier == 1)
    return;

  if (gen.is_line())
    // Multiply every element of the line.
    for (dimension_type column = num_dims; column-- > 0; )
      gen[column] *= multiplier;
  else {
    PPL_ASSERT(gen.is_parameter_or_point());
    // Multiply every element of every parameter.
    for (dimension_type index = num_rows; index-- > 0; ) {
      Grid_Generator& generator = dest[index];
      if (generator.is_parameter_or_point())
	for (dimension_type column = num_dims; column-- > 0; )
	  generator[column] *= multiplier;
    }
  }
}

void
Grid::multiply_grid(const Coefficient& multiplier, Congruence& cg,
		    Congruence_System& dest, const dimension_type num_rows,
		    const dimension_type num_dims) {
  if (multiplier == 1)
    return;

  if (cg.is_proper_congruence())
    // Multiply every element of every congruence.
    for (dimension_type index = num_rows; index-- > 0; ) {
      Congruence& congruence = dest[index];
      if (congruence.is_proper_congruence())
	for (dimension_type column = num_dims; column-- > 0; )
	  congruence[column] *= multiplier;
    }
  else {
    PPL_ASSERT(cg.is_equality());
    // Multiply every element of the equality.
    for (dimension_type column = num_dims; column-- > 0; )
      cg[column] *= multiplier;
  }
}

// TODO: Rename the next two methods to convert and this file to
//       Grid_convert.cc (and equivalently for Polyhedron) to use
//       verbs consistently as function and method names.

void
Grid::conversion(Grid_Generator_System& source, Congruence_System& dest,
		 Dimension_Kinds& dim_kinds) {
  // Quite similar to the congruence to generator version below.
  // Changes here may be needed there too.

  PPL_ASSERT(upper_triangular(source, dim_kinds));

  // Initialize matrix row number counters and compute the LCM of the
  // diagonal entries of the parameters in `source'.
  //
  // The top-down order of the generator system rows corresponds to
  // the left-right order of the dimensions, while the congruence
  // system rows have a bottom-up ordering.
  dimension_type dest_num_rows = 0;
  PPL_DIRTY_TEMP_COEFFICIENT(diagonal_lcm);
  diagonal_lcm = 1;
  const dimension_type dims = source.space_dimension() + 1;
  dimension_type source_index = source.num_rows();
  for (dimension_type dim = dims; dim-- > 0; )
    if (dim_kinds[dim] == GEN_VIRTUAL)
      // Virtual generators map to equalities.
      ++dest_num_rows;
    else {
      --source_index;
      if (dim_kinds[dim] == PARAMETER) {
	// Dimension `dim' has a parameter row at `source_index' in
	// `source', so include in `diagonal_lcm' the `dim'th element
	// of that row.
	lcm_assign(diagonal_lcm, diagonal_lcm, source[source_index][dim]);
	// Parameters map to proper congruences.
	++dest_num_rows;
      }
      // Lines map to virtual congruences.
    }
  PPL_ASSERT(source_index == 0);

  // `source' must be regular.
  if (diagonal_lcm == 0)
    throw std::runtime_error("PPL internal error: Grid::conversion:"
			     " source matrix is singular.");

  dest.resize_no_copy(dest_num_rows, dims + 1 /* moduli */);

  // In `dest' initialize row types and elements, including setting
  // the diagonal elements to the inverse ratio of the `source'
  // diagonal elements.
  dimension_type dest_index = 0;
  source_index = source.num_rows();
  for (dimension_type dim = dims; dim-- > 0; ) {
    if (dim_kinds[dim] == LINE)
      --source_index;
    else {
      Congruence& cg = dest[dest_index];
      for (dimension_type j = dim; j-- > 0; )
	cg[j] = 0;
      for (dimension_type j = dim + 1; j < dims; ++j)
	cg[j] = 0;

      if (dim_kinds[dim] == GEN_VIRTUAL) {
	cg[dims] = 0;		// An equality.
	cg[dim] = 1;
      }
      else {
	PPL_ASSERT(dim_kinds[dim] == PARAMETER);
	--source_index;
	cg[dims] = 1;		// A proper congruence.
	exact_div_assign(cg[dim], diagonal_lcm, source[source_index][dim]);
      }
      ++dest_index;
    }
  }

  PPL_ASSERT(source_index == 0);
  PPL_ASSERT(dest_index == dest_num_rows);
  PPL_ASSERT(lower_triangular(dest, dim_kinds));

  // Convert.
  //
  // `source_index' and `dest_index' hold the positions of pivot rows
  // in `source' and `dest'.  The order of the rows in `dest' is the
  // reverse of the order in `source', so the rows are iterated from
  // last to first (index 0) in `source' and from first to last in
  // `dest'.
  source_index = source.num_rows();
  dest_index = 0;
  PPL_DIRTY_TEMP_COEFFICIENT(multiplier);

  for (dimension_type dim = dims; dim-- > 0; ) {
    if (dim_kinds[dim] != GEN_VIRTUAL) {
      --source_index;
      const Coefficient& source_dim = source[source_index][dim];

      // In the rows in `dest' above `dest_index' divide each element
      // at column `dim' by `source_dim'.
      for (dimension_type row = dest_index; row-- > 0; ) {
	Congruence& cg = dest[row];

	// Multiply the representation of `dest' such that entry `dim'
        // of `g' is a multiple of `source_dim'.  This ensures that
        // the result of the division that follows is a whole number.
	gcd_assign(multiplier, cg[dim], source_dim);
	exact_div_assign(multiplier, source_dim, multiplier);
	multiply_grid(multiplier, cg, dest, dest_num_rows, dims);

	Coefficient& cg_dim = cg[dim];
	exact_div_assign(cg_dim, cg_dim, source_dim);
      }
    }

    // Invert and transpose the source row at `source_index' into the
    // destination row at `dest_index'.
    //
    // Consider each dimension `dim_prec' that precedes `dim', as the
    // rows in `dest' that follow `dim_index' have zeroes at index
    // `dim'.
    dimension_type tmp_source_index = source_index;
    if (dim_kinds[dim] != LINE)
      ++dest_index;
    for (dimension_type dim_prec = dim; dim_prec-- > 0; ) {
      if (dim_kinds[dim_prec] != GEN_VIRTUAL) {
	--tmp_source_index;
	const Coefficient& source_dim = source[tmp_source_index][dim];
	// In order to compute the transpose of the inverse of
	// `source', subtract source[tmp_source_index][dim] times the
	// column vector in `dest' at `dim' from the column vector in
	// `dest' at `dim_prec'.
	//
	// I.e., for each row `dest_index' in `dest' that is above the
	// row `dest_index', subtract dest[tmp_source_index][dim]
	// times the entry `dim' from the entry at `dim_prec'.
	for (dimension_type row = dest_index; row-- > 0; ) {
	  PPL_ASSERT(row < dest_num_rows);
	  Congruence& cg = dest[row];
	  sub_mul_assign(cg[dim_prec], source_dim, cg[dim]);
	}
      }
    }
  }
  // Set the modulus in every congruence.
  const Coefficient& modulus = dest[dest_num_rows - 1][0];
  for (dimension_type row = dest_num_rows; row-- > 0; ) {
    Congruence& cg = dest[row];
    if (cg[dims] > 0)
      // `cg' is a proper congruence.
      cg[dims] = modulus;
  }

  PPL_ASSERT(lower_triangular(dest, dim_kinds));

  // Since we are reducing the system to "strong minimal form",
  // reduce the coefficients in the congruence system
  // using "diagonal" values.
  for (dimension_type dim = dims, i = 0; dim-- > 0; )
    if (dim_kinds[dim] != CON_VIRTUAL)
      // Factor the "diagonal" congruence out of the preceding rows.
      reduce_reduced<Congruence_System, Congruence>
	(dest, dim, i++, 0, dim, dim_kinds, false);
}

void
Grid::conversion(Congruence_System& source, Grid_Generator_System& dest,
		 Dimension_Kinds& dim_kinds) {
  // Quite similar to the generator to congruence version above.
  // Changes here may be needed there too.

  PPL_ASSERT(lower_triangular(source, dim_kinds));

  // Initialize matrix row number counters and compute the LCM of the
  // diagonal entries of the proper congruences in `source'.
  dimension_type source_num_rows = 0, dest_num_rows = 0;
  PPL_DIRTY_TEMP_COEFFICIENT(diagonal_lcm);
  diagonal_lcm = 1;
  dimension_type dims = source.num_columns() - 1;
  for (dimension_type dim = dims; dim-- > 0; )
    if (dim_kinds[dim] == CON_VIRTUAL)
      // Virtual congruences map to lines.
      ++dest_num_rows;
    else {
      if (dim_kinds[dim] == PROPER_CONGRUENCE) {
	// Dimension `dim' has a proper congruence row at
	// `source_num_rows' in `source', so include in `diagonal_lcm'
	// the `dim'th element of that row.
	lcm_assign(diagonal_lcm, diagonal_lcm, source[source_num_rows][dim]);
	// Proper congruences map to parameters.
	++dest_num_rows;
      }
      // Equalities map to virtual generators.
      ++source_num_rows;
    }

  // `source' must be regular.
  if (diagonal_lcm == 0)
    throw std::runtime_error("PPL internal error: Grid::conversion:"
			     " source matrix is singular.");

  dest.set_index_first_pending_row(dest_num_rows);
  dest.resize_no_copy(dest_num_rows, dims + 1 /* parameter divisor */);

  // In `dest' initialize row types and elements, including setting
  // the diagonal elements to the inverse ratio of the `source'
  // diagonal elements.
  //
  // The top-down order of the congruence system rows corresponds to
  // the right-left order of the dimensions.
  dimension_type source_index = 0;
  // The generator system has a bottom-up ordering.
  dimension_type dest_index = dest_num_rows - 1;
  for (dimension_type dim = dims; dim-- > 0; ) {
    if (dim_kinds[dim] == EQUALITY) {
      ++source_index;
    }
    else {
      Grid_Generator& g = dest[dest_index];
      for (dimension_type j = dim; j-- > 0; )
	g[j] = 0;
      for (dimension_type j = dim + 1; j < dims; ++j)
	g[j] = 0;

      if (dim_kinds[dim] == CON_VIRTUAL) {
	g.set_is_line();
	g[dim] = 1;
      }
      else {
	PPL_ASSERT(dim_kinds[dim] == PROPER_CONGRUENCE);
	g.set_is_parameter_or_point();
	exact_div_assign(g[dim], diagonal_lcm, source[source_index][dim]);
	++source_index;
      }
      --dest_index;
    }
  }

  PPL_ASSERT(upper_triangular(dest, dim_kinds));

  // Convert.
  //
  // `source_index' and `dest_index' hold the positions of pivot rows
  // in `source' and `dest'.  The order of the rows in `dest' is the
  // reverse of the order in `source', so the rows are iterated from
  // last to first (index 0) in `source' and from first to last in
  // `dest'.
  source_index = source_num_rows;
  dest_index = 0;
  PPL_DIRTY_TEMP_COEFFICIENT(reduced_source_dim);

  for (dimension_type dim = 0; dim < dims; ++dim) {
    if (dim_kinds[dim] != CON_VIRTUAL) {
      --source_index;
      const Coefficient& source_dim = source[source_index][dim];

      // In the rows in `dest' above `dest_index' divide each element
      // at column `dim' by `source_dim'.
      for (dimension_type row = dest_index; row-- > 0; ) {
	Grid_Generator& g = dest[row];

	// Multiply the representation of `dest' such that entry `dim'
        // of `g' is a multiple of `source_dim'.  This ensures that
        // the result of the division that follows is a whole number.
	gcd_assign(reduced_source_dim, g[dim], source_dim);
	exact_div_assign(reduced_source_dim, source_dim, reduced_source_dim);
	multiply_grid(reduced_source_dim, g, dest, dest_num_rows,
		      dims + 1 /* parameter divisor */);

	Coefficient& g_dim = g[dim];
	exact_div_assign(g_dim, g_dim, source_dim);
      }
    }

    // Invert and transpose the source row at `source_index' into the
    // destination row at `dest_index'.
    //
    // Consider each dimension `dim_fol' that follows `dim', as the
    // rows in `dest' that follow row `dest_index' are zero at index
    // `dim'.
    dimension_type tmp_source_index = source_index;
    if (dim_kinds[dim] != EQUALITY)
      ++dest_index;
    for (dimension_type dim_fol = dim + 1; dim_fol < dims; ++dim_fol) {
      if (dim_kinds[dim_fol] != CON_VIRTUAL) {
	--tmp_source_index;
	const Coefficient& source_dim = source[tmp_source_index][dim];
	// In order to compute the transpose of the inverse of
	// `source', subtract source[tmp_source_index][dim] times the
	// column vector in `dest' at `dim' from the column vector in
	// `dest' at `dim_fol'.
	//
	// I.e., for each row `dest_index' in `dest' that is above the
	// row `dest_index', subtract dest[tmp_source_index][dim]
	// times the entry `dim' from the entry at `dim_fol'.
	for (dimension_type row = dest_index; row-- > 0; ) {
	  PPL_ASSERT(row < dest_num_rows);
	  Grid_Generator& g = dest[row];
	  sub_mul_assign(g[dim_fol], source_dim, g[dim]);
	}
      }
    }
  }

  PPL_ASSERT(upper_triangular(dest, dim_kinds));

  // Since we are reducing the system to "strong minimal form",
  // reduce the coordinates in the grid_generator system
  // using "diagonal" values.
  for (dimension_type dim = 0, i = 0; dim < dims; ++dim)
    if (dim_kinds[dim] != GEN_VIRTUAL)
      // Factor the "diagonal" generator out of the preceding rows.
      reduce_reduced<Grid_Generator_System, Grid_Generator>
	(dest, dim, i++, dim, dims - 1, dim_kinds);

  // Ensure that the parameter divisors are the same as the divisor of
  // the point.
  const Coefficient& system_divisor = dest[0][0];
  for (dimension_type row = dest.num_rows() - 1, dim = dims;
       dim-- > 1; )
    switch (dim_kinds[dim]) {
    case PARAMETER:
      dest[row].set_divisor(system_divisor);
    case LINE:
      --row;
    case GEN_VIRTUAL:
      break;
    }
}

} // namespace Parma_Polyhedra_Library
