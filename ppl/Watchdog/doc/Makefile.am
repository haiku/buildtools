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
# For the most up-to-date information see the Parma Watchdog Library
# site: http://www.cs.unipr.it/pwl/ .

# All the documentation in docdir.
docdir = @docdir@
htmldir = $(docdir)
pdfdir = $(docdir)
psdir = $(docdir)
txtdir = $(docdir)

DOXYGEN = doxygen
INSTALLDOX = ./installdox -q

# Licenses.

PDF_LICENSES = \
gpl.pdf \
fdl.pdf

PS_LICENSES = \
gpl.ps.gz \
fdl.ps.gz

TXT_LICENSES = \
gpl.txt \
fdl.txt

# Library Core Manuals (C++ interface)

USER_CORE_HTML_MANUAL = pwl-user-@VERSION@-html.tar.gz
DEVREF_CORE_HTML_MANUAL = pwl-devref-@VERSION@-html.tar.gz

USER_CORE_PDF_MANUAL = pwl-user-@VERSION@.pdf
DEVREF_CORE_PDF_MANUAL = pwl-devref-@VERSION@.pdf

USER_CORE_PS_MANUAL = pwl-user-@VERSION@.ps.gz
DEVREF_CORE_PS_MANUAL = pwl-devref-@VERSION@.ps.gz

USER_CORE_HTML_DIR = pwl-user-@VERSION@-html
DEVREF_CORE_HTML_DIR = pwl-devref-@VERSION@-html

HTML_DIRS = $(USER_CORE_HTML_DIR) $(DEVREF_CORE_HTML_DIR)

DOX_FILES = \
gpl.dox \
fdl.dox

USER_CORE_STUFF = \
$(DOX_FILES) \
user.tex \
pwl.sty \
../src/pwl_header.hh ../src/pwl_include_files.hh

DEVREF_CORE_STUFF = \
$(DOX_FILES) \
devref.tex \
pwl.sty \
$(PWL_SOURCE_FILES)

##### Distributed documentation #####

DIST_HTML_DOCS = $(USER_CORE_HTML_MANUAL)

DIST_PDF_DOCS = \
$(PDF_LICENSES) \
$(USER_CORE_PDF_MANUAL)

DIST_PS_DOCS = \
$(PS_LICENSES) \
$(USER_CORE_PS_MANUAL)

DIST_TXT_DOCS = \
$(TXT_LICENSES)

DIST_DOCS = \
$(DIST_HTML_DOCS) \
$(DIST_PDF_DOCS) \
$(DIST_PS_DOCS) \
$(DIST_TXT_DOCS)

NONDIST_MANUALS = \
$(DEVREF_CORE_HTML_MANUAL) \
$(DEVREF_CORE_PDF_MANUAL) \
$(DEVREF_CORE_PS_MANUAL)

##### Build Targets #####

# Do nothing by default.
all:

user-html: $(USER_CORE_HTML_MANUAL)

user-pdf: $(USER_CORE_PDF_MANUAL)

user-ps: $(USER_CORE_PS_MANUAL)

user: user-html user-pdf user-ps

devref-html: $(DEVREF_CORE_HTML_MANUAL)

devref-pdf: $(DEVREF_CORE_PDF_MANUAL)

devref-ps: $(DEVREF_CORE_PS_MANUAL)

devref: devref-html devref-pdf devref-ps

world: user devref

install-data-local: \
install-html \
install-pdf \
install-ps \
install-txt

installdirs-local: \
installdirs-html \
installdirs-pdf \
installdirs-ps \
installdirs-txt

uninstall-local: \
uninstall-html \
uninstall-pdf \
uninstall-ps \
uninstall-txt

