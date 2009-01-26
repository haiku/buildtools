/* Definitions of target machine for GCC.
   Common Haiku definitions for all architectures.
   Copyright (C) 1998, 1999, 2000, 2001, 2002, 2004, 2005
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


/* Change debugging to Dwarf2.  */
#undef PREFERRED_DEBUGGING_TYPE
#define PREFERRED_DEBUGGING_TYPE DWARF2_DEBUG

#undef ASM_COMMENT_START
#define ASM_COMMENT_START " #"

/* Output assembler code to FILE to increment profiler label # LABELNO
   for profiling a function entry.  */

#undef MCOUNT_NAME
#define MCOUNT_NAME "_mcount"

#define TARGET_DECLSPEC 1

/* Haiku uses lots of multichars, so don't warn about them unless the
   user explicitly asks for the warnings with -Wmultichar.  Note that
   CC1_SPEC is used for both cc1 and cc1plus.  */

#undef CC1_SPEC
#define CC1_SPEC "%{!no-fpic:%{!fno-pic:%{!fno-pie:%{!fpie:%{!fPIC:%{!fPIE:-fpic}}}}}} %{!Wmultichar: -Wno-multichar} %(cc1_cpu) %{profile:-p}"

#undef CC1PLUS_SPEC
#define CC1PLUS_SPEC "%{!Wctor-dtor-privacy:-Wno-ctor-dtor-privacy}"

/* Provide start and end file specs appropriate to glibc.  */

/* LIB_SPEC for Haiku */
#undef LIB_SPEC
#define LIB_SPEC "-lroot"

/* gcc runtime lib is built into libroot.so on Haiku */
/* ??? This is gonna be lovely when the next release of gcc has 
   some new symbol in, so that links start failing.  */
#undef LIBGCC_SPEC
#define LIBGCC_SPEC ""

/* Note: There currently is no mcount.o on Haiku. In the BeOS specification
   it was i386-mcount.o, but that doesn't exist in gcc 2.95.3 either. */

#undef  STARTFILE_SPEC
#define STARTFILE_SPEC "crti.o%s crtbegin.o%s %{!nostart:start_dyn.o%s} init_term_dyn.o%s %{p:mcount.o%s}"

#undef  ENDFILE_SPEC
#define ENDFILE_SPEC "crtend.o%s crtn.o%s"

/* For native compiler, use standard Haiku include file search paths
   rooted in /boot/develop/headers.  For a cross compiler, don't
   expect the host to use the Haiku directory scheme, and instead look
   for the Haiku include files relative to TOOL_INCLUDE_DIR.  Yes, we
   use ANSI string concatenation here (FIXME) */

#ifndef CROSS_DIRECTORY_STRUCTURE
#undef INCLUDE_DEFAULTS
#define INCLUDE_DEFAULTS \
    { \
    { GPLUSPLUS_INCLUDE_DIR, "G++", 1, 1, 0, 0 }, \
    { GCC_INCLUDE_DIR, "GCC", 0, 0, 0, 0 }, \
    { TOOL_INCLUDE_DIR, "BINUTILS", 0, 1, 0, 0 }, \
    { "/boot/develop/headers/os", 0, 0, 0, 0, 0 }, \
    { "/boot/develop/headers/os/app", 0, 0, 0, 0, 0 }, \
    { "/boot/develop/headers/os/device", 0, 0, 0, 0, 0 }, \
    { "/boot/develop/headers/os/drivers", 0, 0, 0, 0, 0 }, \
    { "/boot/develop/headers/os/game", 0, 0, 0, 0, 0 }, \
    { "/boot/develop/headers/os/interface", 0, 0, 0, 0, 0 }, \
    { "/boot/develop/headers/os/kernel", 0, 0, 0, 0, 0 }, \
    { "/boot/develop/headers/os/mail", 0, 0, 0, 0, 0 }, \
    { "/boot/develop/headers/os/media", 0, 0, 0, 0, 0 }, \
    { "/boot/develop/headers/os/midi", 0, 0, 0, 0, 0 }, \
    { "/boot/develop/headers/os/midi2", 0, 0, 0, 0, 0 }, \
    { "/boot/develop/headers/os/net", 0, 0, 0, 0, 0 }, \
    { "/boot/develop/headers/os/opengl", 0, 0, 0, 0, 0 }, \
    { "/boot/develop/headers/os/storage", 0, 0, 0, 0, 0 }, \
    { "/boot/develop/headers/os/support", 0, 0, 0, 0, 0 }, \
    { "/boot/develop/headers/os/translation", 0, 0, 0, 0, 0 }, \
    { "/boot/develop/headers/os/add-ons/graphics", 0, 0, 0, 0, 0 }, \
    { "/boot/develop/headers/os/add-ons/input_server", 0, 0, 0, 0, 0 }, \
    { "/boot/develop/headers/os/add-ons/screen_saver", 0, 0, 0, 0, 0 }, \
    { "/boot/develop/headers/os/add-ons/tracker", 0, 0, 0, 0, 0 }, \
    { "/boot/develop/headers/os/be_apps/Deskbar", 0, 0, 0, 0, 0 }, \
    { "/boot/develop/headers/os/be_apps/NetPositive", 0, 0, 0, 0, 0 }, \
    { "/boot/develop/headers/os/be_apps/Tracker", 0, 0, 0, 0, 0 }, \
    { "/boot/develop/headers/gnu", 0, 0, 0, 0, 0 }, \
    { "/boot/develop/headers/cpp", 0, 0, 0, 0, 0 }, \
    { "/boot/develop/headers/bsd", 0, 0, 0, 0, 0 }, \
    { "/boot/develop/headers/posix", 0, 0, 0, 0, 0 }, \
    { "/boot/develop/headers", 0, 0, 0, 0, 0 }, \
    { 0, 0, 0, 0, 0, 0 } \
    }
