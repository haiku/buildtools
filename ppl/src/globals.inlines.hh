/* Implementation of global objects: inline functions.
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

#ifndef PPL_globals_inlines_hh
#define PPL_globals_inlines_hh 1

#include <limits>
#include "assert.hh"

namespace Parma_Polyhedra_Library {

inline dimension_type
not_a_dimension() {
  return std::numeric_limits<dimension_type>::max();
}

inline const Weightwatch_Traits::Threshold&
Weightwatch_Traits::get() {
  return weight;
}

inline bool
Weightwatch_Traits::less_than(const Threshold& a, const Threshold& b) {
  return b - a < 1ULL << (sizeof(Threshold)*8-1);
}

inline void
Weightwatch_Traits::from_delta(Threshold& threshold, const Delta& delta) {
  threshold = weight + delta;
}

inline
Throwable::~Throwable() {
}

inline void
maybe_abandon() {
#ifndef NDEBUG
  if (Implementation::in_assert)
    return;
#endif
  if (Weightwatch_Traits::check_function)
    Weightwatch_Traits::check_function();
  if (const Throwable* p = abandon_expensive_computations)
    p->throw_me();
}

inline dimension_type
compute_capacity(const dimension_type requested_size,
		 const dimension_type maximum_size) {
  assert(requested_size <= maximum_size);
  // Speculation factor 2.
  return (requested_size < maximum_size / 2)
    ? 2*(requested_size + 1)
    : maximum_size;
  // Speculation factor 1.5.
  // return (maximum_size - requested_size > requested_size/2)
  //   ? requested_size + requested_size/2 + 1
  //   : maximum_size;
}

template <typename T>
inline typename
Enable_If<Is_Native<T>::value, memory_size_type>::type
external_memory_in_bytes(const T&) {
  return 0;
}

template <typename T>
inline typename
Enable_If<Is_Native<T>::value, memory_size_type>::type
total_memory_in_bytes(const T&) {
  return sizeof(T);
}

inline memory_size_type
external_memory_in_bytes(const mpz_class& x) {
  return x.get_mpz_t()[0]._mp_alloc * PPL_SIZEOF_MP_LIMB_T;
}

inline memory_size_type
total_memory_in_bytes(const mpz_class& x) {
  return sizeof(x) + external_memory_in_bytes(x);
}

inline memory_size_type
external_memory_in_bytes(const mpq_class& x) {
  return external_memory_in_bytes(x.get_num())
    + external_memory_in_bytes(x.get_den());
}

inline memory_size_type
total_memory_in_bytes(const mpq_class& x) {
  return sizeof(x) + external_memory_in_bytes(x);
}

} // namespace Parma_Polyhedra_Library

#endif // !defined(PPL_globals_inlines_hh)
