/* Interval class implementation: non-inline template functions.
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

#ifndef PPL_Interval_templates_hh
#define PPL_Interval_templates_hh 1

#include <algorithm>

namespace Parma_Polyhedra_Library {

template <typename Boundary, typename Info>
template <typename C>
typename Enable_If<Is_Same_Or_Derived<I_Constraint_Base, C>::value, I_Result>::type
Interval<Boundary, Info>::lower_extend(const C& c) {
  PPL_ASSERT(OK());
  bool open;
  switch (c.rel()) {
  case V_LGE:
    return lower_extend();
  case V_NAN:
    return I_NOT_EMPTY | I_EXACT | I_UNCHANGED;
  case V_GT:
    open = true;
    break;
  case V_GE:
  case V_EQ:
    open = false;
    break;
  default:
    PPL_ASSERT(false);
  }
  min_assign(LOWER, lower(), info(), LOWER, c.value(), f_info(c.value(), open));
  PPL_ASSERT(OK());
  return I_ANY;
}

template <typename Boundary, typename Info>
template <typename C>
typename Enable_If<Is_Same_Or_Derived<I_Constraint_Base, C>::value, I_Result>::type
Interval<Boundary, Info>::upper_extend(const C& c) {
  PPL_ASSERT(OK());
  bool open;
  switch (c.rel()) {
  case V_LGE:
    return lower_extend();
  case V_NAN:
    return I_NOT_EMPTY | I_EXACT | I_UNCHANGED;
  case V_LT:
    open = true;
    break;
  case V_LE:
  case V_EQ:
    open = false;
    break;
  default:
    PPL_ASSERT(false);
  }
  max_assign(UPPER, upper(), info(), UPPER, c.value(), f_info(c.value(), open));
  PPL_ASSERT(OK());
  return I_ANY;
}

template <typename Boundary, typename Info>
template <typename From, typename Iterator>
typename Enable_If<Is_Interval<From>::value, void>::type
Interval<Boundary, Info>::CC76_widening_assign(const From& y,
					       Iterator first,
					       Iterator last) {
  // We assume that `y' is contained in or equal to `*this'.
  PPL_ASSERT(contains(y));
  Interval<Boundary, Info>& x = *this;

  // Upper bound.
  if (!x.upper_is_boundary_infinity()) {
    Boundary& x_ub = x.upper();
    const Boundary& y_ub = y.upper();
    PPL_ASSERT(!y.upper_is_boundary_infinity() && y_ub <= x_ub);
    if (y_ub < x_ub) {
      Iterator k = std::lower_bound(first, last, x_ub);
      if (k != last) {
	if (x_ub < *k)
	  x_ub = *k;
      }
      else
	x.upper_extend();
    }
  }

  // Lower bound.
  if (!x.lower_is_boundary_infinity()) {
    Boundary& x_lb = x.lower();
    const Boundary& y_lb = y.lower();
    PPL_ASSERT(!y.lower_is_boundary_infinity() && y_lb >= x_lb);
    if (y_lb > x_lb) {
      Iterator k = std::lower_bound(first, last, x_lb);
      if (k != last) {
	if (x_lb < *k) {
	  if (k != first)
	    x_lb = *--k;
	  else
	    x.lower_extend();
	}
      }
      else {
        if (k != first)
          x_lb = *--k;
        else
          x.lower_extend();
      }
    }
  }
}

template <typename Boundary, typename Info>
Interval<Boundary, Info>::Interval(const char* s) {
  // Get the lower bound.
  Boundary lower_bound;
  Result lower_r = assign_r(lower_bound, s, ROUND_DOWN);
  if (lower_r == V_CVT_STR_UNK || lower_r == V_NAN) {
    throw std::invalid_argument("PPL::Interval(const char* s)"
                                " with s invalid");
  }
  lower_r = result_relation_class(lower_r);

  // Get the upper bound.
  Boundary upper_bound;
  Result upper_r = assign_r(upper_bound, s, ROUND_UP);
  PPL_ASSERT(upper_r != V_CVT_STR_UNK && upper_r != V_NAN);
  upper_r = result_relation_class(upper_r);

  // Buld the interval.
  bool lower_open = false;
  bool upper_open = false;
  bool lower_boundary_infinity = false;
  bool upper_boundary_infinity = false;
  switch (lower_r) {
  case V_EQ:
  case V_GE:
    break;
  case V_GT:
    lower_open = true;
    break;
  case V_GT_MINUS_INFINITY:
    lower_open = true;
  case V_EQ_MINUS_INFINITY:
    lower_boundary_infinity = true;
    break;
  case V_EQ_PLUS_INFINITY:
  case V_LT_PLUS_INFINITY:
    if (upper_r == V_EQ_PLUS_INFINITY || upper_r == V_LT_PLUS_INFINITY)
      assign(UNIVERSE);
    else
      assign(EMPTY);
    break;
  default:
    PPL_ASSERT(false);
  }
  switch (upper_r) {
  case V_EQ:
  case V_LE:
    break;
  case V_LT:
    upper_open = true;
    break;
  case V_EQ_MINUS_INFINITY:
  case V_GT_MINUS_INFINITY:
    if (lower_r == V_EQ_MINUS_INFINITY || lower_r == V_GT_MINUS_INFINITY)
      assign(UNIVERSE);
    else
      assign(EMPTY);
    break;
  case V_LT_PLUS_INFINITY:
    upper_open = true;
  case V_EQ_PLUS_INFINITY:
    upper_boundary_infinity = true;
    break;
  default:
    PPL_ASSERT(false);
  }

  if (!lower_boundary_infinity
      && !upper_boundary_infinity
      && (lower_bound > upper_bound
          || (lower_open && lower_bound == upper_bound)))
    assign(EMPTY);
  else {
    if (lower_boundary_infinity)
      set_minus_infinity(LOWER, lower(), info(), lower_open);
    else
      Boundary_NS::assign(LOWER, lower(), info(),
                          LOWER, lower_bound, SCALAR_INFO, lower_open);
    if (upper_boundary_infinity)
      set_plus_infinity(UPPER, upper(), info(), upper_open);
    else
      Boundary_NS::assign(UPPER, upper(), info(),
                          UPPER, upper_bound, SCALAR_INFO, upper_open);
  }
}


template <typename Boundary, typename Info>
inline std::istream&
operator>>(std::istream& is, Interval<Boundary, Info>& x) {
  // Eat leading white space.
  int c;
  do {
    c = is.get();
  } while (isspace(c));

  // Get the opening parenthesis and handle the empty interval case.
  bool lower_open = false;
  if (c == '(')
    lower_open = true;
  else if (c == '[') {
    c = is.get();
    if (c == ']') {
      // Empty interval.
      x.assign(EMPTY);
      return is;
    }
    else
      is.unget();
  }
  else {
    is.unget();
    is.setstate(std::ios_base::failbit);
    return is;
  }

  // Get the lower bound.
  Boundary lower_bound;
  Result lower_r = input(lower_bound, is, ROUND_DOWN);
  if (lower_r == V_CVT_STR_UNK || lower_r == V_NAN) {
    is.setstate(std::ios_base::failbit);
    return is;
  }
  lower_r = result_relation_class(lower_r);

  // Match the comma separating the lower and upper bounds.
  do {
    c = is.get();
  } while (isspace(c));
  if (c != ',') {
    is.unget();
    is.setstate(std::ios_base::failbit);
    return is;
  }

  // Get the upper bound.
  Boundary upper_bound;
  Result upper_r = input(upper_bound, is, ROUND_UP);
  if (upper_r == V_CVT_STR_UNK || upper_r == V_NAN) {
    is.setstate(std::ios_base::failbit);
    return is;
  }
  upper_r = result_relation_class(upper_r);

  // Get the closing parenthesis.
  do {
    c = is.get();
  } while (isspace(c));
  bool upper_open = false;
  if (c == ')')
    upper_open = true;
  else if (c != ']') {
    is.unget();
    is.setstate(std::ios_base::failbit);
    return is;
  }

  // Buld interval.
  bool lower_boundary_infinity = false;
  bool upper_boundary_infinity = false;
  switch (lower_r) {
  case V_EQ:
  case V_GE:
    break;
  case V_GT:
    lower_open = true;
    break;
  case V_GT_MINUS_INFINITY:
    lower_open = true;
  case V_EQ_MINUS_INFINITY:
    lower_boundary_infinity = true;
    break;
  case V_EQ_PLUS_INFINITY:
  case V_LT_PLUS_INFINITY:
    if (upper_r == V_EQ_PLUS_INFINITY || upper_r == V_LT_PLUS_INFINITY)
      x.assign(UNIVERSE);
    else
      x.assign(EMPTY);
    return is;
  default:
    PPL_ASSERT(false);
  }
  switch (upper_r) {
  case V_EQ:
  case V_LE:
    break;
  case V_LT:
    upper_open = true;
    break;
  case V_GT_MINUS_INFINITY:
    upper_open = true;
  case V_EQ_MINUS_INFINITY:
    if (lower_r == V_EQ_MINUS_INFINITY || lower_r == V_GT_MINUS_INFINITY)
      x.assign(UNIVERSE);
    else
      x.assign(EMPTY);
    return is;
  case V_EQ_PLUS_INFINITY:
  case V_LT_PLUS_INFINITY:
    upper_boundary_infinity = true;
    break;
  default:
    PPL_ASSERT(false);
  }

  if (!lower_boundary_infinity
      && !upper_boundary_infinity
      && (lower_bound > upper_bound
	  || (lower_open && lower_bound == upper_bound)))
    x.assign(EMPTY);
  else {
    if (lower_boundary_infinity)
      set_minus_infinity(LOWER, x.lower(), x.info(), lower_open);
    else
      assign(LOWER, x.lower(), x.info(),
             LOWER, lower_bound, SCALAR_INFO, lower_open);
    if (upper_boundary_infinity)
      set_plus_infinity(UPPER, x.upper(), x.info(), upper_open);
    else
      assign(UPPER, x.upper(), x.info(),
             UPPER, upper_bound, SCALAR_INFO, upper_open);
  }
  return is;
}

template <typename Boundary, typename Info>
template <typename From>
typename Enable_If<Is_Interval<From>::value, bool>::type
Interval<Boundary, Info>::simplify_using_context_assign(const From& y) {
  // FIXME: the following code wrongly assumes that intervals are closed
  // and have no restrictions. It must be generalized.
  if (lt(UPPER, upper(), info(), LOWER, f_lower(y), f_info(y))) {
    lower_extend();
    return false;
  }
  if (gt(LOWER, lower(), info(), UPPER, f_upper(y), f_info(y))) {
    upper_extend();
    return false;
  }
  // Weakening the upper bound.
  if (!upper_is_boundary_infinity() && !y.upper_is_boundary_infinity()
      && y.upper() <= upper())
    upper_extend();
  // Weakening the lower bound.
  if (!lower_is_boundary_infinity() && !y.lower_is_boundary_infinity()
      && y.lower() >= lower())
    lower_extend();
  return true;
}

template <typename Boundary, typename Info>
template <typename From>
typename Enable_If<Is_Interval<From>::value, void>::type
Interval<Boundary, Info>::empty_intersection_assign(const From&) {
  // FIXME: write me.
  assign(EMPTY);
}

} // namespace Parma_Polyhedra_Library

#endif // !defined(PPL_Interval_templates_hh)