# Installation and uninstallation of HTML documentation.
install-html:
	for ball in $(DIST_HTML_DOCS); do \
	  test -f $$ball || test -f $(srcdir)/$$ball || $(MAKE) $$ball; \
	  dir=`basename $$ball .tar.gz`; \
	  $(mkinstalldirs) $(DESTDIR)$(htmldir)/$$dir; \
	  gunzip -c `if test -f $$ball; then echo .; else echo $(srcdir); fi`/$$ball | tar xf - ; \
	  for file in $$dir/*; do \
	    $(INSTALL_DATA) $$file $(DESTDIR)$(htmldir)/$$dir/`basename $$file`; \
	  done; \
	done

installdirs-html:
	for ball in $(DIST_HTML_DOCS); do \
	  dir=`basename $$ball .tar.gz`; \
	  $(mkinstalldirs) $(DESTDIR)$(htmldir)/$$dir; \
	done

uninstall-html:
	for ball in $(DIST_HTML_DOCS); do \
	  dir=`basename $$ball .tar.gz`; \
	  rm -rf $(DESTDIR)$(htmldir)/$$dir; \
	done

# Installation and uninstallation of PDF documentation.
install-pdf:
	$(mkinstalldirs) $(DESTDIR)$(pdfdir)
	for file in $(DIST_PDF_DOCS); do \
	  test -f $$file || test -f $(srcdir)/$$file || $(MAKE) $$file; \
	  $(INSTALL_DATA) `if test -f $$file; then echo .; else echo $(srcdir); fi`/$$file $(DESTDIR)$(pdfdir)/$$file; \
	done

installdirs-pdf:
	$(mkinstalldirs) $(DESTDIR)$(pdfdir)

uninstall-pdf:
	rm -f $(DESTDIR)$(pdfdir)/*.pdf

# Installation and uninstallation of PostScript documentation.
install-ps:
	$(mkinstalldirs) $(DESTDIR)$(psdir)
	for file in $(DIST_PS_DOCS); do \
	  test -f $$file || test -f $(srcdir)/$$file || $(MAKE) $$file; \
	  $(INSTALL_DATA) `if test -f $$file; then echo .; else echo $(srcdir); fi`/$$file $(DESTDIR)$(psdir)/$$file; \
	done

installdirs-ps:
	$(mkinstalldirs) $(DESTDIR)$(psdir)

uninstall-ps:
	rm -f $(DESTDIR)$(psdir)/*.ps.gz

# Installation and uninstallation of pure text documentation.
install-txt:
	$(mkinstalldirs) $(DESTDIR)$(txtdir)
	for file in $(srcdir)/*.txt $(srcdir)/README.doc; do \
	  $(INSTALL_DATA) $$file $(DESTDIR)$(txtdir)/`basename $$file`; \
	done
	for file in BUGS COPYING CREDITS ChangeLog NEWS README; do \
	  $(INSTALL_DATA) $(srcdir)/../$$file $(DESTDIR)$(txtdir)/$$file; \
	done

installdirs-txt:
	$(mkinstalldirs) $(DESTDIR)$(txtdir)

uninstall-txt:
	rm -f $(DESTDIR)$(txtdir)/*.txt $(DESTDIR)$(txtdir)/README.doc
	for file in BUGS COPYING CREDITS ChangeLog NEWS README README.configure ; do \
	  rm -f $(DESTDIR)$(txtdir)/$$file; \
	done

PWL_SOURCE_FILES = $(wildcard $(srcdir)/../src/*.hh $(srcdir)/../src/*.cc)

LATEX_DIRS = \
user.latex-dir \
devref.latex-dir

TEX_ENV = TEXINPUTS=$(abs_srcdir):$(TEXINPUTS)

.SECONDARY: $(LATEX_DIRS)

user.latex-dir: user.doxyconf-latex $(USER_CORE_STUFF)
	rm -rf $@
	$(TEX_ENV) $(DOXYGEN) $<

devref.latex-dir: devref.doxyconf-latex $(DEVREF_CORE_STUFF)
	rm -rf $@
	$(TEX_ENV) $(DOXYGEN) $<

pwl-user-@VERSION@.pdf: user.latex-dir
	$(TEX_ENV) make -C $< refman.pdf && mv -f $</refman.pdf $@

pwl-devref-@VERSION@.pdf: devref.latex-dir
	$(TEX_ENV) make -C $< refman.pdf && mv -f $</refman.pdf $@

$(USER_CORE_HTML_DIR): user.doxyconf-html $(USER_CORE_STUFF)
	rm -rf $@
	$(TEX_ENV) $(DOXYGEN) $<

$(DEVREF_CORE_HTML_DIR): devref.doxyconf-html $(DEVREF_CORE_STUFF)
	rm -rf $@
	$(TEX_ENV) $(DOXYGEN) $<

############################################################################

%.tar: %
	tar cf $@ $<

%.gz: %
	gzip --best --force $<

%.pdf: %.tex
	$(TEX_ENV) pdflatex $<

%.ps:	%.pdf
	pdftops $< $@

EXTRA_DIST= \
$(DIST_DOCS) \
$(DOX_FILES) \
user.tex \
devref.tex \
gpl.tex \
fdl.tex \
pwl.sty \
README.doc

mostlyclean-local:
	rm -rf $(HTML_DIRS) $(LATEX_DIRS) $(NONDIST_MANUALS) *.aux *.log

CLEANFILES = \
$(USER_CORE_HTML_DIR).tag \
$(DEVREF_CORE_HTML_DIR).tag

../src/pwl_include_files.hh:
	$(MAKE) $(AM_MAKEFLAGS) -C ../src pwl_include_files.hh
