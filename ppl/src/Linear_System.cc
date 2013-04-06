/* Linear_System class implementation (non-inline functions).
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

#include "Linear_System.defs.hh"
#include "Coefficient.defs.hh"
#include "Row.defs.hh"
#include "Bit_Matrix.defs.hh"
#include "Scalar_Products.defs.hh"
#include <algorithm>
#include <iostream>
#include <string>
#include <deque>

#include "swapping_sort.icc"

namespace PPL = Parma_Polyhedra_Library;

PPL::dimension_type
PPL::Linear_System::num_lines_or_equalities() const {
  PPL_ASSERT(num_pending_rows() == 0);
  const Linear_System& x = *this;
  dimension_type n = 0;
  for (dimension_type i = num_rows(); i-- > 0; )
    if (x[i].is_line_or_equality())
      ++n;
  return n;
}

void
PPL::Linear_System::merge_rows_assign(const Linear_System& y) {
  PPL_ASSERT(row_size >= y.row_size);
  // Both systems have to be sorted and have no pending rows.
  PPL_ASSERT(check_sorted() && y.check_sorted());
  PPL_ASSERT(num_pending_rows() == 0 && y.num_pending_rows() == 0);

  Linear_System& x = *this;

  // A temporary vector of rows...
  std::vector<Row> tmp;
  // ... with enough capacity not to require any reallocations.
  tmp.reserve(compute_capacity(x.num_rows() + y.num_rows(), max_num_rows()));

  dimension_type xi = 0;
  dimension_type x_num_rows = x.num_rows();
  dimension_type yi = 0;
  dimension_type y_num_rows = y.num_rows();

  while (xi < x_num_rows && yi < y_num_rows) {
    const int comp = compare(x[xi], y[yi]);
    if (comp <= 0) {
      // Elements that can be taken from `x' are actually _stolen_ from `x'
      std::swap(x[xi++], *tmp.insert(tmp.end(), Linear_Row()));
      if (comp == 0)
	// A duplicate element.
	++yi;
    }
    else {
      // (comp > 0)
      Linear_Row copy(y[yi++], row_size, row_capacity);
      std::swap(copy, *tmp.insert(tmp.end(), Linear_Row()));
    }
  }
  // Insert what is left.
  if (xi < x_num_rows)
    while (xi < x_num_rows)
      std::swap(x[xi++], *tmp.insert(tmp.end(), Linear_Row()));
  else
    while (yi < y_num_rows) {
      Linear_Row copy(y[yi++], row_size, row_capacity);
      std::swap(copy, *tmp.insert(tmp.end(), Linear_Row()));
    }

  // We get the result vector and let the old one be destroyed.
  std::swap(tmp, rows);
  // There are no pending rows.
  unset_pending_rows();
  PPL_ASSERT(check_sorted());
}

void
PPL::Linear_System::set_rows_topology() {
  Linear_System& x = *this;
  if (is_necessarily_closed())
    for (dimension_type i = num_rows(); i-- > 0; )
      x[i].set_necessarily_closed();
  else
    for (dimension_type i = num_rows(); i-- > 0; )
      x[i].set_not_necessarily_closed();
}

void
PPL::Linear_System::ascii_dump(std::ostream& s) const {
  // Prints the topology, the number of rows, the number of columns
  // and the sorted flag.  The specialized methods provided by
  // Constraint_System and Generator_System take care of properly
  // printing the contents of the system.
  const Linear_System& x = *this;
  dimension_type x_num_rows = x.num_rows();
  dimension_type x_num_columns = x.num_columns();
  s << "topology " << (is_necessarily_closed()
		       ? "NECESSARILY_CLOSED"
		       : "NOT_NECESSARILY_CLOSED")
    << "\n"
    << x_num_rows << " x " << x_num_columns
    << (x.sorted ? "(sorted)" : "(not_sorted)")
    << "\n"
    << "index_first_pending " << x.first_pending_row()
    << "\n";
  for (dimension_type i = 0; i < x_num_rows; ++i)
    x[i].ascii_dump(s);
}

PPL_OUTPUT_DEFINITIONS_ASCII_ONLY(Linear_System)

bool
PPL::Linear_System::ascii_load(std::istream& s) {
  std::string str;
  if (!(s >> str) || str != "topology")
    return false;
  if (!(s >> str))
    return false;
  if (str == "NECESSARILY_CLOSED")
    set_necessarily_closed();
  else {
    if (str != "NOT_NECESSARILY_CLOSED")
      return false;
    set_not_necessarily_closed();
  }

  dimension_type nrows;
  dimension_type ncols;
  if (!(s >> nrows))
    return false;
  if (!(s >> str) || str != "x")
    return false;
  if (!(s >> ncols))
    return false;
  resize_no_copy(nrows, ncols);

  if (!(s >> str) || (str != "(sorted)" && str != "(not_sorted)"))
    return false;
  set_sorted(str == "(sorted)");
  dimension_type index;
  if (!(s >> str) || str != "index_first_pending")
    return false;
  if (!(s >> index))
    return false;
  set_index_first_pending_row(index);

  Linear_System& x = *this;
  for (dimension_type row = 0; row < nrows; ++row)
    if (!x[row].ascii_load(s))
      return false;

  // Check invariants.
  PPL_ASSERT(OK(true));
  return true;
}

void
PPL::Linear_System::insert(const Linear_Row& r) {
  // The added row must be strongly normalized and have the same
  // topology of the system.
  PPL_ASSERT(r.check_strong_normalized());
  PPL_ASSERT(topology() == r.topology());
  // This method is only used when the system has no pending rows.
  PPL_ASSERT(num_pending_rows() == 0);

  const dimension_type old_num_rows = num_rows();
  const dimension_type old_num_columns = num_columns();
  const dimension_type r_size = r.size();

  // Resize the system, if necessary.
  if (r_size > old_num_columns) {
    add_zero_columns(r_size - old_num_columns);
    if (!is_necessarily_closed() && old_num_rows != 0)
      // Move the epsilon coefficients to the last column
      // (note: sorting is preserved).
      swap_columns(old_num_columns - 1, r_size - 1);
    add_row(r);
  }
  else if (r_size < old_num_columns) {
    // Create a resized copy of the row.
    Linear_Row tmp_row(r, old_num_columns, row_capacity);
    // If needed, move the epsilon coefficient to the last position.
    if (!is_necessarily_closed())
      std::swap(tmp_row[r_size - 1], tmp_row[old_num_columns - 1]);
    add_row(tmp_row);
  }
  else
    // Here r_size == old_num_columns.
    add_row(r);

  // The added row was not a pending row.
  PPL_ASSERT(num_pending_rows() == 0);
  // Do not check for strong normalization,
  // because no modification of rows has occurred.
  PPL_ASSERT(OK(false));
}

void
PPL::Linear_System::insert_pending(const Linear_Row& r) {
  // The added row must be strongly normalized and have the same
  // topology of the system.
  PPL_ASSERT(r.check_strong_normalized());
  PPL_ASSERT(topology() == r.topology());

  const dimension_type old_num_rows = num_rows();
  const dimension_type old_num_columns = num_columns();
  const dimension_type r_size = r.size();

  // Resize the system, if necessary.
  if (r_size > old_num_columns) {
    add_zero_columns(r_size - old_num_columns);
    if (!is_necessarily_closed() && old_num_rows != 0)
      // Move the epsilon coefficients to the last column
      // (note: sorting is preserved).
      swap_columns(old_num_columns - 1, r_size - 1);
    add_pending_row(r);
  }
  else if (r_size < old_num_columns)
    if (is_necessarily_closed() || old_num_rows == 0)
      add_pending_row(Linear_Row(r, old_num_columns, row_capacity));
    else {
      // Create a resized copy of the row (and move the epsilon
      // coefficient to its last position).
      Linear_Row tmp_row(r, old_num_columns, row_capacity);
      std::swap(tmp_row[r_size - 1], tmp_row[old_num_columns - 1]);
      add_pending_row(tmp_row);
    }
  else
    // Here r_size == old_num_columns.
    add_pending_row(r);

  // The added row was a pending row.
  PPL_ASSERT(num_pending_rows() > 0);
  // Do not check for strong normalization,
  // because no modification of rows has occurred.
  PPL_ASSERT(OK(false));
}

void
PPL::Linear_System::add_pending_rows(const Linear_System& y) {
  Linear_System& x = *this;
  PPL_ASSERT(x.row_size == y.row_size);

  const dimension_type x_n_rows = x.num_rows();
  const dimension_type y_n_rows = y.num_rows();
  // Grow to the required size without changing sortedness.
  const bool was_sorted = sorted;
  add_zero_rows(y_n_rows, Linear_Row::Flags(row_topology));
  sorted = was_sorted;

  // Copy the rows of `y', forcing size and capacity.
  for (dimension_type i = y_n_rows; i-- > 0; ) {
    Row copy(y[i], x.row_size, x.row_capacity);
    std::swap(copy, x[x_n_rows+i]);
  }
  // Do not check for strong normalization,
  // because no modification of rows has occurred.
  PPL_ASSERT(OK(false));
}

void
PPL::Linear_System::add_rows(const Linear_System& y) {
  PPL_ASSERT(num_pending_rows() == 0);

  // Adding no rows is a no-op.
  if (y.has_no_rows())
    return;

  // Check if sortedness is preserved.
  if (is_sorted()) {
    if (!y.is_sorted() || y.num_pending_rows() > 0)
      set_sorted(false);
    else {
      // `y' is sorted and has no pending rows.
      const dimension_type n_rows = num_rows();
      if (n_rows > 0)
	set_sorted(compare((*this)[n_rows-1], y[0]) <= 0);
    }
  }

  // Add the rows of `y' as if they were pending.
  add_pending_rows(y);
  // There are no pending_rows.
  unset_pending_rows();

  // Do not check for strong normalization,
  // because no modification of rows has occurred.
  PPL_ASSERT(OK(false));
}

void
PPL::Linear_System::sort_rows() {
  const dimension_type num_pending = num_pending_rows();
  // We sort the non-pending rows only.
  sort_rows(0, first_pending_row());
  set_index_first_pending_row(num_rows() - num_pending);
  sorted = true;
  // Do not check for strong normalization,
  // because no modification of rows has occurred.
  PPL_ASSERT(OK(false));
}

void
PPL::Linear_System::sort_rows(const dimension_type first_row,
			      const dimension_type last_row) {
  PPL_ASSERT(first_row <= last_row && last_row <= num_rows());
  // We cannot mix pending and non-pending rows.
  PPL_ASSERT(first_row >= first_pending_row()
             || last_row <= first_pending_row());

  const dimension_type num_elems = last_row - first_row;
  if (num_elems < 2)
    return;

  // Build the function objects implementing indirect sort comparison,
  // indirect unique comparison and indirect swap operation.
  typedef std::vector<Row> Cont;
  Indirect_Sort_Compare<Cont, Row_Less_Than> sort_cmp(rows, first_row);
  Indirect_Unique_Compare<Cont> unique_cmp(rows, first_row);
  Indirect_Swapper<Cont> swapper(rows, first_row);

  const dimension_type num_duplicates
    = indirect_sort_and_unique(num_elems, sort_cmp, unique_cmp, swapper);

  if (num_duplicates > 0)
    rows.erase(rows.begin() + (last_row - num_duplicates),
               rows.begin() + last_row);

  // NOTE: we cannot check all invariants of the system here,
  // because the caller still has to update `index_first_pending'.
}

void
PPL::Linear_System::add_row(const Linear_Row& r) {
  // The added row must be strongly normalized and have the same
  // number of elements as the existing rows of the system.
  PPL_ASSERT(r.check_strong_normalized());
  PPL_ASSERT(r.size() == row_size);
  // This method is only used when the system has no pending rows.
  PPL_ASSERT(num_pending_rows() == 0);

  const bool was_sorted = is_sorted();

  Matrix::add_row(r);

  //  We update `index_first_pending', because it must be equal to
  // `num_rows()'.
  set_index_first_pending_row(num_rows());

  if (was_sorted) {
    const dimension_type nrows = num_rows();
    // The added row may have caused the system to be not sorted anymore.
    if (nrows > 1) {
      // If the system is not empty and the inserted row is the
      // greatest one, the system is set to be sorted.
      // If it is not the greatest one then the system is no longer sorted.
      Linear_System& x = *this;
      set_sorted(compare(x[nrows-2], x[nrows-1]) <= 0);
    }
    else
      // A system having only one row is sorted.
      set_sorted(true);
  }
  // The added row was not a pending row.
  PPL_ASSERT(num_pending_rows() == 0);
  // Do not check for strong normalization, because no modification of
  // rows has occurred.
  PPL_ASSERT(OK(false));
}

void
PPL::Linear_System::add_pending_row(const Linear_Row& r) {
  // The added row must be strongly normalized and have the same
  // number of elements of the existing rows of the system.
  PPL_ASSERT(r.check_strong_normalized());
  PPL_ASSERT(r.size() == row_size);

  const dimension_type new_rows_size = rows.size() + 1;
  if (rows.capacity() < new_rows_size) {
    // Reallocation will take place.
    std::vector<Row> new_rows;
    new_rows.reserve(compute_capacity(new_rows_size, max_num_rows()));
    new_rows.insert(new_rows.end(), new_rows_size, Row());
    // Put the new row in place.
    Row new_row(r, row_capacity);
    dimension_type i = new_rows_size-1;
    std::swap(new_rows[i], new_row);
    // Steal the old rows.
    while (i-- > 0)
      new_rows[i].swap(rows[i]);
    // Put the new rows into place.
    std::swap(rows, new_rows);
  }
  else {
    // Reallocation will NOT take place.
    // Inserts a new empty row at the end, then substitutes it with a
    // copy of the given row.
    Row tmp(r, row_capacity);
    std::swap(*rows.insert(rows.end(), Row()), tmp);
  }

  // The added row was a pending row.
  PPL_ASSERT(num_pending_rows() > 0);
  // Do not check for strong normalization, because no modification of
  // rows has occurred.
  PPL_ASSERT(OK(false));
}

void
PPL::Linear_System::add_pending_row(const Linear_Row::Flags flags) {
  const dimension_type new_rows_size = rows.size() + 1;
  if (rows.capacity() < new_rows_size) {
    // Reallocation will take place.
    std::vector<Row> new_rows;
    new_rows.reserve(compute_capacity(new_rows_size, max_num_rows()));
    new_rows.insert(new_rows.end(), new_rows_size, Row());
    // Put the new row in place.
    Linear_Row new_row(row_size, row_capacity, flags);
    dimension_type i = new_rows_size-1;
    std::swap(new_rows[i], new_row);
    // Steal the old rows.
    while (i-- > 0)
      new_rows[i].swap(rows[i]);
    // Put the new vector into place.
    std::swap(rows, new_rows);
  }
  else {
    // Reallocation will NOT take place.
    // Insert a new empty row at the end, then construct it assigning
    // it the given type.
    Row& new_row = *rows.insert(rows.end(), Row());
    static_cast<Linear_Row&>(new_row).construct(row_size, row_capacity, flags);
  }

  // The added row was a pending row.
  PPL_ASSERT(num_pending_rows() > 0);
}

void
PPL::Linear_System::normalize() {
  Linear_System& x = *this;
  const dimension_type nrows = x.num_rows();
  // We normalize also the pending rows.
  for (dimension_type i = nrows; i-- > 0; )
    x[i].normalize();
  set_sorted(nrows <= 1);
}

void
PPL::Linear_System::strong_normalize() {
  Linear_System& x = *this;
  const dimension_type nrows = x.num_rows();
  // We strongly normalize also the pending rows.
  for (dimension_type i = nrows; i-- > 0; )
    x[i].strong_normalize();
  set_sorted(nrows <= 1);
}

void
PPL::Linear_System::sign_normalize() {
  Linear_System& x = *this;
  const dimension_type nrows = x.num_rows();
  // We sign-normalize also the pending rows.
  for (dimension_type i = num_rows(); i-- > 0; )
    x[i].sign_normalize();
  set_sorted(nrows <= 1);
}

/*! \relates Parma_Polyhedra_Library::Linear_System */
bool
PPL::operator==(const Linear_System& x, const Linear_System& y) {
  if (x.num_columns() != y.num_columns())
    return false;
  const dimension_type x_num_rows = x.num_rows();
  const dimension_type y_num_rows = y.num_rows();
  if (x_num_rows != y_num_rows)
    return false;
  if (x.first_pending_row() != y.first_pending_row())
    return false;
  // Notice that calling operator==(const Matrix&, const Matrix&)
  // would be wrong here, as equality of the type fields would
  // not be checked.
  for (dimension_type i = x_num_rows; i-- > 0; )
    if (x[i] != y[i])
      return false;
  return true;
}

