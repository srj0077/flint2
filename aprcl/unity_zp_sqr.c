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

    Copyright (C) 2015 Vladimir Glazachev
   
******************************************************************************/

#include "aprcl.h"

void
unity_zp_sqr(unity_zp f, const unity_zp g)
{
    ulong i, p;

    fmpz_mod_poly_sqr(f->poly, g->poly);
    if (f->poly->length == 0)
        return;

    p = n_pow(f->p, f->exp);
    for (i = f->poly->length - 1; i >= p; i--)
    {
        fmpz_add(f->poly->coeffs + i - p,
                f->poly->coeffs + i - p, f->poly->coeffs + i);

        fmpz_set_ui(f->poly->coeffs + i, 0);
        if (fmpz_cmp(f->poly->coeffs + i - p, f->n) >= 0)
            fmpz_sub(f->poly->coeffs + i - p, f->poly->coeffs + i - p, f->n);
    }
    _unity_zp_reduce_cyclotomic(f);
}

void
unity_zp_sqr_inplace(unity_zp f, const unity_zp g, fmpz_t * t)
{
    if (f->p == 5 && f->exp == 1)
        unity_zp_sqr5(f, g, t);
    if (f->p == 7 && f->exp == 1)
        unity_zp_sqr7(f, g, t);
    else
        unity_zp_sqr(f, g);      
}

