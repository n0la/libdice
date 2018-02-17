/*
 * This file is part of libdice.
 *
 * Copyright (C) 2018 Florian Stinglmayr <florian@n0la.org>
 *
 * libdice is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * libdice is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libdice.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <dice.h>

#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void test_dice_evaluate_null(void **data)
{
    dice_t d = NULL;
    dice_result_t *r = NULL;
    size_t rlen = 0;

    assert_false(dice_evaluate(d, &r, &rlen));
}

static void test_dice_evaluate_one(void **data)
{
    dice_t d = NULL;
    dice_result_t *r = NULL;
    size_t rlen = 0;

    d = dice_simple(1, 10);

    assert_non_null(d);
    assert_true(dice_evaluate(d, &r, &rlen));
    assert_non_null(r);

    assert_int_equal(rlen, 1);
    assert_true(r[0].result >= 1 && r[0].result <= 10);

    dice_free(d);
    dice_result_freev(r, rlen);
}

static void test_dice_evaluate_many(void **data)
{
    dice_t d = NULL;
    dice_result_t *r = NULL;
    size_t rlen = 0;
    const int amount = 150;
    int i = 0;

    /* your average evening playing Shadowrun...
     */
    d = dice_simple(amount, 6);

    assert_non_null(d);
    assert_true(dice_evaluate(d, &r, &rlen));
    assert_non_null(r);

    assert_int_equal(rlen, amount);

    for (i = 0; i < amount; i++) {
        assert_true(r[i].result >= 1 && r[i].result <= 6);
    }

    dice_free(d);
    dice_result_freev(r, rlen);
}

int main(int ac, char **av)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_dice_evaluate_null),
        cmocka_unit_test(test_dice_evaluate_one),
        cmocka_unit_test(test_dice_evaluate_many),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
