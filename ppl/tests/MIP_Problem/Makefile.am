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
-I$(top_srcdir)/src \
-I$(top_builddir)/src \
-I$(top_srcdir)/utils \
-I$(top_srcdir)/tests \
@extra_includes@ \
@debug_flag@

LDADD = \
$(top_builddir)/utils/libppl_utils.a \
$(top_builddir)/tests/libppl_tests.a \
$(top_builddir)/src/libppl.la \
@extra_libraries@

TESTS = \
ascii_dump_load1 \
exceptions1 \
mipproblem1 \
mipproblem3

XFAIL_TESTS =

BUGS =

#
# Sources for the tests
#

ascii_dump_load1_SOURCES = ascii_dump_load1.cc

exceptions1_SOURCES = exceptions1.cc

mipproblem1_SOURCES = mipproblem1.cc

mipproblem2_SRCS = mipproblem2.cc

mipproblem3_SOURCES = mipproblem3.cc

if BUILD_WATCHDOG_LIBRARY
WATCHDOG_TESTS = mipproblem2

mipproblem2_SOURCES = $(mipproblem2_SRCS)
mipproblem2_CPPFLAGS = \
$(AM_CPPFLAGS) \
-I$(top_builddir)/Watchdog \
-I$(top_builddir)/Watchdog/src
mipproblem2_LDADD = $(LDADD) $(top_builddir)/Watchdog/src/libpwl.la

endif BUILD_WATCHDOG_LIBRARY

check_PROGRAMS = \
$(TESTS) \
$(WATCHDOG_TESTS) \
$(BUGS)

EXTRA_DIST = $(mipproblem2_SRCS)

MOSTLYCLEANFILES = \
ascii_dump_load1.dat

$(top_builddir)/utils/libppl_utils.a:
	$(MAKE) $(AM_MAKEFLAGS) -C $(top_builddir)/utils libppl_utils.a

$(top_builddir)/tests/libppl_tests.a:
	$(MAKE) $(AM_MAKEFLAGS) -C $(top_builddir)/tests libppl_tests.a

$(top_builddir)/src/libppl.la:
	$(MAKE) $(AM_MAKEFLAGS) -C $(top_builddir)/src libppl.la

$(top_builddir)/Watchdog/src/libpwl.la:
	$(MAKE) $(AM_MAKEFLAGS) -C $(top_builddir)/Watchdog/src libpwl.la