void
PPL::Linear_System::sort_and_remove_with_sat(Bit_Matrix& sat) {
  Linear_System& sys = *this;
  // We can only sort the non-pending part of the system.
  PPL_ASSERT(sys.first_pending_row() == sat.num_rows());
  if (sys.first_pending_row() <= 1) {
    sys.set_sorted(true);
    return;
  }

  const dimension_type num_elems = sat.num_rows();
  // Build the function objects implementing indirect sort comparison,
  // indirect unique comparison and indirect swap operation.
  typedef std::vector<Row> Cont;
  Indirect_Sort_Compare<Cont, Row_Less_Than> sort_cmp(rows);
  Indirect_Unique_Compare<Cont> unique_cmp(rows);
  Indirect_Swapper2<Cont, Bit_Matrix> swapper(rows, sat);

  const dimension_type num_duplicates
    = indirect_sort_and_unique(num_elems, sort_cmp, unique_cmp, swapper);

  const dimension_type new_first_pending_row
    = sys.first_pending_row() - num_duplicates;

  if (sys.num_pending_rows() > 0) {
    // In this case, we must put the duplicates after the pending rows.
    const dimension_type n_rows = sys.num_rows() - 1;
    for (dimension_type i = 0; i < num_duplicates; ++i)
      std::swap(sys[new_first_pending_row + i], sys[n_rows - i]);
  }
  // Erasing the duplicated rows...
  sys.erase_to_end(sys.num_rows() - num_duplicates);
  sys.set_index_first_pending_row(new_first_pending_row);
  // ... and the corresponding rows of the saturation matrix.
  sat.rows_erase_to_end(num_elems - num_duplicates);
  PPL_ASSERT(sys.check_sorted());
  // Now the system is sorted.
  sys.set_sorted(true);
}

