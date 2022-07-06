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

#undef MCOUNT_NAME
#define MCOUNT_NAME "_mcount"

#define TARGET_DECLSPEC 1

#undef SIZE_TYPE
#define SIZE_TYPE "long unsigned int"

#undef PTRDIFF_TYPE
#define PTRDIFF_TYPE "long int"

#undef WCHAR_TYPE
#define WCHAR_TYPE "int"

#undef WCHAR_TYPE_SIZE
#define WCHAR_TYPE_SIZE 32

/* Haiku uses lots of multichars, so don't warn about them unless the
   user explicitly asks for the warnings with -Wmultichar.  Note that
   CC1_SPEC is used for both cc1 and cc1plus.  */
#undef CC1_SPEC
#define CC1_SPEC \
  "%{fpic|fPIC|fpie|fPIE|fno-pic|fno-PIC|fno-pie|fno-PIE:;:-fPIC} \
   %{!Wmultichar: -Wno-multichar} %(cc1_cpu) %{profile:-p}"

#undef CC1PLUS_SPEC
#define CC1PLUS_SPEC "%{!Wctor-dtor-privacy:-Wno-ctor-dtor-privacy}"

#define SUBTARGET_OVERRIDE_OPTIONS			\
  do {							\
    haiku_override_options ();			\
  } while (0)

/* LIB_SPEC for Haiku */
#undef LIB_SPEC
#define LIB_SPEC "-lroot"

/* Use --as-needed -lgcc_s for eh support.  */
#ifdef HAVE_LD_AS_NEEDED
#define USE_LD_AS_NEEDED 1
#endif

/* Pass --eh-frame-hdr to provide a PT_EH_FRAME section, allowing unwind 
   libraries to get frame information. */
#if defined(HAVE_LD_EH_FRAME_HDR)
#define LINK_EH_SPEC "%{!static|static-pie:--eh-frame-hdr} "
#endif

#undef  STARTFILE_SPEC
#define STARTFILE_SPEC "crti.o%s crtbeginS.o%s %{!shared:%{!nostart:start_dyn.o%s}} init_term_dyn.o%s"

#undef  ENDFILE_SPEC
#define ENDFILE_SPEC "crtendS.o%s crtn.o%s"

/* Every program on Haiku links against libroot which contains the pthread
   routines, so there's no need to explicitly call out when doing threaded
   work.  */
#undef GOMP_SELF_SPECS
#define GOMP_SELF_SPECS ""
#undef GTM_SELF_SPECS
#define GTM_SELF_SPECS ""

#ifdef HYBRID_SECONDARY
/* For a secondary compiler on a hybrid system, use alternative search paths.*/
#define INCLUDE_DEFAULTS \
{ \
    { GPLUSPLUS_INCLUDE_DIR, "G++", 1, 1, 0, 0 }, \
    { GPLUSPLUS_TOOL_INCLUDE_DIR, "G++", 1, 1, 0, 0 }, \
    { GPLUSPLUS_BACKWARD_INCLUDE_DIR, "G++", 1, 1, 0, 0 }, \
    { GCC_INCLUDE_DIR, "GCC", 0, 0, 0, 0 }, \
    { FIXED_INCLUDE_DIR, "GCC", 0, 0, 0, 0 }, \
    { TOOL_INCLUDE_DIR, "BINUTILS", 0, 1, 0, 0 }, \
    { "/boot/system/non-packaged/develop/headers/" HYBRID_SECONDARY, 0, 0, 0, 1, 0 }, \
    { "/boot/system/develop/headers/os", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/app", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/device", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/drivers", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/game", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/interface", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/kernel", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/locale", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/mail", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/media", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/midi", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/midi2", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/net", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/opengl", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/storage", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/support", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/translation", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/add-ons/graphics", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/add-ons/input_server", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/add-ons/mail_daemon", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/add-ons/registrar", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/add-ons/screen_saver", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/add-ons/tracker", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/be_apps/Deskbar", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/be_apps/NetPositive", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/be_apps/Tracker", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/3rdparty", 0, 0, 0, 1, 0 }, \
    { "/boot/system/develop/headers/bsd", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/glibc", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/gnu", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/posix", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/" HYBRID_SECONDARY, 0, 0, 0, 1, 0 }, \
        /* Hybrid secondary folders for os kits not in base haiku package */\
    { "/boot/system/develop/headers/" HYBRID_SECONDARY "/os", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/" HYBRID_SECONDARY "/os/opengl", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers", 0, 0, 0, 1, 0 }, \
    { 0, 0, 0, 0, 0, 0 } \
}
#else /* HYBRID_SECONDARY */
/* For both native and cross compiler, use standard Haiku include file
   search paths.
   For a cross compiler, it is expected that an appropriate sysroot has
   been configured (e.g. /boot/system/develop/cross/x86) which will
   be appended to each search folder given below. */
