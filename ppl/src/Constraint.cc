/* Constraint class implementation (non-inline functions).
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

#include "Constraint.defs.hh"
#include "Variable.defs.hh"
#include "Congruence.defs.hh"
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace PPL = Parma_Polyhedra_Library;

void
PPL::Constraint::throw_invalid_argument(const char* method,
					const char* message) const {
  std::ostringstream s;
  s << "PPL::Constraint::" << method << ":" << std::endl
    << message;
  throw std::invalid_argument(s.str());
}

void
PPL::Constraint::throw_dimension_incompatible(const char* method,
					      const char* name_var,
					      const Variable v) const {
  std::ostringstream s;
  s << "PPL::Constraint::" << method << ":" << std::endl
    << "this->space_dimension() == " << space_dimension() << ", "
    << name_var << ".space_dimension() == " << v.space_dimension() << ".";
  throw std::invalid_argument(s.str());
}

PPL::Constraint
PPL::Constraint::construct_epsilon_geq_zero() {
  Linear_Expression e = Variable(0);
  Constraint c(e, NONSTRICT_INEQUALITY, NOT_NECESSARILY_CLOSED);
  return c;
}

PPL::Constraint::Constraint(const Congruence& cg)
  : Linear_Row(cg.is_equality()
	       // Size includes extra column for the inhomogeneous term.
	       ? cg.space_dimension() + 1
	       : (throw_invalid_argument("Constraint(cg)",
					 "congruence cg must be an equality."),
		  0),
	       // Capacity also includes a column for the epsilon coefficient.
	       compute_capacity(cg.space_dimension() + 2, Row::max_size()),
	       Flags(NECESSARILY_CLOSED, LINE_OR_EQUALITY)) {
  Constraint& c = *this;
  // Copy coefficients and inhomogeneous term.
  for (dimension_type i = cg.space_dimension() + 1; i-- > 0; )
    c[i] = cg[i];
  // Enforce normalization.
  strong_normalize();
}

PPL::Constraint::Constraint(const Congruence& cg,
			    dimension_type sz,
			    dimension_type capacity)
  : Linear_Row(cg.is_equality()
	       ? sz
	       : (throw_invalid_argument("Constraint(cg, sz, c)",
					 "congruence cg must be an equality."),
		  0),
	       capacity,
	       Flags(NECESSARILY_CLOSED, LINE_OR_EQUALITY)) {
  Constraint& c = *this;
  // Copy coefficients.
  PPL_ASSERT(sz > 0);
  while (sz-- > 0)
    c[sz] = cg[sz];
}

bool
PPL::Constraint::is_tautological() const {
  PPL_ASSERT(size() > 0);
  const Constraint& x = *this;
  if (x.all_homogeneous_terms_are_zero())
    if (is_equality())
      return x[0] == 0;
    else
      // Non-strict inequality constraint.
      return x[0] >= 0;
  else
    // There is a non-zero homogeneous coefficient.
    if (is_necessarily_closed())
      return false;
    else {
      // The constraint is NOT necessarily closed.
      const dimension_type eps_index = size() - 1;
      const int eps_sign = sgn(x[eps_index]);
      if (eps_sign > 0)
	// We have found the constraint epsilon >= 0.
	return true;
      if (eps_sign == 0)
	// One of the `true' dimensions has a non-zero coefficient.
	return false;
      else {
	// Here the epsilon coefficient is negative: strict inequality.
	if (x[0] <= 0)
	  // A strict inequality such as `lhs - k > 0',
	  // where k is a non negative integer, cannot be trivially true.
	  return false;
	// Checking for another non-zero coefficient.
	for (dimension_type i = eps_index; --i > 0; )
	  if (x[i] != 0)
	    return false;
	// We have the inequality `k > 0',
	// where k is a positive integer.
	return true;
      }
    }
}

bool
PPL::Constraint::is_inconsistent() const {
  PPL_ASSERT(size() > 0);
  const Constraint& x = *this;
  if (x.all_homogeneous_terms_are_zero())
    // The inhomogeneous term is the only non-zero coefficient.
    if (is_equality())
      return x[0] != 0;
    else
      // Non-strict inequality constraint.
      return x[0] < 0;
  else
    // There is a non-zero homogeneous coefficient.
    if (is_necessarily_closed())
      return false;
    else {
      // The constraint is NOT necessarily closed.
      const dimension_type eps_index = size() - 1;
      if (x[eps_index] >= 0)
	// If positive, we have found the constraint epsilon >= 0.
	// If zero, one of the `true' dimensions has a non-zero coefficient.
	// In both cases, it is not trivially false.
	return false;
      else {
	// Here the epsilon coefficient is negative: strict inequality.
	if (x[0] > 0)
	  // A strict inequality such as `lhs + k > 0',
	  // where k is a positive integer, cannot be trivially false.
	  return false;
	// Checking for another non-zero coefficient.
	for (dimension_type i = eps_index; --i > 0; )
	  if (x[i] != 0)
	    return false;
	// We have the inequality `k > 0',
	// where k is zero or a negative integer.
	return true;
      }
    }
}

bool
PPL::Constraint::is_equivalent_to(const Constraint& y) const {
  const Constraint& x = *this;
  const dimension_type x_space_dim = x.space_dimension();
  if (x_space_dim != y.space_dimension())
    return false;

  const Type x_type = x.type();
  if (x_type != y.type()) {
    // Check for special cases.
    if (x.is_tautological())
      return y.is_tautological();
    else
      return x.is_inconsistent() && y.is_inconsistent();
  }

  if (x_type == STRICT_INEQUALITY) {
    // Due to the presence of epsilon-coefficients, syntactically
    // different strict inequalities may actually encode the same
    // topologically open half-space.
    // First, drop the epsilon-coefficient ...
    Linear_Expression x_expr(x);
    Linear_Expression y_expr(y);
    // ... then, re-normalize ...
    x_expr.normalize();
    y_expr.normalize();
    // ... and finally check for syntactic equality.
    for (dimension_type i = x_space_dim + 1; i-- > 0; )
      if (x_expr[i] != y_expr[i])
	return false;
    return true;
  }

  // `x' and 'y' are of the same type and they are not strict inequalities;
  // thus, the epsilon-coefficient, if present, is zero.
  // It is sufficient to check for syntactic equality.
  for (dimension_type i = x_space_dim + 1; i-- > 0; )
    if (x[i] != y[i])
      return false;
  return true;
}

const PPL::Constraint* PPL::Constraint::zero_dim_false_p = 0;
const PPL::Constraint* PPL::Constraint::zero_dim_positivity_p = 0;
const PPL::Constraint* PPL::Constraint::epsilon_geq_zero_p = 0;
const PPL::Constraint* PPL::Constraint::epsilon_leq_one_p = 0;

void
PPL::Constraint::initialize() {
  PPL_ASSERT(zero_dim_false_p == 0);
  zero_dim_false_p
    = new Constraint(Linear_Expression::zero() == Coefficient_one());

  PPL_ASSERT(zero_dim_positivity_p == 0);
  zero_dim_positivity_p
    = new Constraint(Linear_Expression::zero() <= Coefficient_one());

  PPL_ASSERT(epsilon_geq_zero_p == 0);
  epsilon_geq_zero_p
    = new Constraint(construct_epsilon_geq_zero());

  PPL_ASSERT(epsilon_leq_one_p == 0);
  epsilon_leq_one_p
    = new Constraint(Linear_Expression::zero() < Coefficient_one());
}

void
PPL::Constraint::finalize() {
  PPL_ASSERT(zero_dim_false_p != 0);
  delete zero_dim_false_p;
  zero_dim_false_p = 0;

  PPL_ASSERT(zero_dim_positivity_p != 0);
  delete zero_dim_positivity_p;
  zero_dim_positivity_p = 0;

  PPL_ASSERT(epsilon_geq_zero_p != 0);
  delete epsilon_geq_zero_p;
  epsilon_geq_zero_p = 0;

  PPL_ASSERT(epsilon_leq_one_p != 0);
  delete epsilon_leq_one_p;
  epsilon_leq_one_p = 0;
}

/*! \relates Parma_Polyhedra_Library::Constraint */
std::ostream&
PPL::IO_Operators::operator<<(std::ostream& s, const Constraint& c) {
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
  const char* relation_symbol = 0;
  switch (c.type()) {
  case Constraint::EQUALITY:
    relation_symbol = " = ";
    break;
  case Constraint::NONSTRICT_INEQUALITY:
    relation_symbol = " >= ";
    break;
  case Constraint::STRICT_INEQUALITY:
    relation_symbol = " > ";
    break;
  }
  s << relation_symbol << -c.inhomogeneous_term();
  return s;
}

