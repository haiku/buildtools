/* Threads compatibily routines for libgcc2.  */
/* Compile this one with gcc.  */
/* Copyright (C) 1997 Free Software Foundation, Inc.

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

/* As a special exception, if you link this library with other files,
   some of which are compiled with GCC, to produce an executable,
   this library does not by itself cause the resulting executable
   to be covered by the GNU General Public License.
   This exception does not however invalidate any other reasons why
   the executable file might be covered by the GNU General Public License.  */

#ifndef __gthr_beos_h
#define __gthr_beos_h

/* Simple spinlocks for mutex handling. We would need C++ for semaphores. */

/*	we do our own thread-safe implementation	*/
#define __GTHREADS 0

#if defined(MAX)
#undef MAX
#endif
#if defined(MIN)
#undef MIN
#endif

#include <OS.h>

typedef int32 __gthread_mutex_t;

#define __GTHREAD_MUTEX_INIT 0

static inline int
__gthread_active_p ()
{
  return 1;
}

/*	the return value is not documented -- let's assume 0 for "no error"	*/
/*	the only user I found was in frame.c, which doesn't check...	*/
static inline int
__gthread_mutex_lock (__gthread_mutex_t *mutex)
{
	while (atomic_or(mutex, 1)) {
		snooze(3000);
	}
	return 0;
}

#if 0
//	This appears unused, so I will not implement it.
//	If it's needed later, we'll do it then.
static inline int
__gthread_mutex_trylock (__gthread_mutex_t *mutex __attribute__ ((__unused__)))
{
  return 0;
}
#endif

/*	the return value is not documented -- let's assume 0 for "no error"	*/
/*	the only user I found was in frame.c, which doesn't check...	*/
static inline int
__gthread_mutex_unlock (__gthread_mutex_t *mutex)
{
	/* assert(*mutex != 0); */
	atomic_and(mutex, 0);
	return 0;
}

#endif /* not __gthr_beos_h */
