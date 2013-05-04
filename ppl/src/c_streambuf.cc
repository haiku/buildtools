/* c_streambuf class implementation (non-inline functions).
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

#include "c_streambuf.defs.hh"

namespace Parma_Polyhedra_Library {

c_streambuf::int_type
c_streambuf::uflow() {
  int_type c = underflow();
  nextc_buf = traits_type::eof();
  return c;
}

c_streambuf::int_type
c_streambuf::underflow() {
  const int_type eof = traits_type::eof();
  if (traits_type::eq_int_type(nextc_buf, eof)) {
    char buf;
    if (cb_read(&buf, 1) == 1)
      nextc_buf = buf;
    else
      nextc_buf = eof;
  }
  return nextc_buf;
}

std::streamsize
c_streambuf::xsgetn(char_type* s, std::streamsize n) {
  if (n == 0)
    return n;
  const int_type eof = traits_type::eof();
  int a;
  if (traits_type::eq_int_type(nextc_buf, eof))
    a = 0;
  else {
    s[0] = nextc_buf;
    a = 1;
  }
  std::streamsize r = cb_read(s + a, n - a) + a;
  if (r > 0)
    ungetc_buf = traits_type::to_int_type(s[r - 1]);
  else
    ungetc_buf = traits_type::eof();
  return r;
}

c_streambuf::int_type
c_streambuf::pbackfail(int_type c) {
  const int_type eof = traits_type::eof();
  nextc_buf = traits_type::eq_int_type(c, eof) ? ungetc_buf : c;
  ungetc_buf = eof;
  return nextc_buf;
}

std::streamsize
c_streambuf::xsputn(const char_type* s, std::streamsize n) {
  return cb_write(s, n);
}

c_streambuf::int_type
c_streambuf::overflow(int_type c) {
  const int_type eof = traits_type::eof();
  if (traits_type::eq_int_type(c, eof))
    return sync() ? eof : traits_type::not_eof(c);
  else {
    char buf = c;
    if (cb_write(&buf, 1) == 1)
      return c;
    else
      return eof;
  }
}

int
c_streambuf::sync() {
  return cb_sync();
}

} // namespace Parma_Polyhedra_Library
