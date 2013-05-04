# Autoconf source file for the Parma Watchdog Library.
# Copyright (C) 2001-2010 Roberto Bagnara <bagnara@cs.unipr.it>
# Copyright (C) 2010-2011 BUGSENG srl (http://bugseng.com)
#
# This file is part of the Parma Watchdog Library (PWL).
#
# The PWL is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation; either version 3 of the License, or (at your
# option) any later version.
#
# The PWL is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
# for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation,
# Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02111-1307, USA.
#
# For the most up-to-date information see the Parma Polyhedra Library
# site: http://www.cs.unipr.it/ppl/ . */

# Process this file with Autoconf to produce a configure script.

# Every other copy of the package version number gets its value from here.
AC_INIT([the Parma Watchdog Library],[0.8],[bagnara@cs.unipr.it],[pwl])

# Minimum Autoconf version required.
AC_PREREQ(2.61)

# Make sure the sources are there.
AC_CONFIG_SRCDIR(src/Watchdog.cc)

# Specify the location of additional local Autoconf macros.
AC_CONFIG_MACRO_DIR([m4])

# Determine the system type and set output variables to the names of
# the canonical system types.
AC_CANONICAL_HOST

# Use Automake.
AM_INIT_AUTOMAKE([foreign no-define dist-bzip2 dist-zip dist-lzma silent-rules 1.11])
AC_SUBST(VERSION)

# Generate a configuration header file.
AC_CONFIG_HEADER([config.h])

ISODATE=`date +%Y-%m-%d`
AC_SUBST(ISODATE)

AH_BOTTOM([
#if defined(PWL_NDEBUG) && !defined(NDEBUG)
# define NDEBUG PWL_NDEBUG
#endif
])

# C compiler.

AC_ARG_WITH(cc,
  AS_HELP_STRING([--with-cc=XXX], [use XXX as the C compiler]),
  CC=$with_cc)

# C++ compiler.

AC_ARG_WITH(cxx,
  AS_HELP_STRING([--with-cxx=XXX], [use XXX as the C++ compiler]),
  CXX=$with_cxx)

# Checks for programs.

# Note that AC_PROG_CC must precede the first use of $GCC abd AC_PROG_CXX
# must precede the first use of $GXX.  Note also that we do not allow
# AC_PROG_CC and AC_PROG_CXX to affect CFLAGS and CXXFLAGS.
save_CFLAGS="$CFLAGS"
AC_PROG_CC
CFLAGS="$save_CFLAGS"

AM_CONDITIONAL(GCC, test x"$GCC" = xyes)

# The Intel C compiler masquerades as gcc, but we want to know.
if test x"$GCC" = xyes
then
  AC_MSG_CHECKING([whether we are actually using the Intel C compiler])
  AC_LANG_PUSH(C)
  AC_COMPILE_IFELSE([AC_LANG_SOURCE([[
#ifndef __INTEL_COMPILER
choke me
#endif
]])],
  AC_MSG_RESULT(yes)
  ICC=yes,
  AC_MSG_RESULT(no)
  ICC=no,
  AC_MSG_RESULT(no)
  ICC=no)
  AC_LANG_POP(C)
fi

save_CXXFLAGS="$CXXFLAGS"
AC_PROG_CXX
CXXFLAGS="$save_CXXFLAGS"

# The Intel C++ compiler masquerades as g++, but we want to know.
if test x"$GXX" = xyes
then
  AC_MSG_CHECKING([whether we are actually using the Intel C++ compiler])
  AC_LANG_PUSH(C++)
  AC_COMPILE_IFELSE([AC_LANG_SOURCE([[
#ifndef __INTEL_COMPILER
choke me
#endif
]])],
  AC_MSG_RESULT(yes)
  ICPC=yes,
  AC_MSG_RESULT(no)
  ICPC=no,
  AC_MSG_RESULT(no)
  ICPC=no)
  AC_LANG_POP(C++)
fi

AC_PROG_SED
AC_PROG_CXXCPP
AC_PROG_MAKE_SET
AC_PROG_INSTALL

# Compilation flags.

COMP_FLAGS=""
OPT_FLAGS=""

# Determine the system-dependent aspects of rpath usage and add
# the --disable-rpath configure option.
AC_LIB_RPATH

enableval=yes
AC_MSG_CHECKING([whether to compile with debug info])
AC_ARG_ENABLE(debugging,
[  --enable-debugging      compile with debugging information])
case "${enableval}" in
yes)
  AC_MSG_RESULT(yes)
  OPT_FLAGS="-g"
  ;;
