/* stdiobuf class implementation (non-inline functions).
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

#include "stdiobuf.defs.hh"

namespace Parma_Polyhedra_Library {

stdiobuf::int_type
stdiobuf::uflow() {
  ungetc_buf = getc(fp);
  return ungetc_buf;
}

stdiobuf::int_type
stdiobuf::underflow() {
  int_type c = getc(fp);
  return ungetc(c, fp);
}

std::streamsize
stdiobuf::xsgetn(char_type* s, std::streamsize n) {
  std::streamsize r = fread(s, 1, n, fp);
  if (r > 0)
    ungetc_buf = traits_type::to_int_type(s[r - 1]);
  else
    ungetc_buf = traits_type::eof();
  return r;
}

stdiobuf::int_type
stdiobuf::pbackfail(int_type c) {
  const int_type eof = traits_type::eof();
  int_type u = traits_type::eq_int_type(c, eof) ? ungetc_buf : c;
  ungetc_buf = eof;
  return traits_type::eq_int_type(u, eof) ? eof : ungetc(u, fp);
}

std::streamsize
stdiobuf::xsputn(const char_type* s, std::streamsize n) {
  return fwrite(s, 1, n, fp);
}

stdiobuf::int_type
stdiobuf::overflow(int_type c) {
  const int_type eof = traits_type::eof();
  if (traits_type::eq_int_type(c, eof))
    return fflush(fp) ? eof : traits_type::not_eof(c);
  else
    return putc(c, fp);
}

int
stdiobuf::sync() {
  return fflush(fp);
}

} // namespace Parma_Polyhedra_Library