PPL::dimension_type
PPL::Linear_System::gauss(const dimension_type n_lines_or_equalities) {
  Linear_System& x = *this;
  // This method is only applied to a well-formed linear system
  // having no pending rows and exactly `n_lines_or_equalities'
  // lines or equalities, all of which occur before the rays or points
  // or inequalities.
  PPL_ASSERT(x.OK(true));
  PPL_ASSERT(x.num_pending_rows() == 0);
  PPL_ASSERT(n_lines_or_equalities == x.num_lines_or_equalities());
#ifndef NDEBUG
  for (dimension_type i = n_lines_or_equalities; i-- > 0; )
    PPL_ASSERT(x[i].is_line_or_equality());
#endif

  dimension_type rank = 0;
  // Will keep track of the variations on the system of equalities.
  bool changed = false;
  for (dimension_type j = x.num_columns(); j-- > 0; )
    for (dimension_type i = rank; i < n_lines_or_equalities; ++i) {
      // Search for the first row having a non-zero coefficient
      // (the pivot) in the j-th column.
      if (x[i][j] == 0)
	continue;
      // Pivot found: if needed, swap rows so that this one becomes
      // the rank-th row in the linear system.
      if (i > rank) {
	std::swap(x[i], x[rank]);
	// After swapping the system is no longer sorted.
	changed = true;
      }
      // Combine the row containing the pivot with all the lines or
      // equalities following it, so that all the elements on the j-th
      // column in these rows become 0.
      for (dimension_type k = i + 1; k < n_lines_or_equalities; ++k)
	if (x[k][j] != 0) {
	  x[k].linear_combine(x[rank], j);
	  changed = true;
	}
      // Already dealt with the rank-th row.
      ++rank;
      // Consider another column index `j'.
      break;
    }
  if (changed)
    x.set_sorted(false);
  // A well-formed system is returned.
  PPL_ASSERT(x.OK(true));
  return rank;
}