/*! \relates Parma_Polyhedra_Library::Constraint */
std::ostream&
PPL::IO_Operators::operator<<(std::ostream& s, const Constraint::Type& t) {
  const char* n = 0;
  switch (t) {
  case Constraint::EQUALITY:
    n = "EQUALITY";
    break;
  case Constraint::NONSTRICT_INEQUALITY:
    n = "NONSTRICT_INEQUALITY";
    break;
  case Constraint::STRICT_INEQUALITY:
    n = "STRICT_INEQUALITY";
    break;
  }
  s << n;
  return s;
}

PPL_OUTPUT_DEFINITIONS(Constraint)

bool
PPL::Constraint::OK() const {
  // Check the underlying Linear_Row object.
  if (!Linear_Row::OK())
    return false;

  // Topology consistency checks.
  const dimension_type min_size = is_necessarily_closed() ? 1 : 2;
  if (size() < min_size) {
#ifndef NDEBUG
    std::cerr << "Constraint has fewer coefficients than the minimum "
	      << "allowed by its topology:"
	      << std::endl
	      << "size is " << size()
	      << ", minimum is " << min_size << "."
	      << std::endl;
#endif
    return false;
  }

  if (is_equality() && !is_necessarily_closed() && (*this)[size() - 1] != 0) {
#ifndef NDEBUG
    std::cerr << "Illegal constraint: an equality cannot be strict."
	      << std::endl;
#endif
    return false;
  }

  // Normalization check.
  Constraint tmp = *this;
  tmp.strong_normalize();
  if (tmp != *this) {
#ifndef NDEBUG
    std::cerr << "Constraint is not strongly normalized as it should be."
	      << std::endl;
#endif
    return false;
  }

  // All tests passed.
  return true;
}
