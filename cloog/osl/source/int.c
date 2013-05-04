
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                             int.c                               **
     **-----------------------------------------------------------------**
     **                   First version: 18/07/2011                     **
     **-----------------------------------------------------------------**

 
 *****************************************************************************
 * OpenScop: Structures and formats for polyhedral tools to talk together    *
 *****************************************************************************
 *    ,___,,_,__,,__,,__,,__,,_,__,,_,__,,__,,___,_,__,,_,__,                *
 *    /   / /  //  //  //  // /   / /  //  //   / /  // /  /|,_,             *
 *   /   / /  //  //  //  // /   / /  //  //   / /  // /  / / /\             *
 *  |~~~|~|~~~|~~~|~~~|~~~|~|~~~|~|~~~|~~~|~~~|~|~~~|~|~~~|/_/  \            *
 *  | G |C| P | = | L | P |=| = |C| = | = | = |=| = |=| C |\  \ /\           *
 *  | R |l| o | = | e | l |=| = |a| = | = | = |=| = |=| L | \# \ /\          *
 *  | A |a| l | = | t | u |=| = |n| = | = | = |=| = |=| o | |\# \  \         *
 *  | P |n| l | = | s | t |=| = |d| = | = | = | |   |=| o | | \# \  \        *
 *  | H | | y |   | e | o | | = |l|   |   | = | |   | | G | |  \  \  \       *
 *  | I | |   |   | e |   | |   | |   |   |   | |   | |   | |   \  \  \      *
 *  | T | |   |   |   |   | |   | |   |   |   | |   | |   | |    \  \  \     *
 *  | E | |   |   |   |   | |   | |   |   |   | |   | |   | |     \  \  \    *
 *  | * |*| * | * | * | * |*| * |*| * | * | * |*| * |*| * | /      \* \  \   *
 *  | O |p| e | n | S | c |o| p |-| L | i | b |r| a |r| y |/        \  \ /   *
 *  '---'-'---'---'---'---'-'---'-'---'---'---'-'---'-'---'          '--'    *
 *                                                                           *
 * Copyright (C) 2008 University Paris-Sud 11 and INRIA                      *
 *                                                                           *
 * (3-clause BSD license)                                                    *
 * Redistribution and use in source  and binary forms, with or without       *
 * modification, are permitted provided that the following conditions        *
 * are met:                                                                  *
 *                                                                           *
 * 1. Redistributions of source code must retain the above copyright notice, *
 *    this list of conditions and the following disclaimer.                  *
 * 2. Redistributions in binary form must reproduce the above copyright      *
 *    notice, this list of conditions and the following disclaimer in the    *
 *    documentation and/or other materials provided with the distribution.   *
 * 3. The name of the author may not be used to endorse or promote products  *
 *    derived from this software without specific prior written permission.  *
 *                                                                           *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR      *
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES *
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.   *
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,          *
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT  *
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, *
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY     *
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT       *
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF  *
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.         *
 *                                                                           *
 * OpenScop Library, a library to manipulate OpenScop formats and data       *
 * structures. Written by:                                                   *
 * Cedric Bastoul     <Cedric.Bastoul@u-psud.fr> and                         *
 * Louis-Noel Pouchet <Louis-Noel.pouchet@inria.fr>                          *
 *                                                                           *
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#ifdef OSL_GMP_IS_HERE
# include <gmp.h>
#endif

#include <osl/macros.h>
#include <osl/int.h>



/*+***************************************************************************
 *                                Basic Functions                            *
 *****************************************************************************/


/**
 * osl_int_dump_precision function:
 * this function prints in a human readable fashion the precision
 * corresponding to the "precision" parameter.
 * \param[in] file      The file where to print the precision.
 * \param[in] precision The precision to print.
 */
void osl_int_dump_precision(FILE * file, int precision) {

  switch (precision) {
    case OSL_PRECISION_SP:
      fprintf(file, "32 bits");
      break;
    case OSL_PRECISION_DP:
      fprintf(file, "64 bits");
      break;
#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      fprintf(file, "GMP");
      break;
#endif
    default:
      fprintf(file, "unknown precision %d", precision);
  }
}


int osl_int_sizeof(int precision) {
  switch (precision) {
    case OSL_PRECISION_SP:
      return sizeof(long int);

    case OSL_PRECISION_DP:
      return sizeof(long long int);

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      return sizeof(mpz_t);
#endif

    default:
      OSL_error("unknown precision");
  }
}


