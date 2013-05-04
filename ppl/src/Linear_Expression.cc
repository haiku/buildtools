/* Linear_Expression class implementation (non-inline functions).
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

#include "Linear_Expression.defs.hh"
#include "Constraint.defs.hh"
#include "Generator.defs.hh"
#include "Grid_Generator.defs.hh"
#include "Congruence.defs.hh"
#include <stdexcept>
#include <iostream>

namespace PPL = Parma_Polyhedra_Library;

PPL::Linear_Expression::Linear_Expression(const Constraint& c)
  : Linear_Row(c.space_dimension() + 1, Linear_Row::Flags()) {
  Linear_Expression& e = *this;
  for (dimension_type i = size(); i-- > 0; )
    e[i] = c[i];
}

PPL::Linear_Expression::Linear_Expression(const Generator& g)
  : Linear_Row(g.space_dimension() + 1, Linear_Row::Flags()) {
  Linear_Expression& e = *this;
  // Do not copy the divisor of `g'.
  for (dimension_type i = size(); --i > 0; )
    e[i] = g[i];
}

PPL::Linear_Expression::Linear_Expression(const Grid_Generator& g)
  : Linear_Row(g.space_dimension() + 1, Linear_Row::Flags()) {
  Linear_Expression& e = *this;
  // Do not copy the divisor of `g'.
  for (dimension_type i = size(); --i > 0; )
    e[i] = g[i];
}

const PPL::Linear_Expression* PPL::Linear_Expression::zero_p = 0;

void
PPL::Linear_Expression::initialize() {
  PPL_ASSERT(zero_p == 0);
  zero_p = new Linear_Expression(Coefficient_zero());
}

void
PPL::Linear_Expression::finalize() {
  PPL_ASSERT(zero_p != 0);
  delete zero_p;
  zero_p = 0;
}

PPL::Linear_Expression::Linear_Expression(const Congruence& cg)
  : Linear_Row(cg.space_dimension() + 1, Linear_Row::Flags()) {
  Linear_Expression& e = *this;
  for (dimension_type i = size(); i-- > 0; )
    e[i] = cg[i];
}

PPL::Linear_Expression::Linear_Expression(const Variable v)
  : Linear_Row(v.space_dimension() <= max_space_dimension()
	       ? v.space_dimension() + 1
	       : (throw std::length_error("PPL::Linear_Expression::"
					  "Linear_Expression(v):\n"
					  "v exceeds the maximum allowed "
					  "space dimension."),
		  v.space_dimension() + 1)
	       , Linear_Row::Flags()) {
  ++((*this)[v.space_dimension()]);
}

PPL::Linear_Expression::Linear_Expression(const Variable v, const Variable w)
  : Linear_Row() {
  const dimension_type v_space_dim = v.space_dimension();
  const dimension_type w_space_dim = w.space_dimension();
  const dimension_type space_dim = std::max(v_space_dim, w_space_dim);
  if (space_dim > max_space_dimension())
    throw std::length_error("PPL::Linear_Expression::"
                            "Linear_Expression(v, w):\n"
                            "v or w exceed the maximum allowed "
                            "space dimension.");
  construct(space_dim+1, Linear_Row::Flags());
  if (v_space_dim != w_space_dim) {
    ++((*this)[v_space_dim]);
    --((*this)[w_space_dim]);
  }
}

/*! \relates Parma_Polyhedra_Library::Linear_Expression */
PPL::Linear_Expression
PPL::operator+(const Linear_Expression& e1, const Linear_Expression& e2) {
  dimension_type e1_size = e1.size();
  dimension_type e2_size = e2.size();
  dimension_type min_size;
  dimension_type max_size;
  const Linear_Expression* p_e_max;
  if (e1_size > e2_size) {
    min_size = e2_size;
    max_size = e1_size;
    p_e_max = &e1;
  }
  else {
    min_size = e1_size;
    max_size = e2_size;
    p_e_max = &e2;
  }

  Linear_Expression r(max_size, false);
  dimension_type i = max_size;
  while (i > min_size) {
    --i;
    r[i] = (*p_e_max)[i];
  }
  while (i > 0) {
    --i;
    r[i] = e1[i] + e2[i];
  }

  return r;
}

/*! \relates Linear_Expression */
PPL::Linear_Expression
PPL::operator+(const Variable v, const Linear_Expression& e) {
  const dimension_type v_space_dim = v.space_dimension();
  if (v_space_dim > Linear_Expression::max_space_dimension())
    throw std::length_error("Linear_Expression "
                            "PPL::operator+(v, e):\n"
                            "v exceeds the maximum allowed "
                            "space dimension.");
  const dimension_type space_dim = std::max(v_space_dim, e.space_dimension());
  Linear_Expression r(e, space_dim+1);
  ++r[v_space_dim];
  return r;
}

