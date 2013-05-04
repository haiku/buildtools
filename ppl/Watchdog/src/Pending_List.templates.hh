/* Pending_List class implementation.
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

#ifndef PWL_Pending_List_templates_hh
#define PWL_Pending_List_templates_hh 1

#include <iostream>

namespace Parma_Watchdog_Library {

template <typename Traits>
typename Pending_List<Traits>::Iterator
Pending_List<Traits>::insert(const typename Traits::Threshold& deadline,
			     const Handler& handler,
			     bool& expired_flag) {
  Iterator position = active_list.begin();
  for (Iterator active_list_end = active_list.end();
       position != active_list_end && Traits::less_than(position->deadline(), deadline);
       ++position)
    ;
  Iterator ppe;
  // Only allocate a new element if the free list is empty.
  if (free_list.empty())
    ppe = new Pending_Element<typename Traits::Threshold>(deadline, handler, expired_flag);
  else {
    ppe = free_list.begin();
    free_list.erase(ppe);
    ppe->assign(deadline, handler, expired_flag);
  }
  Iterator r = active_list.insert(position, *ppe);
  assert(OK());
  return r;
}

template <typename Traits>
bool
Pending_List<Traits>::OK() const {
  if (!active_list.OK())
    return false;

  if (!free_list.OK())
    return false;

  const typename Traits::Threshold* old;
  Const_Iterator i = active_list.begin();
  old = &i->deadline();
  ++i;
  for (Const_Iterator active_list_end = active_list.end(); i != active_list_end; ++i) {
    const typename Traits::Threshold& t = i->deadline();
    if (Traits::less_than(t, *old)) {
#ifndef NDEBUG
      std::cerr << "The active list is not sorted!"
		<< std::endl;
#endif
      return false;
    }
    old = &t;
  }
  return true;
}

} // namespace Parma_Watchdog_Library

#endif // !defined(PWL_Pending_List_templates_hh)
