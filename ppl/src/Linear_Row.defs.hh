/* Linear_Row class declaration.
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

#ifndef PPL_Linear_Row_defs_hh
#define PPL_Linear_Row_defs_hh 1

#include "Linear_Row.types.hh"
#include "globals.defs.hh"
#include "Row.defs.hh"
#include "Topology.hh"
#include "Linear_Expression.types.hh"
#include "Constraint.types.hh"
#include "Generator.types.hh"

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
//! The base class for linear expressions, constraints and generators.
/*! \ingroup PPL_CXX_interface
  The class Linear_Row allows us to build objects of the form
  \f$[b, a_0, \ldots, a_{d-1}]_{(t, k)}\f$,
  i.e., a finite sequence of coefficients subscripted by a pair of flags,
  which are both stored in a Linear_Row::Flags object.
  The flag \f$t \in \{ \mathrm{c}, \mathrm{nnc} \}\f$ represents
  the <EM>topology</EM> and
  the flag \f$k \in \{\mathord{=}, \mathord{\geq} \}\f$ represents
  the <EM>kind</EM> of the Linear_Row object.
  Note that, even though all the four possible combinations of topology
  and kind values will result in a legal Linear_Row::Flags object, some
  of these pose additional constraints on the values of the Linear_Row's
  coefficients.

  When \f$t = c\f$, we have the following cases
  (\f$d\f$ is the dimension of the vector space):
    - \f$[b, a_0, \ldots, a_{d-1}]_{(c,=)}\f$
      represents the equality constraint
      \f$\sum_{i=0}^{d-1} a_i x_i + b = 0\f$.
    - \f$[b, a_0, \ldots, a_{d-1}]_{(c,\geq)}\f$
      represents the non-strict inequality constraint
      \f$\sum_{i=0}^{d-1} a_i x_i + b \geq 0\f$.
    - \f$[0, a_0, \ldots, a_{d-1}]_{(c,=)}\f$
      represents the line of direction
      \f$\vect{l} = (a_0, \ldots, a_{d-1})^\transpose\f$.
    - \f$[0, a_0, \ldots, a_{d-1}]_{(c,\geq)}\f$
      represents the ray of direction
      \f$\vect{r} = (a_0, \ldots, a_{d-1})^\transpose\f$.
    - \f$[b, a_0, \ldots, a_{d-1}]_{(c,\geq)}\f$, with \f$b > 0\f$,
      represents the point
      \f$\vect{p} = (\frac{a_0}{b}, \ldots, \frac{a_{d-1}}{b})^\transpose\f$.

  When \f$t = \mathrm{nnc}\f$, the last coefficient of the Linear_Row is
  associated to the slack variable \f$\epsilon\f$, so that we have the
  following cases (\f$d\f$ is again the dimension of the vector space,
  but this time we have \f$d+2\f$ coefficients):
    - \f$[b, a_0, \ldots, a_{d-1}, 0]_{(\mathrm{nnc},=)}\f$
      represents the equality constraint
      \f$\sum_{i=0}^{d-1} a_i x_i + b = 0\f$.
    - \f$[b, a_0, \ldots, a_{d-1}, 0]_{(\mathrm{nnc},\geq)}\f$
      represents the non-strict inequality constraint
      \f$\sum_{i=0}^{d-1} a_i x_i + b \geq 0\f$.
    - \f$[b, a_0, \ldots, a_{d-1}, e]_{(\mathrm{nnc},\geq)}\f$,
      with \f$e < 0\f$, represents the strict inequality constraint
      \f$\sum_{i=0}^{d-1} a_i x_i + b > 0\f$.
    - \f$[0, a_0, \ldots, a_{d-1}, 0]_{(\mathrm{nnc},=)}\f$
      represents the line of direction
      \f$\vect{l} = (a_0, \ldots, a_{d-1})^\transpose\f$.
    - \f$[0, a_0, \ldots, a_{d-1}, 0]_{(\mathrm{nnc},\geq)}\f$
      represents the ray of direction
      \f$\vect{r} = (a_0, \ldots, a_{d-1})^\transpose\f$.
    - \f$[b, a_0, \ldots, a_{d-1}, e]_{(\mathrm{nnc},\geq)}\f$,
      with \f$b > 0\f$ and \f$e > 0\f$, represents the point
      \f$\vect{p} = (\frac{a_0}{b}, \ldots, \frac{a_{d-1}}{b})^\transpose\f$.
    - \f$[b, a_0, \ldots, a_{d-1}, 0]_{(\mathrm{nnc},\geq)}\f$,
      with \f$b > 0\f$, represents the closure point
      \f$\vect{c} = (\frac{a_0}{b}, \ldots, \frac{a_{d-1}}{b})^\transpose\f$.

  So, a Linear_Row can be both a constraint and a generator: it can be an
  equality, a strict or non-strict inequality, a line, a ray, a point
  or a closure point.

  The inhomogeneous term of a constraint can be zero or different from zero.

  Points and closure points must have a positive inhomogeneous term
  (which is used as a common divisor for all the other coefficients),
  lines and rays must have the inhomogeneous term equal to zero.
  If needed, the coefficients of points and closure points are negated
  at creation time so that they satisfy this invariant.
  The invariant is maintained because, when combining a point or closure
  point with another generator, we only consider positive combinations.

  The \f$\epsilon\f$ coefficient, when present, is negative for strict
  inequality constraints, positive for points and equal to zero in all
  the other cases.
  Note that the above description corresponds to the end-user, high-level
  view of a Linear_Row object. In the implementation, to allow for code reuse,
  it is sometimes useful to regard an \f$\mathrm{nnc}\f$-object on
  the vector space \f$\Rset^d\f$ as if it was a \f$\mathrm{c}\f$-object
  on the vector space \f$\Rset^{d+1}\f$, therefore interpreting the slack
  variable \f$\epsilon\f$ as an ordinary dimension of the vector space.

  A Linear_Row object implementing a Linear_Expression is always of the form
  \f$[0, a_0, \ldots, a_{d-1}]_{(c,=)}\f$, which represents the
  linear expression \f$\sum_{i=0}^{d-1} a_i x_i\f$.
*/
#endif // defined(PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS)

