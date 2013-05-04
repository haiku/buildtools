/* Linear_Expression class declaration.
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

#ifndef PPL_Linear_Expression_defs_hh
#define PPL_Linear_Expression_defs_hh 1

#include "Linear_Expression.types.hh"
#include "Scalar_Products.types.hh"
#include "Constraint.types.hh"
#include "Generator.types.hh"
#include "Congruence.types.hh"
#include "Grid_Generator.types.hh"
#include "Linear_Row.defs.hh"
#include "Coefficient.types.hh"
#include "Variable.defs.hh"
#include "Constraint_System.types.hh"
#include "Generator_System.types.hh"
#include "Congruence_System.types.hh"
#include "Grid_Generator_System.types.hh"
#include "Polyhedron.types.hh"
#include "Grid.types.hh"
#include <cstddef>

namespace Parma_Polyhedra_Library {
// Put them in the namespace here to declare them friend later.

//! Returns the linear expression \p e1 + \p e2.
/*! \relates Linear_Expression */
Linear_Expression
operator+(const Linear_Expression& e1, const Linear_Expression& e2);

//! Returns the linear expression \p v + \p w.
/*! \relates Linear_Expression */
Linear_Expression
operator+(Variable v, Variable w);

//! Returns the linear expression \p v + \p e.
/*! \relates Linear_Expression */
Linear_Expression
operator+(Variable v, const Linear_Expression& e);

//! Returns the linear expression \p e + \p v.
/*! \relates Linear_Expression */
Linear_Expression
operator+(const Linear_Expression& e, Variable v);

//! Returns the linear expression \p n + \p e.
/*! \relates Linear_Expression */
Linear_Expression
operator+(Coefficient_traits::const_reference n, const Linear_Expression& e);

//! Returns the linear expression \p e + \p n.
/*! \relates Linear_Expression */
Linear_Expression
operator+(const Linear_Expression& e, Coefficient_traits::const_reference n);

//! Returns the linear expression \p e.
/*! \relates Linear_Expression */
Linear_Expression
operator+(const Linear_Expression& e);

//! Returns the linear expression - \p e.
/*! \relates Linear_Expression */
Linear_Expression
operator-(const Linear_Expression& e);

//! Returns the linear expression \p e1 - \p e2.
/*! \relates Linear_Expression */
Linear_Expression
operator-(const Linear_Expression& e1, const Linear_Expression& e2);

//! Returns the linear expression \p v - \p w.
/*! \relates Linear_Expression */
Linear_Expression
operator-(Variable v, Variable w);

//! Returns the linear expression \p v - \p e.
/*! \relates Linear_Expression */
Linear_Expression
operator-(Variable v, const Linear_Expression& e);

//! Returns the linear expression \p e - \p v.
/*! \relates Linear_Expression */
Linear_Expression
operator-(const Linear_Expression& e, Variable v);

//! Returns the linear expression \p n - \p e.
/*! \relates Linear_Expression */
Linear_Expression
operator-(Coefficient_traits::const_reference n, const Linear_Expression& e);

//! Returns the linear expression \p e - \p n.
/*! \relates Linear_Expression */
Linear_Expression
operator-(const Linear_Expression& e, Coefficient_traits::const_reference n);

//! Returns the linear expression \p n * \p e.
/*! \relates Linear_Expression */
Linear_Expression
operator*(Coefficient_traits::const_reference n, const Linear_Expression& e);

//! Returns the linear expression \p e * \p n.
/*! \relates Linear_Expression */
Linear_Expression
operator*(const Linear_Expression& e, Coefficient_traits::const_reference n);

//! Returns the linear expression \p e1 + \p e2 and assigns it to \p e1.
/*! \relates Linear_Expression */
Linear_Expression&
operator+=(Linear_Expression& e1, const Linear_Expression& e2);

//! Returns the linear expression \p e + \p v and assigns it to \p e.
/*! \relates Linear_Expression
  \exception std::length_error
  Thrown if the space dimension of \p v exceeds
  <CODE>Linear_Expression::max_space_dimension()</CODE>.
 */
Linear_Expression&
operator+=(Linear_Expression& e, Variable v);

//! Returns the linear expression \p e + \p n and assigns it to \p e.
/*! \relates Linear_Expression */
Linear_Expression&
operator+=(Linear_Expression& e, Coefficient_traits::const_reference n);

