/* Linear_System class declaration.
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

#ifndef PPL_Linear_System_defs_hh
#define PPL_Linear_System_defs_hh 1

#include "Linear_System.types.hh"
#include "Row.types.hh"
#include "Bit_Row.types.hh"
#include "Bit_Matrix.types.hh"
#include "Matrix.defs.hh"
#include "Topology.hh"
#include "Linear_Row.defs.hh"

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
//! The base class for systems of constraints and generators.
/*! \ingroup PPL_CXX_interface
  An object of this class represents either a constraint system
  or a generator system. Each Linear_System object can be viewed
  as a finite sequence of strong-normalized Linear_Row objects,
  where each Linear_Row implements a constraint or a generator.
  Linear systems are characterized by the matrix of coefficients,
  also encoding the number, size and capacity of Linear_row objects,
  as well as a few additional information, including:
   - the topological kind of (all) the rows;
   - an indication of whether or not some of the rows in the Linear_System
     are <EM>pending</EM>, meaning that they still have to undergo
     an (unspecified) elaboration; if there are pending rows, then these
     form a proper suffix of the overall sequence of rows;
   - a Boolean flag that, when <CODE>true</CODE>, ensures that the
     non-pending prefix of the sequence of rows is sorted.
*/
#endif // defined(PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS)

class Parma_Polyhedra_Library::Linear_System : public Matrix {
public:
  //! Builds an empty linear system with specified topology.
  /*!
    Rows size and capacity are initialized to \f$0\f$.
  */
  Linear_System(Topology topol);

  //! Builds a system with specified topology and dimensions.
  /*!
    \param topol
    The topology of the system that will be created;

    \param n_rows
    The number of rows of the system that will be created;

    \param n_columns
    The number of columns of the system that will be created.

    Creates a \p n_rows \f$\times\f$ \p n_columns system whose
    coefficients are all zero and whose rows are all initialized
    to be of the given topology.
  */
  Linear_System(Topology topol,
		dimension_type n_rows, dimension_type n_columns);

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
  //! A tag class.
  /*! \ingroup PPL_CXX_interface
    Tag class to differentiate the Linear_System copy constructor that
    copies pending rows as pending from the one that transforms
    pending rows into non-pending ones.
  */
#endif // defined(PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS)
  struct With_Pending {
  };

  //! Copy constructor: pending rows are transformed into non-pending ones.
  Linear_System(const Linear_System& y);

  //! Full copy constructor: pending rows are copied as pending.
  Linear_System(const Linear_System& y, With_Pending);

  //! Assignment operator: pending rows are transformed into non-pending ones.
  Linear_System& operator=(const Linear_System& y);

  //! Full assignment operator: pending rows are copied as pending.
  void assign_with_pending(const Linear_System& y);

  //! Swaps \p *this with \p y.
  void swap(Linear_System& y);

  //! Returns the maximum space dimension a Linear_System can handle.
  static dimension_type max_space_dimension();

  //! Returns the space dimension of the rows in the system.
  /*!
    The computation of the space dimension correctly ignores
    the column encoding the inhomogeneous terms of constraint
    (resp., the divisors of generators);
    if the system topology is <CODE>NOT_NECESSARILY_CLOSED</CODE>,
    also the column of the \f$\epsilon\f$-dimension coefficients
    will be ignored.
  */
  dimension_type space_dimension() const;

  //! Makes the system shrink by removing its \p n trailing columns.
  void remove_trailing_columns(dimension_type n);

  //! Permutes the columns of the system.
  /*
    \param cycles
    A vector representing the non-trivial cycles of the permutation
    according to which the columns must be rearranged.

    The \p cycles vector contains, one after the other, the
    non-trivial cycles (i.e., the cycles of length greater than one)
    of a permutation of non-zero column indexes.  Each cycle is
    terminated by zero.  For example, assuming the system has 6
    columns, the permutation \f$ \{ 1 \mapsto 3, 2 \mapsto 4,
    3 \mapsto 6, 4 \mapsto 2, 5 \mapsto 5, 6 \mapsto 1 \}\f$ can be
    represented by the non-trivial cycles \f$(1 3 6)(2 4)\f$ that, in
    turn can be represented by a vector of 6 elements containing 1, 3,
    6, 0, 2, 4, 0.
  */
  void permute_columns(const std::vector<dimension_type>& cycles);

  //! \name Subscript operators
  //@{
  //! Returns a reference to the \p k-th row of the system.
  Linear_Row& operator[](dimension_type k);

