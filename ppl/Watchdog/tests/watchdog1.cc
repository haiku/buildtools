/* Some simple tests for the basic functionality of the PWL.
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

namespace {

volatile bool interrupt = false;

void
do_interrupt() {
  interrupt = true;
}

bool
test01() {
  const int hundredth_secs = 10;
  try {
    bool ok;
    {
      Watchdog w(hundredth_secs, do_interrupt);
      nout << ((float) hundredth_secs)/100.0 << " seconds watchdog" << endl;

      nout << "starting iteration... " << std::flush;
      for (unsigned long i = 0; i < 1000000000; ++i) {
        if (interrupt) {
          nout << "interrupted" << endl;
          ok = true;
          goto done;
        }
      }
      nout << "not interrupted" << endl;
      ok = false;
    done:
      ;
    }
    interrupt = false;
    return ok;
  }
#if !PWL_WATCHDOG_OBJECTS_ARE_SUPPORTED
  catch (const std::logic_error& e) {
    nout << "std::logic_error caught (" << e.what() << ")" << endl;
    return true;
  }
#endif // !PWL_WATCHDOG_OBJECTS_ARE_SUPPORTED
  catch (...) {
    return false;
  }
  // Should never get here.
  return false;
}


} // namespace

BEGIN_MAIN
  DO_TEST(test01);
END_MAIN
