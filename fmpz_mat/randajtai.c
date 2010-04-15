/*============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

===============================================================================*/
/****************************************************************************

   Copyright (C) 2005-2009 Damien Stehle.
   Copyright (C) 2007 David Cade.
   Copyright (C) 2010 William Hart
   
*****************************************************************************/

#include <stdlib.h>
#include <mpir.h>
#include <math.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_mat.h"
#include "ulong_extras.h"

void fmpz_mat_randajtai(fmpz_mat_t mat, double alpha)
{
   ulong r, c, i, j, d, bits;
   fmpz_t tmp;

   r = mat->r;
   c = mat->c;
   d = r;

   if (c != r)
   {
	  printf("Exception: fmpz_mat_ajtai called on an ill-formed matrix\n");
      abort();
   }
   
   fmpz_init(tmp);
   
   for (i = 0; i < d; i++)
   {
      bits = (ulong) pow((double) (2*d - i), alpha);
	  
	  fmpz_set_ui(tmp, 1);
	  fmpz_mul_2exp(tmp, tmp, bits); 
	  fmpz_sub_ui(tmp, tmp, 1);
	  fmpz_randm(mat->rows[i] + i, tmp);
	  fmpz_add_ui(mat->rows[i] + i, mat->rows[i] + i, 2);
	  fmpz_fdiv_q_2exp(mat->rows[i] + i, mat->rows[i] + i, 1);

	  for (j = i + 1; j <= d; j++)
	  { 
	     fmpz_randm(mat->rows[j] + i, tmp);
		 if (n_randint(2))
		    fmpz_neg(mat->rows[j] + i, mat->rows[j] + i);
		 fmpz_zero(mat->rows[i] + j);
	  }
   }

   fmpz_clear(tmp);
}

