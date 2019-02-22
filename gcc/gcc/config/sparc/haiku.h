/* Definitions of target machine for GCC, for ELF on Haiku/sparc64.
   Copyright (C) 2002-2017 Free Software Foundation, Inc.
   Contributed by Matthew Green (mrg@eterna.com.au).

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#define TARGET_OS_CPP_BUILTINS()			\
  do							\
    {							\
      builtin_define ("__HAIKU__");					\
      if (TARGET_ARCH64)				\
	{						\
	  builtin_define ("__sparc64__");		\
	  builtin_define ("__sparc_v9__");		\
	  builtin_define ("__sparcv9");			\
	}						\
      else						\
	builtin_define ("__sparc");			\
      builtin_define ("__sparc__");			\
    }							\
  while (0)

/* Provide a LINK_SPEC appropriate for Haiku.  Here we provide support
   for the special GCC options -static and -shared, which allow us to
   link things in one of these three modes by applying the appropriate
   combinations of options at link-time.  */

#undef	LINK_SPEC
#define LINK_SPEC "-m elf64_sparc %{!r:-shared} %{nostart:-e 0} \
	%{shared:-e 0} %{!shared: %{!nostart: -no-undefined}}"
/* SIZE_TYPE and PTRDIFF_TYPE are wrong from sparc/sparc.h.  */
#undef SIZE_TYPE
#define SIZE_TYPE "long unsigned int"

#undef PTRDIFF_TYPE
#define PTRDIFF_TYPE "long int"

/* This is the char to use for continuation (in case we need to turn
   continuation back on).  */
#undef DBX_CONTIN_CHAR
#define DBX_CONTIN_CHAR '?'

#undef  LOCAL_LABEL_PREFIX
#define LOCAL_LABEL_PREFIX  "."

/* This is how to store into the string LABEL
   the symbol_ref name of an internal numbered label where
   PREFIX is the class of label and NUM is the number within the class.
   This is suitable for output with `assemble_name'.  */

#undef  ASM_GENERATE_INTERNAL_LABEL
#define ASM_GENERATE_INTERNAL_LABEL(LABEL,PREFIX,NUM)	\
  sprintf ((LABEL), "*.L%s%ld", (PREFIX), (long)(NUM))

#undef USER_LABEL_PREFIX
#define USER_LABEL_PREFIX ""

#undef ASM_SPEC
#define ASM_SPEC "%{" FPIE_OR_FPIC_SPEC ":-K PIC} \
%(asm_cpu) %(asm_arch) %(asm_relax)"

#define HAVE_ENABLE_EXECUTE_STACK

#undef TARGET_DEFAULT
#define TARGET_DEFAULT \
  (MASK_V9 + MASK_PTR64 + MASK_64BIT /* + MASK_HARD_QUAD */ \
   + MASK_STACK_BIAS + MASK_APP_REGS + MASK_FPU + MASK_LONG_DOUBLE_128)

#undef SPARC_DEFAULT_CMODEL
#define SPARC_DEFAULT_CMODEL CM_MEDANY

/* Build a compiler that supports -m32 and -m64?  */

#undef LONG_DOUBLE_TYPE_SIZE
#define LONG_DOUBLE_TYPE_SIZE 128

/* We use GNU ld so undefine this so that attribute((init_priority)) works.  */
#undef CTORS_SECTION_ASM_OP
#undef DTORS_SECTION_ASM_OP
