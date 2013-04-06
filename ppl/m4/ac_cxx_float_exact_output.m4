dnl A function to detect whether C++ provides exact output for floats.
dnl Copyright (C) 2001-2010 Roberto Bagnara <bagnara@cs.unipr.it>
dnl Copyright (C) 2010-2011 BUGSENG srl (http://bugseng.com)
dnl
dnl This file is part of the Parma Polyhedra Library (PPL).
dnl
dnl The PPL is free software; you can redistribute it and/or modify it
dnl under the terms of the GNU General Public License as published by the
dnl Free Software Foundation; either version 3 of the License, or (at your
dnl option) any later version.
dnl
dnl The PPL is distributed in the hope that it will be useful, but WITHOUT
dnl ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
dnl FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
dnl for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with this program; if not, write to the Free Software Foundation,
dnl Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02111-1307, USA.
dnl
dnl For the most up-to-date information see the Parma Polyhedra Library
dnl site: http://www.cs.unipr.it/ppl/ .

AC_DEFUN([AC_CXX_FLOAT_EXACT_OUTPUT],
[
dnl AC_REQUIRE([AC_CXX_FLOAT_BINARY_FORMAT])
ac_save_CPPFLAGS="$CPPFLAGS"
ac_save_LIBS="$LIBS"
AC_LANG_PUSH(C++)

AC_MSG_CHECKING([whether C++ provides exact output for floats])

AC_RUN_IFELSE([AC_LANG_SOURCE([[
#include <limits>
#ifdef HAVE_STDINT_H
#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS 1
#endif
#include <stdint.h>
#endif
#ifdef HAVE_INTTYPES_H
#include <inttypes.h>
#endif
#include <sstream>

/* Unique (nonzero) code for the IEEE 754 Single Precision
   floating point format.  */
# define PPL_FLOAT_IEEE754_SINGLE 1

/* Unique (nonzero) code for the IEEE 754 Double Precision
   floating point format.  */
# define PPL_FLOAT_IEEE754_DOUBLE 2

/* Unique (nonzero) code for the IEEE 754 Quad Precision
   floating point format.  */
# define PPL_FLOAT_IEEE754_QUAD 3

/* Unique (nonzero) code for the Intel Double-Extended
   floating point format.  */
# define PPL_FLOAT_INTEL_DOUBLE_EXTENDED 4

bool
check(float value, const char* text) {
  std::ostringstream ss;
  ss.precision(10000);
  ss << value;
  return ss.str() == text;
}

#if SIZEOF_FLOAT == 4

float
convert(uint32_t x) {
  union {
    float value;
    uint32_t word;
  } u;

  u.word = x;
  return u.value;
}

#if PPL_CXX_FLOAT_BINARY_FORMAT == PPL_FLOAT_IEEE754_SINGLE

int
main() {
  if (check(convert(0xaaacccaaU),
            "-3.069535185924732179074680971098132431507110595703125e-13")
      && check(convert(0xcccaaaccU),
               "-106255968")
      && check(convert(0x00000001U),
               "1.40129846432481707092372958328991613128026194187651577175706828388979108268586060148663818836212158203125e-45")
      && check(convert(0x80000001U),
               "-1.40129846432481707092372958328991613128026194187651577175706828388979108268586060148663818836212158203125e-45"))
    return 0;
  else
    return 1;
}

#else // PPL_CXX_FLOAT_BINARY_FORMAT != FLOAT_IEEE754_SINGLE

int
main() {
  return 1;
}

#endif // PPL_CXX_FLOAT_BINARY_FORMAT != FLOAT_IEEE754_SINGLE

#else // SIZEOF_FLOAT != 4

int
main() {
  return 1;
}

#endif // SIZEOF_FLOAT != 4
]])],
  AC_MSG_RESULT(yes)
  ac_cxx_float_exact_output=1,
  AC_MSG_RESULT(no)
  ac_cxx_float_exact_output=0,
  AC_MSG_RESULT([assuming not])
  ac_cxx_float_exact_output=0)

AC_DEFINE_UNQUOTED(PPL_CXX_FLOAT_EXACT_OUTPUT, $ac_cxx_float_exact_output,
  [Not zero if C++ supports exact output for floats.])

AC_LANG_POP(C++)
CPPFLAGS="$ac_save_CPPFLAGS"
LIBS="$ac_save_LIBS"
])
