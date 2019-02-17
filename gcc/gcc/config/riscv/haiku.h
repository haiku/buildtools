/* Definitions for RISC-V Haiku systems with ELF format.
   Copyright (C) 1998-2017 Free Software Foundation, Inc.

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

#undef TARGET_OS_CPP_BUILTINS
#define TARGET_OS_CPP_BUILTINS()		\
  do									\
    {									\
      builtin_define ("__HAIKU__");					\
      if (POINTER_SIZE == 64)						\
        builtin_define ("__riscv64__");				\
      else											\
        builtin_define ("__riscv32__");				\
      builtin_define ("__RISCV__");					\
      builtin_define ("__riscv__");					\
      builtin_define ("__stdcall=__attribute__((__stdcall__))");	\
      builtin_define ("__cdecl=__attribute__((__cdecl__))");		\
      builtin_define ("__STDC_ISO_10646__=201103L"); \
      builtin_assert ("system=haiku");					\
    }									\
  while (0)

#define MUSL_ABI_SUFFIX \
  "%{mabi=ilp32:-sf}" \
  "%{mabi=ilp32f:-sp}" \
  "%{mabi=ilp32d:}" \
  "%{mabi=lp64:-sf}" \
  "%{mabi=lp64f:-sp}" \
  "%{mabi=lp64d:}" \

/* Because RISC-V only has word-sized atomics, it requries libatomic where
   others do not.  So link libatomic by default, as needed.  */
#undef LIB_SPEC
#define LIB_SPEC " -lroot -latomic "

#define ICACHE_FLUSH_FUNC "__riscv_flush_icache"

#undef	LINK_SPEC
#define LINK_SPEC "%{!o*:-o %b} -melf" XLEN_SPEC "lriscv %{!r:-shared} %{nostart:-e 0} %{shared:-e 0} %{!shared: %{!nostart: -no-undefined}} -X"
