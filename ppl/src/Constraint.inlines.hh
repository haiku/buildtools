/* Constraint class implementation: inline functions.
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

#ifndef PPL_Constraint_inlines_hh
#define PPL_Constraint_inlines_hh 1

#include "Linear_Expression.defs.hh"

namespace Parma_Polyhedra_Library {

inline
Constraint::Constraint(Linear_Expression& e, Type type, Topology topology) {
  PPL_ASSERT(type != STRICT_INEQUALITY || topology == NOT_NECESSARILY_CLOSED);
  Linear_Row::swap(e);
  flags() = Flags(topology, (type == EQUALITY
			     ? LINE_OR_EQUALITY
			     : RAY_OR_POINT_OR_INEQUALITY));
}

inline
Constraint::Constraint(const Constraint& c)
  : Linear_Row(c) {
}

inline
Constraint::Constraint(const Constraint& c, const dimension_type sz)
  : Linear_Row(c, sz, sz) {
}

inline
Constraint::~Constraint() {
}

inline Constraint&
Constraint::operator=(const Constraint& c) {
  Linear_Row::operator=(c);
  return *this;
}

inline dimension_type
Constraint::max_space_dimension() {
  return Linear_Row::max_space_dimension();
}

inline dimension_type
Constraint::space_dimension() const {
  return Linear_Row::space_dimension();
}

inline bool
Constraint::is_equality() const {
  return is_line_or_equality();
}

inline bool
Constraint::is_inequality() const {
  return is_ray_or_point_or_inequality();
}

inline Constraint::Type
Constraint::type() const {
  if (is_equality())
    return EQUALITY;
  if (is_necessarily_closed())
    return NONSTRICT_INEQUALITY;
  else
    return ((*this)[size() - 1] < 0)
      ? STRICT_INEQUALITY
      : NONSTRICT_INEQUALITY;
}

inline bool
Constraint::is_nonstrict_inequality() const {
  return type() == NONSTRICT_INEQUALITY;
}

inline bool
Constraint::is_strict_inequality() const {
  return type() == STRICT_INEQUALITY;
}

inline void
Constraint::set_is_equality() {
  set_is_line_or_equality();
}

inline void
Constraint::set_is_inequality() {
  set_is_ray_or_point_or_inequality();
}

inline Coefficient_traits::const_reference
Constraint::coefficient(const Variable v) const {
  if (v.space_dimension() > space_dimension())
    throw_dimension_incompatible("coefficient(v)", "v", v);
  return Linear_Row::coefficient(v.id());
}

inline Coefficient_traits::const_reference
Constraint::inhomogeneous_term() const {
  return Linear_Row::inhomogeneous_term();
}

inline memory_size_type
Constraint::external_memory_in_bytes() const {
  return Linear_Row::external_memory_in_bytes();
}

inline memory_size_type
Constraint::total_memory_in_bytes() const {
  return Linear_Row::total_memory_in_bytes();
}

/*! \relates Constraint */
inline bool
operator==(const Constraint& x, const Constraint& y) {
  return x.is_equivalent_to(y);
}

/*! \relates Constraint */
inline bool
operator!=(const Constraint& x, const Constraint& y) {
  return !x.is_equivalent_to(y);
}

/*! \relates Constraint */
inline Constraint
operator==(const Linear_Expression& e1, const Linear_Expression& e2) {
  Linear_Expression diff = e1 - e2;
  Constraint c(diff, Constraint::EQUALITY, NECESSARILY_CLOSED);
  // Enforce normalization.
  c.strong_normalize();
  return c;
}

/*! \relates Constraint */
inline Constraint
operator==(const Variable v1, const Variable v2) {
  Linear_Expression diff
    = (v1.space_dimension() < v2.space_dimension()) ? v1-v2 : v2-v1;
  return Constraint(diff, Constraint::EQUALITY, NECESSARILY_CLOSED);
}

/*! \relates Constraint */
inline Constraint
operator>=(const Linear_Expression& e1, const Linear_Expression& e2) {
  Linear_Expression diff = e1 - e2;
  Constraint c(diff, Constraint::NONSTRICT_INEQUALITY, NECESSARILY_CLOSED);
  // Enforce normalization.
  c.normalize();
  return c;
}

/*! \relates Constraint */
inline Constraint
operator>=(const Variable v1, const Variable v2) {
  Linear_Expression diff = v1-v2;
  return Constraint(diff, Constraint::NONSTRICT_INEQUALITY, NECESSARILY_CLOSED);
}

/*! \relates Constraint */
inline Constraint
operator>(const Linear_Expression& e1, const Linear_Expression& e2) {
  Linear_Expression diff;
  // Setting the epsilon coefficient to -1.
  // NOTE: this also enforces normalization.
  const dimension_type e1_dim = e1.space_dimension();
  const dimension_type e2_dim = e2.space_dimension();
  if (e1_dim > e2_dim)
    diff -= Variable(e1_dim);
  else
    diff -= Variable(e2_dim);
  diff += e1;
  diff -= e2;

  Constraint c(diff, Constraint::STRICT_INEQUALITY, NOT_NECESSARILY_CLOSED);
  return c;
}