void
PPL::Linear_System
::back_substitute(const dimension_type n_lines_or_equalities) {
  Linear_System& x = *this;
  // This method is only applied to a well-formed system
  // having no pending rows and exactly `n_lines_or_equalities'
  // lines or equalities, all of which occur before the first ray
  // or point or inequality.
  PPL_ASSERT(x.OK(true));
  PPL_ASSERT(x.num_columns() >= 1);
  PPL_ASSERT(x.num_pending_rows() == 0);
  PPL_ASSERT(n_lines_or_equalities <= x.num_lines_or_equalities());
#ifndef NDEBUG
  for (dimension_type i = n_lines_or_equalities; i-- > 0; )
    PPL_ASSERT(x[i].is_line_or_equality());
#endif

  const dimension_type nrows = x.num_rows();
  const dimension_type ncols = x.num_columns();
  // Trying to keep sortedness.
  bool still_sorted = x.is_sorted();
  // This deque of Booleans will be used to flag those rows that,
  // before exiting, need to be re-checked for sortedness.
  std::deque<bool> check_for_sortedness;
  if (still_sorted)
    check_for_sortedness.insert(check_for_sortedness.end(), nrows, false);

  for (dimension_type k = n_lines_or_equalities; k-- > 0; ) {
    // For each line or equality, starting from the last one,
    // looks for the last non-zero element.
    // `j' will be the index of such a element.
    Linear_Row& x_k = x[k];
    dimension_type j = ncols - 1;
    while (j != 0 && x_k[j] == 0)
      --j;

    // Go through the equalities above `x_k'.
    for (dimension_type i = k; i-- > 0; ) {
      Linear_Row& x_i = x[i];
      if (x_i[j] != 0) {
	// Combine linearly `x_i' with `x_k'
	// so that `x_i[j]' becomes zero.
	x_i.linear_combine(x_k, j);
	if (still_sorted) {
	  // Trying to keep sortedness: remember which rows
	  // have to be re-checked for sortedness at the end.
	  if (i > 0)
	    check_for_sortedness[i-1] = true;
	  check_for_sortedness[i] = true;
	}
      }
    }

    // Due to strong normalization during previous iterations,
    // the pivot coefficient `x_k[j]' may now be negative.
    // Since an inequality (or ray or point) cannot be multiplied
    // by a negative factor, the coefficient of the pivot must be
    // forced to be positive.
    const bool have_to_negate = (x_k[j] < 0);
    if (have_to_negate)
      for (dimension_type h = ncols; h-- > 0; )
	PPL::neg_assign(x_k[h]);
    // Note: we do not mark index `k' in `check_for_sortedness',
    // because we will later negate back the row.

    // Go through all the other rows of the system.
    for (dimension_type i = n_lines_or_equalities; i < nrows; ++i) {
      Linear_Row& x_i = x[i];
      if (x_i[j] != 0) {
	// Combine linearly the `x_i' with `x_k'
	// so that `x_i[j]' becomes zero.
	x_i.linear_combine(x_k, j);
	if (still_sorted) {
	  // Trying to keep sortedness: remember which rows
	  // have to be re-checked for sortedness at the end.
	  if (i > n_lines_or_equalities)
	    check_for_sortedness[i-1] = true;
	  check_for_sortedness[i] = true;
	}
      }
    }
    if (have_to_negate)
      // Negate `x_k' to restore strong-normalization.
      for (dimension_type h = ncols; h-- > 0; )
	PPL::neg_assign(x_k[h]);
  }

  // Trying to keep sortedness.
  for (dimension_type i = 0; still_sorted && i+1 < nrows; ++i)
    if (check_for_sortedness[i])
      // Have to check sortedness of `x[i]' with respect to `x[i+1]'.
      still_sorted = (compare(x[i], x[i+1]) <= 0);
  // Set the sortedness flag.
  x.set_sorted(still_sorted);

  // A well-formed system is returned.
  PPL_ASSERT(x.OK(true));
}

