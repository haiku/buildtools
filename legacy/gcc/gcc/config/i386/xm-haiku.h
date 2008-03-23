/* Configuration for GNU C-compiler for BeOS host.
   Copyright (C) 1997, 1998 Free Software Foundation, Inc.
   Contributed by Fred Fish (fnf@cygnus.com), based on xm-rs6000.h
   by Richard Kenner (kenner@vlsi1.ultra.nyu.edu).

This file is part of GNU CC.

GNU CC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

#include <i386/xm-i386.h>

/* Arguments to use with `exit'.  */

#define	SUCCESS_EXIT_CODE	0
#define	FATAL_EXIT_CODE		33

/* Include <sys/wait.h> to define the exit status access macros.  */
#ifndef inhibit_libc
#include <sys/wait.h>
#endif

#define	ONLY_INT_FIELDS

/* Define various things that the Haiku host has. */

#ifndef HAVE_VPRINTF
#define HAVE_VPRINTF
#endif
#ifndef HAVE_PUTENV
#define HAVE_PUTENV
#endif
#define HAVE_RENAME

#define STDC_HEADERS 1

#ifndef CROSS_COMPILE
/* Define this macro to make error messages always emit full paths.
   This is needed so that error output parsing development environment
   can unambiguously determine the source file with an error.  */
#define FULL_PATHS_IN_ERRORS 1
#endif

#ifndef LIBRARY_PATH_ENV
/* If we don't define this, LIBRARY_PATH will be overwritten and
   the execution of collect2 will be failed. */
#define LIBRARY_PATH_ENV	"BELIBRARIES"
#endif