#else /* CROSS_DIRECTORY_STRUCTURE */
#undef	INCLUDE_DEFAULTS
#define INCLUDE_DEFAULTS				\
    { \
    { GPLUSPLUS_INCLUDE_DIR, "G++", 1, 1, 1, 0 }, \
    { GPLUSPLUS_TOOL_INCLUDE_DIR, "G++", 1, 1, 1, 0 } \
    { GPLUSPLUS_BACKWARD_INCLUDE_DIR, "G++", 1, 1, 1, 0 } \
    { GCC_INCLUDE_DIR, "GCC", 0, 0, 1, 0 }, \
    { FIXED_INCLUDE_DIR, "GCC", 0, 0, 1, 0 }, \
    { TOOL_INCLUDE_DIR, "BINUTILS", 0, 1, 1, 0 }, \
    { CROSS_INCLUDE_DIR "/os", 0, 0, 0, 1, 0 }, \
    { CROSS_INCLUDE_DIR "/os/app", 0, 0, 0, 1, 0 }, \
    { CROSS_INCLUDE_DIR "/os/device", 0, 0, 0, 1, 0 }, \
    { CROSS_INCLUDE_DIR "/os/drivers", 0, 0, 0, 1, 0 }, \
    { CROSS_INCLUDE_DIR "/os/game", 0, 0, 0, 1, 0 }, \
    { CROSS_INCLUDE_DIR "/os/interface", 0, 0, 0, 1, 0 }, \
    { CROSS_INCLUDE_DIR "/os/kernel", 0, 0, 0, 1, 0 }, \
    { CROSS_INCLUDE_DIR "/os/mail", 0, 0, 0, 1, 0 }, \
    { CROSS_INCLUDE_DIR "/os/media", 0, 0, 0, 1, 0 }, \
    { CROSS_INCLUDE_DIR "/os/midi", 0, 0, 0, 1, 0 }, \
    { CROSS_INCLUDE_DIR "/os/midi2", 0, 0, 0, 1, 0 }, \
    { CROSS_INCLUDE_DIR "/os/net", 0, 0, 0, 1, 0 }, \
    { CROSS_INCLUDE_DIR "/os/opengl", 0, 0, 0, 1, 0 }, \
    { CROSS_INCLUDE_DIR "/os/storage", 0, 0, 0, 1, 0 }, \
    { CROSS_INCLUDE_DIR "/os/support", 0, 0, 0, 1, 0 }, \
    { CROSS_INCLUDE_DIR "/os/translation", 0, 0, 0, 1, 0 }, \
    { CROSS_INCLUDE_DIR "/os/add-ons/graphics", 0, 0, 0, 1, 0 }, \
    { CROSS_INCLUDE_DIR "/os/add-ons/input_server", 0, 0, 0, 1, 0 }, \
    { CROSS_INCLUDE_DIR "/os/add-ons/screen_saver", 0, 0, 0, 1, 0 }, \
    { CROSS_INCLUDE_DIR "/os/add-ons/tracker", 0, 0, 0, 1, 0 }, \
    { CROSS_INCLUDE_DIR "/os/be_apps/Deskbar", 0, 0, 0, 1, 0 }, \
    { CROSS_INCLUDE_DIR "/os/be_apps/NetPositive", 0, 0, 0, 1, 0 }, \
    { CROSS_INCLUDE_DIR "/os/be_apps/Tracker", 0, 0, 0, 1, 0 }, \
    { CROSS_INCLUDE_DIR "/os/net/netinet", 0, 0, 0, 1, 0 }, \
    { CROSS_INCLUDE_DIR "/gnu", 0, 0, 0, 1, 0 }, \
    { CROSS_INCLUDE_DIR "/cpp", 0, 0, 0, 1, 0 }, \
    { CROSS_INCLUDE_DIR "/bsd", 0, 0, 0, 1, 0 }, \
    { CROSS_INCLUDE_DIR "/posix", 0, 0, 0, 1, 0 }, \
    { CROSS_INCLUDE_DIR , 0, 0, 0, 1, 0 }, \
    { 0, 0, 0, 0, 0, 0 } \
    }
#endif /* CROSS_DIRECTORY_STRUCTURE */

/* Whee.  LIBRARY_PATH is Be's LD_LIBRARY_PATH, which of course will
   cause nasty problems if we override it.  */
#define LIBRARY_PATH_ENV        "BELIBRARIES"

/* Haiku doesn't have a separate math library.  */
#define MATH_LIBRARY ""

/* Haiku headers are C++-aware (and often use C++).  */
#define NO_IMPLICIT_EXTERN_C
