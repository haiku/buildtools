# Automake source file for the Parma Polyhedra Library.
# Copyright (C) 2001-2010 Roberto Bagnara <bagnara@cs.unipr.it>
# Copyright (C) 2010-2011 BUGSENG srl (http://bugseng.com)
#
# This file is part of the Parma Polyhedra Library (PPL).
#
# The PPL is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation; either version 3 of the License, or (at your
# option) any later version.
#
# The PPL is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
# for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation,
# Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02111-1307, USA.
#
# For the most up-to-date information see the Parma Polyhedra Library
# site: http://www.cs.unipr.it/ppl/ .

if VALGRIND_TESTS_ENABLED

CHECKER = \
$(VALGRIND) --tool=memcheck -q --trace-children=yes --leak-check=yes \
--num-callers=40 --leak-resolution=high \
--suppressions=$(top_srcdir)/tests/valgrind_suppressions

else !VALGRIND_TESTS_ENABLED

CHECKER =

endif !VALGRIND_TESTS_ENABLED

TESTS_ENVIRONMENT = $(CHECKER)

AM_CPPFLAGS = \
-I$(top_builddir)/interfaces/C \
@extra_includes@ \
@debug_flag@

if GCC

if HOST_OS_MINGW

# MinGW's <stdlib.h> cannot be compiled in c89 mode.
AM_CFLAGS = -pedantic -std=gnu89 -Werror

else !HOST_OS_MINGW

AM_CFLAGS = -pedantic -std=c89 -Werror

endif !HOST_OS_MINGW

endif GCC

check_LIBRARIES = libppl_c_tests.a

libppl_c_tests_a_SOURCES = \
ppl_c_test.cc

# Dummy C++ source to cause C++ linking.
nodist_EXTRA_libppl_c_tests_a_SOURCES = \
dummy.cc

libppl_c_tests_a_CPPFLAGS = \
-I$(top_builddir)/interfaces/C \
@extra_includes@

LDADD = \
libppl_c_tests.a \
$(top_builddir)/interfaces/C/libppl_c.la \
@extra_libraries@

NORMAL_TESTS = \
formatted_output \
pip_test

#
# Sources for the tests
#

formatted_output_SOURCES = \
formatted_output.c \
print_to_buffer.h \
print_to_buffer.c

# Dummy C++ source to cause C++ linking.
# FIXME: why isn't enough to do this for libppl_c_tests.a?
nodist_EXTRA_formatted_output_SOURCES = \
dummy.cc

pip_test_SOURCES = \
pip_test.c

# Dummy C++ source to cause C++ linking.
# FIXME: why isn't enough to do this for libppl_c_tests.a?
nodist_EXTRA_pip_test_SOURCES = \
dummy.cc

watchdog1_SRCS = watchdog1.c

weightwatch1_SRCS = weightwatch1.c

noinst_HEADERS = \
ppl_c_test.h

if BUILD_WATCHDOG_LIBRARY

WATCHDOG_TESTS = \
watchdog1 \
weightwatch1

WATCHDOG_LIBRARY_CPPFLAGS = \
$(AM_CPPFLAGS) \
-I$(top_builddir)/Watchdog \
-I$(top_builddir)/Watchdog/src

WATCHDOG_LIBRARY_LDADD = \
$(LDADD) \
$(top_builddir)/Watchdog/src/libpwl.la

watchdog1_SOURCES = $(watchdog1_SRCS)
watchdog1_CPPFLAGS = $(WATCHDOG_LIBRARY_CPPFLAGS)
watchdog1_LDADD = $(WATCHDOG_LIBRARY_LDADD)

# Dummy C++ source to cause C++ linking.
# FIXME: why isn't enough to do this for libppl_c_tests.a?
nodist_EXTRA_watchdog1_SOURCES = \
dummy.cc


weightwatch1_SOURCES = $(weightwatch1_SRCS)
weightwatch1_CPPFLAGS = $(WATCHDOG_LIBRARY_CPPFLAGS)
weightwatch1_LDADD = $(WATCHDOG_LIBRARY_LDADD)

# Dummy C++ source to cause C++ linking.
# FIXME: why isn't enough to do this for libppl_c_tests.a?
nodist_EXTRA_weightwatch1_SOURCES = \
dummy.cc

endif BUILD_WATCHDOG_LIBRARY

TESTS = $(NORMAL_TESTS) $(WATCHDOG_TESTS)

XFAIL_TESTS =

check_PROGRAMS = $(TESTS) $(BUGS)

EXTRA_DIST = $(watchdog1_SRCS)

BUGS =

$(top_builddir)/interfaces/C/libppl_c.la:
	$(MAKE) $(AM_MAKEFLAGS) -C $(top_builddir)/interfaces/C libppl_c.la
