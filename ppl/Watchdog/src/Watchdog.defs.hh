/* Watchdog and associated classes' declaration and inline functions.
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

#ifndef PWL_Watchdog_defs_hh
#define PWL_Watchdog_defs_hh 1

#include "Watchdog.types.hh"
#include "Time.defs.hh"
#include "Handler.types.hh"
#include "Pending_List.defs.hh"
#include <cassert>
#include <functional>

#ifdef PWL_HAVE_SYS_TIME_H
# include <sys/time.h>
#endif

namespace Parma_Watchdog_Library {

// Set linkage now to declare it friend later.
extern "C" void PWL_handle_timeout(int signum);

struct Watchdog_Traits {
  typedef Time Threshold;
  static bool less_than(const Threshold& a, const Threshold& b) {
    return a < b;
  }
};

//! A watchdog timer.
class Watchdog {
public:
  template <typename Flag_Base, typename Flag>
  Watchdog(unsigned int units, const Flag_Base* volatile& holder, Flag& flag);

  /*! \brief
    Constructor: if not reset, the watchdog will trigger after \p units
    hundreths of seconds, invoking handler \p function.
  */
  Watchdog(unsigned int units, void (*function)());

  //! Destructor.
  ~Watchdog();

#if PWL_HAVE_DECL_SETITIMER && PWL_HAVE_DECL_SIGACTION

private:
  typedef Pending_List<Watchdog_Traits> WD_Pending_List;
  friend class Init;

  //! Static class initialization.
  static void initialize();
  //! Static class finalization.
  static void finalize();

  //! Whether or not this watchdog has expired.
  bool expired;

  const Handler& handler;
  WD_Pending_List::Iterator pending_position;

  // Private and not implemented: copy construction is not allowed.
  Watchdog(const Watchdog&);
  // Private and not implemented: copy assignment is not allowed.
  Watchdog& operator=(const Watchdog&);

  // Pass this to getitimer().
  static itimerval current_timer_status;

  //! Reads the timer value into \p time.
  static void get_timer(Time& time);

  // Pass this to setitimer().
  static itimerval signal_once;

  // Last time value we set the timer to.
  static Time last_time_requested;

  //! Sets the timer value to \p time.
  static void set_timer(const Time& time);

  //! Stops the timer.
  static void stop_timer();

  //! Quick reschedule to avoid race conditions.
  static void reschedule();

  // Used by the above.
  static Time reschedule_time;

  // Records the time elapsed since last fresh start.
  static Time time_so_far;

  //! The ordered queue of pending watchdog events.
  static WD_Pending_List pending;

  //! The actual signal handler.
  static void handle_timeout(int);

  //! Handles the addition of a new watchdog event.
  static WD_Pending_List::Iterator
  new_watchdog_event(unsigned int units,
                     const Handler& handler,
                     bool& expired_flag);

  //! Handles the removal of the watchdog event referred by \p position.
  void remove_watchdog_event(WD_Pending_List::Iterator position);

  //! Whether the alarm clock is running.
  static volatile bool alarm_clock_running;

  //! Whether we are changing data that is also changed by the signal handler.
  static volatile bool in_critical_section;

  friend void PWL_handle_timeout(int signum);

#endif // PWL_HAVE_DECL_SETITIMER && PWL_HAVE_DECL_SIGACTION
};

#if PWL_HAVE_DECL_SETITIMER && PWL_HAVE_DECL_SIGACTION

class Init {
private:
  //! Count the number of objects created.
  static unsigned int count;

public:
  //! Initializes the PWL.
  Init();

  //! Finalizes the PWL.
  ~Init();
};

#endif // PWL_HAVE_DECL_SETITIMER && PWL_HAVE_DECL_SIGACTION

} // namespace Parma_Watchdog_Library

#include "Watchdog.inlines.hh"

#if PWL_HAVE_DECL_SETITIMER && PWL_HAVE_DECL_SIGACTION

namespace {

Parma_Watchdog_Library::Init Parma_Watchdog_Library_initializer;

} // namespace

#endif // PWL_HAVE_DECL_SETITIMER && PWL_HAVE_DECL_SIGACTION

#endif // !defined(PWL_Watchdog_defs_hh)

