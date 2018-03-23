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

static void test_dice_fudge_construct(void **data)
{
    dice_t d = dice_new();
    bool fudge = true;

    dice_get(d, DICEOPTION_FUDGE, &fudge);
    assert_false(fudge);

    dice_free(d);
}

static void test_dice_fudge_set(void **data)
{
    dice_t d = dice_new();
    bool fudge = false;

    dice_set(d, DICEOPTION_FUDGE, true);
    dice_get(d, DICEOPTION_FUDGE, &fudge);

    assert_true(fudge);
    dice_free(d);
}

static void test_dice_fudge_roll_one(void **data)
{
    dice_t d = dice_new();
    int result = 0, i = 0;

    dice_set(d, DICEOPTION_FUDGE, true);
    dice_set(d, DICEOPTION_AMOUNT, 1L);

    for (i = 0; i < 100000; i++) {
        result = dice_roll(d);
        assert_true(result >= -1 && result <= 1);
    }

    dice_free(d);
}

static void test_dice_fudge_roll_more(void **data)
{
    dice_t d = dice_new();
    int result = 0, i = 0;

    dice_set(d, DICEOPTION_FUDGE, true);
    dice_set(d, DICEOPTION_AMOUNT, 6L);

    for (i = 0; i < 100000; i++) {
        result = dice_roll(d);
        assert_true(result >= -6 && result <= 6);
    }

    dice_free(d);
}

static void test_dice_fudge_parse1(void **data)
{
    dice_t d = dice_new();
    int amount = 0, fudge = false;

    assert_true(dice_parse(d, "4dF"));

    dice_get(d, DICEOPTION_AMOUNT, &amount);
    dice_get(d, DICEOPTION_FUDGE, &fudge);

    assert_int_equal(amount, 4);
    assert_true(fudge);

    dice_free(d);
}

static void test_dice_fudge_parse2(void **data)
{
    dice_t d = dice_new();
    int amount = 0, fudge = false;

    assert_true(dice_parse(d, "df"));

    dice_get(d, DICEOPTION_AMOUNT, &amount);
    dice_get(d, DICEOPTION_FUDGE, &fudge);

    assert_int_equal(amount, 1);
    assert_true(fudge);

    dice_free(d);
}

int main(int ac, char **av)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_dice_fudge_construct),
        cmocka_unit_test(test_dice_fudge_set),
        cmocka_unit_test(test_dice_fudge_roll_one),
        cmocka_unit_test(test_dice_fudge_roll_more),
        cmocka_unit_test(test_dice_fudge_parse1),
        cmocka_unit_test(test_dice_fudge_parse2),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
