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

# Tell aclocal where to find `.m4' files.
ACLOCAL_AMFLAGS = -I m4

dist_noinst_SCRIPTS = \
configure

if BUILD_WATCHDOG_LIBRARY

SUBDIRS = . m4 utils src tests doc

nodist_noinst_HEADERS = \
pwl-config.h

pwl-config.h: config.h $(srcdir)/pwl-config.sed
	$(SED) -f $(srcdir)/pwl-config.sed $< >$@

pwl-config.h.in: config.h.in $(srcdir)/pwl-config.sed
	$(SED) -f $(srcdir)/pwl-config.sed $< >$@

endif BUILD_WATCHDOG_LIBRARY

# Kludge: we need to force building `pwl-config.h' on `make dist',
# hence we list it in `EXTRA_DIST';  but we do not want to distribute
# it, hence we erase it in `dist-hook'.
dist-hook:
	rm -f $(distdir)/pwl-config.h

# Kludge: we need to force building `pwl-config.h' on `make dist',
# hence we list it in `EXTRA_DIST';  but we do not want to distribute
# it, hence we erase it in `dist-hook'.
EXTRA_DIST = \
pwl-config.h \
pwl-config.h.in \
pwl-config.sed \
BUGS \
ChangeLog_2001-2008 \
CREDITS

DISTCLEANFILES = \
pwl-config.h