  //! Returns a constant reference to the \p k-th row of the system.
  const Linear_Row& operator[](dimension_type k) const;
  //@} // Subscript operators

  //! Strongly normalizes the system.
  void strong_normalize();

  //! Sign-normalizes the system.
  void sign_normalize();

  //! \name Accessors
  //@{
  //! Returns the system topology.
  Topology topology() const;

  //! Returns the value of the sortedness flag.
  bool is_sorted() const;

  /*! \brief
    Returns <CODE>true</CODE> if and only if
    the system topology is <CODE>NECESSARILY_CLOSED</CODE>.
  */
  bool is_necessarily_closed() const;

  /*! \brief
    Returns the number of rows in the system
    that represent either lines or equalities.
  */
  dimension_type num_lines_or_equalities() const;

  //! Returns the index of the first pending row.
  dimension_type first_pending_row() const;

  //! Returns the number of rows that are in the pending part of the system.
  dimension_type num_pending_rows() const;
  //@} // Accessors

  /*! \brief
    Returns <CODE>true</CODE> if and only if \p *this is sorted,
    without checking for duplicates.
  */
  bool check_sorted() const;

  //! Sets the system topology to <CODE>NECESSARILY_CLOSED</CODE>.
  void set_necessarily_closed();

  //! Sets the system topology to <CODE>NOT_NECESSARILY_CLOSED</CODE>.
  void set_not_necessarily_closed();

  //! Sets the topology of all rows equal to the system topology.
  void set_rows_topology();

  //! Sets the index to indicate that the system has no pending rows.
  void unset_pending_rows();

  //! Sets the index of the first pending row to \p i.
  void set_index_first_pending_row(dimension_type i);

  //! Sets the sortedness flag of the system to \p b.
  void set_sorted(bool b);

  //! Resizes the system without worrying about the old contents.
  /*!
    \param new_n_rows
    The number of rows of the resized system;

    \param new_n_columns
    The number of columns of the resized system.

    The system is expanded to the specified dimensions avoiding
    reallocation whenever possible.
    The contents of the original system is lost.
  */
  void resize_no_copy(dimension_type new_n_rows, dimension_type new_n_columns);

  //! Adds \p n rows and columns to the system.
  /*!
    \param n
    The number of rows and columns to be added: must be strictly positive.

    Turns the system \f$M \in \Rset^r \times \Rset^c\f$ into
    the system \f$N \in \Rset^{r+n} \times \Rset^{c+n}\f$
    such that
    \f$N = \bigl(\genfrac{}{}{0pt}{}{0}{M}\genfrac{}{}{0pt}{}{J}{o}\bigr)\f$,
    where \f$J\f$ is the specular image
    of the \f$n \times n\f$ identity matrix.
  */
  void add_rows_and_columns(dimension_type n);

  /*! \brief
    Adds a copy of \p r to the system,
    automatically resizing the system or the row's copy, if needed.
  */
  void insert(const Linear_Row& r);

  /*! \brief
    Adds a copy of the given row to the pending part of the system,
    automatically resizing the system or the row, if needed.
  */
  void insert_pending(const Linear_Row& r);

  //! Adds a copy of the given row to the system.
  void add_row(const Linear_Row& r);

  //! Adds a new empty row to the system, setting only its flags.
  void add_pending_row(Linear_Row::Flags flags);

  //! Adds a copy of the given row to the pending part of the system.
  void add_pending_row(const Linear_Row& r);

  //! Adds to \p *this a copy of the rows of `y'.
  /*!
    It is assumed that \p *this has no pending rows.
  */
  void add_rows(const Linear_System& y);

  //! Adds a copy of the rows of `y' to the pending part of `*this'.
  void add_pending_rows(const Linear_System& y);

  /*! \brief
    Sorts the non-pending rows (in growing order) and eliminates
    duplicated ones.
  */
  void sort_rows();

  /*! \brief
    Sorts the rows (in growing order) form \p first_row to
    \p last_row and eliminates duplicated ones.
  */
  void sort_rows(dimension_type first_row, dimension_type last_row);

  /*! \brief
    Assigns to \p *this the result of merging its rows with
    those of \p y, obtaining a sorted system.

    Duplicated rows will occur only once in the result.
    On entry, both systems are assumed to be sorted and have
    no pending rows.
  */
  void merge_rows_assign(const Linear_System& y);