/*! \relates Parma_Polyhedra_Library::Linear_Expression */
PPL::Linear_Expression
PPL::operator+(Coefficient_traits::const_reference n,
	       const Linear_Expression& e) {
  Linear_Expression r(e);
  r[0] += n;
  return r;
}

/*! \relates Linear_Expression */
PPL::Linear_Expression
PPL::operator+(const Variable v, const Variable w) {
  const dimension_type v_space_dim = v.space_dimension();
  const dimension_type w_space_dim = w.space_dimension();
  const dimension_type space_dim = std::max(v_space_dim, w_space_dim);
  if (space_dim > Linear_Expression::max_space_dimension())
    throw std::length_error("Linear_Expression "
                            "PPL::operator+(v, w):\n"
                            "v or w exceed the maximum allowed "
                            "space dimension.");
  Linear_Expression r(space_dim+1, true);
  ++r[v_space_dim];
  ++r[w_space_dim];
  return r;
}

/*! \relates Parma_Polyhedra_Library::Linear_Expression */
PPL::Linear_Expression
PPL::operator-(const Linear_Expression& e) {
  Linear_Expression r(e);
  for (dimension_type i = e.size(); i-- > 0; )
    neg_assign(r[i]);
  return r;
}

/*! \relates Parma_Polyhedra_Library::Linear_Expression */
PPL::Linear_Expression
PPL::operator-(const Linear_Expression& e1, const Linear_Expression& e2) {
  dimension_type e1_size = e1.size();
  dimension_type e2_size = e2.size();
  if (e1_size > e2_size) {
    Linear_Expression r(e1_size, false);
    dimension_type i = e1_size;
    while (i > e2_size) {
      --i;
      r[i] = e1[i];
    }
    while (i > 0) {
      --i;
      r[i] = e1[i] - e2[i];
    }
    return r;
  }
  else {
    Linear_Expression r(e2_size, false);
    dimension_type i = e2_size;
    while (i > e1_size) {
      --i;
      r[i] = -e2[i];
    }
    while (i > 0) {
      --i;
      r[i] = e1[i] - e2[i];
    }
    return r;
  }
}

/*! \relates Parma_Polyhedra_Library::Linear_Expression */
PPL::Linear_Expression
PPL::operator-(const Variable v, const Linear_Expression& e) {
  const dimension_type v_space_dim = v.space_dimension();
  if (v_space_dim > Linear_Expression::max_space_dimension())
    throw std::length_error("Linear_Expression "
                            "PPL::operator-(v, e):\n"
                            "v exceeds the maximum allowed "
                            "space dimension.");
  const dimension_type e_space_dim = e.space_dimension();
  const dimension_type space_dim = std::max(v_space_dim, e_space_dim);
  Linear_Expression r(e, space_dim+1);
  for (dimension_type i = e.size(); i-- > 0; )
    neg_assign(r[i]);
  ++r[v_space_dim];
  return r;
}

/*! \relates Linear_Expression */
PPL::Linear_Expression
PPL::operator-(const Linear_Expression& e, const Variable v) {
  const dimension_type v_space_dim = v.space_dimension();
  if (v_space_dim > Linear_Expression::max_space_dimension())
    throw std::length_error("Linear_Expression "
                            "PPL::operator-(e, v):\n"
                            "v exceeds the maximum allowed "
                            "space dimension.");
  const dimension_type space_dim = std::max(v_space_dim, e.space_dimension());
  Linear_Expression r(e, space_dim+1);
  --r[v_space_dim];
  return r;
}

/*! \relates Parma_Polyhedra_Library::Linear_Expression */
PPL::Linear_Expression
PPL::operator-(Coefficient_traits::const_reference n,
	       const Linear_Expression& e) {
  Linear_Expression r(e);
  for (dimension_type i = e.size(); i-- > 0; )
    neg_assign(r[i]);
  r[0] += n;
  return r;
}

/*! \relates Parma_Polyhedra_Library::Linear_Expression */
PPL::Linear_Expression
PPL::operator*(Coefficient_traits::const_reference n,
	       const Linear_Expression& e) {
  Linear_Expression r(e);
  for (dimension_type i = e.size(); i-- > 0; )
    r[i] *= n;
  return r;
}

/*! \relates Parma_Polyhedra_Library::Linear_Expression */
PPL::Linear_Expression&
PPL::operator+=(Linear_Expression& e1, const Linear_Expression& e2) {
  dimension_type e1_size = e1.size();
  dimension_type e2_size = e2.size();
  if (e1_size >= e2_size)
    for (dimension_type i = e2_size; i-- > 0; )
      e1[i] += e2[i];
  else {
    Linear_Expression new_e(e2);
    for (dimension_type i = e1_size; i-- > 0; )
      new_e[i] += e1[i];
    e1.swap(new_e);
  }
  return e1;
}

