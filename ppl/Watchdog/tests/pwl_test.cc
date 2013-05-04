/* Implementation of utility functions used in test programs.
   Copyright (C) 2001-2010 Roberto Bagnara <bagnara@cs.unipr.it>
   Copyright (C) 2010-2011 BUGSENG srl (http://bugseng.com)

This file is part of the Parma Watchdog Library (PWL).

The PWL is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3 of the License, or (at your
option) any later version.

The PWL is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02111-1307, USA.

For the most up-to-date information see the Parma Polyhedra Library
site: http://www.cs.unipr.it/ppl/ . */

#include "pwl_test.hh"
#include <csignal>
#include <iostream>
#include <exception>
#include <limits>
#ifdef PWL_HAVE_FENV_H
#include <fenv.h>
#endif

namespace {

void
unexpected_exception_handler() {
  std::cerr << "unexpected exception thrown" << std::endl;
  exit(1);
}

void
uncaught_exception_handler() {
  std::cerr << "uncaught exception" << std::endl;
  exit(1);
}

#if PWL_HAVE_DECL_SIGACTION

#if defined(PWL_HAVE_SIGINFO_T) && defined(SA_SIGINFO)

void
fpe_sigaction(int sig, siginfo_t* sip, void*) {
  if (sig != SIGFPE) {
    std::cerr << "fpe_handler called on signal different from SIGFPE"
	      << std::endl;
    exit(1);
  }
  const char* s = 0;
  switch (sip->si_code) {
  case FPE_INTDIV:
    s = "integer divide by zero";
    break;
  case FPE_INTOVF:
    s = "integer overflow";
    break;
  case FPE_FLTDIV:
    s = "floating point divide by zero";
    break;
  case FPE_FLTOVF:
    s = "floating point overflow";
    break;
  case FPE_FLTUND:
    s = "floating point underflow";
    break;
  case FPE_FLTRES:
    s = "floating point inexact result";
    break;
  case FPE_FLTINV:
    s = "floating point invalid operation";
    break;
  case FPE_FLTSUB:
    s = "subscript out of range";
    break;
  default:
    break;
  }
  if (s != 0)
    std::cerr << "SIGFPE caught (cause: " << s << ")"
	      << std::endl;
  else {
    std::cerr << "SIGFPE caught (unknown si_code " << sip->si_code << ")"
	      << std::endl;
#if defined(PWL_HAVE_FENV_H)
    std::cerr << "Inquire with fetestexcept(): ";
#ifdef FE_INEXACT
    if (fetestexcept(FE_INEXACT))
      std::cerr << "FE_INEXACT ";
#endif
#ifdef FE_DIVBYZERO
    if (fetestexcept(FE_DIVBYZERO))
      std::cerr << "FE_DIVBYZERO ";
#endif
#ifdef FE_UNDERFLOW
    if (fetestexcept(FE_UNDERFLOW))
      std::cerr << "FE_UNDERFLOW ";
#endif
#ifdef FE_OVERFLOW
    if (fetestexcept(FE_OVERFLOW))
      std::cerr << "FE_OVERFLOW ";
#endif
#if FE_INVALID
    if (fetestexcept(FE_INVALID))
      std::cerr << "FE_INVALID ";
#endif
    std::cerr << std::endl;
#endif // defined(PWL_HAVE_FENV_H)
  }
  exit(1);
}

#else // !defined(PWL_HAVE_SIGINFO_T) || !defined(SA_SIGINFO)

void
fpe_handler(int sig) {
  if (sig != SIGFPE) {
    std::cerr << "fpe_handler called on signal different from SIGFPE"
	      << std::endl;
    exit(1);
  }
  std::cerr << "SIGFPE caught"
            << std::endl;
#if defined(PWL_HAVE_FENV_H)
  std::cerr << "Inquire with fetestexcept(): ";
#ifdef FE_INEXACT
  if (fetestexcept(FE_INEXACT))
    std::cerr << "FE_INEXACT ";
#endif
#ifdef FE_DIVBYZERO
  if (fetestexcept(FE_DIVBYZERO))
    std::cerr << "FE_DIVBYZERO ";
#endif
#ifdef FE_UNDERFLOW
  if (fetestexcept(FE_UNDERFLOW))
    std::cerr << "FE_UNDERFLOW ";
#endif
#ifdef FE_OVERFLOW
  if (fetestexcept(FE_OVERFLOW))
    std::cerr << "FE_OVERFLOW ";
#endif
#if FE_INVALID
  if (fetestexcept(FE_INVALID))
    std::cerr << "FE_INVALID ";
#endif
  std::cerr << std::endl;
#endif // defined(PWL_HAVE_FENV_H)
  exit(1);
}

#endif // !defined(PWL_HAVE_SIGINFO_T) || !defined(SA_SIGINFO)

#endif // PWL_HAVE_DECL_SIGACTION

} // namespace

namespace Parma_Watchdog_Library {

namespace Test {

void
set_handlers() {
#if PWL_HAVE_DECL_SIGACTION
  struct sigaction action;
  sigemptyset(&action.sa_mask);
#if defined(PWL_HAVE_SIGINFO_T) && defined(SA_SIGINFO)
  action.sa_sigaction = fpe_sigaction;
  action.sa_flags = SA_SIGINFO;
#else // !defined(PWL_HAVE_SIGINFO_T) || !defined(SA_SIGINFO)
  action.sa_handler = fpe_handler;
  action.sa_flags = 0;
#endif // !defined(PWL_HAVE_SIGINFO_T) || !defined(SA_SIGINFO)
  if (sigaction(SIGFPE, &action, NULL) != 0) {
    std::cerr << "sigaction() failed"
	      << std::endl;
    abort();
  }
#endif // PWL_HAVE_DECL_SIGACTION

  std::set_unexpected(unexpected_exception_handler);
  std::set_terminate(uncaught_exception_handler);
}

} // namespace Test

} // namespace Parma_Watchdog_Library
