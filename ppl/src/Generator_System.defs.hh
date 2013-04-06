/* Generator_System class declaration.
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

#ifndef PPL_Generator_System_defs_hh
#define PPL_Generator_System_defs_hh 1

#include "Generator_System.types.hh"
#include "Grid_Generator_System.types.hh"
#include "Linear_Expression.types.hh"
#include "Linear_System.defs.hh"
#include "Generator.types.hh"
#include "Constraint.types.hh"
#include "Polyhedron.types.hh"
#include "Poly_Con_Relation.defs.hh"
#include <iosfwd>

namespace Parma_Polyhedra_Library {

namespace IO_Operators {

//! Output operator.
/*!
  \relates Parma_Polyhedra_Library::Generator_System
  Writes <CODE>false</CODE> if \p gs is empty.  Otherwise, writes on
  \p s the generators of \p gs, all in one row and separated by ", ".
*/
std::ostream& operator<<(std::ostream& s, const Generator_System& gs);

} // namespace IO_Operators

// Put it in the namespace here to declare it friend later.
/*! \relates Polyhedron */
bool operator==(const Polyhedron& x, const Polyhedron& y);

} // namespace Parma_Polyhedra_Library


namespace std {

//! Specializes <CODE>std::swap</CODE>.
/*! \relates Parma_Polyhedra_Library::Generator_System */
void swap(Parma_Polyhedra_Library::Generator_System& x,
	  Parma_Polyhedra_Library::Generator_System& y);

} // namespace std

//! A system of generators.
/*! \ingroup PPL_CXX_interface
    An object of the class Generator_System is a system of generators,
    i.e., a multiset of objects of the class Generator
    (lines, rays, points and closure points).
    When inserting generators in a system, space dimensions are automatically
    adjusted so that all the generators in the system are defined
    on the same vector space.
    A system of generators which is meant to define a non-empty
    polyhedron must include at least one point: the reason is that
    lines, rays and closure points need a supporting point
    (lines and rays only specify directions while closure points only
    specify points in the topological closure of the NNC polyhedron).

    \par
     In all the examples it is assumed that variables
    <CODE>x</CODE> and <CODE>y</CODE> are defined as follows:
    \code
  Variable x(0);
  Variable y(1);
    \endcode

    \par Example 1
    The following code defines the line having the same direction
    as the \f$x\f$ axis (i.e., the first Cartesian axis)
    in \f$\Rset^2\f$:
    \code
  Generator_System gs;
  gs.insert(line(x + 0*y));
    \endcode
    As said above, this system of generators corresponds to
    an empty polyhedron, because the line has no supporting point.
    To define a system of generators that does correspond to
    the \f$x\f$ axis, we can add the following code which
    inserts the origin of the space as a point:
    \code
  gs.insert(point(0*x + 0*y));
    \endcode
    Since space dimensions are automatically adjusted, the following
    code obtains the same effect:
    \code
  gs.insert(point(0*x));
    \endcode
    In contrast, if we had added the following code, we would have
    defined a line parallel to the \f$x\f$ axis through
    the point \f$(0, 1)^\transpose \in \Rset^2\f$.
    \code
  gs.insert(point(0*x + 1*y));
    \endcode

    \par Example 2
    The following code builds a ray having the same direction as
    the positive part of the \f$x\f$ axis in \f$\Rset^2\f$:
    \code
  Generator_System gs;
  gs.insert(ray(x + 0*y));
    \endcode
    To define a system of generators indeed corresponding to the set
    \f[
      \bigl\{\,
        (x, 0)^\transpose \in \Rset^2
      \bigm|
        x \geq 0
      \,\bigr\},
    \f]
    one just has to add the origin:
    \code
  gs.insert(point(0*x + 0*y));
    \endcode

    \par Example 3
    The following code builds a system of generators having four points
    and corresponding to a square in \f$\Rset^2\f$
    (the same as Example 1 for the system of constraints):
    \code
  Generator_System gs;
  gs.insert(point(0*x + 0*y));
  gs.insert(point(0*x + 3*y));
  gs.insert(point(3*x + 0*y));
  gs.insert(point(3*x + 3*y));
    \endcode

    \par Example 4
    By using closure points, we can define the \e kernel
    (i.e., the largest open set included in a given set)
    of the square defined in the previous example.
    Note that a supporting point is needed and, for that purpose,
    any inner point could be considered.
    \code
  Generator_System gs;
  gs.insert(point(x + y));
  gs.insert(closure_point(0*x + 0*y));
  gs.insert(closure_point(0*x + 3*y));
  gs.insert(closure_point(3*x + 0*y));
  gs.insert(closure_point(3*x + 3*y));
    \endcode

    \par Example 5
    The following code builds a system of generators having two points
    and a ray, corresponding to a half-strip in \f$\Rset^2\f$
    (the same as Example 2 for the system of constraints):
    \code
  Generator_System gs;
  gs.insert(point(0*x + 0*y));
  gs.insert(point(0*x + 1*y));
  gs.insert(ray(x - y));
    \endcode

    \note
    After inserting a multiset of generators in a generator system,
    there are no guarantees that an <EM>exact</EM> copy of them
    can be retrieved:
    in general, only an <EM>equivalent</EM> generator system
    will be available, where original generators may have been
    reordered, removed (if they are duplicate or redundant), etc.
*/
class Parma_Polyhedra_Library::Generator_System : protected Linear_System {
public:
  //! Default constructor: builds an empty system of generators.
  Generator_System();