class Parma_Polyhedra_Library::Linear_Row : public Row {
public:
  //! The possible kinds of Linear_Row objects.
  enum Kind {
    LINE_OR_EQUALITY = 0,
    RAY_OR_POINT_OR_INEQUALITY = 1
  };

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
  /*! \brief
    The type of the object to which the coefficients refer to,
    encoding both topology and kind.

    \ingroup PPL_CXX_interface
    This combines the information about the topology (necessarily closed
    or not) and the kind (line/equality or ray/point/inequality)
    of a Linear_Row object.
  */
#endif // defined(PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS)
  class Flags : public Row::Flags {
  public:
    //! Default constructor: builds an object where all flags are invalid.
    Flags();

    //! Builds an object corresponding to the topology \p t.
    explicit Flags(Topology t);

    //! Builds an object corresponding to the topology \p t and kind \p k.
    Flags(Topology t, Kind k);

    //! \name Testing and setting the type
    //@{
    Topology topology() const;
    bool is_necessarily_closed() const;
    bool is_not_necessarily_closed() const;
    bool is_line_or_equality() const;
    bool is_ray_or_point_or_inequality() const;

    void set_necessarily_closed();
    void set_not_necessarily_closed();
    void set_is_line_or_equality();
    void set_is_ray_or_point_or_inequality();
    //@} // Testing and setting the type

    //! Returns <CODE>true</CODE> if and only if \p *this and \p y are equal.
    bool operator==(const Flags& y) const;

    /*! \brief
      Returns <CODE>true</CODE> if and only if \p *this and \p y
      are different.
    */
    bool operator!=(const Flags& y) const;

    PPL_OUTPUT_DECLARATIONS

    /*! \brief
      Loads from \p s an ASCII representation (as produced by
      ascii_dump(std::ostream&) const) and sets \p *this accordingly.
      Returns <CODE>true</CODE> if successful, <CODE>false</CODE> otherwise.
    */
    bool ascii_load(std::istream& s);

  private:
    //! Builds the type from a bit-mask.
    explicit Flags(base_type mask);

    //! \name The bits that are currently in use
    //@{
    // NB: ascii_load assumes that these are sequential.
    static const unsigned rpi_validity_bit
    = Row::Flags::first_free_bit + 0;
    static const unsigned rpi_bit
    = Row::Flags::first_free_bit + 1;
    static const unsigned nnc_validity_bit
    = Row::Flags::first_free_bit + 2;
    static const unsigned nnc_bit
    = Row::Flags::first_free_bit + 3;
    //@}