void
PPL::Linear_System::simplify() {
  Linear_System& x = *this;
  // This method is only applied to a well-formed system
  // having no pending rows.
  PPL_ASSERT(x.OK(true));
  PPL_ASSERT(x.num_pending_rows() == 0);

  // Partially sort the linear system so that all lines/equalities come first.
  dimension_type nrows = x.num_rows();
  dimension_type n_lines_or_equalities = 0;
  for (dimension_type i = 0; i < nrows; ++i)
    if (x[i].is_line_or_equality()) {
      if (n_lines_or_equalities < i) {
	std::swap(x[i], x[n_lines_or_equalities]);
	// The system was not sorted.
	PPL_ASSERT(!x.sorted);
      }
      ++n_lines_or_equalities;
    }
  // Apply Gaussian elimination to the subsystem of lines/equalities.
  const dimension_type rank = x.gauss(n_lines_or_equalities);
  // Eliminate any redundant line/equality that has been detected.
  if (rank < n_lines_or_equalities) {
    const dimension_type
      n_rays_or_points_or_inequalities = nrows - n_lines_or_equalities;
    const dimension_type
      num_swaps = std::min(n_lines_or_equalities - rank,
			   n_rays_or_points_or_inequalities);
    for (dimension_type i = num_swaps; i-- > 0; )
      std::swap(x[--nrows], x[rank + i]);
    x.erase_to_end(nrows);
    x.unset_pending_rows();
    if (n_rays_or_points_or_inequalities > num_swaps)
      x.set_sorted(false);
    n_lines_or_equalities = rank;
  }
  // Apply back-substitution to the system of rays/points/inequalities.
  x.back_substitute(n_lines_or_equalities);
  // A well-formed system is returned.
  PPL_ASSERT(x.OK(true));
}

