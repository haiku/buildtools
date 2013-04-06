/* Row class implementation (non-inline functions).
   Copyright (C) 2001-2010 Roberto Bagnara <bagnara@cs.unipr.it>

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

#include "Row.defs.hh"
#include "Coefficient.defs.hh"
#include <iostream>
#include <iomanip>
#include "assert.hh"

namespace PPL = Parma_Polyhedra_Library;

void
PPL::Row_Impl_Handler::
Impl::expand_within_capacity(const dimension_type new_size) {
  PPL_ASSERT(size() <= new_size && new_size <= max_size());
#if !PPL_CXX_SUPPORTS_FLEXIBLE_ARRAYS
  // vec_[0] is already constructed.
  if (size() == 0 && new_size > 0)
    bump_size();
#endif
  for (dimension_type i = size(); i < new_size; ++i) {
    new (&vec_[i]) Coefficient();
    bump_size();
  }
}

void
PPL::Row_Impl_Handler::Impl::shrink(dimension_type new_size) {
  const dimension_type old_size = size();
  PPL_ASSERT(new_size <= old_size);
  // Since ~Coefficient() does not throw exceptions, nothing here does.
  set_size(new_size);
#if !PPL_CXX_SUPPORTS_FLEXIBLE_ARRAYS
  // Make sure we do not try to destroy vec_[0].
  if (new_size == 0)
    ++new_size;
#endif
  // We assume construction was done "forward".
  // We thus perform destruction "backward".
  for (dimension_type i = old_size; i-- > new_size; )
    vec_[i].~Coefficient();
}

void
PPL::Row_Impl_Handler::Impl::copy_construct_coefficients(const Impl& y) {
  const dimension_type y_size = y.size();
#if PPL_CXX_SUPPORTS_FLEXIBLE_ARRAYS
  for (dimension_type i = 0; i < y_size; ++i) {
    new (&vec_[i]) Coefficient(y.vec_[i]);
    bump_size();
  }
#else
  PPL_ASSERT(y_size > 0);
  if (y_size > 0) {
    vec_[0] = y.vec_[0];
    bump_size();
    for (dimension_type i = 1; i < y_size; ++i) {
      new (&vec_[i]) Coefficient(y.vec_[i]);
      bump_size();
    }
  }
#endif
}

void
PPL::Row::normalize() {
  Row& x = *this;
  // Compute the GCD of all the coefficients.
  const dimension_type sz = size();
  dimension_type i = sz;
  PPL_DIRTY_TEMP_COEFFICIENT(gcd);
  while (i > 0) {
    const Coefficient& x_i = x[--i];
    if (const int x_i_sign = sgn(x_i)) {
      gcd = x_i;
      if (x_i_sign < 0)
	neg_assign(gcd);
      goto compute_gcd;
    }
  }
  // We reach this point only if all the coefficients were zero.
  return;

 compute_gcd:
  if (gcd == 1)
    return;
  while (i > 0) {
    const Coefficient& x_i = x[--i];
    if (x_i != 0) {
      // Note: we use the ternary version instead of a more concise
      // gcd_assign(gcd, x_i) to take advantage of the fact that
      // `gcd' will decrease very rapidly (see D. Knuth, The Art of
      // Computer Programming, second edition, Section 4.5.2,
      // Algorithm C, and the discussion following it).  Our
      // implementation of gcd_assign(x, y, z) for checked numbers is
      // optimized for the case where `z' is smaller than `y', so that
      // on checked numbers we gain.  On the other hand, for the
      // implementation of gcd_assign(x, y, z) on GMP's unbounded
      // integers we cannot make any assumption, so here we draw.
      // Overall, we win.
      gcd_assign(gcd, x_i, gcd);
      if (gcd == 1)
	return;
    }
  }
  // Divide the coefficients by the GCD.
  for (dimension_type j = sz; j-- > 0; ) {
    Coefficient& x_j = x[j];
    exact_div_assign(x_j, x_j, gcd);
  }
}

void
PPL::Row::Flags::ascii_dump(std::ostream& s) const {
  s << "0x";
  std::istream::fmtflags f = s.setf(std::istream::hex);
  std::streamsize sz = s.width(2*sizeof(Flags::base_type));
  std::ostream::char_type ch = s.fill('0');
  s << bits;
  s.fill(ch);
  s.width(sz);
  s.flags(f);
}

PPL_OUTPUT_DEFINITIONS_ASCII_ONLY(Row::Flags)

bool
PPL::Row::Flags::ascii_load(std::istream& s) {
  std::string str;
  std::streamsize sz = s.width(2);
  if (!(s >> str) || str != "0x")
    return false;
  s.width(sz);
  std::istream::fmtflags f = s.setf(std::istream::hex);
  bool r = s >> bits;
  s.flags(f);
  return r;
}

void
PPL::Row::ascii_dump(std::ostream& s) const {
  const Row& x = *this;
  const dimension_type x_size = x.size();
  s << "size " << x_size << " ";
  for (dimension_type i = 0; i < x_size; ++i)
    s << x[i] << ' ';
  s << "f ";
  flags().ascii_dump(s);
  s << "\n";
}

PPL_OUTPUT_DEFINITIONS_ASCII_ONLY(Row)

bool
PPL::Row::ascii_load(std::istream& s) {
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
  if (!(s >> str) || str != "f")
    return false;
  return flags().ascii_load(s);
}

PPL::memory_size_type
PPL::Row_Impl_Handler::Impl::external_memory_in_bytes() const {
  memory_size_type n = 0;
  for (dimension_type i = size(); i-- > 0; )
    n += PPL::external_memory_in_bytes(vec_[i]);
  return n;
}

bool
PPL::Row::OK() const {
#ifndef NDEBUG
  using std::endl;
  using std::cerr;
#endif

  bool is_broken = false;
#if PPL_ROW_EXTRA_DEBUG
# if !PPL_CXX_SUPPORTS_FLEXIBLE_ARRAYS
  if (capacity_ == 0) {
    cerr << "Illegal row capacity: is 0, should be at least 1"
	 << endl;
    is_broken = true;
  }
  else
# endif // !PPL_CXX_SUPPORTS_FLEXIBLE_ARRAYS
  if (capacity_ > max_size()) {
    cerr << "Row capacity exceeds the maximum allowed size:"
	 << endl
	 << "is " << capacity_
	 << ", should be less than or equal to " << max_size() << "."
	 << endl;
    is_broken = true;
  }
#endif // PPL_ROW_EXTRA_DEBUG
  if (size() > max_size()) {
#ifndef NDEBUG
    cerr << "Row size exceeds the maximum allowed size:"
	 << endl
	 << "is " << size()
	 << ", should be less than or equal to " << max_size() << "."
	 << endl;
#endif
    is_broken = true;
  }
#if PPL_ROW_EXTRA_DEBUG
  if (capacity_ < size()) {
#ifndef NDEBUG
    cerr << "Row is completely broken: capacity is " << capacity_
	 << ", size is " << size() << "."
	 << endl;
#endif
    is_broken = true;
  }
#endif // PPL_ROW_EXTRA_DEBUG
  return !is_broken;
}

bool
PPL::Row::OK(const dimension_type row_size,
	     const dimension_type
#if PPL_ROW_EXTRA_DEBUG
	     row_capacity
#endif
	     ) const {
#ifndef NDEBUG
  using std::endl;
  using std::cerr;
#endif

  bool is_broken = !OK();

#if PPL_ROW_EXTRA_DEBUG
  // Check the declared capacity.
# if !PPL_CXX_SUPPORTS_FLEXIBLE_ARRAYS
  if (capacity_ == 1 && row_capacity == 0)
    // This is fine.
    ;
  else
# endif // !PPL_CXX_SUPPORTS_FLEXIBLE_ARRAYS
  if (capacity_ != row_capacity) {
    cerr << "Row capacity mismatch: is " << capacity_
	 << ", should be " << row_capacity << "."
	 << endl;
    is_broken = true;
  }
#endif // PPL_ROW_EXTRA_DEBUG

  // Check the declared size.
  if (size() != row_size) {
#ifndef NDEBUG
    cerr << "Row size mismatch: is " << size()
	 << ", should be " << row_size << "."
	 << endl;
#endif
    is_broken = true;
  }
  return !is_broken;
}

/*! \relates Parma_Polyhedra_Library::Row */
bool
PPL::operator==(const Row& x, const Row& y) {
  const dimension_type x_size = x.size();
  const dimension_type y_size = y.size();
  if (x_size != y_size)
    return false;

  if (x.flags() != y.flags())
    return false;

  for (dimension_type i = x_size; i-- > 0; )
    if (x[i] != y[i])
      return false;

  return true;
}