  protected:
    //! Index of the first bit derived classes can use.
    static const unsigned first_free_bit
    = Row::Flags::first_free_bit + 4;

    friend class Parma_Polyhedra_Library::Linear_Row;
  };

  //! Pre-constructs a row: construction must be completed by construct().
  Linear_Row();

  //! \name Post-constructors
  //@{
  //! Constructs properly a default-constructed element.
  /*!
    Builds a row with type \p t, size \p sz and minimum capacity.
  */
  void construct(dimension_type sz, Flags f);

  //! Constructs properly a default-constructed element.
  /*!
    \param sz
    The size of the row that will be constructed;

    \param capacity
    The minimum capacity of the row that will be constructed.

    \param f
    Flags for the row that will be constructed.

    The row that we are constructing has a minimum capacity, i.e., it
    can contain at least \p capacity elements, \p sz of which will be
    default-constructed now. The row flags are set to \p f.
  */
  void construct(dimension_type sz, dimension_type capacity, Flags f);
  //@} // Post-constructors

  //! Tight constructor: resizing will require reallocation.
  Linear_Row(dimension_type sz, Flags f);

  //! Sizing constructor with capacity.
  Linear_Row(dimension_type sz, dimension_type capacity, Flags f);

  //! Ordinary copy constructor.
  Linear_Row(const Linear_Row& y);

  //! Copy constructor with specified capacity.
  /*!
    It is assumed that \p capacity is greater than or equal to \p y size.
  */
  Linear_Row(const Linear_Row& y, dimension_type capacity);

  //! Copy constructor with specified size and capacity.
  /*!
    It is assumed that \p sz is greater than or equal to the size of \p y
    and, of course, that \p sz is less than or equal to \p capacity.
  */
  Linear_Row(const Linear_Row& y, dimension_type sz, dimension_type capacity);

  //! Destructor.
  ~Linear_Row();

  //! \name Flags inspection methods
  //@{
  //! Returns a const reference to the flags of \p *this.
  const Flags& flags() const;

  //! Returns a non-const reference to the flags of \p *this.
  Flags& flags();

  //! Returns the topological kind of \p *this.
  Topology topology() const;

  /*! \brief
    Returns <CODE>true</CODE> if and only if the topology
    of \p *this row is not necessarily closed.
  */
  bool is_not_necessarily_closed() const;

  /*! \brief
    Returns <CODE>true</CODE> if and only if the topology
    of \p *this row is necessarily closed.
  */
  bool is_necessarily_closed() const;

  /*! \brief
    Returns <CODE>true</CODE> if and only if \p *this row
    represents a line or an equality.
  */
  bool is_line_or_equality() const;

  /*! \brief
    Returns <CODE>true</CODE> if and only if \p *this row
    represents a ray, a point or an inequality.
  */
  bool is_ray_or_point_or_inequality() const;
  //@} // Flags inspection methods

  //! \name Flags coercion methods
  //@{
  //! Sets to \p NECESSARILY_CLOSED the topological kind of \p *this row.
  void set_necessarily_closed();

  //! Sets to \p NOT_NECESSARILY_CLOSED the topological kind of \p *this row.
  void set_not_necessarily_closed();

  //! Sets to \p LINE_OR_EQUALITY the kind of \p *this row.
  void set_is_line_or_equality();

  //! Sets to \p RAY_OR_POINT_OR_INEQUALITY the kind of \p *this row.
  void set_is_ray_or_point_or_inequality();
  //@} // Flags coercion methods

  //! Returns the maximum space dimension a Linear_Row can handle.
  static dimension_type max_space_dimension();

  //! Returns the dimension of the vector space enclosing \p *this.
  dimension_type space_dimension() const;

  //! Returns the inhomogeneous term.
  Coefficient_traits::const_reference inhomogeneous_term() const;

  //! Returns the coefficient \f$a_n\f$.
  Coefficient_traits::const_reference coefficient(dimension_type n) const;

  /*! \brief
    Normalizes the sign of the coefficients so that the first non-zero
    (homogeneous) coefficient of a line-or-equality is positive.
  */
  void sign_normalize();

  /*! \brief
    Strong normalization: ensures that different Linear_Row objects
    represent different hyperplanes or hyperspaces.

    Applies both Linear_Row::normalize() and Linear_Row::sign_normalize().
  */
  void strong_normalize();

  /*! \brief
    Returns <CODE>true</CODE> if and only if the coefficients are
    strongly normalized.
  */
  bool check_strong_normalized() const;

