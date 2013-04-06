/* Generator class implementation (non-inline functions).
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

#include "Generator.defs.hh"

#include "Variable.defs.hh"
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace PPL = Parma_Polyhedra_Library;

void
PPL::Generator::throw_dimension_incompatible(const char* method,
					     const char* name_var,
					     const Variable v) const {
  std::ostringstream s;
  s << "PPL::Generator::" << method << ":" << std::endl
    << "this->space_dimension() == " << space_dimension() << ", "
    << name_var << ".space_dimension() == " << v.space_dimension() << ".";
  throw std::invalid_argument(s.str());
}

void
PPL::Generator::throw_invalid_argument(const char* method,
				       const char* reason) const {
  std::ostringstream s;
  s << "PPL::Generator::" << method << ":" << std::endl
    << reason << ".";
  throw std::invalid_argument(s.str());
}

PPL::Generator
PPL::Generator::point(const Linear_Expression& e,
		      Coefficient_traits::const_reference d) {
  if (d == 0)
    throw std::invalid_argument("PPL::point(e, d):\n"
				"d == 0.");
  Linear_Expression ec = e;
  Generator g(ec, Generator::POINT, NECESSARILY_CLOSED);
  g[0] = d;

  // If the divisor is negative, we negate it as well as
  // all the coefficients of the point, because we want to preserve
  // the invariant: the divisor of a point is strictly positive.
  if (d < 0)
    for (dimension_type i = g.size(); i-- > 0; )
      neg_assign(g[i]);

  // Enforce normalization.
  g.normalize();
  return g;
}

PPL::Generator
PPL::Generator::closure_point(const Linear_Expression& e,
			      Coefficient_traits::const_reference d) {
  if (d == 0)
    throw std::invalid_argument("PPL::closure_point(e, d):\n"
				"d == 0.");
  // Adding the epsilon dimension with coefficient 0.
  Linear_Expression ec = 0 * Variable(e.space_dimension());
  ec += e;
  // A closure point is indeed a point in the higher dimension space.
  Generator g = point(ec, d);
  // Fix the topology.
  g.set_not_necessarily_closed();
  // Enforce normalization.
  g.normalize();
  return g;
}

PPL::Generator
PPL::Generator::ray(const Linear_Expression& e) {
  // The origin of the space cannot be a ray.
  if (e.all_homogeneous_terms_are_zero())
    throw std::invalid_argument("PPL::ray(e):\n"
				"e == 0, but the origin cannot be a ray.");

  Linear_Expression ec = e;
  Generator g(ec, Generator::RAY, NECESSARILY_CLOSED);
  g[0] = 0;
  // Enforce normalization.
  g.normalize();
  return g;
}

PPL::Generator
PPL::Generator::line(const Linear_Expression& e) {
  // The origin of the space cannot be a line.
  if (e.all_homogeneous_terms_are_zero())
    throw std::invalid_argument("PPL::line(e):\n"
				"e == 0, but the origin cannot be a line.");

  Linear_Expression ec = e;
  Generator g(ec, Generator::LINE, NECESSARILY_CLOSED);
  g[0] = 0;
  // Enforce normalization.
  g.strong_normalize();
  return g;
}

bool
PPL::Generator::is_equivalent_to(const Generator& y) const {
  const Generator& x = *this;
  const dimension_type x_space_dim = x.space_dimension();
  if (x_space_dim != y.space_dimension())
    return false;

  const Type x_type = x.type();
  if (x_type != y.type())
    return false;

  if (x_type == POINT
      && !(x.is_necessarily_closed() && y.is_necessarily_closed())) {
    // Due to the presence of epsilon-coefficients, syntactically
    // different points may actually encode the same generator.
    // First, drop the epsilon-coefficient ...
    Linear_Expression x_expr(x);
    Linear_Expression y_expr(y);
    // ... second, re-normalize ...
    x_expr.normalize();
    y_expr.normalize();
    // ... and finally check for syntactic equality.
    for (dimension_type i = x_space_dim + 1; i-- > 0; )
      if (x_expr[i] != y_expr[i])
	return false;
    return true;
  }

  // Here the epsilon-coefficient, if present, is zero.
  // It is sufficient to check for syntactic equality.
  for (dimension_type i = x_space_dim + 1; i-- > 0; )
    if (x[i] != y[i])
      return false;
  return true;
}

const PPL::Generator* PPL::Generator::zero_dim_point_p = 0;
const PPL::Generator* PPL::Generator::zero_dim_closure_point_p = 0;

void
PPL::Generator::initialize() {
  PPL_ASSERT(zero_dim_point_p == 0);
  zero_dim_point_p
    = new Generator(point());

  PPL_ASSERT(zero_dim_closure_point_p == 0);
  zero_dim_closure_point_p
    = new Generator(closure_point());
}

void
PPL::Generator::finalize() {
  PPL_ASSERT(zero_dim_point_p != 0);
  delete zero_dim_point_p;
  zero_dim_point_p = 0;

  PPL_ASSERT(zero_dim_closure_point_p != 0);
  delete zero_dim_closure_point_p;
  zero_dim_closure_point_p = 0;
}

/*! \relates Parma_Polyhedra_Library::Generator */
std::ostream&
PPL::IO_Operators::operator<<(std::ostream& s, const Generator& g) {
  bool needed_divisor = false;
  bool extra_parentheses = false;
  const dimension_type num_variables = g.space_dimension();
  Generator::Type t = g.type();
  switch (t) {
  case Generator::LINE:
    s << "l(";
    break;
  case Generator::RAY:
    s << "r(";
    break;
  case Generator::POINT:
    s << "p(";
    goto any_point;
  case Generator::CLOSURE_POINT:
    s << "c(";
  any_point:
    if (g[0] != 1) {
      needed_divisor = true;
      dimension_type num_non_zero_coefficients = 0;
      for (dimension_type v = 0; v < num_variables; ++v)
	if (g[v+1] != 0)
	  if (++num_non_zero_coefficients > 1) {
	    extra_parentheses = true;
	    s << "(";
	    break;
	  }
    }
    break;
  }

  PPL_DIRTY_TEMP_COEFFICIENT(gv);
  bool first = true;
  for (dimension_type v = 0; v < num_variables; ++v) {
    gv = g[v+1];
    if (gv != 0) {
      if (!first) {
	if (gv > 0)
	  s << " + ";
	else {
	  s << " - ";
	  neg_assign(gv);
	}
      }
      else
	first = false;
      if (gv == -1)
	s << "-";
      else if (gv != 1)
	s << gv << "*";
      s << PPL::Variable(v);
    }
  }
  if (first)
    // A point or closure point in the origin.
    s << 0;
  if (extra_parentheses)
    s << ")";
  if (needed_divisor)
    s << "/" << g[0];
  s << ")";
  return s;
}

