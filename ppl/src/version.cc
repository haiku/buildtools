/* Definition of functions providing version and licensing information.
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
#include "version.hh"

namespace PPL = Parma_Polyhedra_Library;

namespace {

const char version_string[] = PPL_PACKAGE_VERSION;

const char banner_string[] =
"This is "PPL_PACKAGE_NAME" (PPL) version "PPL_PACKAGE_VERSION".\n"
"Copyright (C) 2001-2010 Roberto Bagnara <bagnara@cs.unipr.it>\n"
"\n"
"The PPL is free software; see the source for copying conditions.\n"
"There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A\n"
"PARTICULAR PURPOSE.\n"
"\n"
#if defined(__COMO__)
#define str(s) # s
#define xstr(s) str(s)
"Compiled by the Comeau C++ compiler version "xstr(__COMO_VERSION__)".\n"
#elif defined(__INTEL_COMPILER)
#define str(s) # s
#define xstr(s) str(s)
"Compiled by the Intel C++ compiler version "xstr(__INTEL_COMPILER)".\n"
#elif defined(__GNUC__)
"Compiled by the GNU C++ compiler version "__VERSION__".\n"
#else
"Compiled by an unknown compiler.\n"
#endif
"\n"
"Report bugs to "PPL_PACKAGE_BUGREPORT"."
"  For the most up-to-date information\n"
"see the Parma Polyhedra Library site: http://www.cs.unipr.it/ppl/ .\n"
"\n"
"Contributors:\n"
"Roberto Bagnara, Patricia M. Hill, Enea Zaffanella, Elisa Ricci,\n"
"Abramo Bagnara, Andrea Cimino, Katy Dobson, Elena Mazzi,\n"
"Matthew Mundell, Barbara Quartieri, Enric Rodriguez Carbonell,\n"
"Alessandro Zaccagnini,\n"
"Irene Bacchi, Danilo Bonardi, Sara Bonini, Giordano Fracasso,\n"
"Maximiliano Marchesi, David Merchat, Andrea Pescetti, Angela Stazzone,\n"
"Fabio Trabucchi, Claudio Trento, Tatiana Zolo.\n"
"\n"
"Special thanks to:\n"
"Lucia Alessandrini, Frederic Besson, Tevfik Bultan, Manuel Carro,\n"
"Marco Comini, Goran Frehse, Denis Gopan, Martin Guy, Bruno Haible,\n"
"Bertrand Jeannet, Herve Le Verge, Francesco Logozzo, Costantino Medori,\n"
"Fred Mesnard, Ken Mixter, Jose Morales, Sebastian Pop, Thomas Reps,\n"
"Mooly Sagiv, Sriram Sankaranarayanan, Axel Simon, Fausto Spoto,\n"
"Basile Starynkevitch, Pedro Vasconcelos, Ralf Wildenhues.";

} // namespace

unsigned
PPL::version_major() {
  return PPL_VERSION_MAJOR;
}

unsigned
PPL::version_minor() {
  return PPL_VERSION_MINOR;
}

unsigned
PPL::version_revision() {
  return PPL_VERSION_REVISION;
}

unsigned
PPL::version_beta() {
  return PPL_VERSION_BETA;
}

const char*
PPL::version() {
  return version_string;
}

const char*
PPL::banner() {
  return banner_string;
}