//! Returns the linear expression \p e1 - \p e2 and assigns it to \p e1.
/*! \relates Linear_Expression */
Linear_Expression&
operator-=(Linear_Expression& e1, const Linear_Expression& e2);

//! Returns the linear expression \p e - \p v and assigns it to \p e.
/*! \relates Linear_Expression
  \exception std::length_error
  Thrown if the space dimension of \p v exceeds
  <CODE>Linear_Expression::max_space_dimension()</CODE>.
 */
Linear_Expression&
operator-=(Linear_Expression& e, Variable v);

//! Returns the linear expression \p e - \p n and assigns it to \p e.
/*! \relates Linear_Expression */
Linear_Expression&
operator-=(Linear_Expression& e, Coefficient_traits::const_reference n);

//! Returns the linear expression \p n * \p e and assigns it to \p e.
/*! \relates Linear_Expression */
Linear_Expression&
operator*=(Linear_Expression& e, Coefficient_traits::const_reference n);

//! Returns the linear expression \p e + \p n * \p v and assigns it to \p e.
/*! \relates Linear_Expression */
Linear_Expression&
add_mul_assign(Linear_Expression& e,
               Coefficient_traits::const_reference n, Variable v);

//! Returns the linear expression \p e - \p n * \p v and assigns it to \p e.
/*! \relates Linear_Expression */
Linear_Expression&
sub_mul_assign(Linear_Expression& e,
               Coefficient_traits::const_reference n, Variable v);

namespace IO_Operators {

//! Output operator.
/*! \relates Parma_Polyhedra_Library::Linear_Expression */
std::ostream& operator<<(std::ostream& s, const Linear_Expression& e);

} // namespace IO_Operators

} // namespace Parma_Polyhedra_Library


namespace std {

//! Specializes <CODE>std::swap</CODE>.
/*! \relates Parma_Polyhedra_Library::Linear_Expression */
void swap(Parma_Polyhedra_Library::Linear_Expression& x,
	  Parma_Polyhedra_Library::Linear_Expression& y);

} // namespace std

//! A linear expression.
/*! \ingroup PPL_CXX_interface
  An object of the class Linear_Expression represents the linear expression
  \f[
    \sum_{i=0}^{n-1} a_i x_i + b
  \f]
  where \f$n\f$ is the dimension of the vector space,
  each \f$a_i\f$ is the integer coefficient
  of the \f$i\f$-th variable \f$x_i\f$
  and \f$b\f$ is the integer for the inhomogeneous term.

  \par How to build a linear expression.

  Linear expressions are the basic blocks for defining
  both constraints (i.e., linear equalities or inequalities)
  and generators (i.e., lines, rays, points and closure points).
  A full set of functions is defined to provide a convenient interface
  for building complex linear expressions starting from simpler ones
  and from objects of the classes Variable and Coefficient:
  available operators include unary negation,
  binary addition and subtraction,
  as well as multiplication by a Coefficient.
  The space dimension of a linear expression is defined as the maximum
  space dimension of the arguments used to build it:
  in particular, the space dimension of a Variable <CODE>x</CODE>
  is defined as <CODE>x.id()+1</CODE>,
  whereas all the objects of the class Coefficient have space dimension zero.

  \par Example
  The following code builds the linear expression \f$4x - 2y - z + 14\f$,
  having space dimension \f$3\f$:
  \code
  Linear_Expression e = 4*x - 2*y - z + 14;
  \endcode
  Another way to build the same linear expression is:
  \code
  Linear_Expression e1 = 4*x;
  Linear_Expression e2 = 2*y;
  Linear_Expression e3 = z;
  Linear_Expression e = Linear_Expression(14);
  e += e1 - e2 - e3;
  \endcode
  Note that \p e1, \p e2 and \p e3 have space dimension 1, 2 and 3,
  respectively; also, in the fourth line of code, \p e is created
  with space dimension zero and then extended to space dimension 3
  in the fifth line.
*/
class Parma_Polyhedra_Library::Linear_Expression : private Linear_Row {
public:
  //! Default constructor: returns a copy of Linear_Expression::zero().
  Linear_Expression();

  //! Ordinary copy constructor.
  Linear_Expression(const Linear_Expression& e);

  //! Destructor.
  ~Linear_Expression();

  /*! \brief
    Builds the linear expression corresponding
    to the inhomogeneous term \p n.
  */
  explicit Linear_Expression(Coefficient_traits::const_reference n);