/*! \relates Parma_Polyhedra_Library::Generator */
std::ostream&
PPL::IO_Operators::operator<<(std::ostream& s, const Generator::Type& t) {
  const char* n = 0;
  switch (t) {
  case Generator::LINE:
    n = "LINE";
    break;
  case Generator::RAY:
    n = "RAY";
    break;
  case Generator::POINT:
    n = "POINT";
    break;
  case Generator::CLOSURE_POINT:
    n = "CLOSURE_POINT";
    break;
  }
  s << n;
  return s;
}

bool
PPL::Generator::is_matching_closure_point(const Generator& p) const {
  PPL_ASSERT(topology() == p.topology()
	 && space_dimension() == p.space_dimension()
	 && type() == CLOSURE_POINT
	 && p.type() == POINT);
  const Generator& cp = *this;
  if (cp[0] == p[0]) {
    // Divisors are equal: we can simply compare coefficients
    // (disregarding the epsilon coefficient).
    for (dimension_type i = cp.size() - 2; i > 0; --i)
      if (cp[i] != p[i])
	return false;
    return true;
  }
  else {
    // Divisors are different: divide them by their GCD
    // to simplify the following computation.
    PPL_DIRTY_TEMP_COEFFICIENT(gcd);
    gcd_assign(gcd, cp[0], p[0]);
    const bool rel_prime = (gcd == 1);
    PPL_DIRTY_TEMP_COEFFICIENT(cp_0_scaled);
    PPL_DIRTY_TEMP_COEFFICIENT(p_0_scaled);
    if (!rel_prime) {
      exact_div_assign(cp_0_scaled, cp[0], gcd);
      exact_div_assign(p_0_scaled, p[0], gcd);
    }
    const Coefficient& cp_div = rel_prime ? cp[0] : cp_0_scaled;
    const Coefficient& p_div = rel_prime ? p[0] : p_0_scaled;
    PPL_DIRTY_TEMP_COEFFICIENT(prod1);
    PPL_DIRTY_TEMP_COEFFICIENT(prod2);
    for (dimension_type i = cp.size() - 2; i > 0; --i) {
      prod1 = cp[i] * p_div;
      prod2 = p[i] * cp_div;
      if (prod1 != prod2)
	return false;
    }
    return true;
  }
}

PPL_OUTPUT_DEFINITIONS(Generator)

bool
PPL::Generator::OK() const {
  // Check the underlying Linear_Row object.
  if (!Linear_Row::OK())
    return false;

  // Topology consistency check.
  const dimension_type min_size = is_necessarily_closed() ? 1 : 2;
  if (size() < min_size) {
#ifndef NDEBUG
    std::cerr << "Generator has fewer coefficients than the minimum "
	      << "allowed by its topology:"
	      << std::endl
	      << "size is " << size()
	      << ", minimum is " << min_size << "."
	      << std::endl;
#endif
    return false;
  }

  // Normalization check.
  const Generator& g = *this;
  Generator tmp = g;
  tmp.strong_normalize();
  if (tmp != g) {
#ifndef NDEBUG
    std::cerr << "Generators should be strongly normalized!"
	      << std::endl;
#endif
    return false;
  }

  switch (g.type()) {
  case LINE:
    // Intentionally fall through.
  case RAY:
    if (g[0] != 0) {
#ifndef NDEBUG
      std::cerr << "Lines must have a zero inhomogeneous term!"
		<< std::endl;
#endif
      return false;
    }
    if (!g.is_necessarily_closed() && g[size() - 1] != 0) {
#ifndef NDEBUG
      std::cerr << "Lines and rays must have a zero coefficient "
		<< "for the epsilon dimension!"
		<< std::endl;
#endif
      return false;
    }
    // The following test is correct, since we already checked
    // that the epsilon coordinate is zero.
    if (g.all_homogeneous_terms_are_zero()) {
#ifndef NDEBUG
      std::cerr << "The origin of the vector space cannot be a line or a ray!"
		<< std::endl;
#endif
      return false;
    }
    break;

  case POINT:
    if (g[0] <= 0) {
#ifndef NDEBUG
      std::cerr << "Points must have a positive divisor!"
		<< std::endl;
#endif
      return false;
    }
    if (!g.is_necessarily_closed())
      if (g[size() - 1] <= 0) {
#ifndef NDEBUG
	std::cerr << "In the NNC topology, points must have epsilon > 0"
		  << std::endl;
#endif
	return false;
      }
    break;

  case CLOSURE_POINT:
    if (g[0] <= 0) {
#ifndef NDEBUG
      std::cerr << "Closure points must have a positive divisor!"
		<< std::endl;
#endif
      return false;
    }
    break;
  }

  // All tests passed.
  return true;
}