/*! \relates Parma_Polyhedra_Library::Linear_Expression */
PPL::Linear_Expression&
PPL::operator+=(Linear_Expression& e, const Variable v) {
  const dimension_type v_space_dim = v.space_dimension();
  if (v_space_dim > Linear_Expression::max_space_dimension())
    throw std::length_error("Linear_Expression& "
                            "PPL::operator+=(e, v):\n"
			    "v exceeds the maximum allowed space dimension.");
  const dimension_type e_size = e.size();
  if (e_size <= v_space_dim) {
    Linear_Expression new_e(e, v_space_dim+1);
    e.swap(new_e);
  }
  ++e[v_space_dim];
  return e;
}

/*! \relates Parma_Polyhedra_Library::Linear_Expression */
PPL::Linear_Expression&
PPL::operator-=(Linear_Expression& e1, const Linear_Expression& e2) {
  dimension_type e1_size = e1.size();
  dimension_type e2_size = e2.size();
  if (e1_size >= e2_size)
    for (dimension_type i = e2_size; i-- > 0; )
      e1[i] -= e2[i];
  else {
    Linear_Expression new_e(e1, e2_size);
    for (dimension_type i = e2_size; i-- > 0; )
      new_e[i] -= e2[i];
    e1.swap(new_e);
  }
  return e1;
}

/*! \relates Parma_Polyhedra_Library::Linear_Expression */
PPL::Linear_Expression&
PPL::operator-=(Linear_Expression& e, const Variable v) {
  const dimension_type v_space_dim = v.space_dimension();
  if (v_space_dim > Linear_Expression::max_space_dimension())
    throw std::length_error("Linear_Expression& "
                            "PPL::operator-=(e, v):\n"
			    "v exceeds the maximum allowed space dimension.");
  const dimension_type e_size = e.size();
  if (e_size <= v_space_dim) {
    Linear_Expression new_e(e, v_space_dim+1);
    e.swap(new_e);
  }
  --e[v_space_dim];
  return e;
}

/*! \relates Parma_Polyhedra_Library::Linear_Expression */
PPL::Linear_Expression&
PPL::operator*=(Linear_Expression& e, Coefficient_traits::const_reference n) {
  dimension_type e_size = e.size();
  for (dimension_type i = e_size; i-- > 0; )
    e[i] *= n;
  return e;
}

/*! \relates Parma_Polyhedra_Library::Linear_Expression */
PPL::Linear_Expression&
PPL::add_mul_assign(Linear_Expression& e,
                    Coefficient_traits::const_reference n,
                    const Variable v) {
  const dimension_type v_space_dim = v.space_dimension();
  if (v_space_dim > Linear_Expression::max_space_dimension())
    throw std::length_error("Linear_Expression& "
                            "PPL::add_mul_assign(e, n, v):\n"
			    "v exceeds the maximum allowed space dimension.");
  const dimension_type e_size = e.size();
  if (e_size <= v_space_dim) {
    Linear_Expression new_e(e, v_space_dim+1);
    e.swap(new_e);
  }
  e[v_space_dim] += n;
  return e;
}

/*! \relates Parma_Polyhedra_Library::Linear_Expression */
PPL::Linear_Expression&
PPL::sub_mul_assign(Linear_Expression& e,
                    Coefficient_traits::const_reference n,
                    const Variable v) {
  const dimension_type v_space_dim = v.space_dimension();
  if (v_space_dim > Linear_Expression::max_space_dimension())
    throw std::length_error("Linear_Expression& "
                            "PPL::sub_mul_assign(e, n, v):\n"
			    "v exceeds the maximum allowed space dimension.");
  const dimension_type e_size = e.size();
  if (e_size <= v_space_dim) {
    Linear_Expression new_e(e, v_space_dim+1);
    e.swap(new_e);
  }
  e[v_space_dim] -= n;
  return e;
}

bool
PPL::Linear_Expression::OK() const {
  return Linear_Row::OK();
}

/*! \relates Parma_Polyhedra_Library::Linear_Expression */
std::ostream&
PPL::IO_Operators::operator<<(std::ostream& s, const Linear_Expression& e) {
  const dimension_type num_variables = e.space_dimension();
  PPL_DIRTY_TEMP_COEFFICIENT(ev);
  bool first = true;
  for (dimension_type v = 0; v < num_variables; ++v) {
    ev = e[v+1];
    if (ev != 0) {
      if (!first) {
	if (ev > 0)
	  s << " + ";
	else {
	  s << " - ";
	  neg_assign(ev);
	}
      }
      else
	first = false;
      if (ev == -1)
	s << "-";
      else if (ev != 1)
	s << ev << "*";
      s << PPL::Variable(v);
    }
  }
  // Inhomogeneous term.
  PPL_DIRTY_TEMP_COEFFICIENT(it);
  it = e[0];
  if (it != 0) {
    if (!first) {
      if (it > 0)
	s << " + ";
      else {
	s << " - ";
	neg_assign(it);
      }
    }
    else
      first = false;
    s << it;
  }

  if (first)
    // The null linear expression.
    s << Coefficient_zero();
  return s;
}

PPL_OUTPUT_DEFINITIONS(Linear_Expression)
