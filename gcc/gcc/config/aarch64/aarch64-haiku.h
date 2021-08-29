/* Machine description for AArch64 architecture.
   Copyright (C) 2009-2018 Free Software Foundation, Inc.
   Contributed by ARM Ltd.
   Updated for Haiku by Jaroslaw Pelczar <jarek@jpelczar.com>

   This file is part of GCC.

   GCC is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   GCC is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with GCC; see the file COPYING3.  If not see
   <http://www.gnu.org/licenses/>.  */

#ifndef GCC_AARCH64_HAIKU_H
#define GCC_AARCH64_HAIKU_H

#define TARGET_OS_CPP_BUILTINS()					\
  do									\
    {									\
      builtin_define ("__HAIKU__");					\
      builtin_define ("__stdcall=__attribute__((__stdcall__))");	\
      builtin_define ("__cdecl=__attribute__((__cdecl__))");		\
      builtin_define ("__STDC_ISO_10646__=201103L"); 			\
      builtin_assert ("system=haiku");					\
    }									\
  while (0)

#if TARGET_BIG_ENDIAN_DEFAULT
#define TARGET_LINKER_EMULATION  "aarch64haikub"
#else
#define TARGET_LINKER_EMULATION  "aarch64haiku"
#endif

#if TARGET_FIX_ERR_A53_835769_DEFAULT
#define CA53_ERR_835769_SPEC \
  " %{!mno-fix-cortex-a53-835769:--fix-cortex-a53-835769}"
#else
#define CA53_ERR_835769_SPEC \
  " %{mfix-cortex-a53-835769:--fix-cortex-a53-835769}"
#endif

#if TARGET_FIX_ERR_A53_843419_DEFAULT
#define CA53_ERR_843419_SPEC \
  " %{!mno-fix-cortex-a53-843419:--fix-cortex-a53-843419}"
#else
#define CA53_ERR_843419_SPEC \
  " %{mfix-cortex-a53-843419:--fix-cortex-a53-843419}"
#endif


/* Uninitialized common symbols in non-PIE executables, even with
   strong definitions in dependent shared libraries, will resolve
   to COPY relocated symbol in the executable.  See PR65780.  */
#undef TARGET_BINDS_LOCAL_P
#define TARGET_BINDS_LOCAL_P default_binds_local_p_2

/* Define this to be nonzero if static stack checking is supported.  */
#define STACK_CHECK_STATIC_BUILTIN 1


#undef	LINK_SPEC
#define LINK_SPEC "%{!o*:-o %b} -m " TARGET_LINKER_EMULATION " %{!r:-shared} %{nostart:-e 0} %{shared:-e 0} %{!shared: %{!nostart: -no-undefined}}\
	%{mbig-endian:-EB} %{mlittle-endian:-EL} " CA53_ERR_835769_SPEC " " CA53_ERR_843419_SPEC " -X"

#endif  /* GCC_AARCH64_HAIKU_H */
