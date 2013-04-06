/* Utilities for termination analysis: declarations.
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

#ifndef PPL_termination_defs_hh
#define PPL_termination_defs_hh 1

#include "Generator.types.hh"
#include "C_Polyhedron.types.hh"
#include "NNC_Polyhedron.types.hh"

namespace Parma_Polyhedra_Library {

/*! \brief
  Termination test using an improvement of the method by Mesnard and
  Serebrenik \ref BMPZ10 "[BMPZ10]".

  \tparam PSET
  Any pointset supported by the PPL that provides the
  <CODE>minimized_constraints()</CODE> method.

  \param pset
  A pointset approximating the behavior of a loop whose termination
  is being analyzed.  The variables indices are allocated as follows:
  - \f$ x'_1, \ldots, x'_n \f$ go onto space dimensions
    \f$ 0, \ldots, n-1 \f$,
  - \f$ x_1, \ldots, x_n \f$ go onto space dimensions
    \f$ n, \ldots, 2n-1 \f$,
  .
  where unprimed variables represent the values of the loop-relevant
  program variables before the update performed in the loop body,
  and primed variables represent the values of those program variables
  after the update.

  \return
  <CODE>true</CODE> if any loop approximated by \p pset definitely
  terminates; <CODE>false</CODE> if the test is inconclusive.
  However, if \p pset <EM>precisely</EM> characterizes the effect
  of the loop body onto the loop-relevant program variables,
  then <CODE>true</CODE> is returned <EM>if and only if</EM>
  the loop terminates.
*/
template <typename PSET>
bool
termination_test_MS(const PSET& pset);

/*! \brief
  Termination test using an improvement of the method by Mesnard and
  Serebrenik \ref BMPZ10 "[BMPZ10]".

  \tparam PSET
  Any pointset supported by the PPL that provides the
  <CODE>minimized_constraints()</CODE> method.

  \param pset_before
  A pointset approximating the values of loop-relevant variables
  <EM>before</EM> the update performed in the loop body that is being
  analyzed.  The variables indices are allocated as follows:
  - \f$ x_1, \ldots, x_n \f$ go onto space dimensions
    \f$ 0, \ldots, n-1 \f$.

  \param pset_after
  A pointset approximating the values of loop-relevant variables
  <EM>after</EM> the update performed in the loop body that is being
  analyzed.  The variables indices are allocated as follows:
  - \f$ x'_1, \ldots, x'_n \f$ go onto space dimensions
    \f$ 0, \ldots, n-1 \f$,
  - \f$ x_1, \ldots, x_n \f$ go onto space dimensions
    \f$ n, \ldots, 2n-1 \f$,

  Note that unprimed variables represent the values of the loop-relevant
  program variables before the update performed in the loop body,
  and primed variables represent the values of those program variables
  after the update.  Note also that unprimed variables are assigned
  to different space dimensions in \p pset_before and \p pset_after.

  \return
  <CODE>true</CODE> if any loop approximated by \p pset definitely
  terminates; <CODE>false</CODE> if the test is inconclusive.
  However, if \p pset_before and \p pset_after <EM>precisely</EM>
  characterize the effect of the loop body onto the loop-relevant
  program variables, then <CODE>true</CODE> is returned
  <EM>if and only if</EM> the loop terminates.
*/
template <typename PSET>
bool
termination_test_MS_2(const PSET& pset_before, const PSET& pset_after);

/*! \brief
  Termination test with witness ranking function using an improvement
  of the method by Mesnard and Serebrenik \ref BMPZ10 "[BMPZ10]".

  \tparam PSET
  Any pointset supported by the PPL that provides the
  <CODE>minimized_constraints()</CODE> method.

  \param pset
  A pointset approximating the behavior of a loop whose termination
  is being analyzed.  The variables indices are allocated as follows:
  - \f$ x'_1, \ldots, x'_n \f$ go onto space dimensions
    \f$ 0, \ldots, n-1 \f$,
  - \f$ x_1, \ldots, x_n \f$ go onto space dimensions
    \f$ n, \ldots, 2n-1 \f$,
  .
  where unprimed variables represent the values of the loop-relevant
  program variables before the update performed in the loop body,
  and primed variables represent the values of those program variables
  after the update.

  \param mu
  When <CODE>true</CODE> is returned, this is assigned a point
  of space dimension \f$ n+1 \f$ encoding one (not further specified)
  affine ranking function for the loop being analyzed.
  The ranking function is of the form \f$ \mu_0 + \sum_{i=1}^n \mu_i x_i \f$
  where \f$ \mu_0, \mu_1, \ldots, \mu_n \f$ are the coefficients
  of \p mu corresponding to the space dimensions \f$ n, 0, \ldots, n-1 \f$,
  respectively.

  \return
  <CODE>true</CODE> if any loop approximated by \p pset definitely
  terminates; <CODE>false</CODE> if the test is inconclusive.
  However, if \p pset <EM>precisely</EM> characterizes the effect
  of the loop body onto the loop-relevant program variables,
  then <CODE>true</CODE> is returned <EM>if and only if</EM>
  the loop terminates.
*/
template <typename PSET>
bool
one_affine_ranking_function_MS(const PSET& pset, Generator& mu);

