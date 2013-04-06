/* Congruence class implementation: inline functions.
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

#ifndef PPL_Congruence_inlines_hh
#define PPL_Congruence_inlines_hh 1

#include "Linear_Expression.defs.hh"
#include "Constraint.defs.hh"

#include <sstream>

namespace Parma_Polyhedra_Library {

inline
Congruence::Congruence(const Congruence& cg)
  : Row(cg) {
}

inline
Congruence::Congruence(const Congruence& cg,
		       dimension_type sz, dimension_type capacity)
  : Row(cg, sz, capacity) {
}

inline
Congruence::Congruence(const Congruence& cg,
		       Coefficient_traits::const_reference k)
  : Row(cg) {
  if (k >= 0)
    (*this)[size()-1] *= k;
  else
    (*this)[size()-1] *= -k;
}

inline
Congruence::~Congruence() {
}

inline
Congruence::Congruence(Linear_Expression& le,
		       Coefficient_traits::const_reference m) {
  Row::swap(static_cast<Row&>(le));
  PPL_ASSERT(m >= 0);
  (*this)[size()-1] = m;
}

inline Congruence
Congruence::create(const Linear_Expression& e,
		   Coefficient_traits::const_reference n) {
  // Ensure that diff has capacity for the modulus.
  Linear_Expression diff(e, e.space_dimension() + 2);
  diff -= n;
  Congruence cg(diff, 1);
  return cg;
}

inline Congruence
Congruence::create(Coefficient_traits::const_reference n,
		   const Linear_Expression& e) {
  // Ensure that diff has capacity for the modulus.
  Linear_Expression diff(e, e.space_dimension() + 2);
  diff -= n;
  Congruence cg(diff, 1);
  return cg;
}

/*! \relates Parma_Polyhedra_Library::Congruence */
inline Congruence
operator%=(const Linear_Expression& e1, const Linear_Expression& e2) {
  return Congruence::create(e1, e2);
}

/*! \relates Parma_Polyhedra_Library::Congruence */
inline Congruence
operator%=(const Linear_Expression& e, Coefficient_traits::const_reference n) {
  return Congruence::create(e, n);
}

/*! \relates Parma_Polyhedra_Library::Congruence */
inline Congruence
operator/(const Congruence& cg, Coefficient_traits::const_reference k) {
  Congruence ret(cg, k);
  return ret;
}

inline const Congruence&
Congruence::zero_dim_integrality() {
  return *zero_dim_integrality_p;
}

inline const Congruence&
Congruence::zero_dim_false() {
  return *zero_dim_false_p;
}

inline Congruence&
Congruence::operator=(const Congruence& c) {
  Row::operator=(c);
  return *this;
}

/*! \relates Congruence */
inline Congruence
operator/(const Constraint& c, Coefficient_traits::const_reference m) {
  Congruence ret(c);
  return ret / m;
}

inline Congruence&
Congruence::operator/=(Coefficient_traits::const_reference k) {
  if (k >= 0)
    (*this)[size()-1] *= k;
  else
    (*this)[size()-1] *= -k;
  return *this;
}

/*! \relates Congruence */
inline bool
operator==(const Congruence& x, const Congruence& y) {
  Congruence x_temp(x);
  Congruence y_temp(y);
  x_temp.strong_normalize();
  y_temp.strong_normalize();
  return static_cast<const Row&>(x_temp) == static_cast<const Row&>(y_temp);
}

/*! \relates Congruence */
inline bool
operator!=(const Congruence& x, const Congruence& y) {
  return !(x == y);
}

inline dimension_type
Congruence::max_space_dimension() {
  // The first coefficient holds the inhomogeneous term, while
  // the last coefficient is for the modulus.
  return max_size() - 2;
}

inline dimension_type
Congruence::space_dimension() const {
  return size() - 2;
}

inline Coefficient_traits::const_reference
Congruence::coefficient(const Variable v) const {
  if (v.space_dimension() > space_dimension())
    throw_dimension_incompatible("coefficient(v)", "v", v);
  return (*this)[v.id()+1];
}

inline Coefficient_traits::const_reference
Congruence::inhomogeneous_term() const {
  return (*this)[0];
}

inline Coefficient_traits::const_reference
Congruence::modulus() const {
  PPL_ASSERT(size() > 1);
  return (*this)[size()-1];
}

inline bool
Congruence::is_proper_congruence() const {
  return modulus() > 0;
}

inline bool
Congruence::is_equality() const {
  return modulus() == 0;
}

inline bool
Congruence::is_equal_at_dimension(dimension_type dim,
				  const Congruence& cg) const {
  return operator[](dim) * cg.modulus() == cg[dim] * modulus();
}

inline void
Congruence::set_is_equality() {
  (*this)[size()-1] = 0;
}

inline void
Congruence::negate(dimension_type start, dimension_type end) {
  while (start <= end)
    neg_assign(operator[](start++));
}

inline memory_size_type
Congruence::external_memory_in_bytes() const {
  return Row::external_memory_in_bytes();
}

inline memory_size_type
Congruence::total_memory_in_bytes() const {
  return Row::total_memory_in_bytes();
}

inline void
Congruence::swap(Congruence& y) {
  Row::swap(y);
}

} // namespace Parma_Polyhedra_Library

namespace std {

/*! \relates Parma_Polyhedra_Library::Congruence */
inline void
swap(Parma_Polyhedra_Library::Congruence& x,
     Parma_Polyhedra_Library::Congruence& y) {
  x.swap(y);
}

} // namespace std

#endif // !defined(PPL_Congruence_inlines_hh)
