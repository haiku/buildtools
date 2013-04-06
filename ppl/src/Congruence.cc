/* Congruence class implementation (non-inline functions).
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

#include "Congruence.defs.hh"

#include "Variable.defs.hh"
#include "assert.hh"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace PPL = Parma_Polyhedra_Library;

PPL::Congruence::Congruence(const Constraint& c)
  : Row(c.is_equality()
	? c
	: (throw_invalid_argument("Congruence(c)",
				  "constraint c must be an equality."),
	   c),
	c.space_dimension() + 2,
	compute_capacity(c.space_dimension() + 2, Row::max_size())) {
  (*this)[size()-1] = 0;
}

PPL::Congruence::Congruence(const Constraint& c,
			    dimension_type sz, dimension_type capacity)
  : Row(c.is_equality()
	? c
	: (throw_invalid_argument("Congruence(c)",
				  "constraint c must be an equality."),
	   c),
	sz,
	capacity) {
  PPL_ASSERT(sz > 1);
  (*this)[sz-1] = 0;
}

void
PPL::Congruence::sign_normalize() {
  Row& x = *this;
  const dimension_type sz = x.size() - 1;
  // `first_non_zero' indicates the index of the first
  // coefficient of the row different from zero, disregarding
  // the very first coefficient (inhomogeneous term).
  dimension_type first_non_zero;
  for (first_non_zero = 1; first_non_zero < sz; ++first_non_zero)
    if (x[first_non_zero] != 0)
      break;
  if (first_non_zero < sz)
    // If the first non-zero coefficient of the row is negative,
    // negate all the coefficients and the inhomogeneous term.
    if (x[first_non_zero] < 0) {
      for (dimension_type j = first_non_zero; j < sz; ++j)
	neg_assign(x[j]);
      // Also negate the inhomogeneous term.
      neg_assign(x[0]);
    }
}

void
PPL::Congruence::normalize() {
  sign_normalize();

  dimension_type sz = size();
  if (sz == 0)
    return;

  const Coefficient& mod = modulus();
  if (mod == 0)
    return;

  Coefficient& row_0 = (*this)[0];
  // Factor the modulus out of the inhomogeneous term.
  row_0 %= mod;
  if (row_0 < 0)
    // Make inhomogeneous term positive.
    row_0 += mod;
  return;
}

void
PPL::Congruence::strong_normalize() {
  normalize();
  Row::normalize();
}

PPL::Congruence
PPL::Congruence::create(const Linear_Expression& e1,
			const Linear_Expression& e2) {
  // Ensure that diff is created with capacity for the modulus.
  dimension_type dim, e1_dim, e2_dim;
  e1_dim = e1.space_dimension();
  e2_dim = e2.space_dimension();
  if (e1_dim > e2_dim)
    dim = e1_dim;
  else
    dim = e2_dim;
  Linear_Expression diff(e1_dim > e2_dim ? e1 : e2,
			 dim + 2);
  diff -= (e1_dim > e2_dim ? e2 : e1);
  Congruence cg(diff, 1);
  return cg;
}

void
PPL::Congruence::throw_invalid_argument(const char* method,
					const char* message) const {
  std::ostringstream s;
  s << "PPL::Congruence::" << method << ":" << std::endl
    << message;
  throw std::invalid_argument(s.str());
}

void
PPL::Congruence::throw_dimension_incompatible(const char* method,
					      const char* v_name,
					      const Variable v) const {
  std::ostringstream s;
  s << "this->space_dimension() == " << space_dimension() << ", "
    << v_name << ".space_dimension() == " << v.space_dimension() << ".";
  std::string str = s.str();
  throw_invalid_argument(method, str.c_str());
}

/*! \relates Parma_Polyhedra_Library::Congruence */
std::ostream&
PPL::IO_Operators::operator<<(std::ostream& s, const Congruence& c) {
  const dimension_type num_variables = c.space_dimension();
  PPL_DIRTY_TEMP_COEFFICIENT(cv);
  bool first = true;
  for (dimension_type v = 0; v < num_variables; ++v) {
    cv = c.coefficient(Variable(v));
    if (cv != 0) {
      if (!first) {
	if (cv > 0)
	  s << " + ";
	else {
	  s << " - ";
	  neg_assign(cv);
	}
      }
      else
	first = false;
      if (cv == -1)
	s << "-";
      else if (cv != 1)
	s << cv << "*";
      s << PPL::Variable(v);
    }
  }
  if (first)
    s << Coefficient_zero();
  s << " = " << -c.inhomogeneous_term();
  if (c.is_proper_congruence())
    s << " (mod " << c.modulus() << ")";
  return s;
}

