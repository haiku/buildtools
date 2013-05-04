/* Constraint class declaration.
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

#ifndef PPL_Constraint_defs_hh
#define PPL_Constraint_defs_hh 1

#include "Constraint.types.hh"
#include "Scalar_Products.types.hh"
#include "Linear_Row.defs.hh"
#include "Variable.defs.hh"
#include "Linear_Expression.defs.hh"
#include "Constraint_System.defs.hh"
#include "Polyhedron.types.hh"
#include "Congruence.types.hh"
#include <iosfwd>

namespace Parma_Polyhedra_Library {

// Put them in the namespace here to declare them friend later.

//! Returns <CODE>true</CODE> if and only if \p x is equivalent to \p y.
/*! \relates Constraint */
bool
operator==(const Constraint& x, const Constraint& y);

//! Returns <CODE>true</CODE> if and only if \p x is not equivalent to \p y.
/*! \relates Constraint */
bool
operator!=(const Constraint& x, const Constraint& y);

//! Returns the constraint \p e1 = \p e2.
/*! \relates Constraint */
Constraint
operator==(const Linear_Expression& e1, const Linear_Expression& e2);

//! Returns the constraint \p v1 = \p v2.
/*! \relates Constraint */
Constraint
operator==(Variable v1, Variable v2);

//! Returns the constraint \p e = \p n.
/*! \relates Constraint */
Constraint
operator==(const Linear_Expression& e, Coefficient_traits::const_reference n);

//! Returns the constraint \p n = \p e.
/*! \relates Constraint */
Constraint
operator==(Coefficient_traits::const_reference n, const Linear_Expression& e);

//! Returns the constraint \p e1 \<= \p e2.
/*! \relates Constraint */
Constraint
operator<=(const Linear_Expression& e1, const Linear_Expression& e2);

//! Returns the constraint \p v1 \<= \p v2.
/*! \relates Constraint */
Constraint
operator<=(Variable v1, Variable v2);

//! Returns the constraint \p e \<= \p n.
/*! \relates Constraint */
Constraint
operator<=(const Linear_Expression& e, Coefficient_traits::const_reference n);

//! Returns the constraint \p n \<= \p e.
/*! \relates Constraint */
Constraint
operator<=(Coefficient_traits::const_reference n, const Linear_Expression& e);

//! Returns the constraint \p e1 \>= \p e2.
/*! \relates Constraint */
Constraint
operator>=(const Linear_Expression& e1, const Linear_Expression& e2);

//! Returns the constraint \p v1 \>= \p v2.
/*! \relates Constraint */
Constraint
operator>=(Variable v1, Variable v2);

//! Returns the constraint \p e \>= \p n.
/*! \relates Constraint */
Constraint
operator>=(const Linear_Expression& e, Coefficient_traits::const_reference n);

//! Returns the constraint \p n \>= \p e.
/*! \relates Constraint */
Constraint
operator>=(Coefficient_traits::const_reference n, const Linear_Expression& e);

//! Returns the constraint \p e1 \< \p e2.
/*! \relates Constraint */
Constraint
operator<(const Linear_Expression& e1, const Linear_Expression& e2);

//! Returns the constraint \p v1 \< \p v2.
/*! \relates Constraint */
Constraint
operator<(Variable v1, Variable v2);

//! Returns the constraint \p e \< \p n.
/*! \relates Constraint */
Constraint
operator<(const Linear_Expression& e, Coefficient_traits::const_reference n);

//! Returns the constraint \p n \< \p e.
/*! \relates Constraint */
Constraint
operator<(Coefficient_traits::const_reference n, const Linear_Expression& e);

//! Returns the constraint \p e1 \> \p e2.
/*! \relates Constraint */
Constraint
operator>(const Linear_Expression& e1, const Linear_Expression& e2);

//! Returns the constraint \p v1 \> \p v2.
/*! \relates Constraint */
Constraint
operator>(Variable v1, Variable v2);

//! Returns the constraint \p e \> \p n.
/*! \relates Constraint */
Constraint
operator>(const Linear_Expression& e, Coefficient_traits::const_reference n);

//! Returns the constraint \p n \> \p e.
/*! \relates Constraint */
Constraint
operator>(Coefficient_traits::const_reference n, const Linear_Expression& e);

} // namespace Parma_Polyhedra_Library


namespace std {

//! Specializes <CODE>std::swap</CODE>.
/*! \relates Parma_Polyhedra_Library::Constraint */
void swap(Parma_Polyhedra_Library::Constraint& x,
	  Parma_Polyhedra_Library::Constraint& y);

} // namespace std