void * osl_int_address(int precision, void * base, int offset) {
  switch (precision) {
    case OSL_PRECISION_SP:
      return (long int *)base + offset;

    case OSL_PRECISION_DP:
      return (long long int *)base + offset;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      return (mpz_t *)base + offset;
#endif

    default:
      OSL_error("unknown precision");
  }
}


void osl_int_init(int precision, void * value_base, int value_offset) {
  void * value = osl_int_address(precision, value_base, value_offset);

  switch (precision) {
    case OSL_PRECISION_SP:
      *(long int *)value = 0;
      break;

    case OSL_PRECISION_DP:
      *(long long int *)value = 0;
      break;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      mpz_init(*(mpz_t *)value);
      break;
#endif

    default:
      OSL_error("unknown precision");
  }
}


void * osl_int_malloc(int precision) {
  void * value;

  switch (precision) {
    case OSL_PRECISION_SP:
      value = malloc(sizeof(long int));
      break;

    case OSL_PRECISION_DP:
      value = malloc(sizeof(long long int));
      *(long long int *)value = 0;
      break;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      value = malloc(sizeof(mpz_t));
      break;
#endif

    default:
      OSL_error("unknown precision");
  }

  osl_int_init(precision, value, 0);
  return value;
}


/**
 * val1_base[val1_offset] = val2_base[val2_offset];
 */
