/*=============================================================================

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

=============================================================================*/
/******************************************************************************

    Copyright (C) 2011 Fredrik Johansson

******************************************************************************/

#include <stdlib.h>
#include "flint.h"
#include "nmod_poly.h"
#include "nmod_poly_mat.h"

void
nmod_poly_mat_print(const nmod_poly_mat_t A, const char * x)
{
    len_t i, j;

    printf("<%ld x %ld matrix over Z/nZ[%s]>\n", A->r, A->c, x);

    for (i = 0; i < A->r; i++)
    {
        printf("[");
        for (j = 0; j < A->c; j++)
        {
            /* TODO: pretty */
            nmod_poly_print(nmod_poly_mat_entry(A, i, j));
            if (j + 1 < A->c)
                printf(", ");
        }
        printf("]\n");
    }
    printf("\n");
}
