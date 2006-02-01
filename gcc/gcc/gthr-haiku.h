/* Threads compatibility routines for libgcc2.  */
/* Compile this one with gcc.  */
/* Copyright (C) 1997, 1998 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 2, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA.  */

/* As a special exception, if you link this library with other files,
   some of which are compiled with GCC, to produce an executable,
   this library does not by itself cause the resulting executable
   to be covered by the GNU General Public License.
   This exception does not however invalidate any other reasons why
   the executable file might be covered by the GNU General Public License.  */

#ifndef GCC_GTHR_HAIKU_H
#define GCC_GTHR_HAIKU_H

/* If this file is compiled with threads support, it must
       #define __GTHREADS 1
   to indicate that threads support is present.  Also it has define
   function
     int __gthread_active_p ()
   that returns 1 if thread system is active, 0 if not.

   The threads interface must define the following types:
     __gthread_key_t
     __gthread_once_t
     __gthread_mutex_t

   The threads interface must define the following macros:

     __GTHREAD_ONCE_INIT
     		to initialize __gthread_once_t
     __GTHREAD_MUTEX_INIT
     		to initialize __gthread_mutex_t to get a fast
		non-recursive mutex.
     __GTHREAD_MUTEX_INIT_FUNCTION
     		some systems can't initialize a mutex without a
		function call.  On such systems, define this to a
		function which looks like this:
		  void __GTHREAD_MUTEX_INIT_FUNCTION (__gthread_mutex_t *)
		Don't define __GTHREAD_MUTEX_INIT in this case

   The threads interface must define the following static functions:

     int __gthread_once (__gthread_once_t *once, void (*func) ())

     int __gthread_key_create (__gthread_key_t *keyp, void (*dtor) (void *))
     int __gthread_key_delete (__gthread_key_t key)

     void *__gthread_getspecific (__gthread_key_t key)
     int __gthread_setspecific (__gthread_key_t key, const void *ptr)

     int __gthread_mutex_lock (__gthread_mutex_t *mutex);
     int __gthread_mutex_trylock (__gthread_mutex_t *mutex);
     int __gthread_mutex_unlock (__gthread_mutex_t *mutex);

   All functions returning int should return zero on success or the error
   number.  If the operation is not supported, -1 is returned.

   Currently supported threads packages are
     POSIX threads with -D_PTHREADS
     DCE threads with -D_DCE_THREADS
     Solaris/UI threads with -D_SOLARIS_THREADS
     Haiku threads with -D_HAIKU_THREADS
*/

#include <limits.h>

#include <OS.h>
#include <TLS.h>

#define __GTHREADS 1

// for now __gthread_key_delete is not used anywhere, so we don't need to "emulate it" using additional arrays or something :)
typedef int32 __gthread_key_t;
typedef vint32 __gthread_once_t;
typedef vint32 __gthread_mutex_t;

#define __GTHREAD_ONCE_INIT 0
#define __GTHREAD_MUTEX_INIT 0

static inline int __gthread_active_p ()
{
	return 1;
}

static inline int __gthread_once (__gthread_once_t *once, void (*func) ())
{
	if (atomic_or(once, 1) == 0) {
		func();
	}
	return 0;
}

static inline int __gthread_key_create (__gthread_key_t *keyp, void (*dtor) (void *))
{
	*keyp = tls_allocate();
	return 0;
}

// Haiku doesn't offer deleting TLS keys,
// luckly delete is not used anywahere in gcc so we don't have to implement it (at least so for now :)
// (and do create tricks with structs and arrays for keys, to run dtor for all tls_vars...)
static inline int __gthread_key_delete (__gthread_key_t key)
{
	return -1;
}

static inline void *__gthread_getspecific (__gthread_key_t key)
{
	return tls_get(key);
}

static inline int __gthread_setspecific (__gthread_key_t key, const void *ptr)
{
	tls_set(key, (void*)ptr);
	return 0;
}

static inline int __gthread_mutex_lock (__gthread_mutex_t *mutex)
{
	while (atomic_or(mutex, 1) != 0) {
		snooze(3000);
	}
	return 0;
}

static inline int __gthread_mutex_trylock (__gthread_mutex_t *mutex)
{
	if (atomic_or(mutex, 1) == 0)
		return 0;
	else
		return EBUSY;
}

static inline int __gthread_mutex_unlock (__gthread_mutex_t *mutex)
{
	atomic_and(mutex, 0);
	return 0;
}

#endif /* ! GCC_GTHR_HAIKU_H */
