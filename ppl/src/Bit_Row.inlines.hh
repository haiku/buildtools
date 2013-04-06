/* Bit_Row class implementation: inline functions.
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

#ifndef PPL_Bit_Row_inlines_hh
#define PPL_Bit_Row_inlines_hh 1

#include "globals.defs.hh"
#include "assert.hh"

// For the declaration of ffs(3).
#if defined(PPL_HAVE_STRINGS_H)
# include <strings.h>
#elif defined(PPL_HAVE_STRING_H)
# include <string.h>
#endif

#define PPL_BITS_PER_GMP_LIMB (PPL_SIZEOF_MP_LIMB_T*CHAR_BIT)

namespace Parma_Polyhedra_Library {

inline
Bit_Row::Bit_Row() {
  mpz_init(vec);
}

inline
Bit_Row::Bit_Row(const Bit_Row& y) {
  mpz_init_set(vec, y.vec);
}

inline
Bit_Row::Bit_Row(const Bit_Row& y, const Bit_Row& z) {
  const mp_size_t y_size = y.vec->_mp_size;
  PPL_ASSERT(y_size >= 0);
  const mp_size_t z_size = z.vec->_mp_size;
  PPL_ASSERT(z_size >= 0);
  if (y_size < z_size) {
    PPL_ASSERT(static_cast<unsigned long>(z_size)
           <= ULONG_MAX / PPL_BITS_PER_GMP_LIMB);
    mpz_init2(vec, z_size * PPL_BITS_PER_GMP_LIMB);
    union_helper(y, z);
  }
  else {
    PPL_ASSERT(static_cast<unsigned long>(y_size)
           <= ULONG_MAX / PPL_BITS_PER_GMP_LIMB);
    mpz_init2(vec, y_size * PPL_BITS_PER_GMP_LIMB);
    union_helper(z, y);
  }
}

inline
Bit_Row::~Bit_Row() {
  mpz_clear(vec);
}

inline Bit_Row&
Bit_Row::operator=(const Bit_Row& y) {
  mpz_set(vec, y.vec);
  return *this;
}

inline void
Bit_Row::set(const unsigned long k) {
  mpz_setbit(vec, k);
}

inline void
Bit_Row::clear(const unsigned long k) {
  mpz_clrbit(vec, k);
}

inline void
Bit_Row::clear_from(const unsigned long k) {
  mpz_tdiv_r_2exp(vec, vec, k);
}

inline unsigned long
Bit_Row::count_ones() const {
  mp_size_t x_size = vec->_mp_size;
  PPL_ASSERT(x_size >= 0);
  return x_size == 0 ? 0 : mpn_popcount(vec->_mp_d, x_size);
}

inline bool
Bit_Row::empty() const {
  return mpz_sgn(vec) == 0;
}

inline void
Bit_Row::swap(Bit_Row& y) {
  mpz_swap(vec, y.vec);
}

inline void
Bit_Row::clear() {
  mpz_set_ui(vec, 0UL);
}

inline memory_size_type
Bit_Row::external_memory_in_bytes() const {
  return vec[0]._mp_alloc * PPL_SIZEOF_MP_LIMB_T;
}

inline memory_size_type
Bit_Row::total_memory_in_bytes() const {
  return sizeof(*this) + external_memory_in_bytes();
}

/*! \relates Bit_Row */
inline void
set_union(const Bit_Row& x, const Bit_Row& y, Bit_Row& z) {
  const mp_size_t x_size = x.vec->_mp_size;
  PPL_ASSERT(x_size >= 0);
  const mp_size_t y_size = y.vec->_mp_size;
  PPL_ASSERT(y_size >= 0);
  if (x_size < y_size) {
    PPL_ASSERT(static_cast<unsigned long>(y_size)
           <= ULONG_MAX / PPL_BITS_PER_GMP_LIMB);
    mpz_realloc2(z.vec, y_size * PPL_BITS_PER_GMP_LIMB);
    z.union_helper(x, y);
  }
  else {
    PPL_ASSERT(static_cast<unsigned long>(x_size)
           <= ULONG_MAX / PPL_BITS_PER_GMP_LIMB);
    mpz_realloc2(z.vec, x_size * PPL_BITS_PER_GMP_LIMB);
    z.union_helper(y, x);
  }
}

/*! \relates Bit_Row */
inline void
set_intersection(const Bit_Row& x, const Bit_Row& y, Bit_Row& z) {
  mpz_and(z.vec, x.vec, y.vec);
}

/*! \relates Bit_Row */
inline void
set_difference(const Bit_Row& x, const Bit_Row& y, Bit_Row& z) {
  PPL_DIRTY_TEMP0(mpz_class, complement_y);
  mpz_com(complement_y.get_mpz_t(), y.vec);
  mpz_and(z.vec, x.vec, complement_y.get_mpz_t());
}