/*! \brief
  Termination test with witness ranking function using an improvement
  of the method by Mesnard and Serebrenik \ref BMPZ10 "[BMPZ10]".

  \tparam PSET
  Any pointset supported by the PPL that provides the
  <CODE>minimized_constraints()</CODE> method.

  \param pset_before
  A pointset approximating the values of loop-relevant variables
  <EM>before</EM> the update performed in the loop body that is being
  analyzed.  The variables indices are allocated as follows:
  - \f$ x_1, \ldots, x_n \f$ go onto space dimensions
    \f$ 0, \ldots, n-1 \f$.

  \param pset_after
  A pointset approximating the values of loop-relevant variables
  <EM>after</EM> the update performed in the loop body that is being
  analyzed.  The variables indices are allocated as follows:
  - \f$ x'_1, \ldots, x'_n \f$ go onto space dimensions
    \f$ 0, \ldots, n-1 \f$,
  - \f$ x_1, \ldots, x_n \f$ go onto space dimensions
    \f$ n, \ldots, 2n-1 \f$,

  Note that unprimed variables represent the values of the loop-relevant
  program variables before the update performed in the loop body,
  and primed variables represent the values of those program variables
  after the update.  Note also that unprimed variables are assigned
  to different space dimensions in \p pset_before and \p pset_after.

  \param mu
  When <CODE>true</CODE> is returned, this is assigned a point
  of space dimension \f$ n+1 \f$ encoding one (not further specified)
  affine ranking function for the loop being analyzed.
  The ranking function is of the form \f$ \mu_0 + \sum_{i=1}^n \mu_i x_i \f$
  where \f$ \mu_0, \mu_1, \ldots, \mu_n \f$ are the coefficients
  of \p mu corresponding to the space dimensions \f$ n, 0, \ldots, n-1 \f$,
  respectively.

  \return
  <CODE>true</CODE> if any loop approximated by \p pset definitely
  terminates; <CODE>false</CODE> if the test is inconclusive.
  However, if \p pset_before and \p pset_after <EM>precisely</EM>
  characterize the effect of the loop body onto the loop-relevant
  program variables, then <CODE>true</CODE> is returned
  <EM>if and only if</EM> the loop terminates.
*/
template <typename PSET>
bool
one_affine_ranking_function_MS_2(const PSET& pset_before,
				 const PSET& pset_after,
				 Generator& mu);

/*! \brief
  Termination test with ranking function space using an improvement
  of the method by Mesnard and Serebrenik \ref BMPZ10 "[BMPZ10]".

  \tparam PSET
  Any pointset supported by the PPL that provides the
  <CODE>minimized_constraints()</CODE> method.

  \param pset
  A pointset approximating the behavior of a loop whose termination
  is being analyzed.  The variables indices are allocated as follows:
  - \f$ x'_1, \ldots, x'_n \f$ go onto space dimensions
    \f$ 0, \ldots, n-1 \f$,
  - \f$ x_1, \ldots, x_n \f$ go onto space dimensions
    \f$ n, \ldots, 2n-1 \f$,
  .
  where unprimed variables represent the values of the loop-relevant
  program variables before the update performed in the loop body,
  and primed variables represent the values of those program variables
  after the update.

  \param mu_space
  This is assigned a closed polyhedron of space dimension \f$ n+1 \f$
  representing the space of all the affine ranking functions for the loops
  that are precisely characterized by \p pset.
  These ranking functions are of the form
  \f$ \mu_0 + \sum_{i=1}^n \mu_i x_i \f$
  where \f$ \mu_0, \mu_1, \ldots, \mu_n \f$ identify any point of the
  \p mu_space polyhedron.
  The variables \f$ \mu_0, \mu_1, \ldots, \mu_n \f$
  correspond to the space dimensions of \p mu_space
  \f$ n, 0, \ldots, n-1 \f$, respectively.
  When \p mu_space is empty, it means that the test is inconclusive.
  However, if \p pset <EM>precisely</EM> characterizes the effect
  of the loop body onto the loop-relevant program variables,
  then \p mu_space is empty <EM>if and only if</EM>
  the loop does <EM>not</EM> terminate.
*/
template <typename PSET>
void
all_affine_ranking_functions_MS(const PSET& pset, C_Polyhedron& mu_space);

