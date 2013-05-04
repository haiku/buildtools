/* Congruence_System class implementation: inline functions.
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

#ifndef PPL_Congruence_System_inlines_hh
#define PPL_Congruence_System_inlines_hh 1

#include "Congruence.defs.hh"

namespace Parma_Polyhedra_Library {

inline Congruence&
Congruence_System::operator[](const dimension_type k) {
  return static_cast<Congruence&>(Matrix::operator[](k));
}

inline const Congruence&
Congruence_System::operator[](const dimension_type k) const {
  return static_cast<const Congruence&>(Matrix::operator[](k));
}

inline void
Congruence_System::insert(const Congruence& cg) {
  insert_verbatim(cg);
  static_cast<Congruence&>(operator[](rows.size()-1)).strong_normalize();
  PPL_ASSERT(OK());
}

inline
Congruence_System::Congruence_System()
  : Matrix(0, 2) {
}

inline
Congruence_System::Congruence_System(const Congruence& cg)
  : Matrix(0, 2) {
  insert(cg);
}

inline
Congruence_System::Congruence_System(const Constraint& c)
  : Matrix(0, 2) {
  insert(c);
}

inline
Congruence_System::Congruence_System(const Congruence_System& cs)
  : Matrix(cs) {
}

inline
Congruence_System::Congruence_System(const dimension_type d)
  : Matrix(0, d + 2) {
}

inline
Congruence_System::~Congruence_System() {
}

inline Congruence_System&
Congruence_System::operator=(const Congruence_System& y) {
  Matrix::operator=(y);
  return *this;
}

inline dimension_type
Congruence_System::max_space_dimension() {
  return Matrix::max_num_columns() - 2;
}

inline dimension_type
Congruence_System::space_dimension() const {
  return Matrix::num_columns() - 2;
}

inline void
Congruence_System::clear() {
  Matrix::clear();
  add_zero_columns(2);		// Modulus and constant term.
}

inline void
Congruence_System::resize_no_copy(const dimension_type new_num_rows,
				  const dimension_type new_num_columns) {
  Matrix::resize_no_copy(new_num_rows, new_num_columns, Row::Flags());
}

inline const Congruence_System&
Congruence_System::zero_dim_empty() {
  PPL_ASSERT(zero_dim_empty_p != 0);
  return *zero_dim_empty_p;
}

inline
Congruence_System::const_iterator::const_iterator()
  : i(), csp(0) {
}

inline
Congruence_System::const_iterator::const_iterator(const const_iterator& y)
  : i(y.i), csp(y.csp) {
}

inline
Congruence_System::const_iterator::~const_iterator() {
}

inline Congruence_System::const_iterator&
Congruence_System::const_iterator::operator=(const const_iterator& y) {
  i = y.i;
  csp = y.csp;
  return *this;
}

inline const Congruence&
Congruence_System::const_iterator::operator*() const {
  return static_cast<const Congruence&>(*i);
}

inline const Congruence*
Congruence_System::const_iterator::operator->() const {
  return static_cast<const Congruence*>(i.operator->());
}

inline Congruence_System::const_iterator&
Congruence_System::const_iterator::operator++() {
  ++i;
  skip_forward();
  return *this;
}

inline Congruence_System::const_iterator
Congruence_System::const_iterator::operator++(int) {
  const const_iterator tmp = *this;
  operator++();
  return tmp;
}

inline bool
Congruence_System::const_iterator::operator==(const const_iterator& y) const {
  return i == y.i;
}

inline bool
Congruence_System::const_iterator::operator!=(const const_iterator& y) const {
  return i != y.i;
}

inline
Congruence_System::const_iterator::
const_iterator(const Matrix::const_iterator& iter,
	       const Congruence_System& csys)
  : i(iter), csp(&csys) {
}

inline Congruence_System::const_iterator
Congruence_System::begin() const {
  const_iterator i(Matrix::begin(), *this);
  i.skip_forward();
  return i;
}

inline Congruence_System::const_iterator
Congruence_System::end() const {
  const const_iterator i(Matrix::end(), *this);
  return i;
}

inline bool
Congruence_System::empty() const {
  return begin() == end();
}

inline void
Congruence_System::swap(Congruence_System& y) {
  Matrix::swap(y);
}

inline memory_size_type
Congruence_System::external_memory_in_bytes() const {
  return Matrix::external_memory_in_bytes();
}

inline memory_size_type
Congruence_System::total_memory_in_bytes() const {
  return Matrix::total_memory_in_bytes();
}

} // namespace Parma_Polyhedra_Library


namespace std {

/*! \relates Parma_Polyhedra_Library::Congruence_System */
inline void
swap(Parma_Polyhedra_Library::Congruence_System& x,
     Parma_Polyhedra_Library::Congruence_System& y) {
  x.swap(y);
}

} // namespace std

#endif // !defined(PPL_Congruence_System_inlines_hh)