//! A linear equality or inequality.
/*! \ingroup PPL_CXX_interface
  An object of the class Constraint is either:
  - an equality: \f$\sum_{i=0}^{n-1} a_i x_i + b = 0\f$;
  - a non-strict inequality: \f$\sum_{i=0}^{n-1} a_i x_i + b \geq 0\f$; or
  - a strict inequality: \f$\sum_{i=0}^{n-1} a_i x_i + b > 0\f$;

  where \f$n\f$ is the dimension of the space,
  \f$a_i\f$ is the integer coefficient of variable \f$x_i\f$
  and \f$b\f$ is the integer inhomogeneous term.

  \par How to build a constraint
  Constraints are typically built by applying a relation symbol
  to a pair of linear expressions.
  Available relation symbols are equality (<CODE>==</CODE>),
  non-strict inequalities (<CODE>\>=</CODE> and <CODE>\<=</CODE>) and
  strict inequalities (<CODE>\<</CODE> and <CODE>\></CODE>).
  The space dimension of a constraint is defined as the maximum
  space dimension of the arguments of its constructor.

  \par
  In the following examples it is assumed that variables
  <CODE>x</CODE>, <CODE>y</CODE> and <CODE>z</CODE>
  are defined as follows:
  \code
  Variable x(0);
  Variable y(1);
  Variable z(2);
  \endcode

  \par Example 1
  The following code builds the equality constraint
  \f$3x + 5y - z = 0\f$, having space dimension \f$3\f$:
  \code
  Constraint eq_c(3*x + 5*y - z == 0);
  \endcode
  The following code builds the (non-strict) inequality constraint
  \f$4x \geq 2y - 13\f$, having space dimension \f$2\f$:
  \code
  Constraint ineq_c(4*x >= 2*y - 13);
  \endcode
  The corresponding strict inequality constraint
  \f$4x > 2y - 13\f$ is obtained as follows:
  \code
  Constraint strict_ineq_c(4*x > 2*y - 13);
  \endcode
  An unsatisfiable constraint on the zero-dimension space \f$\Rset^0\f$
  can be specified as follows:
  \code
  Constraint false_c = Constraint::zero_dim_false();
  \endcode
  Equivalent, but more involved ways are the following:
  \code
  Constraint false_c1(Linear_Expression::zero() == 1);
  Constraint false_c2(Linear_Expression::zero() >= 1);
  Constraint false_c3(Linear_Expression::zero() > 0);
  \endcode
  In contrast, the following code defines an unsatisfiable constraint
  having space dimension \f$3\f$:
  \code
  Constraint false_c(0*z == 1);
  \endcode

  \par How to inspect a constraint
  Several methods are provided to examine a constraint and extract
  all the encoded information: its space dimension, its type
  (equality, non-strict inequality, strict inequality) and
  the value of its integer coefficients.

  \par Example 2
  The following code shows how it is possible to access each single
  coefficient of a constraint. Given an inequality constraint
  (in this case \f$x - 5y + 3z \leq 4\f$), we construct a new constraint
  corresponding to its complement (thus, in this case we want to obtain
  the strict inequality constraint \f$x - 5y + 3z > 4\f$).
  \code
  Constraint c1(x - 5*y + 3*z <= 4);
  cout << "Constraint c1: " << c1 << endl;
  if (c1.is_equality())
    cout << "Constraint c1 is not an inequality." << endl;
  else {
    Linear_Expression e;
    for (dimension_type i = c1.space_dimension(); i-- > 0; )
      e += c1.coefficient(Variable(i)) * Variable(i);
    e += c1.inhomogeneous_term();
    Constraint c2 = c1.is_strict_inequality() ? (e <= 0) : (e < 0);
    cout << "Complement c2: " << c2 << endl;
  }
  \endcode
  The actual output is the following:
  \code
  Constraint c1: -A + 5*B - 3*C >= -4
  Complement c2: A - 5*B + 3*C > 4
  \endcode
  Note that, in general, the particular output obtained can be
  syntactically different from the (semantically equivalent)
  constraint considered.
*/
class Parma_Polyhedra_Library::Constraint : private Linear_Row {
public:
  //! Ordinary copy constructor.
  Constraint(const Constraint& c);

  //! Copy-constructs from equality congruence \p cg.
  /*!
    \exception std::invalid_argument
    Thrown if \p cg is a proper congruence.
  */
  explicit Constraint(const Congruence& cg);

  //! Destructor.
  ~Constraint();

  //! Assignment operator.
  Constraint& operator=(const Constraint& c);

  //! Returns the maximum space dimension a Constraint can handle.
  static dimension_type max_space_dimension();

  //! Returns the dimension of the vector space enclosing \p *this.
  dimension_type space_dimension() const;

