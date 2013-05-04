/* Scalar_Products class implementation (non-inline functions).
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

#include "Scalar_Products.defs.hh"
#include "Coefficient.defs.hh"

namespace PPL = Parma_Polyhedra_Library;

void
PPL::Scalar_Products::assign(Coefficient& z,
			     const Linear_Row& x, const Linear_Row& y) {
  // Scalar product is only defined  if `x' and `y' are
  // dimension-compatible.
  PPL_ASSERT(x.size() <= y.size());
  z = 0;
  for (dimension_type i = x.size(); i-- > 0; )
    // The following line optimizes the computation of z += x[i] * y[i].
    add_mul_assign(z, x[i], y[i]);
}

void
PPL::Scalar_Products::assign(Coefficient& z,
			     const Constraint& x, const Generator& y) {
  // Scalar product is only defined if `x' and `y' are
  // dimension-compatible.
  PPL_ASSERT(x.size() <= y.size());
  z = 0;
  for (dimension_type i = x.size(); i-- > 0; )
    // The following line optimizes the computation of z += x[i] * y[i].
    add_mul_assign(z, x[i], y[i]);
}

void
PPL::Scalar_Products::assign(Coefficient& z,
			     const Grid_Generator& x, const Congruence& y) {
  // Scalar product is only defined if `x' and `y' are
  // dimension-compatible.
  PPL_ASSERT(x.size() <= y.size());
  z = 0;
  for (dimension_type i = x.size() - 1 /* parameter divisor */; i-- > 0; )
    // The following line optimizes the computation of z += x[i] *
    // y[i].
    add_mul_assign(z, x[i], y[i]);
}

void
PPL::Scalar_Products::assign(Coefficient& z,
			     const Constraint& x,
			     const Grid_Generator& y) {
  // Scalar product is only defined if `x' and `y' are
  // dimension-compatible.
  PPL_ASSERT(x.size() <= y.size());
  z = 0;
  for (dimension_type i = x.size(); i-- > 0; )
    // The following line optimizes the computation of z += x[i] * y[i].
    add_mul_assign(z, x[i], y[i]);
}

void
PPL::Scalar_Products::assign(Coefficient& z,
			     const Congruence& x, const Grid_Generator& y) {
  // Scalar product is only defined if `x' and `y' are
  // dimension-compatible.
  PPL_ASSERT(x.size() <= y.size());
  z = 0;
  for (dimension_type i = x.size() - 1; i-- > 0; )
    // The following line optimizes the computation of z += x[i] *
    // y[i].
    add_mul_assign(z, x[i], y[i]);
}

void
PPL::Scalar_Products::reduced_assign(Coefficient& z,
				     const Linear_Row& x,
				     const Linear_Row& y) {
  // The reduced scalar product is only defined
  // if the topology of `x' is NNC and `y' has enough coefficients.
  PPL_ASSERT(!x.is_necessarily_closed());
  PPL_ASSERT(x.size() - 1 <= y.size());
  z = 0;
  for (dimension_type i = x.size() - 1; i-- > 0; )
    // The following line optimizes the computation of z += x[i] * y[i].
    add_mul_assign(z, x[i], y[i]);
}

void
PPL::Scalar_Products::reduced_assign(Coefficient& z,
				     const Grid_Generator& x,
				     const Congruence& y) {
  // The reduced scalar product is only defined if the topology of `x'
  // is NNC and `y' has enough coefficients.
  PPL_ASSERT(x.size() <= y.size());
  z = 0;
  for (dimension_type i = x.size() - 1; i-- > 0; )
    // The following line optimizes z += x[i] * y[i].
    add_mul_assign(z, x[i], y[i]);
}

void
PPL::Scalar_Products::homogeneous_assign(Coefficient& z,
					 const Linear_Row& x,
					 const Linear_Row& y) {
  // Scalar product is only defined  if `x' and `y' are
  // dimension-compatible.
  PPL_ASSERT(x.size() <= y.size());
  z = 0;
  // Note the pre-decrement of `i': last iteration should be for `i == 1'.
  for (dimension_type i = x.size(); --i > 0; )
    // The following line optimizes the computation of z += x[i] * y[i].
    add_mul_assign(z, x[i], y[i]);
}

void
PPL::Scalar_Products::homogeneous_assign(Coefficient& z,
					 const Grid_Generator& x,
					 const Congruence& y) {
  // Scalar product is only defined if `x' and `y' are
  // dimension-compatible.
  PPL_ASSERT(x.size() <= y.size());
  z = 0;
  // Note the pre-decrement of `i': last iteration should be for `i == 1'.
  for (dimension_type i = x.size() - 1; --i > 0; )
    // The following line optimizes the computation of z += x[i] * y[i].
    add_mul_assign(z, x[i], y[i]);
}

void
PPL::Scalar_Products::homogeneous_assign(Coefficient& z,
					 const Grid_Generator& x,
					 const Constraint& y) {
  // Scalar product is only defined if `x' and `y' are
  // dimension-compatible.
  PPL_ASSERT(x.size() - 1 <= y.size());
  z = 0;
  // Note the pre-decrement of `i': last iteration should be for `i == 1'.
  for (dimension_type i = x.size() - 1; --i > 0; )
    // The following line optimizes the computation of z += x[i] * y[i].
    add_mul_assign(z, x[i], y[i]);
}
