/* Polyhedron class implementation: conversion().
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

#include "Linear_Row.defs.hh"
#include "Linear_System.defs.hh"
#include "Bit_Row.defs.hh"
#include "Bit_Matrix.defs.hh"
#include "Polyhedron.defs.hh"
#include "Scalar_Products.defs.hh"
#include "Temp.defs.hh"
#include <cstddef>
#include <climits>

namespace PPL = Parma_Polyhedra_Library;

/*!
  \return
  The number of lines of the polyhedron or the number of equality
  constraints in the result of conversion.

  \param source
  The system to use to convert \p dest: it may be modified;

  \param start
  The index of \p source row from which conversion begin;

  \param dest
  The result of the conversion;

  \param sat
  The saturation matrix telling us, for each row in \p source, which
  are the rows of \p dest that satisfy but do not saturate it;

  \param num_lines_or_equalities
  The number of rows in the system \p dest that are either lines of
  the polyhedron (when \p dest is a system of generators) or equality
  constraints (when \p dest is a system of constraints).

  For simplicity, all the following comments assume we are converting a
  constraint system \p source to a generator system \p dest;
  the comments for the symmetric case can be obtained by duality.

  If some of the constraints in \p source are redundant, they will be removed.
  This is why the \p source is not declared to be a constant parameter.

  If \p start is 0, then \p source is a sorted system; also, \p dest is
  a generator system corresponding to an empty constraint system.
  If otherwise \p start is greater than 0, then the two sub-systems of
  \p source made by the non-pending rows and the pending rows, respectively,
  are both sorted; also, \p dest is the generator system corresponding to
  the non-pending constraints of \p source.

  Independently from the value of \p start, \p dest has lines from index 0
  to index \p num_lines_or_equalities - 1 and rays/points from index
  \p num_lines_or_equalities to the last of its rows.

  Note that here the rows of \p sat are indexed by rows of \p dest
  and its columns are indexed by rows of \p source.

  We know that polyhedra can be represented by both a system of
  constraints or a system of generators (points, rays and lines)
  (see Section \ref representation).
  When we have both descriptions for a polyhedron \f$P\f$
  we have what is called a <EM>double description</EM>
  (or <EM>DD pair</EM>) for \f$P\f$.

  Here, the <EM>representation system</EM> refers to the system \f$C\f$
  whose rows represent the constraints that characterize \f$P\f$
  and the <EM>generating system</EM>, the system \f$G\f$ whose rows
  represent the generators of \f$P\f$.
  We say that a pair \f$(C, G)\f$ of (real) systems is
  a <EM>double description pair</EM> if
  \f[
    C\vect{x} \geq \vect{0}
      \quad\iff\quad
        \exists \vect{\lambda} \geq \vect{0} \mathrel{.}
	\vect{x} = G\vect{\lambda}.
  \f]

  The term "double description" is quite natural in the sense that
  such a pair contains two different description of the same object.
  In fact, if we refer to the cone representation of a polyhedron \f$P\f$
  and we call \f$C\f$ and \f$G\f$ the systems of constraints and
  rays respectively, we have
  \f[
    P = \{\, \vect{x} \in \Rset^n \mid C\vect{x} \geq \vect{0}\, \}
      = \{\, \vect{x} \in \Rset^n \mid \vect{x} = G\vect{\lambda}
      \text{ for some } \vect{\lambda} \geq \vect{0}\, \}.
  \f]

  Because of the theorem of Minkowski (see Section \ref prelims),
  we can say that, given a \f$m \times n\f$ representation system
  \f$C\f$ such that
  \f$\mathop{\mathrm{rank}}(C) = n = \mathit{dimension of the whole space}\f$
  for a non-empty polyhedron \f$P\f$,
  it is always possible to find a generating system \f$G\f$ for \f$P\f$
  such that \f$(C, G)\f$ is a DD pair.
  Conversely, Weyl's theorem ensures that, for each generating system
  \f$G\f$, it is possible to find a representation system \f$C\f$
  such that \f$(C, G)\f$ is a DD pair.

  For efficiency reasons, our representation of polyhedra makes use
  of a double description.
  We are thus left with two problems:
    -# given \f$C\f$ find \f$G\f$ such that \f$(C, G)\f$ is a DD pair;
    -# given \f$G\f$ find \f$C\f$ such that \f$(C, G)\f$ is a DD pair.

  Using Farkas' Lemma we can prove that these two problems are
  computationally equivalent (i.e., linear-time reducible to each other).
  Farkas' Lemma establishes a fundamental property of vectors in
  \f$\Rset^n\f$ that, in a sense, captures the essence of duality.
  Consider a matrix \f$A \in \Rset^{m \times n}\f$ and let
  \f$\{ \vect{a}_1, \ldots, \vect{a}_m \}\f$ be its set of row vectors.
  Consider also another vector \f$\vect{c} \in \Rset^n\f$ such that,
  whenever a vector \f$\vect{y} \in \Rset^n\f$ has a non-negative projection
  on the \f$\vect{a}_i\f$'s, it also has a non-negative projection
  on \f$\vect{c}\f$.
  The lemma states that \f$\vect{c}\f$ has this property if and only if
  it is in the cone generated by the \f$\vect{a}_i\f$'s.
  Formally, the lemma states the equivalence of the two following
  assertions:
    -# \f$
         \forall \vect{y}
           \mathrel{:} (A\vect{y} \geq 0 \implies
	   \langle \vect{y},\vect{c} \rangle \geq 0)
       \f$;
    -# \f$
         \exists \vect{\lambda} \geq \vect{0}
           \mathrel{.} \vect{c}^\mathrm{T} = \vect{\lambda}^\mathrm{T}A
       \f$.

  With this result we can prove that \f$(C, G)\f$ is a DD pair
  if and only if \f$(G^\mathrm{T}, C^\mathrm{T})\f$ is a DD pair.

  Suppose \f$(C, G)\f$ is a DD pair.
  Thus, for each \f$x\f$ of the appropriate dimension,
  \f$C\vect{x} \geq \vect{0}\f$ if and only if
  \f$\exists \lambda \geq 0 \mathrel{.} \vect{x} = G\vect{\lambda}\f$,
  which is of course equivalent to
  \f$
    \exists \vect{\lambda} \geq \vect{0}
      \mathrel{.} \vect{x}^\mathrm{T} = \vect{\lambda}^\mathrm{T}G^\mathrm{T}
  \f$.

  First, we assume that \f$\vect{z}\f$ is such that
  \f$G^\mathrm{T}\vect{z} \geq \vect{0}\f$
  and we will show that
  \f$\exists \vect{\mu} \geq \vect{0} \mathrel{.}
  \vect{z} = C^\mathrm{T}\vect{\mu}\f$.
  Let \f$\vect{x}\f$ be such that \f$C\vect{x} \geq \vect{0}\f$.
  Since \f$(C, G)\f$ is a DD pair, this is equivalent to
  \f$
    \exists \vect{\lambda} \geq \vect{0}
      \mathrel{.} \vect{x}^\mathrm{T} = \vect{\lambda}^\mathrm{T}G^\mathrm{T}
  \f$,
  which, by Farkas' Lemma is equivalent to
  \f$
    \forall \vect{y} \mathrel{:} (G^\mathrm{T}\vect{y} \geq \vect{0} \implies
                                 \langle \vect{y}, \vect{x} \rangle \geq 0)
  \f$.
  Taking \f$\vect{y} = \vect{z}\f$ and recalling our assumption that
  \f$G^\mathrm{T}\vect{z} \geq \vect{0}\f$
  we can conclude that \f$\langle \vect{z}, \vect{x} \rangle \geq 0\f$,
  that is equivalent to \f$\langle \vect{x}, \vect{z} \rangle \geq 0\f$.
  We have thus established that
  \f$
    \forall \vect{x} \mathrel{:} (C\vect{x} \geq \vect{0} \implies
    \langle \vect{x}, \vect{z} \rangle \geq 0)
  \f$.
  By Farkas' Lemma, this is equivalent to
  \f$\exists \vect{\mu} \geq \vect{0} \mathrel{.}
  \vect{z}^\mathrm{T} = \vect{\mu}^\mathrm{T} C\f$,
  which is equivalent to what we wanted to prove, that is,
  \f$\exists \vect{\mu} \geq \vect{0} \mathrel{.}
  \vect{z} = C^\mathrm{T}\vect{\mu}\f$.

  In order to prove the reverse implication, the following observation
  turns out to be useful:
  when \f$(C, G)\f$ is a DD pair, \f$CG \geq 0\f$.
  In fact,
  let \f$\vect{e}_j\f$ be the vector whose components are all \f$0\f$
  apart from the \f$j\f$-th one, which is \f$1\f$.
  Clearly \f$\vect{e}_j \geq \vect{0}\f$ and, taking
  \f$\vect{\lambda} = \vect{e}_j\f$ and
  \f$\vect{x} = G\vect{\lambda} = G \vect{e}_j\f$, we have
  \f$C\vect{x} = C(G \vect{e}_j) = (CG)\vect{e}_j \geq \vect{0}\f$,
  since \f$(C, G)\f$ is a DD pair.
  Thus, as \f$(CG)\vect{e}_j\f$ is the \f$j\f$-th column of \f$CG\f$
  and since the choice of \f$j\f$ was arbitrary, \f$CG \geq \vect{0}\f$.

  We now assume that \f$\vect{z}\f$ is such that
  \f$\exists \vect{\mu} \geq \vect{0} \mathrel{.}
  \vect{z} = C^\mathrm{T}\vect{\mu}\f$
  and we will prove that \f$G^\mathrm{T}\vect{z} \geq \vect{0}\f$.
  By Farkas' Lemma, the assumption
  \f$\exists \vect{\mu} \geq \vect{0} \mathrel{.}
  \vect{z}^\mathrm{T} = \vect{\mu}^\mathrm{T}C\f$,
  is equivalent to
  \f$\forall \vect{y} \mathrel{:} (C\vect{y} \geq \vect{0}
  \implies \langle \vect{y}, \vect{z} \rangle \geq 0)\f$.
  If we take \f$\vect{y} = G\vect{e}_j\f$ then \f$C\vect{y}
                 = CG\vect{e}_j \geq 0\f$,
  since \f$CG \geq \vect{0}\f$.
  So
  \f$
    \langle \vect{y}, \vect{z} \rangle
      = (\vect{e}_j^\mathrm{T}G^\mathrm{T}) \vect{z}
      = \vect{e}_j^\mathrm{T}(G^\mathrm{T} \vect{z})
      \geq 0
  \f$,
  that is, the \f$j\f$-th component of \f$G^\mathrm{T}\vect{z}\f$
  is non-negative. The arbitrary choice of \f$j\f$ allows us to conclude
  that \f$G^\mathrm{T}\vect{z} \geq \vect{0}\f$, as required.

  In view of this result, the following exposition assumes, for clarity,
  that the conversion being performed is from constraints to generators.
  Thus, even if the roles of \p source and \p dest can be interchanged,
  in the sequel we assume the \p source system will contain the constraints
  that represent the polyhedron and the \p dest system will contain
  the generator that generates it.

  There are some observations that are useful to understand this function:

  Observation 1: Let \f$A\f$ be a system of constraints that generate
  the polyhedron \f$P\f$ and \f$\vect{c}\f$ a new constraint that must
  be added. Suppose that there is a line \f$\vect{z}\f$ that does not
  saturate the constraint \f$\vect{c}\f$. If we combine the old lines
  and rays that do not saturate \f$\vect{c}\f$ (except \f$\vect{z}\f$)
  with \f$\vect{z}\f$ such that the new ones saturate \f$\vect{c}\f$,
  the new lines and rays also saturate the constraints  saturated by
  the old lines and rays.

  In fact, if \f$\vect{y}_1\f$ is the old generator that does not saturate
  \f$\vect{c}\f$, \f$\vect{y}_2\f$ is the new one such that
  \f[
    \vect{y}_2 = \lambda \vect{y}_1 + \mu \vect{z}
  \f]
  and \f$\vect{c}_1\f$ is a previous constraint that \f$\vect{y}_1\f$
  and \f$\vect{z}\f$ saturates, we can see
  \f[
    \langle \vect{c}_1, \vect{y}_2 \rangle
    = \langle \vect{c}_1, (\lambda \vect{y}_1 + \mu \vect{z}) \rangle
    = \lambda \langle \vect{c}_1, \vect{y}_1 \rangle
       + \mu \langle \vect{c}_1, \vect{z} \rangle
       = 0 + \mu \langle \vect{c}_1, \vect{z} \rangle
       = \mu \langle \vect{c}_1, \vect{z} \rangle
  \f]
  and
  \f[
    \mu \langle \vect{c}_1, \vect{z} \rangle = 0.
  \f]

  Proposition 1: Let \f$\vect{r}_1\f$ and \f$\vect{r}_2\f$ be distinct
  rays of \f$P\f$.
  Then the following statements are equivalent:
  a) \f$\vect{r}_1\f$ and \f$\vect{r}_2\f$ are adjacent extreme rays
     (see Section \ref prelims);
  b) \f$\vect{r}_1\f$ and \f$\vect{r}_2\f$ are extreme rays and the
     rank of the system composed by the constraints saturated by both
     \f$\vect{r}_1\f$ and \f$\vect{r}_2\f$ is equal to
     \f$d - 2\f$, where \f$d\f$ is the rank of the system of constraints.

  In fact, let \f$F\f$ be the system of generators that saturate the
  constraints saturated by both \f$\vect{r}_1\f$ and \f$\vect{r}_2\f$.
  If b) holds, the set \f$F\f$ is 2-dimensional and \f$\vect{r}_1\f$ and
  \f$\vect{r}_2\f$ generate this set. So, every generator
  \f$\vect{x}\f$ of \f$F\f$ can be built as a combination of
  \f$\vect{r}_1\f$ and \f$\vect{r}_2\f$, i.e.
  \f[
    \vect{x} = \lambda \vect{r}_1 + \mu \vect{r}_2.
  \f]
  This combination is non-negative because there exists at least a
  constraint \f$c\f$ saturated by \f$\vect{r}_1\f$ and not
  \f$\vect{r}_2\f$ (or vice versa) (because they are distinct) for which
  \f[
    \langle \vect{c}, \vect{x} \rangle \geq 0
  \f]
  and
  \f[
    \langle \vect{c}, \vect{x} \rangle
    = \lambda \langle \vect{c}, \vect{r}_1 \rangle
                           (or = \mu \langle \vect{c}, \vect{r}_2 \rangle).
  \f]
  So, there is no other extreme ray in \f$F\f$ and a) holds.
  Otherwise, if b) does not hold, the rank of the system generated by
  the constraints saturated by both \f$\vect{r}_1\f$ and \f$\vect{r}_2\f$
  is equal to \f$d - k\f$, with \p k \>= 3, the set \f$F\f$ is
  \p k -dimensional and at least \p k extreme rays are necessary
  to generate \f$F\f$.
  So, \f$\vect{r}_1\f$ and \f$\vect{r}_2\f$ are not adjacent and
  a) does not hold.

  Proposition 2: When we build the new system of generators starting from
  a system \f$A\f$ of constraints of \f$P\f$, if \f$\vect{c}\f$ is the
  constraint to add to \f$A\f$ and all lines of \f$P\f$ saturate
  \f$\vect{c}\f$, the new set of rays is the union of those rays that
  saturate, of those that satisfy and of a set \f$\overline Q\f$ of
  rays such that each of them
  -# lies on the hyper-plane represented by the k-th constraint,
  -# is a positive combination of two adjacent rays \f$\vect{r}_1\f$ and
     \f$\vect{r}_2\f$ such that the first one satisfies the constraint and
     the other does not satisfy it.
  If the adjacency property is not taken in account, the new set of
  rays is not irredundant, in general.

  In fact, if \f$\vect{r}_1\f$ and \f$\vect{r}_2\f$ are not adjacent,
  the rank of the system composed by the constraints saturated by both
  \f$\vect{r}_1\f$ and \f$\vect{r}_2\f$ is different from \f$d - 2\f$
  (see the previous proposition) or neither \f$\vect{r}_1\f$ nor
  \f$\vect{r}_2\f$ are extreme rays. Since the new ray \f$\vect{r}\f$
  is a combination of \f$\vect{r}_1\f$ and \f$\vect{r}_2\f$,
  it saturates the same constraints saturated by both \f$\vect{r}_1\f$ and
  \f$\vect{r}_2\f$.
  If the rank is less than \f$d - 2\f$, the rank of
  the system composed by \f$\vect{c}\f$ (that is saturated by \f$\vect{r}\f$)
  and by the constraints of \f$A\f$ saturated by \f$\vect{r}\f$  is less
  than \f$d - 1\f$. It means that \f$r\f$ is redundant (see
  Section \ref prelims).
  If neither \f$\vect{r}_1\f$ nor \f$\vect{r}_2\f$ are extreme rays,
  they belong to a 2-dimensional face containing exactly two extreme rays
  of \f$P\f$.
  These two adjacent rays build a ray equal to \f$\vect{r}\f$ and so
  \f$\vect{r}\f$ is redundant.
*/
PPL::dimension_type
PPL::Polyhedron::conversion(Linear_System& source,
			    const dimension_type start,
			    Linear_System& dest,
			    Bit_Matrix& sat,
			    dimension_type num_lines_or_equalities) {
  dimension_type source_num_rows = source.num_rows();
  dimension_type dest_num_rows = dest.num_rows();
  const dimension_type source_num_columns = source.num_columns();
  const dimension_type dest_num_columns = dest.num_columns();

  // By construction, the number of columns of `sat' is the same as
  // the number of rows of `source'; also, the number of rows of `sat'
  // is the same as the number of rows of `dest'.
  PPL_ASSERT(source_num_rows == sat.num_columns());
  PPL_ASSERT(dest_num_rows == sat.num_rows());

  // If `start > 0', then we are converting the pending constraints.
  PPL_ASSERT(start == 0 || start == source.first_pending_row());

  // During the iteration on the constraints in `source' we may identify
  // constraints that are redundant: these have to be removed by swapping
  // the rows of `source', taking care not to compromise the sortedness
  // of the constraints that still have to be considered.
  // To this end, the following counter keeps the number of redundant
  // constraints seen so far, to be used as a displacement when swapping rows.
  dimension_type source_num_redundant = 0;

  PPL_DIRTY_TEMP_COEFFICIENT(normalized_sp_i);
  PPL_DIRTY_TEMP_COEFFICIENT(normalized_sp_o);

  // Converting the sub-system of `source' having rows with indexes
  // from `start' to the last one (i.e., `source_num_rows' - 1).
  for (dimension_type k = start; k < source_num_rows; ) {

    // All the `source_num_redundant' redundant constraints identified so far
    // have consecutive indices starting from `k'.
    if (source_num_redundant > 0)
      // Let the next constraint have index `k'.
      // There is no need to swap the columns of `sat' (all zeroes).
      std::swap(source[k], source[k+source_num_redundant]);

    Linear_Row& source_k = source[k];

    // Constraints and generators must have the same dimension,
    // otherwise the scalar product below will bomb.
    PPL_ASSERT(source_num_columns == dest_num_columns);

    // `scalar_prod[i]' will contain the scalar product of the
    // constraint `source_k' and the generator `dest[i]'.  This
    // product is 0 if and only if the generator saturates the
    // constraint.
    PPL_DIRTY_TEMP0(std::vector<Coefficient>, scalar_prod);
    const int needed_space = dest_num_rows - scalar_prod.size();
    if (needed_space > 0)
      scalar_prod.insert(scalar_prod.end(), needed_space, Coefficient_zero());
    // `index_non_zero' will indicate the first generator in `dest'
    // that does not saturate the constraint `source_k'.
    dimension_type index_non_zero = 0;
    for ( ; index_non_zero < dest_num_rows; ++index_non_zero) {
      WEIGHT_BEGIN();
      Scalar_Products::assign(scalar_prod[index_non_zero],
			      source_k,
			      dest[index_non_zero]);
      WEIGHT_ADD_MUL(17, source_num_columns);
      if (scalar_prod[index_non_zero] != 0)
	// The generator does not saturate the constraint.
	break;
      // Check if the client has requested abandoning all expensive
      // computations.  If so, the exception specified by the client
      // is thrown now.
      maybe_abandon();
    }
    for (dimension_type i = index_non_zero + 1; i < dest_num_rows; ++i) {
      WEIGHT_BEGIN();
      Scalar_Products::assign(scalar_prod[i], source_k, dest[i]);
      WEIGHT_ADD_MUL(25, source_num_columns);
      // Check if the client has requested abandoning all expensive
      // computations.  If so, the exception specified by the client
      // is thrown now.
      maybe_abandon();
    }

    // We first treat the case when `index_non_zero' is less than
    // `num_lines_or_equalities', i.e., when the generator that
    // does not saturate the constraint `source_k' is a line.
    // The other case (described later) is when all the lines
    // in `dest' (i.e., all the rows having indexes less than
    // `num_lines_or_equalities') do saturate the constraint.

    if (index_non_zero < num_lines_or_equalities) {
      // Since the generator `dest[index_non_zero]' does not saturate
      // the constraint `source_k', it can no longer be a line
      // (see saturation rule in Section \ref prelims).
      // Therefore, we first transform it to a ray.
      dest[index_non_zero].set_is_ray_or_point_or_inequality();
      // Of the two possible choices, we select the ray satisfying
      // the constraint (namely, the ray whose scalar product
      // with the constraint gives a positive result).
      if (scalar_prod[index_non_zero] < 0) {
	// The ray `dest[index_non_zero]' lies on the wrong half-space:
	// we change it to have the opposite direction.
	neg_assign(scalar_prod[index_non_zero]);
	for (dimension_type j = dest_num_columns; j-- > 0; )
	  neg_assign(dest[index_non_zero][j]);
      }
      // Having changed a line to a ray, we set `dest' to be a
      // non-sorted system, we decrement the number of lines of `dest' and,
      // if necessary, we move the new ray below all the remaining lines.
      dest.set_sorted(false);
      --num_lines_or_equalities;
      if (index_non_zero != num_lines_or_equalities) {
	std::swap(dest[index_non_zero],
		  dest[num_lines_or_equalities]);
	std::swap(scalar_prod[index_non_zero],
		  scalar_prod[num_lines_or_equalities]);
      }
      Linear_Row& dest_nle = dest[num_lines_or_equalities];

      // Computing the new lineality space.
      // Since each line must lie on the hyper-plane corresponding to
      // the constraint `source_k', the scalar product between
      // the line and the constraint must be 0.
      // This property already holds for the lines having indexes
      // between 0 and `index_non_zero' - 1.
      // We have to consider the remaining lines, having indexes
      // between `index_non_zero' and `num_lines_or_equalities' - 1.
      // Each line that does not saturate the constraint has to be
      // linearly combined with generator `dest_nle' so that the
      // resulting new line saturates the constraint.
      // Note that, by Observation 1 above, the resulting new line
      // will still saturate all the constraints that were saturated by
      // the old line.

      Coefficient& scalar_prod_nle = scalar_prod[num_lines_or_equalities];
      for (dimension_type
	     i = index_non_zero; i < num_lines_or_equalities; ++i) {
	if (scalar_prod[i] != 0) {
	  // The following fragment optimizes the computation of
	  //
	  // Coefficient scale = scalar_prod[i];
	  // scale.gcd_assign(scalar_prod_nle);
	  // Coefficient normalized_sp_i = scalar_prod[i] / scale;
	  // Coefficient normalized_sp_n = scalar_prod_nle / scale;
	  // for (dimension_type c = dest_num_columns; c-- > 0; ) {
	  //   dest[i][c] *= normalized_sp_n;
	  //   dest[i][c] -= normalized_sp_i * dest_nle[c];
	  // }
	  normalize2(scalar_prod[i],
		     scalar_prod_nle,
		     normalized_sp_i,
		     normalized_sp_o);
	  Linear_Row& dest_i = dest[i];
	  for (dimension_type c = dest_num_columns; c-- > 0; ) {
	    Coefficient& dest_i_c = dest_i[c];
	    dest_i_c *= normalized_sp_o;
	    sub_mul_assign(dest_i_c, normalized_sp_i, dest_nle[c]);
	  }
	  dest_i.strong_normalize();
	  scalar_prod[i] = 0;
	  // `dest' has already been set as non-sorted.
	}
      }

      // Computing the new pointed cone.
      // Similarly to what we have done during the computation of
      // the lineality space, we consider all the remaining rays
      // (having indexes strictly greater than `num_lines_or_equalities')
      // that do not saturate the constraint `source_k'. These rays
      // are positively combined with the ray `dest_nle' so that the
      // resulting new rays saturate the constraint.
      for (dimension_type
	     i = num_lines_or_equalities + 1; i < dest_num_rows; ++i) {
	if (scalar_prod[i] != 0) {
	  // The following fragment optimizes the computation of
	  //
	  // Coefficient scale = scalar_prod[i];
	  // scale.gcd_assign(scalar_prod_nle);
	  // Coefficient normalized_sp_i = scalar_prod[i] / scale;
	  // Coefficient normalized_sp_n = scalar_prod_nle / scale;
	  // for (dimension_type c = dest_num_columns; c-- > 0; ) {
	  //   dest[i][c] *= normalized_sp_n;
	  //   dest[i][c] -= normalized_sp_i * dest_nle[c];
	  // }
	  normalize2(scalar_prod[i],
		     scalar_prod_nle,
		     normalized_sp_i,
		     normalized_sp_o);
	  Linear_Row& dest_i = dest[i];
          WEIGHT_BEGIN();
	  for (dimension_type c = dest_num_columns; c-- > 0; ) {
	    Coefficient& dest_i_c = dest_i[c];
	    dest_i_c *= normalized_sp_o;
	    sub_mul_assign(dest_i_c, normalized_sp_i, dest_nle[c]);
	  }
	  dest_i.strong_normalize();
	  scalar_prod[i] = 0;
	  // `dest' has already been set as non-sorted.
          WEIGHT_ADD_MUL(41, dest_num_columns);
	}
        // Check if the client has requested abandoning all expensive
        // computations.  If so, the exception specified by the client
        // is thrown now.
	maybe_abandon();
      }
      // Since the `scalar_prod_nle' is positive (by construction), it
      // does not saturate the constraint `source_k'.  Therefore, if
      // the constraint is an inequality, we set to 1 the
      // corresponding element of `sat' ...
      Bit_Row& sat_nle = sat[num_lines_or_equalities];
      if (source_k.is_ray_or_point_or_inequality())
	sat_nle.set(k);
      // ... otherwise, the constraint is an equality which is
      // violated by the generator `dest_nle': the generator has to be
      // removed from `dest'.
      else {
	--dest_num_rows;
	std::swap(dest_nle, dest[dest_num_rows]);
	std::swap(scalar_prod_nle, scalar_prod[dest_num_rows]);
	std::swap(sat_nle, sat[dest_num_rows]);
	// `dest' has already been set as non-sorted.
      }
      // We continue with the next constraint.
      ++k;
    }
    // Here we have `index_non_zero' >= `num_lines_or_equalities',
    // so that all the lines in `dest' saturate the constraint `source_k'.
    else {
      // First, we reorder the generators in `dest' as follows:
      // -# all the lines should have indexes between 0 and
      //    `num_lines_or_equalities' - 1 (this already holds);
      // -# all the rays that saturate the constraint should have
      //    indexes between `num_lines_or_equalities' and
      //    `lines_or_equal_bound' - 1; these rays form the set Q=.
      // -# all the rays that have a positive scalar product with the
      //    constraint should have indexes between `lines_or_equal_bound'
      //    and `sup_bound' - 1; these rays form the set Q+.
      // -# all the rays that have a negative scalar product with the
      //    constraint should have indexes between `sup_bound' and
      //    `dest_num_rows' - 1; these rays form the set Q-.
      dimension_type lines_or_equal_bound = num_lines_or_equalities;
      dimension_type inf_bound = dest_num_rows;
      // While we find saturating generators, we simply increment
      // `lines_or_equal_bound'.
      while (inf_bound > lines_or_equal_bound
	     && scalar_prod[lines_or_equal_bound] == 0)
	++lines_or_equal_bound;
      dimension_type sup_bound = lines_or_equal_bound;
      while (inf_bound > sup_bound) {
	const int sp_sign = sgn(scalar_prod[sup_bound]);
	if (sp_sign == 0) {
	  // This generator has to be moved in Q=.
	  std::swap(dest[sup_bound], dest[lines_or_equal_bound]);
	  std::swap(scalar_prod[sup_bound], scalar_prod[lines_or_equal_bound]);
	  std::swap(sat[sup_bound], sat[lines_or_equal_bound]);
	  ++lines_or_equal_bound;
	  ++sup_bound;
	  dest.set_sorted(false);
	}
	else if (sp_sign < 0) {
	  // This generator has to be moved in Q-.
	  --inf_bound;
	  std::swap(dest[sup_bound], dest[inf_bound]);
	  std::swap(scalar_prod[sup_bound], scalar_prod[inf_bound]);
	  std::swap(sat[sup_bound], sat[inf_bound]);
	  dest.set_sorted(false);
	}
	else
	  // sp_sign > 0: this generator has to be moved in Q+.
	  ++sup_bound;
      }

      if (sup_bound == dest_num_rows) {
	// Here the set Q- is empty.
	// If the constraint is an inequality, then all the generators
	// in Q= and Q+ satisfy the constraint. The constraint is redundant
	// and it can be safely removed from the constraint system.
	// This is why the `source' parameter is not declared `const'.
	if (source_k.is_ray_or_point_or_inequality()) {
	  ++source_num_redundant;
	  --source_num_rows;
	  // NOTE: we continue with the next cycle of the loop
	  // without incrementing the index `k', because:
	  // -# either `k == source_num_rows', and we will exit the loop;
	  // -# or, having increased `source_num_redundant', we will swap
	  //    in position `k' a constraint that still has to be examined.
	}
	else {
	  // The constraint is an equality, so that all the generators
	  // in Q+ violate it. Since the set Q- is empty, we can simply
	  // remove from `dest' all the generators of Q+.
	  dest_num_rows = lines_or_equal_bound;
          // We continue with the next constraint.
	  ++k;
        }
      }
      else {
	// The set Q- is not empty, i.e., at least one generator
	// violates the constraint `source_k'.
	// We have to further distinguish two cases:
	if (sup_bound == num_lines_or_equalities)
	  // The set Q+ is empty, so that all generators that satisfy
	  // the constraint also saturate it.
	  // We can simply remove from `dest' all the generators in Q-.
	  dest_num_rows = sup_bound;
	else {
	  // The sets Q+ and Q- are both non-empty.
	  // The generators of the new pointed cone are all those satisfying
	  // the constraint `source_k' plus a set of new rays enjoying
	  // the following properties:
	  // -# they lie on the hyper-plane represented by the constraint
	  // -# they are obtained as a positive combination of two
	  //    adjacent rays, the first taken from Q+ and the second
	  //    taken from Q-.

	  // The adjacency property is necessary to have an irredundant
	  // set of new rays (see proposition 2).
	  const dimension_type bound = dest_num_rows;

	  // In the following loop,
	  // `i' runs through the generators in the set Q+ and
	  // `j' runs through the generators in the set Q-.
	  for (dimension_type i = lines_or_equal_bound; i < sup_bound; ++i) {
	    for(dimension_type j = sup_bound; j < bound; ++j) {
	      // Checking if generators `dest[i]' and `dest[j]' are adjacent.
	      // If there exist another generator that saturates
	      // all the constraints saturated by both `dest[i]' and
	      // `dest[j]', then they are NOT adjacent.
	      PPL_ASSERT(sat[i].last() == ULONG_MAX || sat[i].last() < k);
	      PPL_ASSERT(sat[j].last() == ULONG_MAX || sat[j].last() < k);

	      // Being the union of `sat[i]' and `sat[j]',
	      // `new_satrow' corresponds to a ray that saturates all the
	      // constraints saturated by both `dest[i]' and `dest[j]'.
	      Bit_Row new_satrow(sat[i], sat[j]);

	      // Compute the number of common saturators.
	      // NOTE: this number has to be less than `k' because
	      // we are treating the `k'-th constraint.
	      const dimension_type
		num_common_satur = k - new_satrow.count_ones();

	      // Even before actually creating the new ray as a
	      // positive combination of `dest[i]' and `dest[j]',
	      // we exploit saturation information to check if
	      // it can be an extremal ray. To this end, we refer
	      // to the definition of a minimal proper face
	      // (see comments in Polyhedron.defs.hh):
	      // an extremal ray saturates at least `n' - `t' - 1
	      // constraints, where `n' is the dimension of the space
	      // and `t' is the dimension of the lineality space.
	      // Since `n == source_num_columns - 1' and
	      // `t == num_lines_or_equalities', we obtain that
	      // an extremal ray saturates at least
	      // `source_num_columns - num_lines_or_equalities - 2'
	      // constraints.
	      if (num_common_satur
		  >= source_num_columns - num_lines_or_equalities - 2) {
		// The minimal proper face rule is satisfied.
		// Now we actually check for redundancy by computing
		// adjacency information.
		bool redundant = false;
		WEIGHT_BEGIN();
		for (dimension_type
		       l = num_lines_or_equalities; l < bound; ++l)
		  if (l != i && l != j
		      && subset_or_equal(sat[l], new_satrow)) {
		    // Found another generator saturating all the
		    // constraints saturated by both `dest[i]' and `dest[j]'.
		    redundant = true;
		    break;
		  }
                PPL_ASSERT(bound >= num_lines_or_equalities);
                WEIGHT_ADD_MUL(15, bound - num_lines_or_equalities);
		if (!redundant) {
		  // Adding the new ray to `dest' and the corresponding
		  // saturation row to `sat'.
		  if (dest_num_rows == dest.num_rows()) {
		    // Make room for one more row.
		    dest.add_pending_row(Linear_Row::Flags(dest.topology(),
							   Linear_Row::RAY_OR_POINT_OR_INEQUALITY));
		    sat.add_recycled_row(new_satrow);
		  }
		  else
                    sat[dest_num_rows].swap(new_satrow);

		  Linear_Row& new_row = dest[dest_num_rows];
		  // The following fragment optimizes the computation of
		  //
		  // Coefficient scale = scalar_prod[i];
		  // scale.gcd_assign(scalar_prod[j]);
		  // Coefficient normalized_sp_i = scalar_prod[i] / scale;
		  // Coefficient normalized_sp_j = scalar_prod[j] / scale;
		  // for (dimension_type c = dest_num_columns; c-- > 0; ) {
		  //   new_row[c] = normalized_sp_i * dest[j][c];
		  //   new_row[c] -= normalized_sp_j * dest[i][c];
		  // }
		  normalize2(scalar_prod[i],
			     scalar_prod[j],
			     normalized_sp_i,
			     normalized_sp_o);
		  WEIGHT_BEGIN();
		  for (dimension_type c = dest_num_columns; c-- > 0; ) {
		    Coefficient& new_row_c = new_row[c];
		    new_row_c = normalized_sp_i * dest[j][c];
		    sub_mul_assign(new_row_c, normalized_sp_o, dest[i][c]);
		  }
                  WEIGHT_ADD_MUL(86, dest_num_columns);
		  new_row.strong_normalize();
		  // Since we added a new generator to `dest',
		  // we also add a new element to `scalar_prod';
		  // by construction, the new ray lies on the hyper-plane
		  // represented by the constraint `source_k'.
		  // Thus, the added scalar product is 0.
		  PPL_ASSERT(scalar_prod.size() >= dest_num_rows);
		  if (scalar_prod.size() <= dest_num_rows)
		    scalar_prod.push_back(Coefficient_zero());
		  else
		    scalar_prod[dest_num_rows] = Coefficient_zero();
		  // Increment the number of generators.
		  ++dest_num_rows;
		} // if (!redundant)
	      }
	    }
            // Check if the client has requested abandoning all expensive
            // computations.  If so, the exception specified by the client
            // is thrown now.
	    maybe_abandon();
	  }
	  // Now we substitute the rays in Q- (i.e., the rays violating
	  // the constraint) with the newly added rays.
	  dimension_type j;
	  if (source_k.is_ray_or_point_or_inequality()) {
	    // The constraint is an inequality:
	    // the violating generators are those in Q-.
	    j = sup_bound;
	    // For all the generators in Q+, set to 1 the corresponding
	    // entry for the constraint `source_k' in the saturation matrix.
            for (dimension_type l = lines_or_equal_bound; l < sup_bound; ++l)
              sat[l].set(k);
	  }
	  else
	    // The constraint is an equality:
	    // the violating generators are those in the union of Q+ and Q-.
	    j = lines_or_equal_bound;

	  // Swapping the newly added rays
	  // (index `i' running through `dest_num_rows - 1' down-to `bound')
	  // with the generators violating the constraint
	  // (index `j' running through `j' up-to `bound - 1').
	  dimension_type i = dest_num_rows;
	  while (j < bound && i > bound) {
	    --i;
	    std::swap(dest[i], dest[j]);
	    std::swap(scalar_prod[i], scalar_prod[j]);
	    std::swap(sat[i], sat[j]);
	    ++j;
	    dest.set_sorted(false);
	  }
	  // Setting the number of generators in `dest':
	  // - if the number of generators violating the constraint
	  //   is less than or equal to the number of the newly added
	  //   generators, we assign `i' to `dest_num_rows' because
	  //   all generators above this index are significant;
	  // - otherwise, we assign `j' to `dest_num_rows' because
	  //   all generators below index `j-1' violates the constraint.
	  dest_num_rows = (j == bound) ? i : j;
	}
	// We continue with the next constraint.
	++k;
      }
    }
  }

  // We may have identified some redundant constraints in `source',
  // which have been swapped at the end of the system.
  if (source_num_redundant > 0) {
    PPL_ASSERT(source_num_redundant == source.num_rows() - source_num_rows);
    source.erase_to_end(source_num_rows);
    sat.columns_erase_to_end(source_num_rows);
  }
  // If `start == 0', then `source' was sorted and remained so.
  // If otherwise `start > 0', then the two sub-system made by the
  // non-pending rows and the pending rows, respectively, were both sorted.
  // Thus, the overall system is sorted if and only if either
  // `start == source_num_rows' (i.e., the second sub-system is empty)
  // or the row ordering holds for the two rows at the boundary between
  // the two sub-systems.
  if (start > 0 && start < source_num_rows)
    source.set_sorted(compare(source[start - 1], source[start]) <= 0);
  // There are no longer pending constraints in `source'.
  source.unset_pending_rows();

  // We may have identified some redundant rays in `dest',
  // which have been swapped at the end of the system.
  if (dest_num_rows < dest.num_rows()) {
    dest.erase_to_end(dest_num_rows);
    // Be careful: we might have erased some of the non-pending rows.
    if (dest.first_pending_row() > dest_num_rows)
      dest.unset_pending_rows();
    sat.rows_erase_to_end(dest_num_rows);
  }
  if (dest.is_sorted())
    // If the non-pending generators in `dest' are still declared to be
    // sorted, then we have to also check for the sortedness of the
    // pending generators.
    for (dimension_type i = dest.first_pending_row(); i < dest_num_rows; ++i)
      if (compare(dest[i - 1], dest[i]) > 0) {
	dest.set_sorted(false);
	break;
      }
  // There are no pending generators in `dest'.
  dest.unset_pending_rows();

  return num_lines_or_equalities;
}