/*! \brief
  Termination test with ranking function space using an improvement
  of the method by Mesnard and Serebrenik \ref BMPZ10 "[BMPZ10]".

  \tparam PSET
  Any pointset supported by the PPL that provides the
  <CODE>minimized_constraints()</CODE> method.

  \param pset_before
  A pointset approximating the values of loop-relevant variables
  <EM>before</EM> the update performed in the loop body that is being
  analyzed.  The variables indices are allocated as follows:
  - \f$ x_1, \ldots, x_n \f$ go onto space dimensions
    \f$ 0, \ldots, n-1 \f$.

  \param pset_after
  A pointset approximating the values of loop-relevant variables
  <EM>after</EM> the update performed in the loop body that is being
  analyzed.  The variables indices are allocated as follows:
  - \f$ x'_1, \ldots, x'_n \f$ go onto space dimensions
    \f$ 0, \ldots, n-1 \f$,
  - \f$ x_1, \ldots, x_n \f$ go onto space dimensions
    \f$ n, \ldots, 2n-1 \f$,

  Note that unprimed variables represent the values of the loop-relevant
  program variables before the update performed in the loop body,
  and primed variables represent the values of those program variables
  after the update.  Note also that unprimed variables are assigned
  to different space dimensions in \p pset_before and \p pset_after.

  \param mu_space
  This is assigned a closed polyhedron of space dimension \f$ n+1 \f$
  representing the space of all the affine ranking functions for the loops
  that are precisely characterized by \p pset.
  These ranking functions are of the form
  \f$ \mu_0 + \sum_{i=1}^n \mu_i x_i \f$
  where \f$ \mu_0, \mu_1, \ldots, \mu_n \f$ identify any point of the
  \p mu_space polyhedron.
  The variables \f$ \mu_0, \mu_1, \ldots, \mu_n \f$
  correspond to the space dimensions of \p mu_space
  \f$ n, 0, \ldots, n-1 \f$, respectively.
  When \p mu_space is empty, it means that the test is inconclusive.
  However, if \p pset_before and \p pset_after <EM>precisely</EM>
  characterize the effect of the loop body onto the loop-relevant
  program variables, then \p mu_space is empty <EM>if and only if</EM>
  the loop does <EM>not</EM> terminate.
*/
template <typename PSET>
void
all_affine_ranking_functions_MS_2(const PSET& pset_before,
				  const PSET& pset_after,
				  C_Polyhedron& mu_space);

/*! \brief
  Computes the spaces of affine \e quasi ranking functions
  using an improvement of the method by Mesnard and Serebrenik
  \ref BMPZ10 "[BMPZ10]".

  \tparam PSET
  Any pointset supported by the PPL that provides the
  <CODE>minimized_constraints()</CODE> method.

  \param pset
  A pointset approximating the behavior of a loop whose termination
  is being analyzed.  The variables indices are allocated as follows:
  - \f$ x'_1, \ldots, x'_n \f$ go onto space dimensions
    \f$ 0, \ldots, n-1 \f$,
  - \f$ x_1, \ldots, x_n \f$ go onto space dimensions
    \f$ n, \ldots, 2n-1 \f$,
  .
  where unprimed variables represent the values of the loop-relevant
  program variables before the update performed in the loop body,
  and primed variables represent the values of those program variables
  after the update.

  \param decreasing_mu_space
  This is assigned a closed polyhedron of space dimension \f$ n+1 \f$
  representing the space of all the decreasing affine functions
  for the loops that are precisely characterized by \p pset.

  \param bounded_mu_space
  This is assigned a closed polyhedron of space dimension \f$ n+1 \f$
  representing the space of all the lower bounded affine functions
  for the loops that are precisely characterized by \p pset.

  These quasi-ranking functions are of the form
  \f$ \mu_0 + \sum_{i=1}^n \mu_i x_i \f$
  where \f$ \mu_0, \mu_1, \ldots, \mu_n \f$ identify any point of the
  \p decreasing_mu_space and \p bounded_mu_space polyhedrons.
  The variables \f$ \mu_0, \mu_1, \ldots, \mu_n \f$
  correspond to the space dimensions \f$ n, 0, \ldots, n-1 \f$, respectively.
  When \p decreasing_mu_space (resp., \p bounded_mu_space) is empty,
  it means that the test is inconclusive.
  However, if \p pset <EM>precisely</EM> characterizes the effect
  of the loop body onto the loop-relevant program variables,
  then \p decreasing_mu_space (resp., \p bounded_mu_space) will be empty
  <EM>if and only if</EM> there is no decreasing (resp., lower bounded)
  affine function, so that the loop does not terminate.
*/
template <typename PSET>
void
all_affine_quasi_ranking_functions_MS(const PSET& pset,
                                      C_Polyhedron& decreasing_mu_space,
                                      C_Polyhedron& bounded_mu_space);