  //! Linearly combines \p *this with \p y so that <CODE>*this[k]</CODE> is 0.
  /*!
    \param y
    The Linear_Row that will be combined with \p *this object;

    \param k
    The position of \p *this that have to be \f$0\f$.

    Computes a linear combination of \p *this and \p y having
    the element of index \p k equal to \f$0\f$. Then it assigns
    the resulting Linear_Row to \p *this and normalizes it.
  */
  void linear_combine(const Linear_Row& y, dimension_type k);

  /*! \brief
    Returns <CODE>true</CODE> if and only if all the
    terms of \p *this are \f$0\f$.
  */
  bool is_zero() const;

  /*! \brief
    Returns <CODE>true</CODE> if and only if all the homogeneous
    terms of \p *this are \f$0\f$.
  */
  bool all_homogeneous_terms_are_zero() const;

  PPL_OUTPUT_DECLARATIONS

  /*! \brief
    Loads from \p s an ASCII representation (as produced by
    ascii_dump(std::ostream&) const) and sets \p *this accordingly.
    Returns <CODE>true</CODE> if successful, <CODE>false</CODE> otherwise.
  */
  bool ascii_load(std::istream& s);

  //! Checks if all the invariants are satisfied.
  bool OK() const;

  /*! \brief
    Checks if all the invariants are satisfied and that the actual
    size and capacity match the values provided as arguments.
  */
  bool OK(dimension_type row_size, dimension_type row_capacity) const;

private:
  friend class Parma_Polyhedra_Library::Linear_Expression;
  friend class Parma_Polyhedra_Library::Constraint;
  friend class Parma_Polyhedra_Library::Generator;
};

namespace Parma_Polyhedra_Library {

//! Returns <CODE>true</CODE> if and only if \p x and \p y are equal.
/*! \relates Linear_Row */
bool operator==(const Linear_Row& x, const Linear_Row& y);

//! Returns <CODE>true</CODE> if and only if \p x and \p y are different.
/*! \relates Linear_Row */
bool operator!=(const Linear_Row& x, const Linear_Row& y);

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
//! The basic comparison function.
/*! \relates Linear_Row
  \return
  The returned absolute value can be \f$0\f$, \f$1\f$ or \f$2\f$.

  \param x
  A row of coefficients;

  \param y
  Another row.

  Compares \p x and \p y, where \p x and \p y may be of different size,
  in which case the "missing" coefficients are assumed to be zero.
  The comparison is such that:
  -# equalities are smaller than inequalities;
  -# lines are smaller than points and rays;
  -# the ordering is lexicographic;
  -# the positions compared are, in decreasing order of significance,
     1, 2, ..., \p size(), 0;
  -# the result is negative, zero, or positive if x is smaller than,
     equal to, or greater than y, respectively;
  -# when \p x and \p y are different, the absolute value of the
     result is 1 if the difference is due to the coefficient in
     position 0; it is 2 otherwise.

  When \p x and \p y represent the hyper-planes associated
  to two equality or inequality constraints, the coefficient
  at 0 is the known term.
  In this case, the return value can be characterized as follows:
  - -2, if \p x is smaller than \p y and they are \e not parallel;
  - -1, if \p x is smaller than \p y and they \e are parallel;
  -  0, if \p x and y are equal;
  - +1, if \p y is smaller than \p x and they \e are parallel;
  - +2, if \p y is smaller than \p x and they are \e not parallel.
*/
#endif // defined(PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS)
int compare(const Linear_Row& x, const Linear_Row& y);

} // namespace Parma_Polyhedra_Library


namespace std {

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
//! Specializes <CODE>std::swap</CODE>.
/*! \relates Parma_Polyhedra_Library::Linear_Row */
#endif // defined(PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS)
void swap(Parma_Polyhedra_Library::Linear_Row& x,
	  Parma_Polyhedra_Library::Linear_Row& y);

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
//! Specializes <CODE>std::iter_swap</CODE>.
/*! \relates Parma_Polyhedra_Library::Linear_Row */
#endif // defined(PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS)
void iter_swap(std::vector<Parma_Polyhedra_Library::Linear_Row>::iterator x,
	       std::vector<Parma_Polyhedra_Library::Linear_Row>::iterator y);

} // namespace std

#include "Linear_Row.inlines.hh"

#endif // !defined(PPL_Linear_Row_defs_hh)
