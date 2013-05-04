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

# Libtool -version-info for libppl.la.
#
#  1. Start with version information of `0:0:0' for each Libtool library.
#
#  2. Update the version information only immediately before a public
#     release of your software.  More frequent updates are unnecessary,
#     and only guarantee that the current interface number gets larger
#     faster.
#
#  3. If the library source code has changed at all since the last
#     update, then increment REVISION (`C:R:A' becomes `C:r+1:A').
#
#  4. If any interfaces have been added, removed, or changed since the
#     last update, increment CURRENT, and set REVISION to 0.
#
#  5. If any interfaces have been added since the last public release,
#     then increment AGE.
#
#  6. If any interfaces have been removed since the last public release,
#     then set AGE to 0.
#
#	PPL release		-version-info
#	    0.1			    -----
#	    0.2			    -----
#	    0.3			    0:0:0
#	    0.4			    1:0:1
#	    0.5			    2:0:0
#	    0.6			    3:0:0
#	    0.7			    4:0:0
#	    0.8			    5:0:0
#	    0.9			    6:0:0
#	    0.10		    7:0:0
#	    0.10.1		    8:0:1
#	    0.10.2		    8:0:1
#	    0.11		    9:0:0
#	    0.11.1		    9:0:0

LIBPPL_LT_CURRENT =  9
LIBPPL_LT_REVISION = 0
LIBPPL_LT_AGE =      0

AM_CPPFLAGS = \
-I$(top_builddir) \
-I$(top_srcdir)/src \
@extra_includes@

lib_LTLIBRARIES = libppl.la

bin_PROGRAMS = ppl-config

ppl_config_SOURCES = \
BUGS.cc \
COPYING.cc \
CREDITS.cc

nodist_ppl_config_SOURCES = \
ppl-config.cc \
ppl.hh

ppl_config_LDADD = \
libppl.la

if USE_NATIVE_INTEGERS

COEFFICIENT_TYPES_INCLUDE_FILES =

COEFFICIENT_DEFS_INCLUDE_FILES =

endif USE_NATIVE_INTEGERS

if USE_CHECKED_INTEGERS

COEFFICIENT_TYPES_INCLUDE_FILES =

COEFFICIENT_DEFS_INCLUDE_FILES =

endif USE_CHECKED_INTEGERS

if USE_GMP_INTEGERS

COEFFICIENT_TYPES_INCLUDE_FILES = \
  GMP_Integer.types.hh

COEFFICIENT_DEFS_INCLUDE_FILES = \
  GMP_Integer.defs.hh \
  GMP_Integer.inlines.hh

endif USE_GMP_INTEGERS