namespace Implementation {

#if defined(__GNUC__)

/*! \brief
  Assuming \p u is nonzero, returns the index of the first set bit in \p u.
*/
inline unsigned int
first_one(unsigned int u) {
  PPL_ASSERT(u != 0);
  return __builtin_ctz(u);
}

/*! \brief
  Assuming \p ul is nonzero, returns the index of the first set bit in
  \p ul.
*/
inline unsigned int
first_one(unsigned long ul) {
  PPL_ASSERT(ul != 0);
  return __builtin_ctzl(ul);
}

/*! \brief
  Assuming \p ull is nonzero, returns the index of the first set bit in
  \p ull.
*/
inline unsigned int
first_one(unsigned long long ull) {
  PPL_ASSERT(ull != 0);
  return __builtin_ctzll(ull);
}

#elif PPL_HAVE_DECL_FFS && PPL_SIZEOF_MP_LIMB_T == PPL_SIZEOF_INT

/*! \brief
  Assuming \p w is nonzero, returns the index of the first set bit in \p w.
*/
inline unsigned int
first_one(mp_limb_t w) {
  return ffs(w)-1;
}

#else

/*! \brief
  Assuming \p w is nonzero, returns the index of the first set bit in \p w.
*/
inline unsigned int
first_one(mp_limb_t w) {
  unsigned int r = 0;
  w = w & -w;
#if PPL_SIZEOF_MP_LIMB_T == 8
  if ((w & 0xffffffff) == 0) {
    w >>= 32;
    r += 32;
  }
#elif PPL_SIZEOF_MP_LIMB_T != 4
#error "size of mp_limb_t not supported by first_one(mp_limb_t w)."
#endif
  if ((w & 0xffff) == 0) {
    w >>= 16;
    r += 16;
  }
  if ((w & 0xff) == 0) {
    w >>= 8;
    r += 8;
  }
  if (w & 0xf0)
    r += 4;
  if (w & 0xcc)
    r += 2;
  if (w & 0xaa)
    r += 1;
  return r;
}
#endif // !defined(__GNUC__)
       // && (!PPL_HAVE_DECL_FFS || PPL_SIZEOF_MP_LIMB_T != PPL_SIZEOF_INT)

#if defined(__GNUC__)

/*! \brief
  Assuming \p u is nonzero, returns the index of the last set bit in \p u.
*/
inline unsigned int
last_one(unsigned int u) {
  PPL_ASSERT(u != 0);
  return sizeof(unsigned int)*CHAR_BIT - 1 - __builtin_clz(u);
}

/*! \brief
  Assuming \p ul is nonzero, returns the index of the last set bit in
  \p ul.
*/
inline unsigned int
last_one(unsigned long ul) {
  PPL_ASSERT(ul != 0);
  return sizeof(unsigned long)*CHAR_BIT - 1 - __builtin_clzl(ul);
}

/*! \brief
  Assuming \p ull is nonzero, returns the index of the last set bit in
  \p ull.
*/
inline unsigned int
last_one(unsigned long long ull) {
  PPL_ASSERT(ull != 0);
  return sizeof(unsigned long long)*CHAR_BIT - 1 - __builtin_clzll(ull);
}

#else // !defined(__GNUC__)

/*! \brief
  Assuming \p w is nonzero, returns the index of the last set bit in \p w.
*/
inline unsigned int
last_one(mp_limb_t w) {
  PPL_ASSERT(w != 0);
  unsigned int r = 0;
#if PPL_SIZEOF_MP_LIMB_T == 8
  if (w &
#if PPL_SIZEOF_LONG == 8
      0xffffffff00000000
#else
      0xffffffff00000000LL
#endif
      ) {
    w >>= 32;
    r += 32;
  }
#elif PPL_SIZEOF_MP_LIMB_T != 4
#error "size of mp_limb_t not supported by last_one(mp_limb_t w)."
#endif
  if (w & 0xffff0000) {
    w >>= 16;
    r += 16;
  }
  if (w & 0xff00) {
    w >>= 8;
    r += 8;
  }
  if (w & 0xf0) {
    w >>= 4;
    r += 4;
  }
  if (w & 0xc) {
    w >>= 2;
    r += 2;
  }
  if (w & 0x2)
    r += 1;
  return r;
}

#endif // !defined(__GNUC__)

} // namespace Implementation

} // namespace Parma_Polyhedra_Library


namespace std {

/*! \relates Parma_Polyhedra_Library::Bit_Row */
inline void
swap(Parma_Polyhedra_Library::Bit_Row& x,
     Parma_Polyhedra_Library::Bit_Row& y) {
  x.swap(y);
}

/*! \relates Parma_Polyhedra_Library::Bit_Row */
inline void
iter_swap(std::vector<Parma_Polyhedra_Library::Bit_Row>::iterator x,
	  std::vector<Parma_Polyhedra_Library::Bit_Row>::iterator y) {
  swap(*x, *y);
}

} // namespace std

#endif // !defined(PPL_Bit_Row_inlines_hh)