no)
  AC_MSG_RESULT(no)
  ;;
*)
  AC_MSG_ERROR([bad value ${enableval} for --enable-debugging, needs yes or no])
  ;;
esac

enableval=no
AC_MSG_CHECKING([whether to compile for profiling])
AC_ARG_ENABLE(profiling,
[  --enable-profiling      compile for profiling])
case "${enableval}" in
yes)
  AC_MSG_RESULT(yes)
  OPT_FLAGS="-g"
  COMP_FLAGS="$COMP_FLAGS -pg -DPWL_PROFILING=1"
  ;;
no)
  AC_MSG_RESULT(no)
  ;;
*)
  AC_MSG_ERROR([bad value ${enableval} for --enable-profiling, needs yes or no])
  ;;
esac

enableval=no
AC_MSG_CHECKING([whether to compile for test coverage])
AC_ARG_ENABLE(coverage,
[  --enable-coverage       compile for test coverage])
case "${enableval}" in
yes)
  AC_MSG_RESULT(yes)
  OPT_FLAGS="-g"
  COMP_FLAGS="$COMP_FLAGS -fprofile-arcs -ftest-coverage"
  ;;
no)
  AC_MSG_RESULT(no)
  ;;
*)
  AC_MSG_ERROR([bad value ${enableval} for --enable-coverage, needs yes or no])
  ;;
esac

enableval=no
AC_MSG_CHECKING([whether to enable checking of run-time assertions])
AC_ARG_ENABLE(assertions,
[  --enable-assertions     check run-time assertions])
case "${enableval}" in
yes)
  AC_MSG_RESULT(yes)
  ;;
no)
  AC_MSG_RESULT(no)
  AC_DEFINE(PWL_NDEBUG, 1, [Assertions are disabled when this is defined])
  debug_flag="-DNDEBUG=1"
  ;;
*)
  AC_MSG_ERROR([bad value ${enableval} --enable-assertions, needs yes or no])
  ;;
esac

arch=no
enableval=standard
AC_MSG_CHECKING([whether to enable optimizations])
AC_ARG_ENABLE(optimization,
[  --enable-optimization   enable compiler optimizations])
case "${enableval}" in
sspeed)
  AC_MSG_RESULT(sspeed)
  OPT_FLAGS="$OPT_FLAGS -O3 -fomit-frame-pointer"
  arch=yes
  ;;
speed)
  AC_MSG_RESULT(speed)
  OPT_FLAGS="$OPT_FLAGS -O3"
  arch=yes
  ;;
size)
  AC_MSG_RESULT(size)
  OPT_FLAGS="$OPT_FLAGS -Os"
  arch=yes
  ;;
standard | yes)
  AC_MSG_RESULT(standard)
  OPT_FLAGS="$OPT_FLAGS -O2"
  ;;
mild)
  AC_MSG_RESULT(mild)
  OPT_FLAGS="$OPT_FLAGS -O1"
  ;;
zero)
  AC_MSG_RESULT(zero)
  OPT_FLAGS="$OPT_FLAGS -O0"
  ;;
no)
  AC_MSG_RESULT(no)
  ;;
*)
  AC_MSG_ERROR([bad value ${enableval} for --enable-optimization, needs sspeed, speed, size, standard, mild, zero, yes or no])
  ;;
esac

enableval=$arch
AC_MSG_CHECKING([for which architecture to optimize])
AC_ARG_ENABLE(arch,
[  --enable-arch[=arch]      optimize for architecture arch])
case "${enableval}" in
yes)
  m=`uname -m`
  case $m in
  i?86 | k6 | athlon)
    AC_MSG_RESULT($m)
    OPT_FLAGS="$OPT_FLAGS -march=$m"
    ;;
  *)
    AC_MSG_RESULT(default)
    ;;
  esac
  ;;
no)
  AC_MSG_RESULT(default)
  ;;
*)
  AC_MSG_RESULT($enableval)
  OPT_FLAGS="$OPT_FLAGS -march=$enableval"
  ;;
esac

CFLAGS="$COMP_FLAGS $OPT_FLAGS $CFLAGS"
CXXFLAGS="$COMP_FLAGS $OPT_FLAGS $CXXFLAGS"

# System-dependent adjustments.
no_undefined=no

case "${host_os}" in
cygwin)
  no_undefined=yes
  ;;
*)
  ;;