  //! Builds the singleton system containing only generator \p g.
  explicit Generator_System(const Generator& g);

  //! Ordinary copy constructor.
  Generator_System(const Generator_System& gs);

  //! Destructor.
  ~Generator_System();

  //! Assignment operator.
  Generator_System& operator=(const Generator_System& y);

  //! Returns the maximum space dimension a Generator_System can handle.
  static dimension_type max_space_dimension();

  //! Returns the dimension of the vector space enclosing \p *this.
  dimension_type space_dimension() const;

  /*! \brief
    Removes all the generators from the generator system
    and sets its space dimension to 0.
  */
  void clear();

  /*! \brief
    Inserts in \p *this a copy of the generator \p g,
    increasing the number of space dimensions if needed.
  */
  void insert(const Generator& g);

  //! Initializes the class.
  static void initialize();

  //! Finalizes the class.
  static void finalize();

  /*! \brief
    Returns the singleton system containing only Generator::zero_dim_point().
  */
  static const Generator_System& zero_dim_univ();

  //! An iterator over a system of generators
  /*! \ingroup PPL_CXX_interface
      A const_iterator is used to provide read-only access
      to each generator contained in an object of Generator_System.

      \par Example
      The following code prints the system of generators
      of the polyhedron <CODE>ph</CODE>:
      \code
  const Generator_System& gs = ph.generators();
  for (Generator_System::const_iterator i = gs.begin(),
         gs_end = gs.end(); i != gs_end; ++i)
    cout << *i << endl;
      \endcode
      The same effect can be obtained more concisely by using
      more features of the STL:
      \code
  const Generator_System& gs = ph.generators();
  copy(gs.begin(), gs.end(), ostream_iterator<Generator>(cout, "\n"));
      \endcode
  */
  class const_iterator
    : public std::iterator<std::forward_iterator_tag,
			   Generator,
			   ptrdiff_t,
			   const Generator*,
			   const Generator&> {
  public:
    //! Default constructor.
    const_iterator();

    //! Ordinary copy constructor.
    const_iterator(const const_iterator& y);

    //! Destructor.
    ~const_iterator();

    //! Assignment operator.
    const_iterator& operator=(const const_iterator& y);

    //! Dereference operator.
    const Generator& operator*() const;

    //! Indirect member selector.
    const Generator* operator->() const;

    //! Prefix increment operator.
    const_iterator& operator++();

    //! Postfix increment operator.
    const_iterator operator++(int);

    /*! \brief
      Returns <CODE>true</CODE> if and only if
      \p *this and \p y are identical.
    */
    bool operator==(const const_iterator& y) const;

    /*! \brief
      Returns <CODE>true</CODE> if and only if
      \p *this and \p y are different.
    */
    bool operator!=(const const_iterator& y) const;

  private:
    friend class Generator_System;

    //! The const iterator over the Linear_System.
    Linear_System::const_iterator i;

    //! A const pointer to the Linear_System.
    const Linear_System* gsp;

    //! Constructor.
    const_iterator(const Linear_System::const_iterator& iter,
		   const Generator_System& gsys);

    /*! \brief
      \p *this skips to the next generator, skipping those
      closure points that are immediately followed by a matching point.
    */
    void skip_forward();
  };

  //! Returns <CODE>true</CODE> if and only if \p *this has no generators.
  bool empty() const;

  /*! \brief
    Returns the const_iterator pointing to the first generator,
    if \p *this is not empty;
    otherwise, returns the past-the-end const_iterator.
  */
  const_iterator begin() const;

  //! Returns the past-the-end const_iterator.
  const_iterator end() const;

  //! Checks if all the invariants are satisfied.
  /*!
    Returns <CODE>true</CODE> if and only if \p *this is a valid
    Linear_System and each row in the system is a valid Generator.
  */
  bool OK() const;

  PPL_OUTPUT_DECLARATIONS

  /*! \brief
    Loads from \p s an ASCII representation (as produced by
    ascii_dump(std::ostream&) const) and sets \p *this accordingly.
    Returns <CODE>true</CODE> if successful, <CODE>false</CODE> otherwise.

    Resizes the matrix of generators using the numbers of rows and columns
    read from \p s, then initializes the coordinates of each generator
    and its type reading the contents from \p s.
  */
  bool ascii_load(std::istream& s);

  //! Returns the total size in bytes of the memory occupied by \p *this.
  memory_size_type total_memory_in_bytes() const;

  //! Returns the size in bytes of the memory managed by \p *this.
  memory_size_type external_memory_in_bytes() const;