# The ordering of the following list *matters*!
INCLUDE_FILES = \
namespaces.hh \
compiler.hh \
assert.hh \
meta_programming.hh \
Slow_Copy.hh \
Has_Assign_Or_Swap.hh \
assign_or_swap.hh \
mp_std_bits.defs.hh \
mp_std_bits.inlines.hh \
Temp.defs.hh \
Temp.inlines.hh \
Temp.templates.hh \
Coefficient_traits_template.hh \
Checked_Number.types.hh \
$(COEFFICIENT_TYPES_INCLUDE_FILES) \
Coefficient.types.hh \
stdiobuf.types.hh \
c_streambuf.types.hh \
globals.types.hh \
iterator_to_const.types.hh \
distances.types.hh \
Interval_Info.types.hh \
Interval.types.hh \
Box.types.hh \
Constraint.types.hh \
Generator.types.hh \
Grid_Generator.types.hh \
Congruence.types.hh \
Init.types.hh \
Row.types.hh \
Linear_Row.types.hh \
Matrix.types.hh \
Variable.types.hh \
Variables_Set.types.hh \
Linear_Expression.types.hh \
Linear_System.types.hh \
Bit_Row.types.hh \
Bit_Matrix.types.hh \
Constraint_System.types.hh \
Generator_System.types.hh \
Grid_Generator_System.types.hh \
Congruence_System.types.hh \
Scalar_Products.types.hh \
PIP_Tree.types.hh \
PIP_Problem.types.hh \
Poly_Con_Relation.types.hh \
Poly_Gen_Relation.types.hh \
BHRZ03_Certificate.types.hh \
H79_Certificate.types.hh \
Grid_Certificate.types.hh \
Partial_Function.types.hh \
Polyhedron.types.hh \
C_Polyhedron.types.hh \
NNC_Polyhedron.types.hh \
Grid.types.hh \
Ptr_Iterator.types.hh \
DB_Row.types.hh \
DB_Matrix.types.hh \
BD_Shape.types.hh \
OR_Matrix.types.hh \
Octagonal_Shape.types.hh \
fpu.types.hh \
Float.defs.hh \
Float.inlines.hh \
C_Integer.hh \
fpu.defs.hh \
fpu-c99.inlines.hh \
fpu-ia32.inlines.hh \
fpu-none.inlines.hh \
fpu-sparc.inlines.hh \
Rounding_Dir.defs.hh \
Rounding_Dir.inlines.hh \
Result.defs.hh \
Result.inlines.hh \
Numeric_Format.defs.hh \
checked.defs.hh \
checked.inlines.hh \
checked_int.inlines.hh \
checked_float.inlines.hh \
checked_mpz.inlines.hh \
checked_mpq.inlines.hh \
checked_ext.inlines.hh \
Checked_Number.defs.hh \
Checked_Number.inlines.hh \
Checked_Number.templates.hh \
WRD_coefficient_types.defs.hh \
WRD_coefficient_types.inlines.hh \
checked_numeric_limits.hh \
$(COEFFICIENT_DEFS_INCLUDE_FILES) \
Coefficient.defs.hh \
Coefficient.inlines.hh \
stdiobuf.defs.hh \
stdiobuf.inlines.hh \
c_streambuf.defs.hh \
c_streambuf.inlines.hh \
globals.defs.hh \
globals.inlines.hh \
math_utilities.defs.hh \
math_utilities.inlines.hh \
iterator_to_const.defs.hh \
iterator_to_const.inlines.hh \
distances.defs.hh \
distances.inlines.hh \
Boundary.defs.hh \
intervals.defs.hh \
Interval_Info.defs.hh \
Interval_Info.inlines.hh \
Interval_Restriction.defs.hh \
Interval.defs.hh \
Interval.inlines.hh \
Interval.templates.hh \
Box.defs.hh \
Box_Status.inlines.hh \
Box.inlines.hh \
Box.templates.hh \
Rational_Interval.hh \
Rational_Box.hh \
Variable.defs.hh \
Variable.inlines.hh \
Variables_Set.defs.hh \
Variables_Set.inlines.hh \
Init.defs.hh \
Init.inlines.hh \
initializer.hh \
Topology.hh \
Row.defs.hh \
Row.inlines.hh \
Linear_Row.defs.hh \
Linear_Row.inlines.hh \
Matrix.defs.hh \
Matrix.inlines.hh \
Bit_Row.defs.hh \
Bit_Row.inlines.hh \
Linear_System.defs.hh \
Linear_System.inlines.hh \
Bit_Matrix.defs.hh \
Bit_Matrix.inlines.hh \
Constraint_System.defs.hh \
Generator_System.defs.hh \
Grid_Generator_System.defs.hh \
Congruence_System.defs.hh \
Linear_Expression.defs.hh \
Linear_Expression.inlines.hh \
Constraint.defs.hh \
Constraint.inlines.hh \
Constraint_System.inlines.hh \
Generator.defs.hh \
Generator.inlines.hh \
Grid_Generator.defs.hh \
Grid_Generator.inlines.hh \
Congruence.defs.hh \
Congruence.inlines.hh \
Generator_System.inlines.hh \
Grid_Generator_System.inlines.hh \
Congruence_System.inlines.hh \
Scalar_Products.defs.hh \
Scalar_Products.inlines.hh \
MIP_Problem.types.hh \
MIP_Problem.defs.hh \
MIP_Problem.inlines.hh \
MIP_Problem.templates.hh \
PIP_Tree.types.hh \
PIP_Tree.defs.hh \
PIP_Tree.inlines.hh \
PIP_Problem.types.hh \
PIP_Problem.defs.hh \
PIP_Problem.inlines.hh \
PIP_Problem.templates.hh \
Poly_Con_Relation.defs.hh \
Poly_Con_Relation.inlines.hh \
Poly_Gen_Relation.defs.hh \
Poly_Gen_Relation.inlines.hh \
BHRZ03_Certificate.defs.hh \
BHRZ03_Certificate.inlines.hh \
H79_Certificate.defs.hh \
H79_Certificate.inlines.hh \
Grid_Certificate.defs.hh \
Grid_Certificate.inlines.hh \
Partial_Function.defs.hh \
Partial_Function.inlines.hh \
Polyhedron.defs.hh \
Ph_Status.inlines.hh \
Polyhedron.inlines.hh \
Polyhedron.templates.hh \
Grid.defs.hh \
Grid_Status.inlines.hh \
Grid.inlines.hh \
Grid.templates.hh \
C_Polyhedron.defs.hh \
C_Polyhedron.inlines.hh \
NNC_Polyhedron.defs.hh \
NNC_Polyhedron.inlines.hh \
Widening_Function.types.hh \
Widening_Function.defs.hh \
Widening_Function.inlines.hh \
Ptr_Iterator.defs.hh \
Ptr_Iterator.inlines.hh \
DB_Row.defs.hh \
DB_Row.inlines.hh \
DB_Row.templates.hh \
DB_Matrix.defs.hh \
DB_Matrix.inlines.hh \
DB_Matrix.templates.hh \
BD_Shape.defs.hh \
BDS_Status.inlines.hh \
BD_Shape.inlines.hh \
BD_Shape.templates.hh \
OR_Matrix.defs.hh \
OR_Matrix.inlines.hh \
OR_Matrix.templates.hh \
Octagonal_Shape.defs.hh \
Og_Status.inlines.hh \
Octagonal_Shape.inlines.hh \
Octagonal_Shape.templates.hh \
Determinate.types.hh \
Determinate.defs.hh \
Determinate.inlines.hh \
Powerset.types.hh \
Powerset.defs.hh \
Powerset.inlines.hh \
Powerset.templates.hh \
Pointset_Powerset.types.hh \
Pointset_Powerset.defs.hh \
Pointset_Powerset.inlines.hh \
Pointset_Powerset.templates.hh \
Partially_Reduced_Product.types.hh \
Partially_Reduced_Product.defs.hh \
Partially_Reduced_Product.inlines.hh \
Partially_Reduced_Product.templates.hh \
Weight_Profiler.defs.hh \
max_space_dimension.hh \
algorithms.hh \
termination.defs.hh \
termination.templates.hh \
wrap_assign.hh \
wrap_string.hh
#Any_Pointset.types.hh \
#Any_Pointset.defs.hh \
#Any_Pointset.inlines.hh \
#Ask_Tell.types.hh \
#Ask_Tell.defs.hh \
#Ask_Tell.inlines.hh \
#Ask_Tell.templates.hh \
#Pointset_Ask_Tell.types.hh \
#Pointset_Ask_Tell.defs.hh \
#Pointset_Ask_Tell.inlines.hh \
#Pointset_Ask_Tell.templates.hh

