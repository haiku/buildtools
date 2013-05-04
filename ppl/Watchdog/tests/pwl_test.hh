/* Header file for test programs.
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

#ifndef PWL_pwl_test_hh
#define PWL_pwl_test_hh 1

#include "pwl.hh"
#include <stdexcept>
#include <sstream>
#include <list>
#include <iterator>
#include <string>
#include <iostream>
#include <algorithm>
#include <typeinfo>
#include <cstdlib>

#ifndef NOISY
#define NOISY 0
#endif

#ifndef VERY_NOISY
#define VERY_NOISY 0
#endif

#define TRY try

#define CATCH \
catch (const std::overflow_error& e) { \
  std::cerr << "arithmetic overflow (" << e.what() << ")" \
            << std::endl; \
  exit(1); \
} \
catch (const std::exception& e) { \
  std::cerr << "std::exception caught: " \
            << e.what() << " (type == " << typeid(e).name() << ")" \
            << std::endl; \
  exit(1); \
}

#define BEGIN_MAIN				\
int						\
main() try {					\
  set_handlers();				\
  bool succeeded = false;			\
  bool overflow = false;			\
  std::list<std::string> failed_tests;

#define END_MAIN							\
  if (failed_tests.empty())						\
    return 0;								\
  else {								\
    std::cerr << "failed tests: ";					\
    std::copy(failed_tests.begin(), failed_tests.end(),			\
	      std::ostream_iterator<std::string>(std::cerr, " "));	\
    std::cerr << std::endl;						\
    return 1;								\
  }									\
}									\
catch (const std::overflow_error& e) {					\
  std::cerr << "arithmetic overflow (" << e.what() << ")"		\
            << std::endl;						\
  exit(1);								\
}									\
catch (const std::exception& e) {					\
  std::cerr << "std::exception caught: "				\
	    << e.what() << " (type == " << typeid(e).name() << ")"	\
	    << std::endl;						\
  exit(1);								\
}

#define ANNOUNCE_TEST(test)		 \
  nout << "\n=== " #test " ===" << std::endl

#define RUN_TEST(test)							\
  try {									\
    overflow = false;							\
    succeeded = test();							\
  }									\
  catch (const std::overflow_error& e) {				\
    nout << "arithmetic overflow (" << e.what() << ")"			\
	 << std::endl;							\
    overflow = true;							\
    succeeded = false;							\
  }									\
  catch (const std::exception& e) {					\
    nout << "std::exception caught: "					\
	 << e.what() << " (type == " << typeid(e).name() << ")"		\
	 << std::endl;							\
    succeeded = false;							\
  }									\
  catch (...) {								\
    nout << "unknown exception caught"					\
	 << std::endl;							\
    succeeded = false;							\
  }

#define DO_TEST(test)			 \
  ANNOUNCE_TEST(test);			 \
  RUN_TEST(test);			 \
  if (!succeeded)			 \
    failed_tests.push_back(#test);

#define DO_TEST_F(test)			 \
  ANNOUNCE_TEST(test);			 \
  RUN_TEST(test);			 \
  if (succeeded)			 \
    failed_tests.push_back(#test);

#define DO_TEST_OVERFLOW(test)		 \
  ANNOUNCE_TEST(test);			 \
  RUN_TEST(test);			 \
  if (succeeded || !overflow)		 \
    failed_tests.push_back(#test);

// Turn s into a string: PWL_TEST_STR(x + y) => "x + y".
#define PWL_TEST_STR(s) #s

// Turn the expansion of s into a string: PWL_TEST_XSTR(x) => "s expanded".
#define PWL_TEST_XSTR(s) PWL_TEST_STR(s)


namespace Parma_Watchdog_Library {

namespace Test {

static bool
check_noisy(const char*
#if PWL_HAVE_DECL_GETENV || NOISY || VERY_NOISY
            environment_variable
#endif
            ) {
#if PWL_HAVE_DECL_GETENV
  return getenv(environment_variable) != 0;
#else
#if NOISY
  if (strcmp(environment_variable, "PWL_NOISY_TESTS") == 0)
    return true;
#endif
#if VERY_NOISY
  if (strcmp(environment_variable, "PWL_VERY_NOISY_TESTS") == 0)
    return true;
#endif
  return false;
#endif
}

template<typename CharT, typename Traits = std::char_traits<CharT> >
class nullbuf : public std::basic_streambuf<CharT, Traits> {
protected:
  virtual typename Traits::int_type overflow(typename Traits::int_type c) {
    return Traits::not_eof(c);
  }
};

template <class CharT, class Traits = std::char_traits<CharT> >
class noisy_ostream : public std::basic_ostream<CharT, Traits> {
private:
  nullbuf<CharT, Traits> black_hole;

public:
  noisy_ostream(const std::basic_ostream<CharT, Traits>& os,
		const char* environment_variable)
    : std::basic_ostream<CharT, Traits>(check_noisy(environment_variable)
					? os.rdbuf()
					: &black_hole) {
  }
};

static noisy_ostream<char> nout(std::cout, "PWL_NOISY_TESTS");
static noisy_ostream<char> vnout(std::cout, "PWL_VERY_NOISY_TESTS");

void
set_handlers();

} // namespace Test

} // namespace Parma_Watchdog_Library

// These using directive and declaration are just to avoid the
// corresponding namespace qualifications in all the tests.
using namespace Parma_Watchdog_Library;
using namespace Parma_Watchdog_Library::Test;
using std::endl;

#endif // !defined(PWL_pwl_test_hh)
