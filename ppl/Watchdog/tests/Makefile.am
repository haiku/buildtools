# Automake source file for the Parma Watchdog Library.
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

if VALGRIND_TESTS_ENABLED

CHECKER = \
$(VALGRIND) --tool=memcheck -q --trace-children=yes --leak-check=yes \
--num-callers=40 --leak-resolution=high \
--suppressions=$(srcdir)/valgrind_suppressions

else !VALGRIND_TESTS_ENABLED

CHECKER =

endif !VALGRIND_TESTS_ENABLED

TESTS_ENVIRONMENT = $(CHECKER)

AM_CPPFLAGS = \
-I.. \
-I../src \
@debug_flag@

check_LIBRARIES = libpwl_tests.a

libpwl_tests_a_SOURCES = \
pwl_test.cc

LDADD = \
../src/libpwl.la \
libpwl_tests.a

noinst_HEADERS = \
pwl_test.hh

EXTRA_DIST = valgrind_suppressions

TESTS = \
watchdog1

XFAIL_TESTS =

#
# Sources for the tests
#

watchdog1_SOURCES = watchdog1.cc

check_PROGRAMS = $(TESTS)

../src/libpwl.la:
	$(MAKE) $(AM_MAKEFLAGS) -C ../src libpwl.la
