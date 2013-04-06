/* Generator_System class implementation: inline functions.
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

#ifndef PPL_Generator_System_inlines_hh
#define PPL_Generator_System_inlines_hh 1

#include "Generator.defs.hh"

namespace Parma_Polyhedra_Library {

inline
Generator_System::Generator_System()
  : Linear_System(NECESSARILY_CLOSED) {
}

inline
Generator_System::Generator_System(const Generator& g)
  : Linear_System(g.topology()) {
  Linear_System::insert(g);
}

inline
Generator_System::Generator_System(const Generator_System& gs)
  : Linear_System(gs) {
}

inline
Generator_System::Generator_System(const Topology topol)
  : Linear_System(topol) {
}

inline
Generator_System::Generator_System(const Topology topol,
				   const dimension_type n_rows,
				   const dimension_type n_columns)
  : Linear_System(topol, n_rows, n_columns) {
}

inline
Generator_System::~Generator_System() {
}

inline Generator_System&
Generator_System::operator=(const Generator_System& y) {
  Linear_System::operator=(y);
  return *this;
}

inline dimension_type
Generator_System::max_space_dimension() {
  return Linear_System::max_space_dimension();
}

inline dimension_type
Generator_System::space_dimension() const {
  return Linear_System::space_dimension();
}

inline void
Generator_System::clear() {
  Linear_System::clear();
}

inline Generator&
Generator_System::operator[](const dimension_type k) {
  return static_cast<Generator&>(Linear_System::operator[](k));
}

inline const Generator&
Generator_System::operator[](const dimension_type k) const {
  return static_cast<const Generator&>(Linear_System::operator[](k));
}

inline
Generator_System::const_iterator::const_iterator()
  : i(), gsp(0) {
}

inline
Generator_System::const_iterator::const_iterator(const const_iterator& y)
  : i(y.i), gsp(y.gsp) {
}

inline
Generator_System::const_iterator::~const_iterator() {
}

inline
Generator_System::const_iterator&
Generator_System::const_iterator::operator=(const const_iterator& y) {
  i = y.i;
  gsp = y.gsp;
  return *this;
}

inline const Generator&
Generator_System::const_iterator::operator*() const {
  return static_cast<const Generator&>(*i);
}

inline const Generator*
Generator_System::const_iterator::operator->() const {
  return static_cast<const Generator*>(i.operator->());
}

inline Generator_System::const_iterator&
Generator_System::const_iterator::operator++() {
  ++i;
  if (!gsp->is_necessarily_closed())
    skip_forward();
  return *this;
}

inline Generator_System::const_iterator
Generator_System::const_iterator::operator++(int) {
  const const_iterator tmp = *this;
  operator++();
  return tmp;
}

inline bool
Generator_System::const_iterator::operator==(const const_iterator& y) const {
  return i == y.i;
}

inline bool
Generator_System::const_iterator::operator!=(const const_iterator& y) const {
  return i != y.i;
}

inline
Generator_System::const_iterator::
const_iterator(const Linear_System::const_iterator& iter,
	       const Generator_System& gsys)
  : i(iter), gsp(&gsys) {
}

inline bool
Generator_System::empty() const {
  return Linear_System::has_no_rows();
}

inline Generator_System::const_iterator
Generator_System::begin() const {
  const_iterator i(Linear_System::begin(), *this);
  if (!is_necessarily_closed())
    i.skip_forward();
  return i;
}

inline Generator_System::const_iterator
Generator_System::end() const {
  const const_iterator i(Linear_System::end(), *this);
  return i;
}

inline const Generator_System&
Generator_System::zero_dim_univ() {
  PPL_ASSERT(zero_dim_univ_p != 0);
  return *zero_dim_univ_p;
}

inline void
Generator_System::swap(Generator_System& y) {
  Linear_System::swap(y);
}

inline memory_size_type
Generator_System::external_memory_in_bytes() const {
  return Linear_System::external_memory_in_bytes();
}

inline memory_size_type
Generator_System::total_memory_in_bytes() const {
  return Linear_System::total_memory_in_bytes();
}

inline void
Generator_System::simplify() {
  Linear_System::simplify();
  remove_invalid_lines_and_rays();
}

} // namespace Parma_Polyhedra_Library


namespace std {

/*! \relates Parma_Polyhedra_Library::Constraint_System */
inline void
swap(Parma_Polyhedra_Library::Generator_System& x,
     Parma_Polyhedra_Library::Generator_System& y) {
  x.swap(y);
}

} // namespace std

#endif // !defined(PPL_Generator_System_inlines_hh)
