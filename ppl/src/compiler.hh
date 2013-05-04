/* C++ compiler related stuff.
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

#ifndef PPL_compiler_hh
#define PPL_compiler_hh 1

namespace Parma_Polyhedra_Library {

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
/*! \brief
  No-op macro that allows to avoid unused variable warnings from
  the compiler.
*/
#endif // defined(PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS)
#define used(v) (void)v

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
/*! \brief
  No-op function that force the compiler to store the argument and
  to reread it from memory if needed (thus preventing CSE).
*/
#endif // defined(PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS)
template <typename T>
inline void
cc_flush(const T& x) {
#if defined(__GNUC__) || defined(__INTEL_COMPILER)
  __asm__ __volatile__ ("" : "+m" (const_cast<T&>(x)));
#else
  // FIXME: is it possible to achieve the same effect in a portable way?
  used(x);
#endif
}

#ifndef PPL_SUPPRESS_UNINIT_WARNINGS
#define PPL_SUPPRESS_UNINIT_WARNINGS 1
#endif

#ifndef PPL_SUPPRESS_UNINITIALIZED_WARNINGS
#define PPL_SUPPRESS_UNINITIALIZED_WARNINGS 1
#endif

#if PPL_SUPPRESS_UNINITIALIZED_WARNINGS
template <typename T>
struct Suppress_Uninitialized_Warnings_Type {
  typedef T synonym;
};

#define PPL_UNINITIALIZED(type, name)                                   \
  type name = Suppress_Uninitialized_Warnings_Type<type>::synonym ()
#else
#define PPL_UNINITIALIZED(type, name)           \
  type name
#endif

} // namespace Parma_Polyhedra_Library

#endif // !defined(PPL_compiler_hh)
