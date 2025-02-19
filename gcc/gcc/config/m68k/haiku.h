/* Definitions for Motorola 68k running Haiku
   Copyright (C) 1995, 1996, 1997, 1998, 1999, 2000, 2002, 2003, 2004, 2007
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
the Free Software Foundation, 51 Franklin Street, Fifth Floor,
Boston, MA 02110-1301, USA.  */

/* Default target comes from config.gcc.  */

#undef TARGET_DEFAULT
#ifdef TARGET_CPU_DEFAULT
#define TARGET_DEFAULT TARGET_CPU_DEFAULT
#else
#define TARGET_DEFAULT (MASK_BITFIELD|MASK_68881|MASK_68020)
#endif

/* for 68k machines this only needs to be TRUE for the 68000 */

#undef STRICT_ALIGNMENT
#define STRICT_ALIGNMENT 0

/* Here are four prefixes that are used by asm_fprintf to
   facilitate customization for alternate assembler syntaxes.
   Machines with no likelihood of an alternate syntax need not
   define these and need not use asm_fprintf.  */

/* The prefix for register names.  Note that REGISTER_NAMES
   is supposed to include this prefix. Also note that this is NOT an
   fprintf format string, it is a literal string */

#undef REGISTER_PREFIX
#define REGISTER_PREFIX "%"

/* The prefix for local (compiler generated) labels.
   These labels will not appear in the symbol table.  */

#undef LOCAL_LABEL_PREFIX
#define LOCAL_LABEL_PREFIX "."

/* The prefix to add to user-visible assembler symbols.  */

#undef USER_LABEL_PREFIX
#define USER_LABEL_PREFIX ""

#undef ASM_COMMENT_START
#define ASM_COMMENT_START "|"

/* Target OS builtins.  */

#undef TARGET_OS_CPP_BUILTINS
#define TARGET_OS_CPP_BUILTINS()					\
  do									\
    {									\
	builtin_define ("__HAIKU__");					\
	builtin_define ("__M68K__");					\
	builtin_define_std ("mc68000");					\
	builtin_define_std ("mc68020");					\
    builtin_define ("__STDC_ISO_10646__=201103L"); \
	builtin_assert ("system=haiku");				\
    }									\
  while (0)

#define TARGET_OBJFMT_CPP_BUILTINS()		\
  do						\
    {						\
	builtin_define ("__ELF__");		\
    }						\
  while (0)

#undef CPP_SPEC
#if TARGET_DEFAULT & MASK_68881
#define CPP_SPEC \
  "%{fPIC|fpic|fPIE|fpie:-D__PIC__ -D__pic__} %{!msoft-float:-D__HAVE_68881__} %{posix:-D_POSIX_SOURCE} %{pthread:-D_REENTRANT}"
#else
#define CPP_SPEC \
  "%{fPIC|fpic|fPIE|fpie:-D__PIC__ -D__pic__} %{m68881:-D__HAVE_68881__} %{posix:-D_POSIX_SOURCE} %{pthread:-D_REENTRANT}"
#endif

/* We override the ASM_SPEC from svr4.h because we must pass -m68040 down
   to the assembler.  */
#undef ASM_SPEC
#define ASM_SPEC \
  "%{v:-V} %{Qy:} %{!Qn:-Qy} %{n} %{T} %{Ym,*} %{Yd,*} %{Wa,*:%*} \
%{m68040} %{m68060:-m68040}"

/* Provide a LINK_SPEC appropriate for Haiku.  Here we provide support
   for the special GCC options -static and -shared, which allow us to
   link things in one of these three modes by applying the appropriate
   combinations of options at link-time.  */

/* If ELF is the default format, we should not use /lib/elf.  */

#undef	LINK_SPEC
/*#define LINK_SPEC "%{!o*:-o %b} -m elf_m68k_haiku -shared -no-undefined %{nostart:-e 0}"*/
#define LINK_SPEC "-m m68kelf %{!r:-shared} %{nostart:-e 0} %{shared:-e 0} %{!shared: %{!nostart: -no-undefined}}"

/* XXX: not sure for the rest there... */

/* Currently, JUMP_TABLES_IN_TEXT_SECTION must be defined in order to
   keep switch tables in the text section.  */

#define JUMP_TABLES_IN_TEXT_SECTION 1

/* This is how to output an assembler line that says to advance the
   location counter to a multiple of 2**LOG bytes.  */

/* Use the default action for outputting the case label.  */
#undef ASM_OUTPUT_CASE_LABEL
#define ASM_RETURN_CASE_JUMP				\
  do {							\
    if (TARGET_COLDFIRE)				\
      {							\
	if (ADDRESS_REG_P (operands[0]))		\
	  return "jmp %%pc@(2,%0:l)";			\
	else						\
	  return "ext%.l %0\n\tjmp %%pc@(2,%0:l)";	\
      }							\
    else						\
      return "jmp %%pc@(2,%0:w)";			\
  } while (0)

#undef ASM_OUTPUT_ALIGN
#define ASM_OUTPUT_ALIGN(FILE,LOG)				\
  if ((LOG) > 0)						\
    fprintf ((FILE), "%s%u\n", ALIGN_ASM_OP, 1 << (LOG));

/* If defined, a C expression whose value is a string containing the
   assembler operation to identify the following data as uninitialized global
   data.  */

#define BSS_SECTION_ASM_OP "\t.section\t.bss"