NESTED_INCLUDE_FILES = \
Ph_Status.idefs.hh \
Grid_Status.idefs.hh \
Box_Status.idefs.hh \
BDS_Status.idefs.hh \
Og_Status.idefs.hh

libppl_la_SOURCES = \
Box.cc \
checked.cc \
Checked_Number.cc \
Float.cc \
fpu-ia32.cc \
Constraint.cc \
Constraint_System.cc \
Congruence.cc \
Congruence_System.cc \
Generator_System.cc \
Grid_Generator_System.cc \
Generator.cc \
Grid_Generator.cc \
Init.cc \
Coefficient.cc \
Linear_Expression.cc \
Linear_System.cc \
Matrix.cc \
Scalar_Products.cc \
MIP_Problem.cc \
PIP_Tree.cc \
PIP_Problem.cc \
Poly_Con_Relation.cc \
Poly_Gen_Relation.cc \
BHRZ03_Certificate.cc \
H79_Certificate.cc \
Grid_Certificate.cc \
Partial_Function.cc \
Polyhedron_nonpublic.cc \
Polyhedron_public.cc \
Polyhedron_chdims.cc \
Polyhedron_widenings.cc \
C_Polyhedron.cc \
NNC_Polyhedron.cc \
Grid_nonpublic.cc \
Grid_public.cc \
Grid_chdims.cc \
Grid_widenings.cc \
BD_Shape.cc \
Octagonal_Shape.cc \
Pointset_Powerset.cc \
Row.cc \
Linear_Row.cc \
Bit_Matrix.cc \
Bit_Row.cc \
Ph_Status.cc \
Grid_Status.cc \
Variable.cc \
Variables_Set.cc \
conversion.cc \
minimize.cc \
simplify.cc \
Grid_conversion.cc \
Grid_simplify.cc \
stdiobuf.cc \
c_streambuf.cc \
globals.cc \
mp_std_bits.cc \
Weight_Profiler.cc \
version.cc \
$(INCLUDE_FILES) \
$(NESTED_INCLUDE_FILES) \
swapping_sort.icc \
termination.cc \
wrap_string.cc
#Pointset_Ask_Tell.cc

if NO_UNDEFINED

NO_UNDEFINED_FLAG = -no-undefined

endif NO_UNDEFINED

libppl_la_LIBADD = @extra_libraries@

libppl_la_LDFLAGS = \
$(NO_UNDEFINED_FLAG) \
-version-info $(LIBPPL_LT_CURRENT):$(LIBPPL_LT_REVISION):$(LIBPPL_LT_AGE)

