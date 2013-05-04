/* Weight_Profiler class implementation.
   Copyright (C) 2001-2010 Roberto Bagnara <bagnara@cs.unipr.it>
   Copyright (C) 2010-2011 BUGSENG srl (http://bugseng.com)

This file is part of the Parma Polyhedra Library (PPL).

The PPL is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3 of the License, or (at your
option) any later version.

The PPL is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02111-1307, USA.

For the most up-to-date information see the Parma Polyhedra Library
site: http://www.cs.unipr.it/ppl/ . */

#include <ppl-config.h>
#include "globals.defs.hh"

#if PPL_PROFILE_ADD_WEIGHT
#include <iostream>
#include <cmath>
#include "Weight_Profiler.defs.hh"

namespace Parma_Polyhedra_Library {

void Weight_Profiler::output_stats() {
  std::cout << file << ":" << line << ": Weight_Profiler ";
  if (stat[VALID].samples == 0 && stat[DISCARDED].samples == 0)
    std::cout << "never reached.";
  else {
    if (stat[VALID].samples > 0) {
      double avg = stat[VALID].sum / stat[VALID].count;
      double var = stat[VALID].ssum / stat[VALID].count - avg * avg;
      std::cout << " samples(" << stat[VALID].samples << ")"
		<< " count(" << stat[VALID].count << ")"
		<< " min( " << stat[VALID].min << ")"
		<< " max( " << stat[VALID].max << ")"
		<< " avg(" << avg << ")";
      std::cout << " var( " << var << ")"
		<< " stddev( " << sqrt(var) << ")";
    }
    if (stat[DISCARDED].samples > 0) {
      std::cout << " tmin( " << tmin << ")"
		<< " tmax( " << tmax << ")";
      double avg = stat[DISCARDED].sum / stat[DISCARDED].count;
      std::cout << " samples(" << stat[DISCARDED].samples << ")"
		<< " count(" << stat[DISCARDED].count << ")"
		<< " min( " << stat[DISCARDED].min << ")"
		<< " max( " << stat[DISCARDED].max << ")"
		<< " avg(" << avg << ")";
    }
  }
  std::cout << std::endl;
}

double Weight_Profiler::tune_adj() {
  begin();
  adj = 0;
  static Weight_Profiler adjtc(__FILE__, __LINE__, 0, 0, 0);
  for (int i = 0; i < 1000; ++i)
    adjtc.end(1);
  //    return adjtc.stat[VALID].sum / adjtc.stat[VALID].count;
  return adjtc.stat[VALID].min;
}

struct timespec Weight_Profiler::stamp;
double Weight_Profiler::adj = Weight_Profiler::tune_adj();

} // namespace Parma_Polyhedra_Library

#endif