/*! \relates Constraint */
inline Constraint
operator>(const Variable v1, const Variable v2) {
  Linear_Expression diff = v1-v2;
  diff -= Variable(std::max(v1.space_dimension(), v2.space_dimension()));
  return Constraint(diff,
                    Constraint::STRICT_INEQUALITY,
                    NOT_NECESSARILY_CLOSED);
}

/*! \relates Constraint */
inline Constraint
operator==(Coefficient_traits::const_reference n, const Linear_Expression& e) {
  Linear_Expression diff = n - e;
  Constraint c(diff, Constraint::EQUALITY, NECESSARILY_CLOSED);
  // Enforce normalization.
  c.strong_normalize();
  return c;
}

/*! \relates Constraint */
inline Constraint
operator>=(Coefficient_traits::const_reference n, const Linear_Expression& e) {
  Linear_Expression diff = n - e;
  Constraint c(diff, Constraint::NONSTRICT_INEQUALITY, NECESSARILY_CLOSED);
  // Enforce normalization.
  c.normalize();
  return c;
}

/*! \relates Constraint */
inline Constraint
operator>(Coefficient_traits::const_reference n, const Linear_Expression& e) {
  Linear_Expression diff;
  // Setting the epsilon coefficient to -1.
  // NOTE: this also enforces normalization.
  diff -= Variable(e.space_dimension());
  diff += n;
  diff -= e;

  Constraint c(diff, Constraint::STRICT_INEQUALITY, NOT_NECESSARILY_CLOSED);
  return c;
}

/*! \relates Constraint */
inline Constraint
operator==(const Linear_Expression& e, Coefficient_traits::const_reference n) {
  Linear_Expression diff = e - n;
  Constraint c(diff, Constraint::EQUALITY, NECESSARILY_CLOSED);
  // Enforce normalization.
  c.strong_normalize();
  return c;
}

/*! \relates Constraint */
inline Constraint
operator>=(const Linear_Expression& e, Coefficient_traits::const_reference n) {
  Linear_Expression diff = e - n;
  Constraint c(diff, Constraint::NONSTRICT_INEQUALITY, NECESSARILY_CLOSED);
  // Enforce normalization.
  c.normalize();
  return c;
}

/*! \relates Constraint */
inline Constraint
operator>(const Linear_Expression& e, Coefficient_traits::const_reference n) {
  Linear_Expression diff;
  // Setting the epsilon coefficient to -1.
  // NOTE: this also enforces normalization.
  diff -= Variable(e.space_dimension());
  diff += e;
  diff -= n;

  Constraint c(diff, Constraint::STRICT_INEQUALITY, NOT_NECESSARILY_CLOSED);
  c.set_not_necessarily_closed();
  c.set_is_inequality();
  return c;
}

/*! \relates Constraint */
inline Constraint
operator<=(const Linear_Expression& e1, const Linear_Expression& e2) {
  return e2 >= e1;
}

/*! \relates Constraint */
inline Constraint
operator<=(const Variable v1, const Variable v2) {
  return v2 >= v1;
}

/*! \relates Constraint */
inline Constraint
operator<=(Coefficient_traits::const_reference n, const Linear_Expression& e) {
  return e >= n;
}

/*! \relates Constraint */
inline Constraint
operator<=(const Linear_Expression& e, Coefficient_traits::const_reference n) {
  return n >= e;
}

/*! \relates Constraint */
inline Constraint
operator<(const Linear_Expression& e1, const Linear_Expression& e2) {
  return e2 > e1;
}

/*! \relates Constraint */
inline Constraint
operator<(const Variable v1, const Variable v2) {
  return v2 > v1;
}

/*! \relates Constraint */
inline Constraint
operator<(Coefficient_traits::const_reference n, const Linear_Expression& e) {
  return e > n;
}

/*! \relates Constraint */
inline Constraint
operator<(const Linear_Expression& e, Coefficient_traits::const_reference n) {
  return n > e;
}

inline const Constraint&
Constraint::zero_dim_false() {
  PPL_ASSERT(zero_dim_false_p != 0);
  return *zero_dim_false_p;
}

inline const Constraint&
Constraint::zero_dim_positivity() {
  PPL_ASSERT(zero_dim_positivity_p != 0);
  return *zero_dim_positivity_p;
}

inline const Constraint&
Constraint::epsilon_geq_zero() {
  PPL_ASSERT(epsilon_geq_zero_p != 0);
  return *epsilon_geq_zero_p;
}

inline const Constraint&
Constraint::epsilon_leq_one() {
  PPL_ASSERT(epsilon_leq_one_p != 0);
  return *epsilon_leq_one_p;
}

inline void
Constraint::ascii_dump(std::ostream& s) const {
  Linear_Row::ascii_dump(s);
}

inline bool
Constraint::ascii_load(std::istream& s) {
  return Linear_Row::ascii_load(s);
}

inline void
Constraint::swap(Constraint& y) {
  Linear_Row::swap(y);
}

} // namespace Parma_Polyhedra_Library

namespace std {

/*! \relates Parma_Polyhedra_Library::Constraint */
inline void
swap(Parma_Polyhedra_Library::Constraint& x,
     Parma_Polyhedra_Library::Constraint& y) {
  x.swap(y);
}

} // namespace std

#endif // !defined(PPL_Constraint_inlines_hh)