#define INCLUDE_DEFAULTS \
{ \
    { GPLUSPLUS_INCLUDE_DIR, "G++", 1, 1, 0, 0 }, \
    { GPLUSPLUS_TOOL_INCLUDE_DIR, "G++", 1, 1, 0, 0 }, \
    { GPLUSPLUS_BACKWARD_INCLUDE_DIR, "G++", 1, 1, 0, 0 }, \
    { GCC_INCLUDE_DIR, "GCC", 0, 0, 0, 0 }, \
    { FIXED_INCLUDE_DIR, "GCC", 0, 0, 0, 0 }, \
    { TOOL_INCLUDE_DIR, "BINUTILS", 0, 1, 0, 0 }, \
    { "/boot/system/non-packaged/develop/headers", 0, 0, 0, 1, 0 }, \
    { "/boot/system/develop/headers/os", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/app", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/device", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/drivers", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/game", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/interface", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/kernel", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/locale", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/mail", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/media", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/midi", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/midi2", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/net", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/opengl", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/storage", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/support", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/translation", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/add-ons/graphics", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/add-ons/input_server", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/add-ons/mail_daemon", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/add-ons/registrar", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/add-ons/screen_saver", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/add-ons/tracker", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/be_apps/Deskbar", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/be_apps/NetPositive", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/os/be_apps/Tracker", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/3rdparty", 0, 0, 0, 1, 0 }, \
    	/* TODO: To be removed when libtiff has been outsourced. */\
    { "/boot/system/develop/headers/bsd", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/glibc", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/gnu", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers/posix", 0, 0, 1, 1, 0 }, \
    { "/boot/system/develop/headers", 0, 0, 0, 1, 0 }, \
    { 0, 0, 0, 0, 0, 0 } \
}
#endif /* HYBRID_SECONDARY */

/* Whee.  LIBRARY_PATH is Be's LD_LIBRARY_PATH, which of course will
   cause nasty problems if we override it.  */
#define LIBRARY_PATH_ENV        "BELIBRARIES"

/* Set STANDARD_STARTFILE_PREFIX_1 set to "/boot/system/develop/lib/", or the
   respective secondary architecture path. The user specific paths are set via
   LIBRARY_PATH_ENV. */
#undef STANDARD_STARTFILE_PREFIX_1
#undef STANDARD_STARTFILE_PREFIX_2
#undef MD_STARTFILE_PREFIX
#undef STARTFILE_PREFIX_SPEC
#ifdef HYBRID_SECONDARY
/* For a secondary compiler on a hybrid system, use alternative search paths.*/
#define STANDARD_STARTFILE_PREFIX_1 \
  "/boot/system/non-packaged/develop/lib/" HYBRID_SECONDARY "/"
#define STANDARD_STARTFILE_PREFIX_2 \
  "/boot/system/develop/lib/" HYBRID_SECONDARY "/"
#else /* HYBRID_SECONDARY */
#define STANDARD_STARTFILE_PREFIX_1   "/boot/system/non-packaged/develop/lib/"
#define STANDARD_STARTFILE_PREFIX_2   "/boot/system/develop/lib/"
#endif /* HYBRID_SECONDARY */

/* Haiku doesn't have a separate math library.  */
#define MATH_LIBRARY ""

/* Haiku headers are C++-aware (and often use C++).  */
/* #define NO_IMPLICIT_EXTERN_C */

#define LINK_SSP_SPEC "%{fstack-protector|fstack-protector-all" \
		       "|fstack-protector-strong|fstack-protector-explicit" \
		       ":-lssp_nonshared}"

/* Do not use TM clone registry in Haiku for now */
#define USE_TM_CLONE_REGISTRY 0