void osl_int_assign(int precision,
                    void * val1_base, int val1_offset,
                    void * val2_base, int val2_offset) {
  void * val1 = osl_int_address(precision, val1_base, val1_offset);
  void * val2 = osl_int_address(precision, val2_base, val2_offset);

  switch (precision) {
    case OSL_PRECISION_SP:
      *(long int *)val1 = *(long int *)val2;
      break;

    case OSL_PRECISION_DP:
      *(long long int *)val1 = *(long long int *)val2;
      break;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      mpz_set(*(mpz_t *)val1, *(mpz_t *)val2);
      break;
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * value_base[value_offset] = i;
 */
void osl_int_set_si(int precision, void * value_base, int value_offset,
                    int i) {
  void * value = osl_int_address(precision, value_base, value_offset);

  switch (precision) {
    case OSL_PRECISION_SP:
      *(long int *)value = (long int)i;
      break;

    case OSL_PRECISION_DP:
      *(long long int *)value = (long long int)i;
      break;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      mpz_set_si(*(mpz_t *)value, i);
      break;
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * return value_base[value_offset];
 */
int osl_int_get_si(int precision, void * value_base, int value_offset) {
  void * value = osl_int_address(precision, value_base, value_offset);

  switch (precision) {
    case OSL_PRECISION_SP:
      return *(int *)value;

    case OSL_PRECISION_DP:
      return *(int *)value;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      return mpz_get_si(*(mpz_t *)value);
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * value_base[value_offset] = i; // including initialization for GMP
 */
void osl_int_init_set_si(int precision,
                         void * value_base, int value_offset, int i) {
  void * value = osl_int_address(precision, value_base, value_offset);

  switch (precision) {
    case OSL_PRECISION_SP:
      *(long int *)value = (long int)i;
      break;

    case OSL_PRECISION_DP:
      *(long long int *)value = (long long int)i;
      break;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      mpz_init_set_si(*(mpz_t *)value, i);
      break;
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * value_base[value_offset] = 0; // Including cleaning for GMP
 */
void osl_int_clear(int precision, void * value_base, int value_offset) {
  void * value = osl_int_address(precision, value_base, value_offset);
  
  switch (precision) {
    case OSL_PRECISION_SP:
      *(long int *)value = 0;
      break;

    case OSL_PRECISION_DP:
      *(long long int *)value = 0;
      break;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      mpz_clear(*(mpz_t *)value);
      break;
#endif

    default:
      OSL_error("unknown precision");
  }
}


void osl_int_free(int precision, void * value_base, int value_offset) {
  void * value = osl_int_address(precision, value_base, value_offset);

  osl_int_clear(precision, value_base, value_offset);
  free(value);
}


/**
 * osl_int_print function:
 * this function displays an integer value into a file (file, possibly stdout).
 * \param file         The file where the integer has to be printed.
 * \param precision    The precision of the integer.
 * \param value_base   Address of the base integer value.
 * \param value_offset Offset in number of values from the base integer value.
 */
void osl_int_print(FILE * file, int precision,
                   void * value_base, int value_offset) {
  char string[OSL_MAX_STRING];
  
  osl_int_sprint(string, precision, value_base, value_offset);
  fprintf(file, "%s", string);
}


/**
 * osl_int_sprint function:
 * this function prints an integer value into a string, it uses the
 * OpenScop Library formats OSL_FMT_* to format the printing.
 * \param string       The string where the integer has to be printed.
 * \param precision    The precision of the integer.
 * \param value_base   Address of the base integer value.
 * \param value_offset Offset in number of values from the base integer value.
 */
void osl_int_sprint(char * string, int precision,
                    void * value_base, int value_offset) {
  void * value = osl_int_address(precision, value_base, value_offset);
            
  switch (precision) {
    case OSL_PRECISION_SP:
      sprintf(string, OSL_FMT_SP, *(long int *)value);
      break;

    case OSL_PRECISION_DP:
      sprintf(string, OSL_FMT_DP, *(long long int *)value);
      break;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP: {
      char * str;
      str = mpz_get_str(0, 10, *(mpz_t *)value); //TODO: 10 -> #define
      sprintf(string, OSL_FMT_MP, str);
      free(str);
      break;
    }
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * osl_int_sprint_txt function:
 * this function is similar to osl_int_sprintf but it prints the value
 * using OSL_TMT_TXT_* formats.
 * \see osl_int_sprintf
 */
void osl_int_sprint_txt(char * string, int precision,
                        void * value_base, int value_offset) {
  void * value = osl_int_address(precision, value_base, value_offset);
            
  switch (precision) {
    case OSL_PRECISION_SP:
      sprintf(string, OSL_FMT_TXT_SP, *(long int *)value);
      break;

    case OSL_PRECISION_DP:
      sprintf(string, OSL_FMT_TXT_DP, *(long long int *)value);
      break;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP: {
      char * str;
      str = mpz_get_str(0, 10, *(mpz_t *)value); //TODO: 10 -> #define
      sprintf(string, OSL_FMT_TXT_MP, str);
      free(str);
      break;
    }
#endif

    default:
      OSL_error("unknown precision");
  }
}


void osl_int_sread(char ** string, int precision,
                   void * value_base, int value_offset) {
  void * value = osl_int_address(precision, value_base, value_offset);
  int nb_read = 0;

  switch (precision) {
    case OSL_PRECISION_SP:
      nb_read = sscanf(*string, OSL_FMT_TXT_SP, (long int *)value);
      if (nb_read == 0)
        OSL_error("failed to read an integer");
      break;

    case OSL_PRECISION_DP:
      nb_read = sscanf(*string, OSL_FMT_TXT_DP, (long long int *)value);
      if (nb_read == 0)
        OSL_error("failed to read an integer");
      break;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP: {
      long long int tmp;
      nb_read = sscanf(*string, OSL_FMT_TXT_DP, &tmp);
      if (nb_read == 0)
        OSL_error("failed to read an integer");
      mpz_set_si(*(mpz_t *)value, tmp);
      break;
    }
#endif

    default:
      OSL_error("unknown precision");
  }

  // Update the position in the input string.
  *string = *string + nb_read;
}


/*+***************************************************************************
 *                            Arithmetic Operations                          *
 *****************************************************************************/


/**
 * result_base[result_offset] = value_base[value_offset] + 1;
 */
void osl_int_increment(int precision,
                       void * result_base, int result_offset,
                       void * value_base,  int value_offset) {
  void * result = osl_int_address(precision, result_base, result_offset);
  void * value  = osl_int_address(precision, value_base, value_offset);

  switch (precision) {
    case OSL_PRECISION_SP:
      *(long int *)result = *(long int *)value + (long int)1;
      break;

    case OSL_PRECISION_DP:
      *(long long int *)result = *(long long int *)value + (long long int)1;
      break;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      mpz_add_ui(*(mpz_t *)result, *(mpz_t *)value, 1);
      break;
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * result_base[result_offset] = value_base[value_offset] - 1;
 */
void osl_int_decrement(int precision,
                       void * result_base, int result_offset,
                       void * value_base,  int value_offset) {
  void * result = osl_int_address(precision, result_base, result_offset);
  void * value  = osl_int_address(precision, value_base, value_offset);

  switch (precision) {
    case OSL_PRECISION_SP:
      *(long int *)result = *(long int *)value - (long int)1;
      break;

    case OSL_PRECISION_DP:
      *(long long int *)result = *(long long int *)value - (long long int)1;
      break;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP: {
      mpz_t one;
      mpz_init_set_si(one, 1);
      mpz_sub(*(mpz_t *)result, *(mpz_t *)value, one);
      mpz_clear(one);
      break;
    }
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * result_base[result_offset] = val1_base[val1_offset]+val2_base[val2_offset];
 */
void osl_int_add(int precision,
                 void * result_base, int result_offset,
                 void * val1_base,   int val1_offset,
                 void * val2_base,   int val2_offset) {
  void * result = osl_int_address(precision, result_base, result_offset);
  void * val1   = osl_int_address(precision, val1_base, val1_offset);
  void * val2   = osl_int_address(precision, val2_base, val2_offset);

  switch (precision) {
    case OSL_PRECISION_SP:
      *(long int *)result = *(long int *)val1 + *(long int *)val2;
      break;

    case OSL_PRECISION_DP:
      *(long long int *)result = *(long long int *)val1 +
                                 *(long long int *)val2;
      break;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      mpz_add(*(mpz_t *)result, *(mpz_t *)val1, *(mpz_t *)val2);
      break;
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * result_base[result_offset] = value_base[value_offset] + i;
 */
void osl_int_add_si(int precision,
                    void * result_base, int result_offset,
                    void * value_base,  int value_offset, int i) {
  void * result = osl_int_address(precision, result_base, result_offset);
  void * value  = osl_int_address(precision, value_base, value_offset);

  switch (precision) {
    case OSL_PRECISION_SP:
      *(long int *)result = *(long int *)value + (long int)i;
      break;

    case OSL_PRECISION_DP:
      *(long long int *)result = *(long long int *)value + (long long int)i;
      break;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP: {
      mpz_t si;
      mpz_init_set_si(si, i);
      mpz_add(*(mpz_t *)result, *(mpz_t *)value, si);
      mpz_clear(si);
      break;
    }
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * result_base[result_offset] = val1_base[val1_offset]*val2_base[val2_offset];
 */
void osl_int_mul(int precision,
                 void * result_base, int result_offset,
                 void * val1_base,   int val1_offset,
                 void * val2_base,   int val2_offset) {
  void * result = osl_int_address(precision, result_base, result_offset);
  void * val1   = osl_int_address(precision, val1_base, val1_offset);
  void * val2   = osl_int_address(precision, val2_base, val2_offset);

  switch (precision) {
    case OSL_PRECISION_SP:
      *(long int *)result = *(long int *)val1 * *(long int *)val2;
      break;

    case OSL_PRECISION_DP:
      *(long long int *)result = *(long long int *)val1 *
                                 *(long long int *)val2;
      break;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      mpz_mul(*(mpz_t *)result, *(mpz_t *)val1, *(mpz_t *)val2);
      break;
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * result_base[result_offset] = value_base[value_offset] * i;
 */
void osl_int_mul_si(int precision,
                    void * result_base, int result_offset,
                    void * value_base,  int value_offset, int i) {
  void * result = osl_int_address(precision, result_base, result_offset);
  void * value  = osl_int_address(precision, value_base, value_offset);

  switch (precision) {
    case OSL_PRECISION_SP:
      *(long int *)result = *(long int *)value * (long int)i;
      break;

    case OSL_PRECISION_DP:
      *(long long int *)result = *(long long int *)value * (long long int)i;
      break;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      mpz_mul_si(*(mpz_t *)result, *(mpz_t *)value, i);
      break;
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * result_base[result_offset] = val1_base[val1_offset]-val2_base[val2_offset];
 */
void osl_int_sub(int precision,
                 void * result_base, int result_offset,
                 void * val1_base,   int val1_offset,
                 void * val2_base,   int val2_offset) {
  void * result = osl_int_address(precision, result_base, result_offset);
  void * val1   = osl_int_address(precision, val1_base, val1_offset);
  void * val2   = osl_int_address(precision, val2_base, val2_offset);

  switch (precision) {
    case OSL_PRECISION_SP:
      *(long int *)result = *(long int *)val1 - *(long int *)val2;
      break;

    case OSL_PRECISION_DP:
      *(long long int *)result = *(long long int *)val1 -
                                 *(long long int *)val2;
      break;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      mpz_sub(*(mpz_t *)result, *(mpz_t *)val1, *(mpz_t *)val2);
      break;
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * result_base[result_offset] = -value_base[value_offset];
 */
void osl_int_oppose(int precision,
                    void * result_base, int result_offset,
                    void * value_base,  int value_offset) {
  void * result = osl_int_address(precision, result_base, result_offset);
  void * value  = osl_int_address(precision, value_base, value_offset);

  switch (precision) {
    case OSL_PRECISION_SP:
      *(long int *)result = -*(long int *)value;
      break;

    case OSL_PRECISION_DP:
      *(long long int *)result = -*(long long int *)value;
      break;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      mpz_neg(*(mpz_t *)result, *(mpz_t *)value);
      break;
#endif

    default:
      OSL_error("unknown precision");
  }
}


/*+***************************************************************************
 *                            Conditional Operations                         *
 *****************************************************************************/


/**
 * (val1_base[val1_offset] == val2_base[val2_offset])
 */
int osl_int_eq(int precision,
               void * val1_base, int val1_offset,
               void * val2_base, int val2_offset) {
  void * val1 = osl_int_address(precision, val1_base, val1_offset);
  void * val2 = osl_int_address(precision, val2_base, val2_offset);

  switch (precision) {
    case OSL_PRECISION_SP:
      return (*(long int *)val1 == *(long int *)val2);

    case OSL_PRECISION_DP:
      return (*(long long int *)val1 == *(long long int *)val2);

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      return (mpz_cmp(*(mpz_t *)val1, *(mpz_t *)val2) == 0);
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * (val1_base[val1_offset] != val2_base[val2_offset])
 */
int osl_int_ne(int precision,
               void * val1_base, int val1_offset,
               void * val2_base, int val2_offset) {
  return !osl_int_eq(precision,
                          val1_base, val1_offset,
                          val2_base, val2_offset);
}


/**
 * (value_base[value_offset] > 0)
 */
int osl_int_pos(int precision, void * value_base, int value_offset) {
  void * value = osl_int_address(precision, value_base, value_offset);

  switch (precision) {
    case OSL_PRECISION_SP:
      return (*(long int *)value > 0);

    case OSL_PRECISION_DP:
      return (*(long long int *)value > 0);

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      return (mpz_sgn(*(mpz_t *)value) > 0);
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * (value_base[value_offset] < 0)
 */
int osl_int_neg(int precision, void * value_base, int value_offset) {
  void * value = osl_int_address(precision, value_base, value_offset);

  switch (precision) {
    case OSL_PRECISION_SP:
      return (*(long int *)value < 0);

    case OSL_PRECISION_DP:
      return (*(long long int *)value < 0);

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      return (mpz_sgn(*(mpz_t *)value) < 0);
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * (value_base[value_offset] == 0)
 */
int osl_int_zero(int precision, void * value_base, int value_offset) {
  void * value = osl_int_address(precision, value_base, value_offset);

  switch (precision) {
    case OSL_PRECISION_SP:
      return (*(long int *)value == 0);

    case OSL_PRECISION_DP:
      return (*(long long int *)value == 0);

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      return (mpz_sgn(*(mpz_t *)value) == 0);
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * (value_base[value_offset] == 1)
 */
int osl_int_one(int precision, void * value_base, int value_offset) {
  void * value = osl_int_address(precision, value_base, value_offset);

  switch (precision) {
    case OSL_PRECISION_SP:
      return (*(long int *)value == (long int)1);

    case OSL_PRECISION_DP:
      return (*(long long int *)value == (long long int)1);

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      return (mpz_cmp_si(*(mpz_t *)value, 1) == 0);
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * (value_base[value_offset] == -1)
 */
int osl_int_mone(int precision, void * value_base, int value_offset) {
  void * value = osl_int_address(precision, value_base, value_offset);

  switch (precision) {
    case OSL_PRECISION_SP:
      return (*(long int *)value == (long int)-1);

    case OSL_PRECISION_DP:
      return (*(long long int *)value == (long long int)-1);

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      return (mpz_cmp_si(*(mpz_t *)value, -1) == 0);
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * ((val1_base[val1_offset] % val2_base[val2_offset]) == 0)
 */
int osl_int_divisible(int precision,
                      void * val1_base, int val1_offset,
                      void * val2_base, int val2_offset) {
  void * val1 = osl_int_address(precision, val1_base, val1_offset);
  void * val2 = osl_int_address(precision, val2_base, val2_offset);

  switch (precision) {
    case OSL_PRECISION_SP:
      return ((*(long int *)val1 % *(long int *)val2) == 0);

    case OSL_PRECISION_DP:
      return ((*(long long int *)val1 % *(long long int *)val2) == 0);

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      return mpz_divisible_p(*(mpz_t *)val1, *(mpz_t *)val2);
#endif

    default:
      OSL_error("unknown precision");
  }
}
