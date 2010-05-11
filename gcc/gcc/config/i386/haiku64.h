/* Definitions for AMD x86_64 running Haiku with ELF format.
   Copyright (C) 1998, 1999, 2000, 2001, 2002, 2004
   Free Software Foundation, Inc.

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


#if TARGET_64BIT_DEFAULT
#define TARGET_VERSION fprintf (stderr, " (x86-64 Haiku/ELF)");
#else
#define TARGET_VERSION fprintf (stderr, " (i386 Haiku/ELF)");
#endif

/* The SVR4 ABI for the i386 says that records and unions are returned
 *   in memory.  
 *
 *   TODO: Linux64 doesn't use pcc_struct_return scheme. Does haiku? 
 *         If not this could be removed.
 */
#undef DEFAULT_PCC_STRUCT_RETURN
#define DEFAULT_PCC_STRUCT_RETURN 1

#define TARGET_OS_CPP_BUILTINS()					\
  do									\
    {									\
	builtin_define ("__HAIKU__");					\
	builtin_define ("__stdcall=__attribute__((__stdcall__))");	\
	builtin_define ("__cdecl=__attribute__((__cdecl__))");		\
	builtin_assert ("system=haiku");					\
    /* Haiku apparently doesn't support merging of symbols across shared \
       object boundaries. Hence we need to explicitly specify that \
       type_infos are not merged, so that they get compared by name \
       instead of by pointer. */ \
    builtin_define ("__GXX_MERGED_TYPEINFO_NAMES=0"); \
    builtin_define ("__GXX_TYPEINFO_EQUALITY_INLINE=0"); \
    }									\
  while (0)

/* Provide a LINK_SPEC appropriate for Haiku.  Here we provide support
   for the special GCC options -static and -shared, which allow us to
   link things in one of these three modes by applying the appropriate
   combinations of options at link-time.  */

#undef	LINK_SPEC
#define LINK_SPEC "-m elf_x86_64_haiku -shared -Bsymbolic %{nostart:-e 0} %{shared:-e 0} %{!shared: %{!nostart: -no-undefined}}"