bool
PPL::Congruence::is_tautological() const {
  if ((is_equality() && inhomogeneous_term() == 0)
      || (is_proper_congruence()
	  && (inhomogeneous_term() % modulus() == 0))) {
    for (unsigned i = space_dimension(); i > 0; --i)
      if (operator[](i) != 0)
	return false;
    return true;
  }
  return false;
}

bool
PPL::Congruence::is_inconsistent() const {
  if (inhomogeneous_term() == 0
      || (is_proper_congruence()
	  && ((inhomogeneous_term() % modulus()) == 0)))
    return false;
  for (unsigned i = space_dimension(); i > 0; --i)
    if (operator[](i) != 0)
      return false;
  return true;
}

void
PPL::Congruence::ascii_dump(std::ostream& s) const {
  const Row& x = *this;
  const dimension_type x_size = x.size();
  s << "size " << x_size << " ";
  if (x_size > 0) {
    for (dimension_type i = 0; i < x_size - 1; ++i)
      s << x[i] << ' ';
    s << "m " << x[x_size - 1];
  }
  s << std::endl;
}

PPL_OUTPUT_DEFINITIONS(Congruence)

bool
PPL::Congruence::ascii_load(std::istream& s) {
  std::string str;
  if (!(s >> str) || str != "size")
    return false;
  dimension_type new_size;
  if (!(s >> new_size))
    return false;

  Row& x = *this;
  const dimension_type old_size = x.size();
  if (new_size < old_size)
    x.shrink(new_size);
  else if (new_size > old_size) {
    Row y(new_size, Row::Flags());
    x.swap(y);
  }

  if (new_size > 0) {
    for (dimension_type col = 0; col < new_size - 1; ++col)
      if (!(s >> x[col]))
	return false;
    if (!(s >> str) || str != "m")
      return false;
    if (!(s >> x[new_size-1]))
      return false;
  }
  return true;
}

bool
PPL::Congruence::OK() const {
  // A Congruence must be a valid Row.
  if (!Row::OK())
    return false;

  // Modulus check.
  if (modulus() < 0) {
#ifndef NDEBUG
    std::cerr << "Congruence has a negative modulus " << modulus() << "."
	      << std::endl;
#endif
    return false;
  }

  // All tests passed.
  return true;
}

const PPL::Congruence* PPL::Congruence::zero_dim_false_p = 0;
const PPL::Congruence* PPL::Congruence::zero_dim_integrality_p = 0;

void
PPL::Congruence::initialize() {
  PPL_ASSERT(zero_dim_false_p == 0);
  zero_dim_false_p
    = new Congruence((Linear_Expression::zero() %= Coefficient(-1)) / 0);

  PPL_ASSERT(zero_dim_integrality_p == 0);
  zero_dim_integrality_p
    = new Congruence(Linear_Expression::zero() %= Coefficient(-1));
}

void
PPL::Congruence::finalize() {
  PPL_ASSERT(zero_dim_false_p != 0);
  delete zero_dim_false_p;
  zero_dim_false_p = 0;

  PPL_ASSERT(zero_dim_integrality_p != 0);
  delete zero_dim_integrality_p;
  zero_dim_integrality_p = 0;
}