void
PPL::Linear_System::add_rows_and_columns(const dimension_type n) {
  PPL_ASSERT(n > 0);
  const bool was_sorted = is_sorted();
  const dimension_type old_n_rows = num_rows();
  const dimension_type old_n_columns = num_columns();
  add_zero_rows_and_columns(n, n, Linear_Row::Flags(row_topology));
  Linear_System& x = *this;
  // The old system is moved to the bottom.
  for (dimension_type i = old_n_rows; i-- > 0; )
    std::swap(x[i], x[i + n]);
  for (dimension_type i = n, c = old_n_columns; i-- > 0; ) {
    // The top right-hand sub-system (i.e., the system made of new
    // rows and columns) is set to the specular image of the identity
    // matrix.
    Linear_Row& r = x[i];
    r[c++] = 1;
    r.set_is_line_or_equality();
    // Note: `r' is strongly normalized.
  }
  // If the old system was empty, the last row added is either
  // a positivity constraint or a point.
  if (old_n_columns == 0) {
    x[n-1].set_is_ray_or_point_or_inequality();
    // Since ray, points and inequalities come after lines
    // and equalities, this case implies the system is sorted.
    set_sorted(true);
  }
  else if (was_sorted)
    set_sorted(compare(x[n-1], x[n]) <= 0);

  // A well-formed system has to be returned.
  PPL_ASSERT(OK(true));
}