  /*! \brief
    Sorts the pending rows and eliminates those that also occur
    in the non-pending part of the system.
  */
  void sort_pending_and_remove_duplicates();

  class With_Bit_Matrix_iterator;

  /*! \brief
    Sorts the system, removing duplicates, keeping the saturation
    matrix consistent.

    \param sat
    Bit matrix with rows corresponding to the rows of \p *this.
  */
  void sort_and_remove_with_sat(Bit_Matrix& sat);

  //! Minimizes the subsystem of equations contained in \p *this.
  /*!
    This method works only on the equalities of the system:
    the system is required to be partially sorted, so that
    all the equalities are grouped at its top; it is assumed that
    the number of equalities is exactly \p n_lines_or_equalities.
    The method finds a minimal system for the equalities and
    returns its rank, i.e., the number of linearly independent equalities.
    The result is an upper triangular subsystem of equalities:
    for each equality, the pivot is chosen starting from
    the right-most columns.
  */
  dimension_type gauss(dimension_type n_lines_or_equalities);

  /*! \brief
    Back-substitutes the coefficients to reduce
    the complexity of the system.

    Takes an upper triangular system having \p n_lines_or_equalities rows.
    For each row, starting from the one having the minimum number of
    coefficients different from zero, computes the expression of an element
    as a function of the remaining ones and then substitutes this expression
    in all the other rows.
  */
  void back_substitute(dimension_type n_lines_or_equalities);

  /*! \brief
    Applies Gaussian elimination and back-substitution so as to
    simplify the linear system.
  */
  void simplify();

  /*! \brief
    Normalizes the system by dividing each row for the GCD of the
    row's elements.
  */
  void normalize();

  //! Clears the system deallocating all its rows.
  void clear();

  PPL_OUTPUT_DECLARATIONS

  /*! \brief
    Loads from \p s an ASCII representation (as produced by
    ascii_dump(std::ostream&) const) and sets \p *this accordingly.
    Returns <CODE>true</CODE> if successful, <CODE>false</CODE> otherwise.

    Reads into a Linear_System object the information produced by the
    output of ascii_dump(std::ostream&) const.  The specialized methods
    provided by Constraint_System and Generator_System take care of
    properly reading the contents of the system.
  */
  bool ascii_load(std::istream& s);

  //! Returns the total size in bytes of the memory occupied by \p *this.
  memory_size_type total_memory_in_bytes() const;

  //! Returns the size in bytes of the memory managed by \p *this.
  memory_size_type external_memory_in_bytes() const;

  //! Checks if all the invariants are satisfied.
  /*!
    \param check_strong_normalized
    <CODE>true</CODE> if and only if the strong normalization of all
    the rows in the system has to be checked.

    By default, the strong normalization check is performed.
    This check may be turned off to avoid useless repeated checking;
    e.g., when re-checking a well-formed Linear_System after the permutation
    or deletion of some of its rows.
  */
  bool OK(bool check_strong_normalized = true) const;

private:
  //! The topological kind of the rows in the system.
  Topology row_topology;

  //! The index of the first pending row.
  dimension_type index_first_pending;

  /*! \brief
    <CODE>true</CODE> if rows are sorted in the ascending order as defined by
    <CODE>bool compare(const Linear_Row&, const Linear_Row&)</CODE>.
    If <CODE>false</CODE> may not be sorted.
  */
  bool sorted;

  //! Ordering predicate (used when implementing the sort algorithm).
  struct Row_Less_Than {
    bool operator()(const Row& x, const Row& y) const;
  };
};

namespace std {

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
//! Specializes <CODE>std::swap</CODE>.
/*! \relates Parma_Polyhedra_Library::Linear_System */
#endif // defined(PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS)
void swap(Parma_Polyhedra_Library::Linear_System& x,
	  Parma_Polyhedra_Library::Linear_System& y);

} // namespace std

namespace Parma_Polyhedra_Library {

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
//! Returns <CODE>true</CODE> if and only if \p x and \p y are identical.
/*! \relates Linear_System */
#endif // defined(PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS)
bool operator==(const Linear_System& x, const Linear_System& y);

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
//! Returns <CODE>true</CODE> if and only if \p x and \p y are different.
/*! \relates Linear_System */
#endif // defined(PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS)
bool operator!=(const Linear_System& x, const Linear_System& y);

} // namespace Parma_Polyhedra_Library

#include "Linear_System.inlines.hh"

#endif // !defined(PPL_Linear_System_defs_hh)