  //! The constraint type.
  enum Type {
    /*! The constraint is an equality. */
    EQUALITY,
    /*! The constraint is a non-strict inequality. */
    NONSTRICT_INEQUALITY,
    /*! The constraint is a strict inequality. */
    STRICT_INEQUALITY
  };

  //! Returns the constraint type of \p *this.
  Type type() const;

  /*! \brief
    Returns <CODE>true</CODE> if and only if
    \p *this is an equality constraint.
  */
  bool is_equality() const;

  /*! \brief
    Returns <CODE>true</CODE> if and only if
    \p *this is an inequality constraint (either strict or non-strict).
  */
  bool is_inequality() const;

  /*! \brief
    Returns <CODE>true</CODE> if and only if
    \p *this is a non-strict inequality constraint.
  */
  bool is_nonstrict_inequality() const;

  /*! \brief
    Returns <CODE>true</CODE> if and only if
    \p *this is a strict inequality constraint.
  */
  bool is_strict_inequality() const;

  //! Returns the coefficient of \p v in \p *this.
  /*!
    \exception std::invalid_argument thrown if the index of \p v
    is greater than or equal to the space dimension of \p *this.
  */
  Coefficient_traits::const_reference coefficient(Variable v) const;

  //! Returns the inhomogeneous term of \p *this.
  Coefficient_traits::const_reference inhomogeneous_term() const;

  //! Initializes the class.
  static void initialize();

  //! Finalizes the class.
  static void finalize();

  //! The unsatisfiable (zero-dimension space) constraint \f$0 = 1\f$.
  static const Constraint& zero_dim_false();

  /*! \brief
    The true (zero-dimension space) constraint \f$0 \leq 1\f$,
    also known as <EM>positivity constraint</EM>.
  */
  static const Constraint& zero_dim_positivity();

  /*! \brief
    Returns a lower bound to the total size in bytes of the memory
    occupied by \p *this.
  */
  memory_size_type total_memory_in_bytes() const;

  //! Returns the size in bytes of the memory managed by \p *this.
  memory_size_type external_memory_in_bytes() const;

  /*! \brief
    Returns <CODE>true</CODE> if and only if
    \p *this is a tautology (i.e., an always true constraint).

    A tautology can have either one of the following forms:
    - an equality: \f$\sum_{i=0}^{n-1} 0 x_i + 0 = 0\f$; or
    - a non-strict inequality: \f$\sum_{i=0}^{n-1} 0 x_i + b \geq 0\f$,
      where \f$b \geq 0\f$; or
    - a strict inequality: \f$\sum_{i=0}^{n-1} 0 x_i + b > 0\f$,
      where \f$b > 0\f$.
  */
  bool is_tautological() const;

  /*! \brief
    Returns <CODE>true</CODE> if and only if
    \p *this is inconsistent (i.e., an always false constraint).

    An inconsistent constraint can have either one of the following forms:
    - an equality: \f$\sum_{i=0}^{n-1} 0 x_i + b = 0\f$,
      where \f$b \neq 0\f$; or
    - a non-strict inequality: \f$\sum_{i=0}^{n-1} 0 x_i + b \geq 0\f$,
      where \f$b < 0\f$; or
    - a strict inequality: \f$\sum_{i=0}^{n-1} 0 x_i + b > 0\f$,
      where \f$b \leq 0\f$.
  */
  bool is_inconsistent() const;

  /*! \brief
    Returns <CODE>true</CODE> if and only if \p *this and \p y
    are equivalent constraints.

    Constraints having different space dimensions are not equivalent.
    Note that constraints having different types may nonetheless be
    equivalent, if they both are tautologies or inconsistent.
  */
  bool is_equivalent_to(const Constraint& y) const;

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
  void swap(Constraint& y);

private:
  /*! \brief
    Holds (between class initialization and finalization) a pointer to
    the unsatisfiable (zero-dimension space) constraint \f$0 = 1\f$.
  */
  static const Constraint* zero_dim_false_p;

  /*! \brief
    Holds (between class initialization and finalization) a pointer to
    the true (zero-dimension space) constraint \f$0 \leq 1\f$, also
    known as <EM>positivity constraint</EM>.
  */
  static const Constraint* zero_dim_positivity_p;

  /*! \brief
    Holds (between class initialization and finalization) a pointer to
    the zero-dimension space constraint \f$\epsilon \geq 0\f$.
  */
  static const Constraint* epsilon_geq_zero_p;

  /*! \brief
    Holds (between class initialization and finalization) a pointer to
    the zero-dimension space constraint \f$\epsilon \leq 1\f$
    (used to implement NNC polyhedra).
  */
  static const Constraint* epsilon_leq_one_p;