  //! Builds the linear expression corresponding to the variable \p v.
  /*!
    \exception std::length_error
    Thrown if the space dimension of \p v exceeds
    <CODE>Linear_Expression::max_space_dimension()</CODE>.
  */
  Linear_Expression(Variable v);

  //! Builds the linear expression corresponding to constraint \p c.
  /*!
    Given the constraint
    \f$c = \bigl(\sum_{i=0}^{n-1} a_i x_i + b \relsym 0\bigr)\f$,
    where \f$\mathord{\relsym} \in \{ =, \geq, > \}\f$,
    this builds the linear expression \f$\sum_{i=0}^{n-1} a_i x_i + b\f$.
    If \p c is an inequality (resp., equality) constraint, then
    the built linear expression is unique up to a positive
    (resp., non-zero) factor.
  */
  explicit Linear_Expression(const Constraint& c);

  /*! \brief
    Builds the linear expression corresponding to generator \p g
    (for points and closure points, the divisor is not copied).

    Given the generator
    \f$g = (\frac{a_0}{d}, \ldots, \frac{a_{n-1}}{d})^\transpose\f$
    (where, for lines and rays, we have \f$d = 1\f$),
    this builds the linear expression \f$\sum_{i=0}^{n-1} a_i x_i\f$.
    The inhomogeneous term of the linear expression will always be 0.
    If \p g is a ray, point or closure point (resp., a line), then
    the linear expression is unique up to a positive
    (resp., non-zero) factor.
  */
  explicit Linear_Expression(const Generator& g);

  /*! \brief
    Builds the linear expression corresponding to grid generator \p g
    (for points, parameters and lines the divisor is not copied).

    Given the grid generator
    \f$g = (\frac{a_0}{d}, \ldots, \frac{a_{n-1}}{d})^\transpose\f$
    this builds the linear expression \f$\sum_{i=0}^{n-1} a_i x_i\f$.
    The inhomogeneous term of the linear expression is always 0.
  */
  explicit Linear_Expression(const Grid_Generator& g);

  //! Builds the linear expression corresponding to congruence \p cg.
  /*!
    Given the congruence
    \f$cg = \bigl(\sum_{i=0}^{n-1} a_i x_i + b = 0 \pmod{m}\bigr)\f$,
    this builds the linear expression \f$\sum_{i=0}^{n-1} a_i x_i + b\f$.
  */
  explicit Linear_Expression(const Congruence& cg);

  //! Returns the maximum space dimension a Linear_Expression can handle.
  static dimension_type max_space_dimension();

  //! Returns the dimension of the vector space enclosing \p *this.
  dimension_type space_dimension() const;

  //! Returns the coefficient of \p v in \p *this.
  Coefficient_traits::const_reference coefficient(Variable v) const;

  //! Returns the inhomogeneous term of \p *this.
  Coefficient_traits::const_reference inhomogeneous_term() const;

  //! Returns <CODE>true</CODE> if and only if \p *this is \f$0\f$.
  bool is_zero() const;

  /*! \brief
    Returns <CODE>true</CODE> if and only if all the homogeneous
    terms of \p *this are \f$0\f$.
  */
  bool all_homogeneous_terms_are_zero() const;

  //! Initializes the class.
  static void initialize();

  //! Finalizes the class.
  static void finalize();

  //! Returns the (zero-dimension space) constant 0.
  static const Linear_Expression& zero();

  /*! \brief
    Returns a lower bound to the total size in bytes of the memory
    occupied by \p *this.
  */
  memory_size_type total_memory_in_bytes() const;

  //! Returns the size in bytes of the memory managed by \p *this.
  memory_size_type external_memory_in_bytes() const;

  PPL_OUTPUT_DECLARATIONS

  /*! \brief
    Loads from \p s an ASCII representation (as produced by
    ascii_dump(std::ostream&) const) and sets \p *this accordingly.
    Returns <CODE>true</CODE> if successful, <CODE>false</CODE> otherwise.
  */
  bool ascii_load(std::istream& s);

  //! Checks if all the invariants are satisfied.
  bool OK() const;

  //! Swaps \p *this with \p y.
  void swap(Linear_Expression& y);

private:
  /*! \brief
    Holds (between class initialization and finalization) a pointer to
    the (zero-dimension space) constant 0.
  */
  static const Linear_Expression* zero_p;

