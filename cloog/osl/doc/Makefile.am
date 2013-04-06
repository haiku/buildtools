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
# * | T | |   |   | e |   | |   | |   |   |   | |   | |   | |    \  \  \    *
# * | E | |   |   |   |   | |   | |   |   |   | |   | |   | |     \  \  \   *
# * | * |*| * | * | * | * |*| * |*| * | * | * |*| * |*| * | /      \* \  \  *
# * | O |p| e | n | S | c |o| p |-| L | i | b |r| a |r| y |/        \  \ /  *
# * '---'-'---'---'---'---'-'---'-'---'---'---'-'---'-'---'          '--'   *
# *                                                                         *
# * Copyright (C) 2008 University Paris-Sud and INRIA                       *
# *                                                                         *
# * (3-clause BSD license)                                                  *
# *                                                                         *
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
SUBDIRS 		=

#############################################################################

MAINTAINERCLEANFILES	= Makefile.in

EXTRA_DIST		=			\
	htmldoc.tar.gz				\
	openscop.pdf				\
	S4.cloog				\
	ascii-art.txt				\
	images/basic.eps			\
	images/basic.fig			\
	images/basic.jpg			\
	images/basic.pdf			\
	images/basic.txt			\
	images/basic1.eps			\
	images/basic1.fig			\
	images/basic1.jpg			\
	images/basic1.pdf			\
	images/basic1.txt			\
	images/basic2.eps			\
	images/basic2.fig			\
	images/basic2.jpg			\
	images/basic2.pdf			\
	images/basic2.txt			\
	images/tree.eps				\
	images/tree.fig				\
	images/tree.jpg				\
	images/tree.pdf				\
	images/tree.txt


info_TEXINFOS		= openscop.texi

DOCDIR			= htmldoc
DOXYFILE		= Doxyfile
DOXYGEN			= @DOXYGEN@

# The following requires a fixed version of the Emacs 19.30 etags.
ETAGS_ARGS		= --lang=none \
 --regex='/^@node[ \t]+\([^,]+\)/\1/' $(srcdir)/doc/openscop.texi
TAGS_DEPENDENCIES	= openscop.texi $(DOXYFILE).in

htmldoc.tar.gz:
	mkdir -p $(top_srcdir)/doc/htmldoc
	$(DOXYGEN) $(DOXYFILE)
	tar czf htmldoc.tar.gz htmldoc
