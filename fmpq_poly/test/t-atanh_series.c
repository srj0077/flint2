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

    Copyright (C) 2009 William Hart
    Copyright (C) 2010 Sebastian Pancratz
    Copyright (C) 2011 Fredrik Johansson

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpq_poly.h"
#include "fmpq_poly.h"
#include "ulong_extras.h"

int
main(void)
{
    int i, result;
    flint_rand_t state;
    ulong cflags = UWORD(0);

    flint_printf("atanh_series....");
    fflush(stdout);

    flint_randinit(state);

    /* Check aliasing of a and c */
    for (i = 0; i < 20 * flint_test_multiplier(); i++)
    {
        fmpq_poly_t a, b;
        slong n = n_randint(state, 50) + 1;

        fmpq_poly_init(a);
        fmpq_poly_init(b);

        fmpq_poly_randtest_not_zero(a, state, n_randint(state, 50) + 1, 50);
        fmpq_poly_set_coeff_ui(a, 0, UWORD(0));

        fmpq_poly_canonicalise(a);

        fmpq_poly_atanh_series(b, a, n);
        fmpq_poly_atanh_series(a, a, n);

        cflags |= fmpq_poly_is_canonical(a) ? 0 : 1;
        cflags |= fmpq_poly_is_canonical(b) ? 0 : 2;
        result = (fmpq_poly_equal(a, b) && !cflags);
        if (!result)
        {
            flint_printf("FAIL:\n");
            fmpq_poly_debug(a), flint_printf("\n\n");
            fmpq_poly_debug(b), flint_printf("\n\n");
            flint_printf("cflags = %wu\n\n", cflags);
            abort();
        }

        fmpq_poly_clear(a);
        fmpq_poly_clear(b);
    }

    /* Check 2*atanh(A) = atanh(2*A/(1+A^2)) */
    for (i = 0; i < 20 * flint_test_multiplier(); i++)
    {
        fmpq_poly_t A, B, atanhA, atanhB;
        slong n = n_randint(state, 80) + 1;

        fmpq_poly_init(A);
        fmpq_poly_init(B);
        fmpq_poly_init(atanhA);
        fmpq_poly_init(atanhB);

        fmpq_poly_randtest_not_zero(A, state, n_randint(state, 80) + 1, 80);
        fmpq_poly_set_coeff_ui(A, 0, UWORD(0));

        fmpq_poly_randtest_not_zero(B, state, n_randint(state, 80) + 1, 80);
        fmpq_poly_set_coeff_ui(B, 0, UWORD(0));

        fmpq_poly_mullow(B, A, A, n);
        fmpq_poly_set_coeff_ui(B, 0, UWORD(1));
        fmpq_poly_div_series(B, A, B, n);
        fmpq_poly_add(B, B, B);

        fmpq_poly_atanh_series(atanhA, A, n);
        fmpq_poly_atanh_series(atanhB, B, n);
        fmpq_poly_add(atanhA, atanhA, atanhA);

        cflags |= fmpq_poly_is_canonical(atanhA) ? 0 : 1;
        cflags |= fmpq_poly_is_canonical(atanhB) ? 0 : 2;
        result = (fmpq_poly_equal(atanhA, atanhB) && !cflags);
        if (!result)
        {
            flint_printf("FAIL:\n");
            flint_printf("A = "), fmpq_poly_debug(A), flint_printf("\n\n");
            flint_printf("B = "), fmpq_poly_debug(B), flint_printf("\n\n");
            flint_printf("2*atanh(A) = "), fmpq_poly_debug(atanhA), flint_printf("\n\n");
            flint_printf("atanh(B) = "), fmpq_poly_debug(atanhB), flint_printf("\n\n");
            flint_printf("cflags = %wu\n\n", cflags);
            abort();
        }

        fmpq_poly_clear(A);
        fmpq_poly_clear(B);
        fmpq_poly_clear(atanhA);
        fmpq_poly_clear(atanhB);
    }

    flint_randclear(state);
    flint_cleanup();
    flint_printf("PASS\n");
    return 0;
}
