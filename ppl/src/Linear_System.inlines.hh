/* Linear_System class implementation: inline functions.
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

#ifndef PPL_Linear_System_inlines_hh
#define PPL_Linear_System_inlines_hh 1

#include "Bit_Row.defs.hh"

namespace Parma_Polyhedra_Library {

inline memory_size_type
Linear_System::external_memory_in_bytes() const {
  return Matrix::external_memory_in_bytes();
}

inline memory_size_type
Linear_System::total_memory_in_bytes() const {
  return sizeof(*this) + external_memory_in_bytes();
}

inline bool
Linear_System::is_sorted() const {
  // The flag `sorted' does not really reflect the sortedness status
  // of a system (if `sorted' evaluates to `false' nothing is known).
  // This assertion is used to ensure that the system
  // is actually sorted when `sorted' value is 'true'.
  PPL_ASSERT(!sorted || check_sorted());
  return sorted;
}

inline void
Linear_System::set_sorted(const bool b) {
  sorted = b;
}

inline
Linear_System::Linear_System(Topology topol)
  : Matrix(),
    row_topology(topol),
    index_first_pending(0),
    sorted(true) {
}

inline
Linear_System::Linear_System(Topology topol,
			     dimension_type n_rows, dimension_type n_columns)
  : Matrix(n_rows, n_columns, Linear_Row::Flags(topol)),
    row_topology(topol),
    index_first_pending(n_rows),
    sorted(true) {
}

inline dimension_type
Linear_System::first_pending_row() const {
  return index_first_pending;
}

inline dimension_type
Linear_System::num_pending_rows() const {
  PPL_ASSERT(num_rows() >= first_pending_row());
  return num_rows() - first_pending_row();
}

inline void
Linear_System::unset_pending_rows() {
  index_first_pending = num_rows();
}

inline void
Linear_System::set_index_first_pending_row(const dimension_type i) {
  index_first_pending = i;
}

inline
Linear_System::Linear_System(const Linear_System& y)
  : Matrix(y),
    row_topology(y.row_topology) {
  unset_pending_rows();
  // Previously pending rows may violate sortedness.
  sorted = (y.num_pending_rows() > 0) ? false : y.sorted;
  PPL_ASSERT(num_pending_rows() == 0);
}

inline
Linear_System::Linear_System(const Linear_System& y, With_Pending)
  : Matrix(y),
    row_topology(y.row_topology),
    index_first_pending(y.index_first_pending),
    sorted(y.sorted) {
}

inline Linear_System&
Linear_System::operator=(const Linear_System& y) {
  Matrix::operator=(y);
  row_topology = y.row_topology;
  unset_pending_rows();
  // Previously pending rows may violate sortedness.
  sorted = (y.num_pending_rows() > 0) ? false : y.sorted;
  PPL_ASSERT(num_pending_rows() == 0);
  return *this;
}

inline void
Linear_System::assign_with_pending(const Linear_System& y) {
  Matrix::operator=(y);
  row_topology = y.row_topology;
  index_first_pending = y.index_first_pending;
  sorted = y.sorted;
}

inline void
Linear_System::swap(Linear_System& y) {
  Matrix::swap(y);
  std::swap(row_topology, y.row_topology);
  std::swap(index_first_pending, y.index_first_pending);
  std::swap(sorted, y.sorted);
}

inline void
Linear_System::clear() {
  // Note: do NOT modify the value of `row_topology'.
  Matrix::clear();
  index_first_pending = 0;
  sorted = true;
}

inline void
Linear_System::resize_no_copy(const dimension_type new_n_rows,
			      const dimension_type new_n_columns) {
  Matrix::resize_no_copy(new_n_rows, new_n_columns,
			 Linear_Row::Flags(row_topology));
  // Even though `*this' may happen to keep its sortedness, we believe
  // that checking such a property is not worth the effort.  In fact,
  // it is very likely that the system will be overwritten as soon as
  // we return.
  set_sorted(false);
}

inline void
Linear_System::set_necessarily_closed() {
  row_topology = NECESSARILY_CLOSED;
  if (!has_no_rows())
    set_rows_topology();
}

inline void
Linear_System::set_not_necessarily_closed() {
  row_topology = NOT_NECESSARILY_CLOSED;
  if (!has_no_rows())
    set_rows_topology();
}

inline bool
Linear_System::is_necessarily_closed() const {
  return row_topology == NECESSARILY_CLOSED;
}

inline Linear_Row&
Linear_System::operator[](const dimension_type k) {
  return static_cast<Linear_Row&>(Matrix::operator[](k));
}

inline const Linear_Row&
Linear_System::operator[](const dimension_type k) const {
  return static_cast<const Linear_Row&>(Matrix::operator[](k));
}

inline Topology
Linear_System::topology() const {
  return row_topology;
}

inline dimension_type
Linear_System::max_space_dimension() {
  // Column zero holds the inhomogeneous term or the divisor.
  // In NNC linear systems, the last column holds the coefficient
  // of the epsilon dimension.
  return max_num_columns() - 2;
}

inline dimension_type
Linear_System::space_dimension() const {
  const dimension_type n_columns = num_columns();
  return (n_columns == 0)
    ? 0
    : n_columns - (is_necessarily_closed() ? 1 : 2);
}

inline void
Linear_System::remove_trailing_columns(const dimension_type n) {
  Matrix::remove_trailing_columns(n);
  // Have to re-normalize the rows of the system,
  // since we removed some coefficients.
  strong_normalize();
}

inline void
Linear_System::permute_columns(const std::vector<dimension_type>& cycles) {
  Matrix::permute_columns(cycles);
  // The rows with permuted columns are still normalized but may
  // be not strongly normalized: sign normalization is necessary.
  sign_normalize();
}

/*! \relates Linear_System */
inline bool
operator!=(const Linear_System& x, const Linear_System& y) {
  return !(x == y);
}

inline bool
Linear_System::Row_Less_Than::operator()(const Row& x, const Row& y) const {
  return compare(static_cast<const Linear_Row&>(x),
		 static_cast<const Linear_Row&>(y)) < 0;
}

} // namespace Parma_Polyhedra_Library

namespace std {

/*! \relates Parma_Polyhedra_Library::Linear_System */
inline void
swap(Parma_Polyhedra_Library::Linear_System& x,
     Parma_Polyhedra_Library::Linear_System& y) {
  x.swap(y);
}

} // namespace std

#endif // !defined(PPL_Linear_System_inlines_hh)