esac
AM_CONDITIONAL(NO_UNDEFINED, test x$no_undefined = xyes)


# Allow additions to C and C++ compilation flags.

AC_ARG_WITH(cflags,
[  --with-cflags=xxx       add XXX to the options for the C compiler],
CFLAGS="$CFLAGS $with_cflags")

AC_ARG_WITH(cxxflags,
[  --with-cxxflags=xxx     add XXX to the options for the C++ compiler],
CXXFLAGS="$CXXFLAGS $with_cxxflags")

# Check for Perl.
AC_PATH_PROG([PERL], perl, no)
AC_SUBST([PERL])
AM_CONDITIONAL(HAVE_PERL, test x"$PERL" != xno)

# Checks for C typedefs, structures, and compiler characteristics.
AC_LANG(C)
AC_C_CONST

# Use C++ for the remaining checks.
AC_LANG(C++)

enableval=no
AC_MSG_CHECKING([whether tests should be run under Valgrind])
AC_ARG_ENABLE(valgrind-tests,
  AS_HELP_STRING([--enable-valgrind-tests],
                 [run library tests under Valgrind]))
case "${enableval}" in
yes)
  AC_CHECK_PROG(VALGRIND, valgrind, valgrind)
  if test x"$VALGRIND" = xvalgrind
  then
    AC_MSG_RESULT(yes)
    enable_valgrind_tests=yes
  else
    AC_MSG_ERROR([bad value ${enableval} for --enable-valgrind-tests, cannot find Valgrind])
  fi
  ;;
no)
  AC_MSG_RESULT(no)
  enable_valgrind_tests=no
  ;;
*)
  AC_MSG_ERROR([bad value ${enableval} for --enable-valgrind-tests, needs yes or no])
  ;;
esac
AM_CONDITIONAL(VALGRIND_TESTS_ENABLED, test x"$enable_valgrind_tests" = xyes)

enableval=yes
AC_MSG_CHECKING([whether to build the Parma Watchdog Library])
AC_ARG_ENABLE(watchdog,
  AS_HELP_STRING([--enable-watchdog],
                 [build also the Parma Watchdog Library]))
case "${enableval}" in
yes)
  build_watchdog_library=yes
  ;;
no)
  build_watchdog_library=no
  ;;
*)
  AC_MSG_ERROR([bad value ${enableval} for --enable-watchdog, needs yes or no])
  ;;
esac
AC_MSG_RESULT($build_watchdog_library)
AM_CONDITIONAL(BUILD_WATCHDOG_LIBRARY, test x"$build_watchdog_library" = xyes)

if test x"$build_watchdog_library" = xyes
then
  # Checks for header files.
  AC_HEADER_TIME
  AC_CHECK_HEADERS([fenv.h sys/time.h])

  # Checks for the availability of C library functions in C++.
  AC_CHECK_DECLS([getenv], , , [#include <cstdlib>])
  AC_CHECK_DECLS([setitimer], [], [], [[
#ifdef HAVE_SYS_TIME_H
# include <sys/time.h>
#endif
  ]])
  AC_CHECK_DECLS([sigaction], , , [#include <csignal>])

  # Checks for typedefs, structures, and compiler characteristics.
  AC_CHECK_TYPES([siginfo_t], [], [], [[
#include <signal.h>
  ]])
fi

# Libtool.
LT_INIT([dlopen])

# If we are using GCC or the Intel C/C++ compiler we want to compile
# with lots of warnings enabled.
if test x"$GCC" = xyes
then
  if test x"$ICC" = xyes
  then
    CFLAGS="$CFLAGS -w2 -wd161,177,193,279,383,444,981,1098,1188,1418,1419,1572"
  else
    CFLAGS="$CFLAGS -W -Wall"
  fi
fi
if test x"$GXX" = xyes
then
  if test x"$ICPC" = xyes
  then
    CXXFLAGS="$CXXFLAGS -w2 -wd161,177,193,279,383,444,981,1098,1188,1418,1419,1572"
  else
    CXXFLAGS="$CXXFLAGS -W -Wall"
  fi
fi

AC_SUBST(debug_flag)

AC_CONFIG_FILES(Makefile
                src/Makefile
                m4/Makefile
                doc/Makefile
                doc/user.doxyconf-latex
                doc/devref.doxyconf-latex
                doc/user.doxyconf-html
                doc/devref.doxyconf-html
                tests/Makefile
                utils/Makefile)
AC_OUTPUT
