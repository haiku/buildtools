/* PIP_Problem class implementation: inline functions.
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

#ifndef PPL_PIP_Problem_inlines_hh
#define PPL_PIP_Problem_inlines_hh 1

namespace Parma_Polyhedra_Library {

inline dimension_type
PIP_Problem::space_dimension() const {
  return external_space_dim;
}

inline dimension_type
PIP_Problem::max_space_dimension() {
  return Constraint::max_space_dimension();
}

inline PIP_Problem::const_iterator
PIP_Problem::constraints_begin() const {
  return input_cs.begin();
}

inline PIP_Problem::const_iterator
PIP_Problem::constraints_end() const {
  return input_cs.end();
}

inline const Variables_Set&
PIP_Problem::parameter_space_dimensions() const {
  return parameters;
}

inline void
PIP_Problem::swap(PIP_Problem& y) {
  std::swap(external_space_dim, y.external_space_dim);
  std::swap(internal_space_dim, y.internal_space_dim);
  std::swap(status, y.status);
  std::swap(current_solution, y.current_solution);
  std::swap(input_cs, y.input_cs);
  std::swap(first_pending_constraint, y.first_pending_constraint);
  std::swap(parameters, y.parameters);
  std::swap(initial_context, y.initial_context);
  for (dimension_type i = CONTROL_PARAMETER_NAME_SIZE; i-- > 0; )
    std::swap(control_parameters[i], y.control_parameters[i]);
  std::swap(big_parameter_dimension, y.big_parameter_dimension);
}

inline PIP_Problem&
PIP_Problem::operator=(const PIP_Problem& y) {
  PIP_Problem tmp(y);
  swap(tmp);
  return *this;
}

inline PIP_Problem::Control_Parameter_Value
PIP_Problem::get_control_parameter(Control_Parameter_Name n) const {
  PPL_ASSERT(n >= 0 && n < CONTROL_PARAMETER_NAME_SIZE);
  return control_parameters[n];
}

inline dimension_type
PIP_Problem::get_big_parameter_dimension() const {
  return big_parameter_dimension;
}

} // namespace Parma_Polyhedra_Library

namespace std {

/*! \relates Parma_Polyhedra_Library::PIP_Problem */
inline void
swap(Parma_Polyhedra_Library::PIP_Problem& x,
     Parma_Polyhedra_Library::PIP_Problem& y) {
  x.swap(y);
}

} // namespace std

#endif // !defined(PPL_PIP_Problem_inlines_hh)