void
PPL::Linear_System::sort_pending_and_remove_duplicates() {
  PPL_ASSERT(num_pending_rows() > 0);
  PPL_ASSERT(is_sorted());
  Linear_System& x = *this;

  // The non-pending part of the system is already sorted.
  // Now sorting the pending part..
  const dimension_type first_pending = x.first_pending_row();
  x.sort_rows(first_pending, x.num_rows());
  // Recompute the number of rows, because we may have removed
  // some rows occurring more than once in the pending part.
  dimension_type num_rows = x.num_rows();

  dimension_type k1 = 0;
  dimension_type k2 = first_pending;
  dimension_type num_duplicates = 0;
  // In order to erase them, put at the end of the system
  // those pending rows that also occur in the non-pending part.
  while (k1 < first_pending && k2 < num_rows) {
    const int cmp = compare(x[k1], x[k2]);
    if (cmp == 0) {
      // We found the same row.
      ++num_duplicates;
      --num_rows;
      // By initial sortedness, we can increment index `k1'.
      ++k1;
      // Do not increment `k2'; instead, swap there the next pending row.
      if (k2 < num_rows)
	std::swap(x[k2], x[k2 + num_duplicates]);
    }
    else if (cmp < 0)
      // By initial sortedness, we can increment `k1'.
      ++k1;
    else {
      // Here `cmp > 0'.
      // Increment `k2' and, if we already found any duplicate,
      // swap the next pending row in position `k2'.
      ++k2;
      if (num_duplicates > 0 && k2 < num_rows)
	std::swap(x[k2], x[k2 + num_duplicates]);
    }
  }
  // If needed, swap any duplicates found past the pending rows
  // that has not been considered yet; then erase the duplicates.
  if (num_duplicates > 0) {
    if (k2 < num_rows)
      for (++k2; k2 < num_rows; ++k2)
	std::swap(x[k2], x[k2 + num_duplicates]);
    x.erase_to_end(num_rows);
  }
  // Do not check for strong normalization,
  // because no modification of rows has occurred.
  PPL_ASSERT(OK(false));
}

