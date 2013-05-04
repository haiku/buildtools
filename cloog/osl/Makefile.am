#
#   /*+------------------------------------------------------------------**
#    **                       OpenScop Library                           **
#    **------------------------------------------------------------------**
#    **                         makefile.am                              **
#    **------------------------------------------------------------------**
#    **                   First version: 30/04/2008                      **
#    **------------------------------------------------------------------**
#
#   
# ***************************************************************************
# * OpenScop: Structures and formats for polyhedral tools to talk together  *
# ***************************************************************************
# *   ,___,,_,__,,__,,__,,__,,_,__,,_,__,,__,,___,_,__,,_,__,               *
# *   /   / /  //  //  //  // /   / /  //  //   / /  // /  /|,_,            *
# *  /   / /  //  //  //  // /   / /  //  //   / /  // /  / / /\            *
# * |~~~|~|~~~|~~~|~~~|~~~|~|~~~|~|~~~|~~~|~~~|~|~~~|~|~~~|/_/  \           *
# * | G |C| P | = | L | P |=| = |C| = | = | = |=| = |=| C |\  \ /\          *
# * | R |l| o | = | e | l |=| = |a| = | = | = |=| = |=| L | \# \ /\         *
# * | A |a| l | = | t | u |=| = |n| = | = | = |=| = |=| o | |\# \  \        *
# * | P |n| l | = | s | t |=| = |d| = | = | = | |   |=| o | | \# \  \       *
# * | H | | y |   | e | o | | = |l|   |   | = | |   | | G | |  \  \  \      *
# * | I | |   |   | e |   | |   | |   |   |   | |   | |   | |   \  \  \     *
# * | T | |   |   |   |   | |   | |   |   |   | |   | |   | |    \  \  \    *
# * | E | |   |   |   |   | |   | |   |   |   | |   | |   | |     \  \  \   *
# * | * |*| * | * | * | * |*| * |*| * | * | * |*| * |*| * | /      \* \  \  *
# * | O |p| e | n | S | c |o| p |-| L | i | b |r| a |r| y |/        \  \ /  *
# * '---'-'---'---'---'---'-'---'-'---'---'---'-'---'-'---'          '--'   *
# *                                                                         *
# * Copyright (C) 2008 University Paris-Sud 11 and INRIA                    *
# *                                                                         *
# * (3-clause BSD license)                                                  *
# * Redistribution and use in source  and binary forms, with or without     *
# * modification, are permitted provided that the following conditions      *
# * are met:                                                                *
# *                                                                         *
# * 1. Redistributions of source code must retain the above copyright       *
# *    notice, this list of conditions and the following disclaimer.        *
# * 2. Redistributions in binary form must reproduce the above copyright    *
# *    notice, this list of conditions and the following disclaimer in the  *
# *    documentation and/or other materials provided with the distribution. *
# * 3. The name of the author may not be used to endorse or promote         *
# *    products derived from this software without specific prior written   *
# *    permission.                                                          *
# *                                                                         *
# * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR    *
# * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED          *
# * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE  *
# * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,      *
# * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES      *
# * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR      *
# * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)      *
# * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,     *
# * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING   *
# * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE      *
# * POSSIBILITY OF SUCH DAMAGE.                                             *
# *                                                                         *
# * OpenScop Library, a library to manipulate OpenScop formats and data     *
# * structures. Written by:                                                 *
# * Cedric Bastoul     <Cedric.Bastoul@u-psud.fr> and                       *
# * Louis-Noel Pouchet <Louis-Noel.pouchet@inria.fr>                        *
# *                                                                         *
# ***************************************************************************/
#
# Makefile.am (or makefile if generated) of the OpenScop Library.
# Makefile.am is not a makefile, you must run the 'autogen.sh' THEN the
# configure shellscript to generate the Makefile thanks to this file.


#############################################################################

SUBDIRS = . doc tests
ACLOCAL_AMFLAGS = -I m4

#############################################################################

lib_LTLIBRARIES = libosl.la

#############################################################################

pkginclude_HEADERS = \
	include/osl/osl.h \
	include/osl/statement.h \
	include/osl/interface.h \
	include/osl/generic.h \
	include/osl/vector.h \
	include/osl/relation.h \
	include/osl/relation_list.h \
	include/osl/macros.h \
	include/osl/int.h \
	include/osl/names.h \
	include/osl/strings.h \
	include/osl/body.h \
	include/osl/util.h \
	include/osl/scop.h

pkgextensionsincludedir = $(pkgincludedir)/extensions
pkgextensionsinclude_HEADERS = \
	include/osl/extensions/textual.h \
	include/osl/extensions/comment.h \
	include/osl/extensions/scatnames.h \
	include/osl/extensions/arrays.h \
	include/osl/extensions/coordinates.h \
	include/osl/extensions/irregular.h

DEFAULT_INCLUDES = -I.
INCLUDES = -I$(top_builddir)/include -I$(top_srcdir)/include
AM_CFLAGS = $(CFLAGS_WARN)

#############################################################################

libosl_la_CPPFLAGS = -g
libosl_la_SOURCES = \
	source/scop.c \
	source/statement.c \
	source/extensions/textual.c \
	source/extensions/comment.c \
	source/extensions/scatnames.c \
	source/extensions/arrays.c \
	source/extensions/coordinates.c \
	source/extensions/irregular.c \
	source/interface.c \
	source/generic.c \
	source/relation.c \
	source/relation_list.c \
	source/vector.c \
	source/names.c \
	source/strings.c \
	source/body.c \
	source/int.c \
	source/util.c

MAINTAINERCLEANFILES 	=			\
	autoconf/texinfo.tex			\
	Makefile.in				\
	aclocal.m4				\
	configure				\
	source/stamp-h.in			\
	$(AUX_DIST)

#############################################################################

ctags:
	ctags -R --c++-kinds=+p --fields=+iaS --extra=+q -f$(HOME)/.ctags .

#############################################################################
