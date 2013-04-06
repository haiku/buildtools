dnl A function to check for the existence and usability of GMP.
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

AC_DEFUN([AC_CHECK_GMP],
[
dnl Since libgmp and libgmpxx are usually installed in the same location,
dnl let the prefixes default from each other.
if test -n "$with_libgmpxx_prefix" && test -z "$with_libgmp_prefix"; then
  with_libgmp_prefix="$with_libgmpxx_prefix"
else
  if test -n "$with_libgmp_prefix" && test -z "$with_libgmpxx_prefix"; then
    with_libgmpxx_prefix="$with_libgmp_prefix"
  fi
fi

AC_ARG_WITH(gmp-build,
  AS_HELP_STRING([--with-gmp-build=DIR],
                 [use a non-installed build of GMP in DIR]),
  gmp_build_dir=$with_gmp_build
  if test -z "$with_libgmp_prefix"
  then
    CPPFLAGS="$CPPFLAGS -I$gmp_build_dir -I$gmp_build_dir/tune"
    LDFLAGS="$LDFLAGS -L$gmp_build_dir -L$gmp_build_dir/.libs"
    LDFLAGS="$LDFLAGS -L$gmp_build_dir/tune"
  else
    AC_MSG_ERROR([cannot use --with-gmp-build and --with-gmp-prefix together])
  fi)

dnl Both libgmp and libbmpxx come from the gmp package.
AC_LIB_FROMPACKAGE([gmp], [gmp])
AC_LIB_FROMPACKAGE([gmpxx], [gmp])

dnl Check how to link with libgmp.
AC_LIB_LINKFLAGS([gmp])

dnl Check how to link with libgmpxx.
AC_LIB_LINKFLAGS([gmpxx], [gmp])

ac_save_LIBS="$LIBS"
LIBS="$LIBS $LIBGMPXX"
AC_LANG_PUSH(C++)

AC_MSG_CHECKING([for the GMP library version 4.1.3 or above])
AC_RUN_IFELSE([AC_LANG_SOURCE([[
#include <gmpxx.h>
#include <climits>
#include <string>
#include <sstream>
#include <iostream>

#if __GNU_MP_VERSION < 4 || (__GNU_MP_VERSION == 4 && __GNU_MP_VERSION_MINOR < 1) || (__GNU_MP_VERSION == 4 && __GNU_MP_VERSION_MINOR == 1 && __GNU_MP_VERSION_PATCHLEVEL < 3)
#GMP version 4.1.3 or higher is required
#endif

#ifndef BITS_PER_MP_LIMB
#define BITS_PER_MP_LIMB GMP_LIMB_BITS
#endif

int
main() {
  std::string header_version;
  {
    std::ostringstream s(header_version);
    s << __GNU_MP_VERSION << "." << __GNU_MP_VERSION_MINOR;
    // Starting from GMP version 4.3.0, the gmp_version variable
    // always contains three parts.  In previous versions the
    // patchlevel was omitted if it was 0.
    if (__GNU_MP_VERSION_PATCHLEVEL != 0
        || __GNU_MP_VERSION > 4
        || (__GNU_MP_VERSION == 4 && __GNU_MP_VERSION_MINOR >= 3))
      s << "." << __GNU_MP_VERSION_PATCHLEVEL;
    header_version = s.str();
  }

  std::string library_version = gmp_version;

  if (header_version != library_version) {
    std::cerr
      << "GMP header (gmp.h) and library (ligmp.*) version mismatch:\n"
      << "header gives " << header_version << ";\n"
      << "library gives " << library_version << "." << std::endl;
    return 1;
  }

  if (sizeof(mp_limb_t)*CHAR_BIT != BITS_PER_MP_LIMB
      || BITS_PER_MP_LIMB != mp_bits_per_limb) {
    std::cerr
      << "GMP header (gmp.h) and library (ligmp.*) bits-per-limb mismatch:\n"
      << "header gives " << BITS_PER_MP_LIMB << ";\n"
      << "library gives " << mp_bits_per_limb << ".\n"
      << "This probably means you are on a bi-arch system and\n"
      << "you are compiling with the wrong header or linking with\n"
      << "the wrong library." << std::endl;
    return 1;
  }

  mpz_class n("3141592653589793238462643383279502884");
  return 0;
}
]])],
  AC_MSG_RESULT(yes)
  ac_cv_have_gmp=yes,
  AC_MSG_RESULT(no)
  ac_cv_have_gmp=no,
  AC_COMPILE_IFELSE([AC_LANG_SOURCE([[
#include <gmpxx.h>

#if __GNU_MP_VERSION < 4 || (__GNU_MP_VERSION == 4 && __GNU_MP_VERSION_MINOR < 1) || (__GNU_MP_VERSION == 4 && __GNU_MP_VERSION_MINOR == 1 && __GNU_MP_VERSION_PATCHLEVEL < 3)
#GMP version 4.1.3 or higher is required
#endif

int
main() {
  return 0;
}
]])],
    AC_MSG_RESULT(yes)
    ac_cv_have_gmp=yes,
    AC_MSG_RESULT(no)
    ac_cv_have_gmp=no))

have_gmp=${ac_cv_have_gmp}

if test x"$ac_cv_have_gmp" = xyes
then

AC_CHECK_SIZEOF(mp_limb_t, , [#include <gmpxx.h>])

AC_MSG_CHECKING([whether GMP has been compiled with support for exceptions])
AC_RUN_IFELSE([AC_LANG_SOURCE([[
#include <gmpxx.h>
#include <new>
#include <cstddef>

static void*
x_malloc(size_t) {
  throw std::bad_alloc();
}

static void*
x_realloc(void*, size_t, size_t) {
  throw std::bad_alloc();
}

static void
x_free(void*, size_t) {
}

int main() {
  mp_set_memory_functions(x_malloc, x_realloc, x_free);
  try {
    mpz_class n("3141592653589793238462643383279502884");
  }
  catch (std::bad_alloc&) {
    return 0;
  }
  return 1;
}
]])],
  AC_MSG_RESULT(yes)
  ac_cv_gmp_supports_exceptions=yes,
  AC_MSG_RESULT(no)
  ac_cv_gmp_supports_exceptions=no,
  AC_MSG_RESULT([assuming not])
  ac_cv_gmp_supports_exceptions=no)

gmp_supports_exceptions=${ac_cv_gmp_supports_exceptions}
if test x"$gmp_supports_exceptions" = xyes
then
  value=1
else
  value=0
fi
AC_DEFINE_UNQUOTED(PPL_GMP_SUPPORTS_EXCEPTIONS, $value,
  [Not zero if GMP has been compiled with support for exceptions.])

fi

AC_LANG_POP(C++)
LIBS="$ac_save_LIBS"

dnl We use libtool, therefore we take $LTLIBGMPXX, not $LIBGMPXX.
gmp_library_option="$LTLIBGMPXX"
])
