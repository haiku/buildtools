/* Grid_Generator class implementation (non-inline functions).
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

#include "Grid_Generator.defs.hh"
#include <iostream>
#include <sstream>

namespace PPL = Parma_Polyhedra_Library;

void
PPL::Grid_Generator::throw_invalid_argument(const char* method,
					    const char* reason) const {
  std::ostringstream s;
  s << "PPL::Grid_Generator::" << method << ":" << std::endl
    << reason << ".";
  throw std::invalid_argument(s.str());
}

PPL::Grid_Generator
PPL::Grid_Generator::parameter(const Linear_Expression& e,
			       Coefficient_traits::const_reference d) {
  if (d == 0)
    throw std::invalid_argument("PPL::parameter(e, d):\n"
				"d == 0.");
  // Add 2 to space dimension to allow for parameter divisor column.
  Linear_Expression ec(e,
		       e.space_dimension() + 2);
  Generator g(ec, Generator::RAY, NECESSARILY_CLOSED);
  g[0] = 0;
  // Using this constructor saves reallocation when creating the
  // coefficients.
  Grid_Generator gg(g);
  gg.set_divisor(d);

  // If the divisor is negative, negate it and all the coefficients of
  // the parameter.  This ensures that divisors are always positive.
  if (d < 0)
    for (dimension_type i = gg.size(); i-- > 0; )
      neg_assign(gg[i]);

  return gg;
}

PPL::Grid_Generator
PPL::Grid_Generator::grid_point(const Linear_Expression& e,
				Coefficient_traits::const_reference d) {
  if (d == 0)
    throw std::invalid_argument("PPL::grid_point(e, d):\n"
				"d == 0.");
  // Add 2 to space dimension to allow for parameter divisor column.
  Linear_Expression ec(e,
		       e.space_dimension() + 2);
  Generator g(ec, Generator::POINT, NECESSARILY_CLOSED);
  g[0] = d;
  // Using this constructor saves reallocation when creating the
  // coefficients.
  Grid_Generator gg(g);

  // If the divisor is negative, negate it and all the coefficients of
  // the parameter.  This ensures that divisors are always positive.
  if (d < 0)
    for (dimension_type i = gg.size(); i-- > 0; )
      neg_assign(gg[i]);

  // Enforce normalization.
  gg.normalize();
  return gg;
}

PPL::Grid_Generator
PPL::Grid_Generator::grid_line(const Linear_Expression& e) {
  // The origin of the space cannot be a line.
  if (e.all_homogeneous_terms_are_zero())
    throw std::invalid_argument("PPL::grid_line(e):\n"
				"e == 0, but the origin cannot be a line.");

  // Add 2 to space dimension to allow for parameter divisor column.
  Linear_Expression ec(e,
		       e.space_dimension() + 2);
  Generator g(ec, Generator::LINE, NECESSARILY_CLOSED);
  g[0] = 0;
  // Using this constructor saves reallocation when creating the
  // coefficients.
  Grid_Generator gg(g);

  // Enforce normalization.
  gg.strong_normalize();
  return gg;
}

void
PPL::Grid_Generator::coefficient_swap(Grid_Generator& y) {
  // Swap one coefficient at a time into *this.  Doing this instead of
  // swapping the entire row ensures that the row keeps the same
  // capacity.
  if (y.is_line())
    set_is_line();
  else
    set_is_ray_or_point();
  PPL_ASSERT(size() > 0);
  PPL_ASSERT(y.size() > 0);
  dimension_type sz = size() - 1;
  dimension_type y_sz = y.size() - 1;
  // Swap parameter divisors.
  std::swap(operator[](sz), y[y_sz]);
  for (dimension_type j = (sz > y_sz ? y_sz : sz); j-- > 0; )
    std::swap(operator[](j), y[j]);
}

void
PPL::Grid_Generator::ascii_dump(std::ostream& s) const {
  const Grid_Generator& x = *this;
  const dimension_type x_size = x.size();
  s << "size " << x_size << " ";
  for (dimension_type i = 0; i < x_size; ++i)
    s << x[i] << ' ';
  switch (x.type()) {
  case Generator::LINE:
    s << "L";
    break;
  case Generator::RAY:
    s << "Q";
    break;
  case Generator::POINT:
    s << "P";
    break;
  }
  s << "\n";
}

PPL_OUTPUT_DEFINITIONS(Grid_Generator)

bool
PPL::Grid_Generator::ascii_load(std::istream& s) {
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

  for (dimension_type col = 0; col < new_size; ++col)
    if (!(s >> x[col]))
      return false;

  if (!(s >> str))
    return false;
  if (str == "L")
    set_is_line();
  else if (str == "P" || str == "Q")
    set_is_ray_or_point();
  else
    return false;

  return true;
}

void
PPL::Grid_Generator::set_is_parameter() {
  if (is_line())
    set_is_parameter_or_point();
  else if (!is_line_or_parameter()) {
    // The generator is a point.
    Generator::operator[](size() - 1) = Generator::operator[](0);
    Generator::operator[](0) = 0;
  }
}

bool
PPL::Grid_Generator::is_equivalent_to(const Grid_Generator& y) const {
  const Grid_Generator& x = *this;
  dimension_type x_space_dim = x.space_dimension();
  if (x_space_dim != y.space_dimension())
    return false;

  const Type x_type = x.type();
  if (x_type != y.type())
    return false;

  Grid_Generator tmp = *this;
  Grid_Generator tmp_y = y;
  dimension_type& last = x_space_dim;
  ++last;
  if (x_type == POINT || x_type == LINE) {
    tmp[last] = 0;
    tmp_y[last] = 0;
  }
  // Normalize the copies, including the divisor column.
  tmp.Row::normalize();
  tmp_y.Row::normalize();
  // Check for equality.
  while (last-- > 0)
    if (tmp[last] != tmp_y[last])
      return false;
  return true;
}

bool
PPL::Grid_Generator::is_equal_to(const Grid_Generator& y) const {
  if (type() != y.type())
    return false;
  for (dimension_type col = (is_parameter() ? size() : size() - 1);
       col-- > 0; )
    if (Generator::operator[](col) != y.Generator::operator[](col))
      return false;
  return true;
}

bool
PPL::Grid_Generator::all_homogeneous_terms_are_zero() const {
  // Start at size() - 1 to avoid the extra grid generator column.
  for (dimension_type i = size() - 1; --i > 0; )
    if (operator[](i) != 0)
      return false;
  return true;
}

void
PPL::Grid_Generator::scale_to_divisor(Coefficient_traits::const_reference d) {
  if (is_parameter_or_point()) {
    if (d == 0)
      throw std::invalid_argument("PPL::Grid_Generator::scale_to_divisor(d):\n"
				  "d == 0.");

    PPL_DIRTY_TEMP_COEFFICIENT(factor);
    exact_div_assign(factor, d, divisor());
    set_divisor(d);
    PPL_ASSERT(factor > 0);
    if (factor > 1)
      for (dimension_type col = size() - 2; col >= 1; --col)
	Generator::operator[](col) *= factor;
  }
}

const PPL::Grid_Generator* PPL::Grid_Generator::zero_dim_point_p = 0;

void
PPL::Grid_Generator::initialize() {
  PPL_ASSERT(zero_dim_point_p == 0);
  zero_dim_point_p
    = new Grid_Generator(grid_point());
}

void
PPL::Grid_Generator::finalize() {
  PPL_ASSERT(zero_dim_point_p != 0);
  delete zero_dim_point_p;
  zero_dim_point_p = 0;
}

/*! \relates Parma_Polyhedra_Library::Grid_Generator */
std::ostream&
PPL::IO_Operators::operator<<(std::ostream& s, const Grid_Generator& g) {
  bool need_divisor = false;
  bool extra_parentheses = false;
  const dimension_type num_variables = g.space_dimension();
  Grid_Generator::Type t = g.type();
  switch (t) {
  case Grid_Generator::LINE:
    s << "l(";
    break;
  case Grid_Generator::PARAMETER:
    s << "q(";
    if (g[num_variables + 1] == 1)
      break;
    goto any_point;
  case Grid_Generator::POINT:
    s << "p(";
    if (g[0] > 1) {
    any_point:
      need_divisor = true;
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
    // A generator in the origin.
    s << 0;
  if (extra_parentheses)
    s << ")";
  if (need_divisor)
    s << "/" << g.divisor();
  s << ")";
  return s;
}

/*! \relates Parma_Polyhedra_Library::Grid_Generator */
std::ostream&
PPL::IO_Operators::operator<<(std::ostream& s,
			      const Grid_Generator::Type& t) {
  const char* n = 0;
  switch (t) {
  case Grid_Generator::LINE:
    n = "LINE";
    break;
  case Grid_Generator::PARAMETER:
    n = "PARAMETER";
    break;
  case Generator::POINT:
    n = "POINT";
    break;
  }
  s << n;
  return s;
}

bool
PPL::Grid_Generator::OK() const {
  if (!is_necessarily_closed()) {
#ifndef NDEBUG
    std::cerr << "Grid_Generator should be necessarily closed."
	      << std::endl;
#endif
    return false;
  }

  // Topology consistency check.
  if (size() < 1) {
#ifndef NDEBUG
    std::cerr << "Grid_Generator has fewer coefficients than the minimum "
	      << "allowed:" << std::endl
	      << "size is " << size() << ", minimum is 1." << std::endl;
#endif
    return false;
  }

  switch (type()) {
  case Grid_Generator::LINE:
    if (operator[](0) != 0) {
#ifndef NDEBUG
      std::cerr << "Inhomogeneous terms of lines must be zero!"
		<< std::endl;
#endif
      return false;
    }
    break;

  case Grid_Generator::PARAMETER:
    if (operator[](0) != 0) {
#ifndef NDEBUG
      std::cerr << "Inhomogeneous terms of parameters must be zero!"
		<< std::endl;
#endif
      return false;
    }
    // Fall through.

  case Grid_Generator::POINT:
    if (divisor() <= 0) {
#ifndef NDEBUG
      std::cerr << "Points and parameters must have positive divisors!"
		<< std::endl;
#endif
      return false;
    }
    break;

  }

  // All tests passed.
  return true;
}
