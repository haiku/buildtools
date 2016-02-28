/* Definitions for MIPS running Haiku
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


#define TARGET_OS_CPP_BUILTINS()					\
  do									\
    {									\
	builtin_define ("__HAIKU__");					\
	builtin_define ("__MIPS__");					\
	builtin_define ("__MIPSEL__");					\
	builtin_define ("_MIPSEL_");					\
	builtin_define ("__stdcall=__attribute__((__stdcall__))");	\
	builtin_define ("__cdecl=__attribute__((__cdecl__))");		\
    builtin_define ("__STDC_ISO_10646__=201103L"); \
	builtin_assert ("system=haiku");					\
	if (flag_pic)							\
	  {								\
	    builtin_define ("__PIC__");					\
	    builtin_define ("__pic__");					\
	  }								\
    }									\
  while (0)

#undef	LINK_SPEC
#define LINK_SPEC "%{!o*:-o %b} -m elf_mipsel_haiku %{!r:-shared} %{nostart:-e 0}"

