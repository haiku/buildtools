/*	Definitions for ARM running Haiku systems using ELF
	Copyright (C) 1993, 1994, 1997, 1998, 1999, 2000, 2001, 2002, 2003, 2004,
	2005 Free Software Foundation, Inc.

	This file is part of GCC.

	GCC is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2, or (at your option)
	any later version.

	GCC is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with GCC; see the file COPYING.  If not, write to
	the Free Software Foundation, 59 Temple Place - Suite 330,
	Boston, MA 02111-1307, USA.  */

/* Unsigned chars produces much better code than signed.  */
#define DEFAULT_SIGNED_CHAR  0

#undef  TARGET_DEFAULT_FLOAT_ABI
#define TARGET_DEFAULT_FLOAT_ABI ARM_FLOAT_ABI_SOFT

/* We default to the "aapcs-linux" ABI so that enums are int-sized by
   default.  */
#undef  ARM_DEFAULT_ABI
#define ARM_DEFAULT_ABI ARM_ABI_AAPCS_LINUX

/* bpabi.h sets FPUTYPE_DEFAULT to VFP */

#undef  MULTILIB_DEFAULTS
#define MULTILIB_DEFAULTS \
  { "marm", "mlittle-endian", "msoft-float", "mno-thumb-interwork" }

/* Default is set by bpabi.h */
/*
#undef TARGET_DEFAULT
*/

#undef SUBTARGET_CPU_DEFAULT
#define SUBTARGET_CPU_DEFAULT TARGET_CPU_arm6

/* Now we define the strings used to build the spec file.  */
/* interestingly, bpabi defines __GXX_TYPEINFO_EQUALITY_INLINE=0 too as we do. */

#undef TARGET_OS_CPP_BUILTINS
#define TARGET_OS_CPP_BUILTINS()		\
  do									\
    {									\
      builtin_define ("__HAIKU__");					\
      builtin_define ("__ARM__");					\
      builtin_define ("__arm__");					\
      builtin_define ("__stdcall=__attribute__((__stdcall__))");	\
      builtin_define ("__cdecl=__attribute__((__cdecl__))");		\
      builtin_define ("__STDC_ISO_10646__=201103L"); \
      builtin_assert ("system=haiku");					\
      /* Haiku apparently doesn't support merging of symbols across shared \
		 object boundaries. Hence we need to explicitly specify that \
         type_infos are not merged, so that they get compared by name \
         instead of by pointer. */ \
      builtin_define ("__GXX_MERGED_TYPEINFO_NAMES=0"); \
      /*builtin_define ("__GXX_TYPEINFO_EQUALITY_INLINE=0"); done in bpabi: */\
      TARGET_BPABI_CPP_BUILTINS();					\
    }									\
  while (0)

/* Use the default LIBGCC_SPEC, not the empty version in haiku.h, as we
   do not use multilib (needed ??).  */
#undef LIBGCC_SPEC

/* If ELF is the default format, we should not use /lib/elf.  */

#undef	LINK_SPEC
#define LINK_SPEC "%{!o*:-o %b} -m armelf %{!r:-shared} %{nostart:-e 0} %{shared:-e 0} %{!shared: %{!nostart: -no-undefined}}\
  %{mbig-endian:-EB} %{mlittle-endian:-EL} -X"

