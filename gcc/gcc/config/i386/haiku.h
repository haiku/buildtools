/* Definitions for Intel x86 running Haiku
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


#undef ASM_COMMENT_START
#define ASM_COMMENT_START " #"

/* The SVR4 ABI for the i386 says that records and unions are returned
   in memory.  */
#undef DEFAULT_PCC_STRUCT_RETURN
#define DEFAULT_PCC_STRUCT_RETURN 1

#undef DBX_REGISTER_NUMBER
#define DBX_REGISTER_NUMBER(n) \
  (TARGET_64BIT ? dbx64_register_map[n] : svr4_dbx_register_map[n])

#define TARGET_OS_CPP_BUILTINS()					\
  do									\
    {									\
	builtin_define ("__HAIKU__");					\
	builtin_define ("__INTEL__");					\
	builtin_define ("_X86_");					\
	builtin_define ("__stdcall=__attribute__((__stdcall__))");	\
	builtin_define ("__cdecl=__attribute__((__cdecl__))");		\
    builtin_define ("__STDC_ISO_10646__=201103L"); \
	builtin_assert ("system=haiku");					\
    }									\
  while (0)

/* Provide a LINK_SPEC appropriate for Haiku.  Here we provide support
   for the special GCC options -static and -shared, which allow us to
   link things in one of these three modes by applying the appropriate
   combinations of options at link-time.  */

/* If ELF is the default format, we should not use /lib/elf.  */

#undef	LINK_SPEC
#define LINK_SPEC "-m elf_i386_haiku %{!r:-shared} %{nostart:-e 0} %{shared:-e 0} %{!shared: %{!nostart: -no-undefined}}"

/* A C statement (sans semicolon) to output to the stdio stream
   FILE the assembler definition of uninitialized global DECL named
   NAME whose size is SIZE bytes and alignment is ALIGN bytes.
   Try to use asm_output_aligned_bss to implement this macro.  */

#define ASM_OUTPUT_ALIGNED_BSS(FILE, DECL, NAME, SIZE, ALIGN) \
  asm_output_aligned_bss (FILE, DECL, NAME, SIZE, ALIGN)

/* On 32-bit i386, because there are so few registers, keep the frame pointer disabled by default.
 * Other architectures have it always enabled for Haiku */
#undef CC1_SPEC
#define CC1_SPEC HAIKU_CC1_SPEC