  friend class Parma_Polyhedra_Library::Congruence;
  friend class Parma_Polyhedra_Library::Scalar_Products;
  friend class Parma_Polyhedra_Library::Topology_Adjusted_Scalar_Product_Sign;
  friend class Parma_Polyhedra_Library::Constraint_System;
  friend class Parma_Polyhedra_Library::Constraint_System::const_iterator;
  // FIXME: the following friend declaration should be avoided.
  friend class Parma_Polyhedra_Library::Polyhedron;

  friend
  Parma_Polyhedra_Library
  ::Linear_Expression::Linear_Expression(const Constraint& c);

  //! Default constructor: private and not implemented.
  Constraint();

  /*! \brief
    Builds a constraint of type \p type and topology \p topology,
    stealing the coefficients from \p e.
  */
  Constraint(Linear_Expression& e, Type type, Topology topology);

  //! Constructs from a congruence, with specified size and capacity.
  Constraint(const Congruence& cg, dimension_type sz, dimension_type capacity);

  /*! \brief
    Throws a <CODE>std::invalid_argument</CODE> exception containing
    error message \p message.
  */
  void
  throw_invalid_argument(const char* method, const char* message) const;

  /*! \brief
    Throws a <CODE>std::invalid_argument</CODE> exception
    containing the appropriate error message.
  */
  void
  throw_dimension_incompatible(const char* method,
			       const char* name_var,
			       Variable v) const;

  friend Constraint
  operator==(const Linear_Expression& e1, const Linear_Expression& e2);
  friend Constraint
  operator==(Variable v1, Variable v2);
  friend Constraint
  operator==(const Linear_Expression& e, Coefficient_traits::const_reference n);
  friend Constraint
  operator==(Coefficient_traits::const_reference n, const Linear_Expression& e);

  friend Constraint
  operator>=(const Linear_Expression& e1, const Linear_Expression& e2);
  friend Constraint
  operator>=(Variable v1, Variable v2);
  friend Constraint
  operator>=(const Linear_Expression& e, Coefficient_traits::const_reference n);
  friend Constraint
  operator>=(Coefficient_traits::const_reference n, const Linear_Expression& e);

  friend Constraint
  operator<=(const Linear_Expression& e1, const Linear_Expression& e2);
  friend Constraint
  operator<=(const Linear_Expression& e, Coefficient_traits::const_reference n);
  friend Constraint
  operator<=(Coefficient_traits::const_reference n, const Linear_Expression& e);

  friend Constraint
  operator>(const Linear_Expression& e1, const Linear_Expression& e2);
  friend Constraint
  operator>(Variable v1, Variable v2);
  friend Constraint
  operator>(const Linear_Expression& e, Coefficient_traits::const_reference n);
  friend Constraint
  operator>(Coefficient_traits::const_reference n, const Linear_Expression& e);

  friend Constraint
  operator<(const Linear_Expression& e1, const Linear_Expression& e2);
  friend Constraint
  operator<(const Linear_Expression& e, Coefficient_traits::const_reference n);
  friend Constraint
  operator<(Coefficient_traits::const_reference n, const Linear_Expression& e);

  //! Copy constructor with given size.
  Constraint(const Constraint& c, dimension_type sz);

  /*! \brief
    Builds a new copy of the zero-dimension space constraint
    \f$\epsilon \geq 0\f$ (used to implement NNC polyhedra).
  */
  static Constraint construct_epsilon_geq_zero();

  //! Returns the zero-dimension space constraint \f$\epsilon \geq 0\f$.
  static const Constraint& epsilon_geq_zero();

  /*! \brief
    The zero-dimension space constraint \f$\epsilon \leq 1\f$
    (used to implement NNC polyhedra).
  */
  static const Constraint& epsilon_leq_one();

  //! Sets the constraint type to <CODE>EQUALITY</CODE>.
  void set_is_equality();

  //! Sets the constraint to be an inequality.
  /*!
    Whether the constraint type will become <CODE>NONSTRICT_INEQUALITY</CODE>
    or <CODE>STRICT_INEQUALITY</CODE> depends on the topology and the value
    of the low-level coefficients of the constraint.
  */
  void set_is_inequality();
};

namespace Parma_Polyhedra_Library {

namespace IO_Operators {

//! Output operator.
/*! \relates Parma_Polyhedra_Library::Constraint */
std::ostream& operator<<(std::ostream& s, const Constraint& c);

//! Output operator.
/*! \relates Parma_Polyhedra_Library::Constraint */
std::ostream& operator<<(std::ostream& s, const Constraint::Type& t);

} // namespace IO_Operators

} // namespace Parma_Polyhedra_Library

#include "Constraint.inlines.hh"

#endif // !defined(PPL_Constraint_defs_hh)
