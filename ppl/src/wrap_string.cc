/* String wrapping helper function.
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

#include "wrap_string.hh"
#include <cstdlib>

namespace Parma_Polyhedra_Library {

namespace IO_Operators {

std::string
wrap_string(const std::string& src_string,
	    unsigned indent_depth,
	    unsigned preferred_first_line_length,
	    unsigned preferred_line_length) {
  std::string dst_string;
  const char *src = src_string.c_str();
  for (int line = 0; ; ++line) {
    int linelen = (line == 0
                   ? preferred_first_line_length
                   : preferred_line_length);
    int last_comma = -1;
    int last_space = -1;
    int split_pos = -1;
    int i;
    for (i = 0; i <= linelen; ++i) {
      if (src[i] == '\0' || src[i] == '\n') {
	split_pos = i;
	break;
      }
      if (src[i] == ',' && i < linelen)
	last_comma = i;
      if (isspace(src[i]) && (i == 0 || !isspace(src[i-1])))
	last_space = i;
    }
    if (split_pos < 0) {
      if (last_comma >= 0)
	split_pos = last_comma + 1;
      else if (last_space >= 0)
	split_pos = last_space;
      else {
	for ( ; src[i]; ++i) {
	  if (src[i] == ',') {
	    ++i;
	    break;
	  }
	  if (isspace(src[i]))
	    break;
	}
	split_pos = i;
      }
    }
    if (split_pos > 0 && line > 0 && indent_depth > 0)
	dst_string.append(indent_depth, ' ');
    dst_string.append(src, split_pos);
    src += split_pos;
    if (isspace(*src))
      ++src;
    while (*src == ' ')
      ++src;
    if (*src == '\0')
      break;
    dst_string.push_back('\n');
  }
  return dst_string;
}

} // namespace IO_Operators

} // namespace Parma_Polyhedra_Library

