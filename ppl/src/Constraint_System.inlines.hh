/* Constraint_System class implementation: inline functions.
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

#ifndef PPL_Constraint_System_inlines_hh
#define PPL_Constraint_System_inlines_hh 1

#include "Constraint.defs.hh"

namespace Parma_Polyhedra_Library {

inline
Constraint_System::Constraint_System()
  : Linear_System(NECESSARILY_CLOSED) {
}

inline
Constraint_System::Constraint_System(const Constraint& c)
  : Linear_System(c.topology()) {
  Linear_System::insert(c);
}

inline
Constraint_System::Constraint_System(const Constraint_System& cs)
  : Linear_System(cs) {
}

inline
Constraint_System::Constraint_System(const Topology topol)
  : Linear_System(topol) {
}

inline
Constraint_System::Constraint_System(const Topology topol,
				     const dimension_type n_rows,
				     const dimension_type n_columns)
  : Linear_System(topol, n_rows, n_columns) {
}

inline
Constraint_System::~Constraint_System() {
}

inline Constraint_System&
Constraint_System::operator=(const Constraint_System& y) {
  Linear_System::operator=(y);
  return *this;
}

inline Constraint&
Constraint_System::operator[](const dimension_type k) {
  return static_cast<Constraint&>(Linear_System::operator[](k));
}

inline const Constraint&
Constraint_System::operator[](const dimension_type k) const {
  return static_cast<const Constraint&>(Linear_System::operator[](k));
}

inline dimension_type
Constraint_System::max_space_dimension() {
  return Linear_System::max_space_dimension();
}

inline dimension_type
Constraint_System::space_dimension() const {
  return Linear_System::space_dimension();
}

inline void
Constraint_System::clear() {
  Linear_System::clear();
}

inline const Constraint_System&
Constraint_System::zero_dim_empty() {
  PPL_ASSERT(zero_dim_empty_p != 0);
  return *zero_dim_empty_p;
}

inline
Constraint_System::const_iterator::const_iterator()
  : i(), csp(0) {
}

inline
Constraint_System::const_iterator::const_iterator(const const_iterator& y)
  : i(y.i), csp(y.csp) {
}

inline
Constraint_System::const_iterator::~const_iterator() {
}

inline Constraint_System::const_iterator&
Constraint_System::const_iterator::operator=(const const_iterator& y) {
  i = y.i;
  csp = y.csp;
  return *this;
}

inline const Constraint&
Constraint_System::const_iterator::operator*() const {
  return static_cast<const Constraint&>(*i);
}

inline const Constraint*
Constraint_System::const_iterator::operator->() const {
  return static_cast<const Constraint*>(i.operator->());
}

inline Constraint_System::const_iterator&
Constraint_System::const_iterator::operator++() {
  ++i;
  skip_forward();
  return *this;
}

inline Constraint_System::const_iterator
Constraint_System::const_iterator::operator++(int) {
  const const_iterator tmp = *this;
  operator++();
  return tmp;
}

inline bool
Constraint_System::const_iterator::operator==(const const_iterator& y) const {
  return i == y.i;
}

inline bool
Constraint_System::const_iterator::operator!=(const const_iterator& y) const {
  return i != y.i;
}

inline
Constraint_System::const_iterator::
const_iterator(const Linear_System::const_iterator& iter,
	       const Constraint_System& csys)
  : i(iter), csp(&csys) {
}

inline Constraint_System::const_iterator
Constraint_System::begin() const {
  const_iterator i(Linear_System::begin(), *this);
  i.skip_forward();
  return i;
}

inline Constraint_System::const_iterator
Constraint_System::end() const {
  const const_iterator i(Linear_System::end(), *this);
  return i;
}

inline bool
Constraint_System::empty() const {
  return begin() == end();
}

inline void
Constraint_System::add_low_level_constraints() {
  if (is_necessarily_closed())
    // The positivity constraint.
    insert(Constraint::zero_dim_positivity());
  else {
    // Add the epsilon constraints.
    insert(Constraint::epsilon_leq_one());
    insert(Constraint::epsilon_geq_zero());
  }
}

inline void
Constraint_System::swap(Constraint_System& y) {
  Linear_System::swap(y);
}

inline memory_size_type
Constraint_System::external_memory_in_bytes() const {
  return Linear_System::external_memory_in_bytes();
}

inline memory_size_type
Constraint_System::total_memory_in_bytes() const {
  return Linear_System::total_memory_in_bytes();
}

inline void
Constraint_System::simplify() {
  Linear_System::simplify();
}

} // namespace Parma_Polyhedra_Library


namespace std {

/*! \relates Parma_Polyhedra_Library::Constraint_System */
inline void
swap(Parma_Polyhedra_Library::Constraint_System& x,
     Parma_Polyhedra_Library::Constraint_System& y) {
  x.swap(y);
}

} // namespace std

#endif // !defined(PPL_Constraint_System_inlines_hh)