/* A C statement (sans semicolon) to output to the stdio stream
   FILE the assembler definition of uninitialized global DECL named
   NAME whose size is SIZE bytes and alignment is ALIGN bytes.
   Try to use asm_output_aligned_bss to implement this macro.  */

#define ASM_OUTPUT_ALIGNED_BSS(FILE, DECL, NAME, SIZE, ALIGN) \
  asm_output_aligned_bss (FILE, DECL, NAME, SIZE, ALIGN)

/* Output assembler code to FILE to increment profiler label # LABELNO
   for profiling a function entry.  */

#undef FUNCTION_PROFILER
#define FUNCTION_PROFILER(FILE, LABELNO) \
{									\
  asm_fprintf (FILE, "\tlea (%LLP%d,%Rpc),%Ra1\n", (LABELNO));		\
  if (flag_pic)								\
    fprintf (FILE, "\tbsr.l _mcount@PLTPC\n");				\
  else									\
    fprintf (FILE, "\tjbsr _mcount\n");					\
}

/* How to renumber registers for dbx and gdb.
   On the Sun-3, the floating point registers have numbers
   18 to 25, not 16 to 23 as they do in the compiler.  */

#define DBX_REGISTER_NUMBER(REGNO) ((REGNO) < 16 ? (REGNO) : (REGNO) + 2)

/* Do not break .stabs pseudos into continuations.  */

#define DBX_CONTIN_LENGTH 0

/* 1 if N is a possible register number for a function value.  For
   m68k/SVR4 allow d0, a0, or fp0 as return registers, for integral,
   pointer, or floating types, respectively.  Reject fp0 if not using
   a 68881 coprocessor.  */

#undef FUNCTION_VALUE_REGNO_P
#define FUNCTION_VALUE_REGNO_P(N) \
  ((N) == 0 || (N) == 8 || (TARGET_68881 && (N) == 16))

/* Define this to be true when FUNCTION_VALUE_REGNO_P is true for
   more than one register.  */

#undef NEEDS_UNTYPED_CALL
#define NEEDS_UNTYPED_CALL 1

/* Define how to generate (in the callee) the output value of a
   function and how to find (in the caller) the value returned by a
   function.  VALTYPE is the data type of the value (as a tree).  If
   the precise function being called is known, FUNC is its
   FUNCTION_DECL; otherwise, FUNC is 0.  For m68k/SVR4 generate the
   result in d0, a0, or fp0 as appropriate.  */

#undef FUNCTION_VALUE
#define FUNCTION_VALUE(VALTYPE, FUNC)					\
  (TREE_CODE (VALTYPE) == REAL_TYPE && TARGET_68881			\
   ? gen_rtx_REG (TYPE_MODE (VALTYPE), 16)				\
   : (POINTER_TYPE_P (VALTYPE)						\
      ? gen_rtx_REG (TYPE_MODE (VALTYPE), 8)				\
      : gen_rtx_REG (TYPE_MODE (VALTYPE), 0)))

/* For compatibility with the large body of existing code which does
   not always properly declare external functions returning pointer
   types, the m68k/SVR4 convention is to copy the value returned for
   pointer functions from a0 to d0 in the function epilogue, so that
   callers that have neglected to properly declare the callee can
   still find the correct return value.  */

#define FUNCTION_EXTRA_EPILOGUE(FILE, SIZE)				\
do {									\
  if (current_function_returns_pointer					\
      && ! find_equiv_reg (0, get_last_insn (), 0, 0, 0, 8, Pmode))	\
    asm_fprintf (FILE, "\tmove.l %Ra0,%Rd0\n");				\
} while (0);

/* Define how to find the value returned by a library function
   assuming the value has mode MODE.
   For m68k/SVR4 look for integer values in d0, pointer values in d0
   (returned in both d0 and a0), and floating values in fp0.  */

#undef LIBCALL_VALUE
#define LIBCALL_VALUE(MODE)						\
  ((((MODE) == SFmode || (MODE) == DFmode || (MODE) == XFmode)		\
    && TARGET_68881)							\
   ? gen_rtx_REG ((MODE), 16)						\
   : gen_rtx_REG ((MODE), 0))

/* For m68k SVR4, structures are returned using the reentrant
   technique.  */
#undef PCC_STATIC_STRUCT_RETURN
#define DEFAULT_PCC_STRUCT_RETURN 0

/* Finalize the trampoline by flushing the insn cache.  */

#undef FINALIZE_TRAMPOLINE
#define FINALIZE_TRAMPOLINE(TRAMP)					\
  emit_library_call (gen_rtx_SYMBOL_REF (Pmode, "__clear_cache"),	\
		     LCT_NORMAL, VOIDmode, TRAMP, Pmode,			\
		     plus_constant (Pmode, TRAMP, TRAMPOLINE_SIZE), \
		     Pmode);

/* Clear the instruction cache from `beg' to `end'.  This makes an
   inline system call to SYS_cacheflush.  The arguments are as
   follows:

	cacheflush (addr, scope, cache, len)

   addr	  - the start address for the flush
   scope  - the scope of the flush (see the cpush insn)
   cache  - which cache to flush (see the cpush insn)
   len    - a factor relating to the number of flushes to perform:
	    len/16 lines, or len/4096 pages.  */

#define CLEAR_INSN_CACHE(BEG, END)					\
{									\
extern void clear_caches(void *address, int length, unsigned long flags); \
  void *ptr = BEG;							\
  int len = (END - BEG + 32);						\
  clear_caches(ptr, len, 0x0005);					\
}
