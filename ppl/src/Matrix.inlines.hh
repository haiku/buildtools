/* Matrix class implementation: inline functions.
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

#ifndef PPL_Matrix_inlines_hh
#define PPL_Matrix_inlines_hh 1

#include "globals.defs.hh"
#include <algorithm>
#include "assert.hh"

namespace Parma_Polyhedra_Library {

inline dimension_type
Matrix::max_num_rows() {
  return std::vector<Row>().max_size();
}

inline dimension_type
Matrix::max_num_columns() {
  return Row::max_size();
}

inline memory_size_type
Matrix::total_memory_in_bytes() const {
  return sizeof(*this) + external_memory_in_bytes();
}

inline
Matrix::const_iterator::const_iterator()
  : i() {
}

inline
Matrix::const_iterator::const_iterator(const Iter& b)
  : i(b) {
}

inline
Matrix::const_iterator::const_iterator(const const_iterator& y)
  : i(y.i) {
}

inline Matrix::const_iterator&
Matrix::const_iterator::operator=(const const_iterator& y) {
  i = y.i;
  return *this;
}

inline Matrix::const_iterator::reference
Matrix::const_iterator::operator*() const {
  return *i;
}

inline Matrix::const_iterator::pointer
Matrix::const_iterator::operator->() const {
  return &*i;
}

inline Matrix::const_iterator&
Matrix::const_iterator::operator++() {
  ++i;
  return *this;
}

inline Matrix::const_iterator
Matrix::const_iterator::operator++(int) {
  return const_iterator(i++);
}

inline bool
Matrix::const_iterator::operator==(const const_iterator& y) const {
  return i == y.i;
}

inline bool
Matrix::const_iterator::operator!=(const const_iterator& y) const {
  return !operator==(y);
}

inline bool
Matrix::has_no_rows() const {
  return rows.empty();
}

inline Matrix::const_iterator
Matrix::begin() const {
  return const_iterator(rows.begin());
}

inline Matrix::const_iterator
Matrix::end() const {
  return const_iterator(rows.end());
}

inline void
Matrix::swap(Matrix& y) {
  std::swap(rows, y.rows);
  std::swap(row_size, y.row_size);
  std::swap(row_capacity, y.row_capacity);
}

inline
Matrix::Matrix()
  : rows(),
    row_size(0),
    row_capacity(0) {
}

inline
Matrix::Matrix(const Matrix& y)
  : rows(y.rows),
    row_size(y.row_size),
    row_capacity(compute_capacity(y.row_size, max_num_columns())) {
}

inline
Matrix::~Matrix() {
}

inline Matrix&
Matrix::operator=(const Matrix& y) {
  // Without the following guard against auto-assignments we would
  // recompute the row capacity based on row size, possibly without
  // actually increasing the capacity of the rows.  This would lead to
  // an inconsistent state.
  if (this != &y) {
    // The following assignment may do nothing on auto-assignments...
    rows = y.rows;
    row_size = y.row_size;
    // ... hence the following assignment must not be done on
    // auto-assignments.
    row_capacity = compute_capacity(y.row_size, max_num_columns());
  }
  return *this;
}

inline void
Matrix::add_row(const Row& y) {
  Row new_row(y, row_capacity);
  add_recycled_row(new_row);
}

inline Row&
Matrix::operator[](const dimension_type k) {
  PPL_ASSERT(k < rows.size());
  return rows[k];
}

inline const Row&
Matrix::operator[](const dimension_type k) const {
  PPL_ASSERT(k < rows.size());
  return rows[k];
}

inline dimension_type
Matrix::num_rows() const {
  return rows.size();
}

inline dimension_type
Matrix::num_columns() const {
  return row_size;
}

/*! \relates Matrix */
inline bool
operator!=(const Matrix& x, const Matrix& y) {
  return !(x == y);
}

inline void
Matrix::erase_to_end(const dimension_type first_to_erase) {
  PPL_ASSERT(first_to_erase <= rows.size());
  if (first_to_erase < rows.size())
    rows.erase(rows.begin() + first_to_erase, rows.end());
}

inline void
Matrix::clear() {
  // Clear `rows' and minimize its capacity.
  std::vector<Row>().swap(rows);
  row_size = 0;
  row_capacity = 0;
}

} // namespace Parma_Polyhedra_Library

namespace std {

/*! \relates Parma_Polyhedra_Library::Matrix */
inline void
swap(Parma_Polyhedra_Library::Matrix& x,
     Parma_Polyhedra_Library::Matrix& y) {
  x.swap(y);
}

} // namespace std

#endif // !defined(PPL_Matrix_inlines_hh)
