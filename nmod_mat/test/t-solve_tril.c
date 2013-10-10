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

    Copyright (C) 2010,2011 Fredrik Johansson

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <gmp.h>
#include "flint.h"
#include "nmod_mat.h"
#include "ulong_extras.h"

int
main(void)
{
    slong i;
    flint_rand_t state;
    flint_randinit(state);

    flint_printf("solve_tril....");
    fflush(stdout);

    for (i = 0; i < 10 * flint_test_multiplier(); i++)
    {
        nmod_mat_t A, X, B, Y;
        mp_limb_t m;
        slong rows, cols;
        int unit;

        m = n_randtest_prime(state, 0);
        rows = n_randint(state, 200);
        cols = n_randint(state, 200);
        unit = n_randint(state, 2);

        nmod_mat_init(A, rows, rows, m);
        nmod_mat_init(B, rows, cols, m);
        nmod_mat_init(X, rows, cols, m);
        nmod_mat_init(Y, rows, cols, m);

        nmod_mat_randtril(A, state, unit);
        nmod_mat_randtest(X, state);
        nmod_mat_mul(B, A, X);

        /* Check Y = A^(-1) * (A * X) = X */
        nmod_mat_solve_tril(Y, A, B, unit);
        if (!nmod_mat_equal(Y, X))
        {
            flint_printf("FAIL!\n");
            flint_printf("A:\n");
            nmod_mat_print_pretty(A);
            flint_printf("X:\n");
            nmod_mat_print_pretty(X);
            flint_printf("B:\n");
            nmod_mat_print_pretty(B);
            flint_printf("Y:\n");
            nmod_mat_print_pretty(Y);
            abort();
        }

        /* Check aliasing */
        nmod_mat_solve_tril(B, A, B, unit);
        if (!nmod_mat_equal(B, X))
        {
            flint_printf("FAIL!\n");
            flint_printf("aliasing test failed");
            flint_printf("A:\n");
            nmod_mat_print_pretty(A);
            flint_printf("B:\n");
            nmod_mat_print_pretty(B);
            abort();
        }

        nmod_mat_clear(A);
        nmod_mat_clear(B);
        nmod_mat_clear(X);
        nmod_mat_clear(Y);
    }

    flint_randclear(state);

    flint_printf("PASS\n");
    return 0;
}
