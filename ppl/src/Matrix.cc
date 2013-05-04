/* Matrix class implementation (non-inline functions).
   Copyright (C) 2001-2010 Roberto Bagnara <bagnara@cs.unipr.it>

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

#include "Matrix.defs.hh"
#include "Row.defs.hh"
#include <algorithm>
#include <iostream>
#include <string>

namespace PPL = Parma_Polyhedra_Library;

PPL::Matrix::Matrix(const dimension_type n_rows,
		    const dimension_type n_columns,
		    Row::Flags row_flags)
  :
#ifdef NDEBUG
    rows(n_rows),
#else
    rows(n_rows <= max_num_rows() ? n_rows : 0),
#endif
    row_size(n_columns),
    row_capacity(compute_capacity(n_columns, max_num_columns())) {
  PPL_ASSERT(n_rows <= max_num_rows());
  // Construct in direct order: will destroy in reverse order.
  for (dimension_type i = 0; i < n_rows; ++i)
    rows[i].construct(n_columns, row_capacity, row_flags);
  PPL_ASSERT(OK());
}

void
PPL::Matrix::add_zero_rows(const dimension_type n, Row::Flags row_flags) {
  PPL_ASSERT(n > 0);
  PPL_ASSERT(n <= max_num_rows() - num_rows());
  const dimension_type old_num_rows = rows.size();
  const dimension_type new_num_rows = old_num_rows + n;

  if (rows.capacity() < new_num_rows) {
    // Reallocation will take place.
    std::vector<Row> new_rows;
    new_rows.reserve(compute_capacity(new_num_rows, max_num_rows()));
    new_rows.insert(new_rows.end(), new_num_rows, Row());
    // Construct the new rows.
    dimension_type i = new_num_rows;
    while (i-- > old_num_rows)
      new_rows[i].construct(row_size, row_capacity, row_flags);
    // Steal the old rows.
    ++i;
    while (i-- > 0)
      new_rows[i].swap(rows[i]);
    // Put the new vector into place.
    std::swap(rows, new_rows);
  }
  else {
    // Reallocation will NOT take place.
    rows.insert(rows.end(), n, Row());
    for (dimension_type i = new_num_rows; i-- > old_num_rows; )
      rows[i].construct(row_size, row_capacity, row_flags);
  }
}

void
PPL::Matrix::add_zero_columns(const dimension_type n) {
  PPL_ASSERT(n > 0);
  PPL_ASSERT(n <= max_num_columns() - num_columns());
  const dimension_type num_rows = rows.size();
  const dimension_type new_num_columns = row_size + n;

  if (new_num_columns <= row_capacity)
    // We have enough capacity: we resize existing rows.
    for (dimension_type i = num_rows; i-- > 0; )
      rows[i].expand_within_capacity(new_num_columns);
  else {
    // Capacity exhausted: we must reallocate the rows and
    // make sure all the rows have the same capacity.
    const dimension_type new_row_capacity
      = compute_capacity(new_num_columns, max_num_columns());
    PPL_ASSERT(new_row_capacity <= max_num_columns());
    for (dimension_type i = num_rows; i-- > 0; ) {
      Row new_row(rows[i], new_num_columns, new_row_capacity);
      std::swap(rows[i], new_row);
    }
    row_capacity = new_row_capacity;
  }
  // Rows have been expanded.
  row_size = new_num_columns;
}

void
PPL::Matrix::add_zero_rows_and_columns(const dimension_type n,
				       const dimension_type m,
				       Row::Flags row_flags) {
  PPL_ASSERT(n > 0);
  PPL_ASSERT(n <= max_num_rows() - num_rows());
  PPL_ASSERT(m > 0);
  PPL_ASSERT(m <= max_num_columns() - num_columns());
  const dimension_type old_num_rows = rows.size();
  const dimension_type new_num_rows = old_num_rows + n;
  const dimension_type new_num_columns = row_size + m;

  if (new_num_columns <= row_capacity) {
    // We can recycle the old rows.
    if (rows.capacity() < new_num_rows) {
      // Reallocation will take place.
      std::vector<Row> new_rows;
      new_rows.reserve(compute_capacity(new_num_rows, max_num_rows()));
      new_rows.insert(new_rows.end(), new_num_rows, Row());
      // Construct the new rows.
      dimension_type i = new_num_rows;
      while (i-- > old_num_rows)
	new_rows[i].construct(new_num_columns, row_capacity, row_flags);
      // Expand and steal the old rows.
      ++i;
      while (i-- > 0) {
	rows[i].expand_within_capacity(new_num_columns);
	new_rows[i].swap(rows[i]);
      }
      // Put the new vector into place.
      std::swap(rows, new_rows);
    }
    else {
      // Reallocation will NOT take place.
      rows.insert(rows.end(), n, Row());
      // Construct the new rows.
      dimension_type i = new_num_rows;
      while (i-- > old_num_rows)
	rows[i].construct(new_num_columns, row_capacity, row_flags);
      // Expand the old rows.
      ++i;
      while (i-- > 0)
	rows[i].expand_within_capacity(new_num_columns);
    }
    row_size = new_num_columns;
  }
  else {
    // We cannot even recycle the old rows.
    Matrix new_matrix;
    new_matrix.rows.reserve(compute_capacity(new_num_rows, max_num_rows()));
    new_matrix.rows.insert(new_matrix.rows.end(), new_num_rows, Row());
    // Construct the new rows.
    new_matrix.row_size = new_num_columns;
    new_matrix.row_capacity = compute_capacity(new_num_columns,
					       max_num_columns());
    dimension_type i = new_num_rows;
    while (i-- > old_num_rows)
      new_matrix.rows[i].construct(new_matrix.row_size,
				   new_matrix.row_capacity,
				   row_flags);
    // Copy the old rows.
    ++i;
    while (i-- > 0) {
      Row new_row(rows[i],
		  new_matrix.row_size,
		  new_matrix.row_capacity);
      std::swap(new_matrix.rows[i], new_row);
    }
    // Put the new vector into place.
    swap(new_matrix);
  }
}

void
PPL::Matrix::add_recycled_row(Row& y) {
  // The added row must have the same size and capacity as the
  // existing rows of the system.
  PPL_ASSERT(y.OK(row_size, row_capacity));
  const dimension_type new_rows_size = rows.size() + 1;
  if (rows.capacity() < new_rows_size) {
    // Reallocation will take place.
    std::vector<Row> new_rows;
    new_rows.reserve(compute_capacity(new_rows_size, max_num_rows()));
    new_rows.insert(new_rows.end(), new_rows_size, Row());
    // Put the new row in place.
    dimension_type i = new_rows_size-1;
    std::swap(new_rows[i], y);
    // Steal the old rows.
    while (i-- > 0)
      new_rows[i].swap(rows[i]);
    // Put the new rows into place.
    std::swap(rows, new_rows);
  }
  else
    // Reallocation will NOT take place.
    // Inserts a new empty row at the end,
    // then substitutes it with a copy of the given row.
    std::swap(*rows.insert(rows.end(), Row()), y);

  PPL_ASSERT(OK());
}

void
PPL::Matrix::resize_no_copy(const dimension_type new_n_rows,
			    const dimension_type new_n_columns,
			    Row::Flags row_flags) {
  dimension_type old_n_rows = rows.size();
  // Note that, if we have `new_n_rows <= old_n_rows' and
  // `new_n_columns >= row_size', the matrix will keep its sortedness.
  // This is obvious if `new_n_columns == row_size'.
  // If `new_n_columns > row_size', then sortedness is maintained
  // because trailing zeroes will be added to all rows.
  if (new_n_rows > old_n_rows) {
    if (new_n_columns <= row_capacity) {
      // We can recycle the old rows.
      if (rows.capacity() < new_n_rows) {
	// Reallocation (of vector `rows') will take place.
	std::vector<Row> new_rows;
	new_rows.reserve(compute_capacity(new_n_rows, max_num_rows()));
	new_rows.insert(new_rows.end(), new_n_rows, Row());
	// Construct the new rows (be careful: each new row must have
	// the same capacity as each one of the old rows).
	dimension_type i = new_n_rows;
	while (i-- > old_n_rows)
	  new_rows[i].construct(new_n_columns, row_capacity, row_flags);
	// Steal the old rows.
	++i;
	while (i-- > 0)
	  new_rows[i].swap(rows[i]);
	// Put the new vector into place.
	std::swap(rows, new_rows);
      }
      else {
	// Reallocation (of vector `rows') will NOT take place.
	rows.insert(rows.end(), new_n_rows - old_n_rows, Row());
	// Be careful: each new row must have
	// the same capacity as each one of the old rows.
	for (dimension_type i = new_n_rows; i-- > old_n_rows; )
	  rows[i].construct(new_n_columns, row_capacity, row_flags);
      }
    }
    else {
      // We cannot even recycle the old rows: allocate a new matrix and swap.
      Matrix new_matrix(new_n_rows, new_n_columns, row_flags);
      swap(new_matrix);
      return;
    }
  }
  else if (new_n_rows < old_n_rows) {
    // Drop some rows.
    rows.erase(rows.begin() + new_n_rows, rows.end());
    old_n_rows = new_n_rows;
  }
  // Here we have the right number of rows.
  if (new_n_columns != row_size) {
    if (new_n_columns < row_size) {
      // Shrink the existing rows.
      for (dimension_type i = old_n_rows; i-- > 0; )
	rows[i].shrink(new_n_columns);
    }
    else
      // We need more columns.
      if (new_n_columns <= row_capacity)
	// But we have enough capacity: we resize existing rows.
	for (dimension_type i = old_n_rows; i-- > 0; )
	  rows[i].expand_within_capacity(new_n_columns);
      else {
	// Capacity exhausted: we must reallocate the rows and
	// make sure all the rows have the same capacity.
	const dimension_type new_row_capacity
	  = compute_capacity(new_n_columns, max_num_columns());
	for (dimension_type i = old_n_rows; i-- > 0; ) {
	  Row new_row(new_n_columns, new_row_capacity, row_flags);
	  std::swap(rows[i], new_row);
	}
	row_capacity = new_row_capacity;
      }
    // Rows have grown or shrunk.
    row_size = new_n_columns;
  }
}

void
PPL::Matrix::ascii_dump(std::ostream& s) const {
  const Matrix& x = *this;
  dimension_type x_num_rows = x.num_rows();
  dimension_type x_num_columns = x.num_columns();
  s << x_num_rows << " x " << x_num_columns << "\n";
  for (dimension_type i = 0; i < x_num_rows; ++i)
    x[i].ascii_dump(s);
}

PPL_OUTPUT_DEFINITIONS_ASCII_ONLY(Matrix)

bool
PPL::Matrix::ascii_load(std::istream& s) {
  Matrix& x = *this;
  std::string str;
  dimension_type x_num_rows;
  dimension_type x_num_cols;
  if (!(s >> x_num_rows))
    return false;
  if (!(s >> str) || str != "x")
    return false;
  if (!(s >> x_num_cols))
    return false;

  resize_no_copy(x_num_rows, x_num_cols, Row::Flags());

  for (dimension_type row = 0; row < x_num_rows; ++row)
    if (!x[row].ascii_load(s))
      return false;

  // Check invariants.
  PPL_ASSERT(OK());
  return true;
}

void
PPL::Matrix::swap_columns(const dimension_type i, const dimension_type j) {
  PPL_ASSERT(i != j && i < num_columns() && j < num_columns());
  for (dimension_type k = num_rows(); k-- > 0; ) {
    Row& rows_k = rows[k];
    std::swap(rows_k[i], rows_k[j]);
  }
}

void
PPL::Matrix::remove_trailing_columns(const dimension_type n) {
  PPL_ASSERT(n > 0);
  PPL_ASSERT(n <= row_size);
  row_size -= n;
  for (dimension_type i = num_rows(); i-- > 0; )
    rows[i].shrink(row_size);
}

void
PPL::Matrix::permute_columns(const std::vector<dimension_type>& cycles) {
  PPL_DIRTY_TEMP_COEFFICIENT(tmp);
  const dimension_type n = cycles.size();
  PPL_ASSERT(cycles[n - 1] == 0);
  for (dimension_type k = num_rows(); k-- > 0; ) {
    Row& rows_k = rows[k];
    for (dimension_type i = 0, j = 0; i < n; i = ++j) {
      // Make `j' be the index of the next cycle terminator.
      while (cycles[j] != 0)
	++j;
      // Cycles of length less than 2 are not allowed.
      PPL_ASSERT(j - i >= 2);
      if (j - i == 2)
	// For cycles of length 2 no temporary is needed, just a swap.
	std::swap(rows_k[cycles[i]], rows_k[cycles[i+1]]);
      else {
	// Longer cycles need a temporary.
	std::swap(rows_k[cycles[j-1]], tmp);
	for (dimension_type l = j-1; l > i; --l)
	  std::swap(rows_k[cycles[l-1]], rows_k[cycles[l]]);
	std::swap(tmp, rows_k[cycles[i]]);
      }
    }
  }
}

/*! \relates Parma_Polyhedra_Library::Matrix */
bool
PPL::operator==(const Matrix& x, const Matrix& y) {
  if (x.num_columns() != y.num_columns())
    return false;
  const dimension_type x_num_rows = x.num_rows();
  const dimension_type y_num_rows = y.num_rows();
  if (x_num_rows != y_num_rows)
    return false;
  for (dimension_type i = x_num_rows; i-- > 0; )
    if (x[i] != y[i])
      return false;
  return true;
}

PPL::memory_size_type
PPL::Matrix::external_memory_in_bytes() const {
  memory_size_type n = rows.capacity() * sizeof(Row);
  for (dimension_type i = num_rows(); i-- > 0; )
    n += rows[i].external_memory_in_bytes(row_capacity);
  return n;
}

bool
PPL::Matrix::OK() const {
  if (row_size > row_capacity) {
#ifndef NDEBUG
    std::cerr << "Matrix completely broken: "
	      << "row_capacity is " << row_capacity
	      << ", row_size is " << row_size
	      << std::endl;
#endif
    return false;
  }

  const Matrix& x = *this;
  for (dimension_type i = 0, n_rows = num_rows(); i < n_rows; ++i)
    if (!x[i].OK(row_size, row_capacity))
      return false;

  // All checks passed.
  return true;
}