if BUILD_CXX_INTERFACE

include_HEADERS = ppl.hh

else !BUILD_CXX_INTERFACE

noinst_HEADERS = ppl.hh

endif !BUILD_CXX_INTERFACE

nodist_noinst_HEADERS = ppl_include_files.hh

ppl_include_files.hh: $(INCLUDE_FILES) Makefile
	for file in $(INCLUDE_FILES) ; \
	do \
	  i="#include \"$$file\"" ; \
	  ( cd $(top_srcdir)/src ; $(FGREP) -q "$$i" $(INCLUDE_FILES) ) || echo "$$i" ; \
	done > $@

EXTRA_DIST = ppl_header.hh ppl-config.cc.in version.hh.in

if HAVE_PERL

ppl.hh:	$(top_builddir)/ppl-config.h $(top_builddir)/src/version.hh ppl_header.hh ppl_include_files.hh $(INCLUDE_FILES) $(NESTED_INCLUDE_FILES) Makefile $(top_builddir)/utils/build_header
	$(top_builddir)/utils/build_header \
		-I $(top_builddir) -I $(top_builddir)/src \
		$(top_srcdir)/src/ppl_header.hh >$@

BUGS.cc: $(top_builddir)/utils/text2cxxarray $(top_srcdir)/BUGS
	$(top_builddir)/utils/text2cxxarray --name=BUGS_array \
		$(top_srcdir)/BUGS >$@
COPYING.cc: $(top_builddir)/utils/text2cxxarray $(top_srcdir)/COPYING
	$(top_builddir)/utils/text2cxxarray --name=COPYING_array \
		$(top_srcdir)/COPYING >$@
CREDITS.cc: $(top_builddir)/utils/text2cxxarray $(top_srcdir)/CREDITS
	$(top_builddir)/utils/text2cxxarray --name=CREDITS_array \
		$(top_srcdir)/CREDITS >$@

else !HAVE_PERL

ppl.hh.sed: Makefile
	@echo "/^\/\* BEGIN ppl-config.h \*\/$$/ {"    >$@
	@echo "  r $(top_builddir)/ppl-config.h"      >>$@
	@echo "  : loop"                              >>$@
	@echo "  /\n\/\* END ppl-config.h \*\/$$/ !{" >>$@
	@echo "    N"                                 >>$@
	@echo "    b loop"                            >>$@
	@echo "  }"                                   >>$@
	@echo "  d"                                   >>$@
	@echo "}"                                     >>$@

ppl.hh:	ppl.hh.dist ppl.hh.sed
	$(SED) -f ppl.hh.sed $< >$@
	rm -f ppl.hh.sed

BUGS.cc:	BUGS.cc.dist
	cp -f $< $@
COPYING.cc:	COPYING.cc.dist
	cp -f $< $@
CREDITS.cc:	CREDITS.cc.dist
	cp -f $< $@

endif !HAVE_PERL

if USE_PRECOMPILED_HEADERS

ppl.hh.gch: ppl.hh
	$(CXXCOMPILE) -xc++-header -o $@ $<

PRECOMPILED = ppl.hh.gch

else !USE_PRECOMPILED_HEADERS

PRECOMPILED =

endif !USE_PRECOMPILED_HEADERS

BUILT_SOURCES = \
$(include_HEADERS) \
$(nodist_noinst_HEADERS) \
$(noinst_HEADERS) \
$(PRECOMPILED) \
BUGS.cc \
COPYING.cc \
CREDITS.cc

# ppl.hh is not distributed.
# ppl.hh.dist, which is distributed, is a copy of ppl.hh;
# likewise for BUGS.cc.dist, COPYING.cc.dist and CREDITS.cc.dist.
dist-hook:
	mv -f $(distdir)/ppl.hh $(distdir)/ppl.hh.dist
	mv -f $(distdir)/BUGS.cc $(distdir)/BUGS.cc.dist
	mv -f $(distdir)/COPYING.cc $(distdir)/COPYING.cc.dist
	mv -f $(distdir)/CREDITS.cc $(distdir)/CREDITS.cc.dist

CLEANFILES = $(BUILT_SOURCES)

$(top_builddir)/utils/build_header:
	$(MAKE) $(AM_MAKEFLAGS) -C $(top_builddir)/utils build_header

$(top_builddir)/utils/text2cxxarray:
	$(MAKE) $(AM_MAKEFLAGS) -C $(top_builddir)/utils text2cxxarray

$(top_builddir)/ppl-config.h:
	$(MAKE) $(AM_MAKEFLAGS) -C $(top_builddir) ppl-config.h