  //! Swaps \p *this with \p y.
  void swap(Generator_System& y);

private:
  /*! \brief
    Holds (between class initialization and finalization) a pointer to
    the singleton system containing only Generator::zero_dim_point().
  */
  static const Generator_System* zero_dim_univ_p;

  friend class const_iterator;
  friend class Parma_Polyhedra_Library::Polyhedron;
  friend class Parma_Polyhedra_Library::Grid_Generator_System;

  friend bool operator==(const Polyhedron& x, const Polyhedron& y);

  //! Builds an empty system of generators having the specified topology.
  explicit Generator_System(Topology topol);

  /*! \brief
    Builds a system of \p n_rows rays/points on a \p n_columns - 1
    dimensional space (including the \f$\epsilon\f$ dimension, if
    \p topol is <CODE>NOT_NECESSARILY_CLOSED</CODE>).
  */
  Generator_System(Topology topol,
		   dimension_type n_rows, dimension_type n_columns);

  /*! \brief
    Adjusts \p *this so that it matches the topology and
    the number of space dimensions given as parameters
    (adding or removing columns if needed).
    Returns <CODE>false</CODE> if and only if \p topol is
    equal to <CODE>NECESSARILY_CLOSED</CODE> and \p *this
    contains closure points.
  */
  bool adjust_topology_and_space_dimension(Topology topol,
					   dimension_type num_dimensions);

  /*! \brief
    For each unmatched closure point in \p *this, adds the
    corresponding point.

    It is assumed that the topology of \p *this
    is <CODE>NOT_NECESSARILY_CLOSED</CODE>.
  */
  void add_corresponding_points();

  /*! \brief
    Returns <CODE>true</CODE> if and only if \p *this
    contains one or more points.
  */
  bool has_points() const;

  /*! \brief
    For each unmatched point in \p *this, adds the corresponding
    closure point.

    It is assumed that the topology of \p *this
    is <CODE>NOT_NECESSARILY_CLOSED</CODE>.
  */
  void add_corresponding_closure_points();

  /*! \brief
    Returns <CODE>true</CODE> if and only if \p *this
    contains one or more closure points.

    Note: the check for the presence of closure points is
    done under the point of view of the user. Namely, we scan
    the generator system using high-level iterators, so that
    closure points that are matching the corresponding points
    will be disregarded.
  */
  bool has_closure_points() const;

  //! Returns the \p k- th generator of the system.
  Generator& operator[](dimension_type k);

  //! Returns a constant reference to the \p k- th generator of the system.
  const Generator& operator[](dimension_type k) const;

  /*! \brief
    Returns the relations holding between the generator system
    and the constraint \p c.
  */
  Parma_Polyhedra_Library::Poly_Con_Relation
  relation_with(const Constraint& c) const;

  //! Returns <CODE>true</CODE> if all the generators satisfy \p c.
  bool satisfied_by_all_generators(const Constraint& c) const;

  //! Returns <CODE>true</CODE> if all the generators satisfy \p c.
  /*!
    It is assumed that <CODE>c.is_necessarily_closed()</CODE> holds.
  */
  bool satisfied_by_all_generators_C(const Constraint& c) const;

  //! Returns <CODE>true</CODE> if all the generators satisfy \p c.
  /*!
    It is assumed that <CODE>c.is_necessarily_closed()</CODE> does not hold.
  */
  bool satisfied_by_all_generators_NNC(const Constraint& c) const;

  //! Assigns to a given variable an affine expression.
  /*!
    \param v
    Index of the column to which the affine transformation is assigned;

    \param expr
    The numerator of the affine transformation:
    \f$\sum_{i = 0}^{n - 1} a_i x_i + b\f$;

    \param denominator
    The denominator of the affine transformation.

    We want to allow affine transformations (see the Introduction) having
    any rational coefficients. Since the coefficients of the
    constraints are integers we must also provide an integer \p denominator
    that will be used as denominator of the affine transformation.
    The denominator is required to be a positive integer.

    The affine transformation assigns to each element of \p v -th
    column the follow expression:
    \f[
      \frac{\sum_{i = 0}^{n - 1} a_i x_i + b}
           {\mathrm{denominator}}.
    \f]

    \p expr is a constant parameter and unaltered by this computation.
  */
  void affine_image(dimension_type v,
		    const Linear_Expression& expr,
		    Coefficient_traits::const_reference denominator);

  //! Returns the number of lines of the system.
  dimension_type num_lines() const;

  //! Returns the number of rays of the system.
  dimension_type num_rays() const;

  //! Removes all the invalid lines and rays.
  /*!
    The invalid lines and rays are those with all
    the homogeneous terms set to zero.
  */
  void remove_invalid_lines_and_rays();

  /*! \brief
    Applies Gaussian elimination and back-substitution so as
    to provide a partial simplification of the system of generators.

    It is assumed that the system has no pending generators.
  */
  void simplify();

  /*! \brief
    Inserts in \p *this a copy of the generator \p g,
    increasing the number of space dimensions if needed.
    It is a pending generator.
  */
  void insert_pending(const Generator& g);
};

// Generator_System.inlines.hh is not included here on purpose.

#endif // !defined(PPL_Generator_System_defs_hh)
