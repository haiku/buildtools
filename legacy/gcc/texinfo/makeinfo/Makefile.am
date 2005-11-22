## Makefile.am for texinfo/makeinfo.
## $Id: Makefile.am,v 1.1 2004/10/28 18:14:10 zooey Exp $
## Run automake in .. to produce Makefile.in from this.

noinst_PROGRAMS = makeinfo

localedir = $(datadir)/locale
INCLUDES = -I$(top_srcdir)/lib -I../intl -DLOCALEDIR=\"$(localedir)\"
LDADD = ../lib/libtxi.a @INTLLIBS@

makeinfo_SOURCES = makeinfo.c makeinfo.h multi.c

EXTRA_DIST = README