/*! \brief
  Computes the spaces of affine \e quasi ranking functions
  using an improvement of the method by Mesnard and Serebrenik
  \ref BMPZ10 "[BMPZ10]".

  \tparam PSET
  Any pointset supported by the PPL that provides the
  <CODE>minimized_constraints()</CODE> method.

  \param pset_before
  A pointset approximating the values of loop-relevant variables
  <EM>before</EM> the update performed in the loop body that is being
  analyzed.  The variables indices are allocated as follows:
  - \f$ x_1, \ldots, x_n \f$ go onto space dimensions
    \f$ 0, \ldots, n-1 \f$.

  \param pset_after
  A pointset approximating the values of loop-relevant variables
  <EM>after</EM> the update performed in the loop body that is being
  analyzed.  The variables indices are allocated as follows:
  - \f$ x'_1, \ldots, x'_n \f$ go onto space dimensions
    \f$ 0, \ldots, n-1 \f$,
  - \f$ x_1, \ldots, x_n \f$ go onto space dimensions
    \f$ n, \ldots, 2n-1 \f$,

  Note that unprimed variables represent the values of the loop-relevant
  program variables before the update performed in the loop body,
  and primed variables represent the values of those program variables
  after the update.  Note also that unprimed variables are assigned
  to different space dimensions in \p pset_before and \p pset_after.

  \param decreasing_mu_space
  This is assigned a closed polyhedron of space dimension \f$ n+1 \f$
  representing the space of all the decreasing affine functions
  for the loops that are precisely characterized by \p pset.

  \param bounded_mu_space
  This is assigned a closed polyhedron of space dimension \f$ n+1 \f$
  representing the space of all the lower bounded affine functions
  for the loops that are precisely characterized by \p pset.

  These ranking functions are of the form
  \f$ \mu_0 + \sum_{i=1}^n \mu_i x_i \f$
  where \f$ \mu_0, \mu_1, \ldots, \mu_n \f$ identify any point of the
  \p decreasing_mu_space and \p bounded_mu_space polyhedrons.
  The variables \f$ \mu_0, \mu_1, \ldots, \mu_n \f$
  correspond to the space dimensions \f$ n, 0, \ldots, n-1 \f$, respectively.
  When \p decreasing_mu_space (resp., \p bounded_mu_space) is empty,
  it means that the test is inconclusive.
  However, if \p pset_before and \p pset_after <EM>precisely</EM>
  characterize the effect of the loop body onto the loop-relevant
  program variables, then \p decreasing_mu_space (resp., \p bounded_mu_space)
  will be empty <EM>if and only if</EM> there is no decreasing
  (resp., lower bounded) affine function, so that the loop does not terminate.
*/
template <typename PSET>
void
all_affine_quasi_ranking_functions_MS_2(const PSET& pset_before,
                                        const PSET& pset_after,
                                        C_Polyhedron& decreasing_mu_space,
                                        C_Polyhedron& bounded_mu_space);

/*! \brief
  Like termination_test_MS() but using the method by Podelski and
  Rybalchenko \ref BMPZ10 "[BMPZ10]".
*/
template <typename PSET>
bool
termination_test_PR(const PSET& pset);

/*! \brief
  Like termination_test_MS_2() but using an alternative formalization
  of the method by Podelski and Rybalchenko \ref BMPZ10 "[BMPZ10]".
*/
template <typename PSET>
bool
termination_test_PR_2(const PSET& pset_before, const PSET& pset_after);

/*! \brief
  Like one_affine_ranking_function_MS() but using the method by Podelski
  and Rybalchenko \ref BMPZ10 "[BMPZ10]".
*/
template <typename PSET>
bool
one_affine_ranking_function_PR(const PSET& pset, Generator& mu);

/*! \brief
  Like one_affine_ranking_function_MS_2() but using an alternative
  formalization of the method by Podelski and Rybalchenko
  \ref BMPZ10 "[BMPZ10]".
*/
template <typename PSET>
bool
one_affine_ranking_function_PR_2(const PSET& pset_before,
				 const PSET& pset_after,
				 Generator& mu);

/*! \brief
  Like all_affine_ranking_functions_MS() but using the method by Podelski
  and Rybalchenko \ref BMPZ10 "[BMPZ10]".
*/
template <typename PSET>
void
all_affine_ranking_functions_PR(const PSET& pset, NNC_Polyhedron& mu_space);

/*! \brief
  Like all_affine_ranking_functions_MS_2() but using an alternative
  formalization of the method by Podelski and Rybalchenko
  \ref BMPZ10 "[BMPZ10]".
*/
template <typename PSET>
void
all_affine_ranking_functions_PR_2(const PSET& pset_before,
				  const PSET& pset_after,
				  NNC_Polyhedron& mu_space);

} // namespace Parma_Polyhedra_Library

#include "termination.templates.hh"

#endif // !defined(PPL_termination_defs_hh)