bool
PPL::Linear_System::check_sorted() const {
  const Linear_System& x = *this;
  for (dimension_type i = first_pending_row(); i-- > 1; )
    if (compare(x[i], x[i-1]) < 0)
      return false;
  return true;
}

bool
PPL::Linear_System::OK(const bool check_strong_normalized) const {
#ifndef NDEBUG
  using std::endl;
  using std::cerr;
#endif

  // `index_first_pending' must be less than or equal to `num_rows()'.
  if (first_pending_row() > num_rows()) {
#ifndef NDEBUG
    cerr << "Linear_System has a negative number of pending rows!"
	 << endl;
#endif
    return false;
  }

  // An empty system is OK,
  // unless it is an NNC system with exactly one column.
  if (has_no_rows()) {
    if (is_necessarily_closed() || num_columns() != 1)
      return true;
    else {
#ifndef NDEBUG
      cerr << "NNC Linear_System has one column" << endl;
#endif
      return false;
    }
  }

  // A non-empty system will contain constraints or generators; in
  // both cases it must have at least one column for the inhomogeneous
  // term and, if it is NNC, another one for the epsilon coefficient.
  const dimension_type min_cols = is_necessarily_closed() ? 1 : 2;
  if (num_columns() < min_cols) {
#ifndef NDEBUG
    cerr << "Linear_System has fewer columns than the minimum "
	 << "allowed by its topology:"
	 << endl
	 << "num_columns is " << num_columns()
	 << ", minimum is " << min_cols
	 << endl;
#endif
    return false;
  }

  const Linear_System& x = *this;
  const dimension_type n_rows = num_rows();
  for (dimension_type i = 0; i < n_rows; ++i) {
    if (!x[i].OK(row_size, row_capacity))
      return false;
    // Checking for topology mismatches.
    if (x.topology() != x[i].topology()) {
#ifndef NDEBUG
      cerr << "Topology mismatch between the system "
	   << "and one of its rows!"
	   << endl;
#endif
      return false;
    }
  }

  if (check_strong_normalized) {
    // Check for strong normalization of rows.
    // Note: normalization cannot be checked inside the
    // Linear_Row::OK() method, because a Linear_Row object may also
    // implement a Linear_Expression object, which in general cannot
    // be (strongly) normalized.
    Linear_System tmp(x, With_Pending());
    tmp.strong_normalize();
    if (x != tmp) {
#ifndef NDEBUG
      cerr << "Linear_System rows are not strongly normalized!"
	   << endl;
#endif
      return false;
    }
  }

  if (sorted && !check_sorted()) {
#ifndef NDEBUG
    cerr << "The system declares itself to be sorted but it is not!"
	 << endl;
#endif
    return false;
  }

  // All checks passed.
  return true;
}
