/* Bit_Matrix class declaration.
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

#ifndef PPL_Bit_Matrix_defs_hh
#define PPL_Bit_Matrix_defs_hh 1

#include "Bit_Matrix.types.hh"
#include "Linear_System.defs.hh"
#include "Bit_Row.defs.hh"
#include <vector>
#include <iosfwd>

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
//! A matrix of bits.
/*! \ingroup PPL_CXX_interface */
#endif // defined(PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS)
class Parma_Polyhedra_Library::Bit_Matrix {
public:
  //! Default constructor.
  Bit_Matrix();

  //! Construct a bit matrix with \p n_rows rows and \p n_columns columns.
  Bit_Matrix(dimension_type n_rows, dimension_type n_columns);

  //! Copy constructor.
  Bit_Matrix(const Bit_Matrix& y);

  //! Destructor.
  ~Bit_Matrix();

  //! Assignment operator.
  Bit_Matrix& operator=(const Bit_Matrix& y);

  //! Swaps \p *this with \p y.
  void swap(Bit_Matrix& y);

  //! Subscript operator.
  Bit_Row& operator[](dimension_type k);

  //! Constant subscript operator.
  const Bit_Row& operator[](dimension_type k) const;

  //! Clears the matrix deallocating all its rows.
  void clear();

  //! Transposes the matrix.
  void transpose();

  //! Makes \p *this a transposed copy of \p y.
  void transpose_assign(const Bit_Matrix& y);

  //! Returns the maximum number of rows of a Bit_Matrix.
  static dimension_type max_num_rows();

  //! Returns the number of columns of \p *this.
  dimension_type num_columns() const;

  //! Returns the number of rows of \p *this.
  dimension_type num_rows() const;

  //! Sorts the rows and removes duplicates.
  void sort_rows();

  //! Looks for \p row in \p *this, which is assumed to be sorted.
  /*!
    \return
    <CODE>true</CODE> if \p row belongs to \p *this, false otherwise.

    \param row
    The row that will be searched for in the matrix.

    Given a sorted bit matrix (this ensures better efficiency),
    tells whether it contains the given row.
  */
  bool sorted_contains(const Bit_Row& row) const;

  //! Adds \p row to \p *this.
  /*!
    \param row
    The row whose implementation will be recycled.

    The only thing that can be done with \p row upon return is destruction.
  */
  void add_recycled_row(Bit_Row& row);

  //! Erases the rows from the \p first_to_erase -th to the last one.
  void rows_erase_to_end(dimension_type first_to_erase);

  //! Erases the columns from the \p first_to_erase -th to the last one.
  void columns_erase_to_end(dimension_type first_to_erase);

  //! Resizes the matrix copying the old contents.
  void resize(dimension_type new_n_rows, dimension_type new_n_columns);

  //! Checks if all the invariants are satisfied.
  bool OK() const;

  PPL_OUTPUT_DECLARATIONS

  /*! \brief
    Loads from \p s an ASCII representation (as produced by
    ascii_dump(std::ostream&) const) and sets \p *this accordingly.
    Returns <CODE>true</CODE> if successful, <CODE>false</CODE> otherwise.
  */
  bool ascii_load(std::istream& s);

  //! Returns the total size in bytes of the memory occupied by \p *this.
  memory_size_type total_memory_in_bytes() const;

  //! Returns the size in bytes of the memory managed by \p *this.
  memory_size_type external_memory_in_bytes() const;

#ifndef NDEBUG
  //! Checks whether \p *this is sorted. It does NOT check for duplicates.
  bool check_sorted() const;
#endif

private:
  //! Contains the rows of the matrix.
  std::vector<Bit_Row> rows;

  //! Size of the initialized part of each row.
  dimension_type row_size;

  //! Ordering predicate (used when implementing the sort algorithm).
  /*! \ingroup PPL_CXX_interface */
  struct Bit_Row_Less_Than {
    bool operator()(const Bit_Row& x, const Bit_Row& y) const;
  };

  friend
  void Parma_Polyhedra_Library::
  Linear_System::sort_and_remove_with_sat(Bit_Matrix& sat);

};

namespace Parma_Polyhedra_Library {

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
//! Returns <CODE>true</CODE> if and only if \p x and \p y are equal.
/*! \relates Bit_Matrix */
#endif // defined(PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS)
bool operator==(const Bit_Matrix& x, const Bit_Matrix& y);

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
//! Returns <CODE>true</CODE> if and only if \p x and \p y are not equal.
/*! \relates Bit_Matrix */
#endif // defined(PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS)
bool operator!=(const Bit_Matrix& x, const Bit_Matrix& y);

} // namespace Parma_Polyhedra_Library

namespace std {

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
//! Specializes <CODE>std::swap</CODE>.
/*! \relates Parma_Polyhedra_Library::Bit_Matrix */
#endif // defined(PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS)
void swap(Parma_Polyhedra_Library::Bit_Matrix& x,
	  Parma_Polyhedra_Library::Bit_Matrix& y);

} // namespace std

#include "Bit_Matrix.inlines.hh"

#endif // !defined(PPL_Bit_Matrix_defs_hh)