  friend class Parma_Polyhedra_Library::Scalar_Products;
  friend class Parma_Polyhedra_Library::Constraint;
  friend class Parma_Polyhedra_Library::Generator;
  // The following declaration grants access to Grid_Generator::parameter.
  friend class Parma_Polyhedra_Library::Grid_Generator;
  friend class Parma_Polyhedra_Library::Congruence;
  // FIXME: the following friend declaration should be avoided.
  friend class Parma_Polyhedra_Library::Polyhedron;
  friend class Parma_Polyhedra_Library::Grid;

  // FIXME: the following friend declaration is only to grant access to
  // Constraint_System::affine_preimage().
  friend class Parma_Polyhedra_Library::Constraint_System;

  // FIXME: the following friend declaration is only to grant access to
  // Generator_System::affine_image().
  friend class Parma_Polyhedra_Library::Generator_System;

  // FIXME: the following friend declaration is only to grant access to
  // Congruence_System::affine_preimage().
  friend class Parma_Polyhedra_Library::Congruence_System;

  // FIXME: the following friend declaration is only to grant access to
  // Grid_Generator_System::affine_image().
  friend class Parma_Polyhedra_Library::Grid_Generator_System;

  //! Copy constructor with a specified space dimension.
  Linear_Expression(const Linear_Expression& e, dimension_type sz);

  //! Implementation sizing constructor.
  /*!
    The bool parameter is just to avoid problems with
    the constructor Linear_Expression(Coefficient_traits::const_reference n).
  */
  Linear_Expression(dimension_type sz, bool);

  /*! \brief
    Builds the linear expression corresponding to the difference of
    \p v and \p w.

    \exception std::length_error
    Thrown if the space dimension of \p v or the one of \p w exceed
    <CODE>Linear_Expression::max_space_dimension()</CODE>.
  */
  Linear_Expression(Variable v, Variable w);

  friend Linear_Expression
  operator+(const Linear_Expression& e1, const Linear_Expression& e2);
  friend Linear_Expression
  operator+(Coefficient_traits::const_reference n, const Linear_Expression& e);
  friend Linear_Expression
  operator+(const Linear_Expression& e, Coefficient_traits::const_reference n);
  friend Linear_Expression
  operator+(Variable v, const Linear_Expression& e);
  friend Linear_Expression
  operator+(Variable v, Variable w);

  friend Linear_Expression
  operator-(const Linear_Expression& e);

  friend Linear_Expression
  operator-(const Linear_Expression& e1, const Linear_Expression& e2);
  friend Linear_Expression
  operator-(Variable v, Variable w);
  friend Linear_Expression
  operator-(Coefficient_traits::const_reference n, const Linear_Expression& e);
  friend Linear_Expression
  operator-(const Linear_Expression& e, Coefficient_traits::const_reference n);
  friend Linear_Expression
  operator-(Variable v, const Linear_Expression& e);
  friend Linear_Expression
  operator-(const Linear_Expression& e, Variable v);

  friend Linear_Expression
  operator*(Coefficient_traits::const_reference n, const Linear_Expression& e);
  friend Linear_Expression
  operator*(const Linear_Expression& e, Coefficient_traits::const_reference n);

  friend Linear_Expression&
  operator+=(Linear_Expression& e1, const Linear_Expression& e2);
  friend Linear_Expression&
  operator+=(Linear_Expression& e, Variable v);
  friend Linear_Expression&
  operator+=(Linear_Expression& e, Coefficient_traits::const_reference n);

  friend Linear_Expression&
  operator-=(Linear_Expression& e1, const Linear_Expression& e2);
  friend Linear_Expression&
  operator-=(Linear_Expression& e, Variable v);
  friend Linear_Expression&
  operator-=(Linear_Expression& e, Coefficient_traits::const_reference n);

  friend Linear_Expression&
  operator*=(Linear_Expression& e, Coefficient_traits::const_reference n);

  friend Linear_Expression&
  add_mul_assign(Linear_Expression& e,
                 Coefficient_traits::const_reference n, Variable v);
  friend Linear_Expression&
  sub_mul_assign(Linear_Expression& e,
                 Coefficient_traits::const_reference n, Variable v);

  friend std::ostream&
  Parma_Polyhedra_Library::IO_Operators
  ::operator<<(std::ostream& s, const Linear_Expression& e);
};

#include "Linear_Expression.inlines.hh"

#endif // !defined(PPL_Linear_Expression_defs_hh)
