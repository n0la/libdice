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

/* private library function
 */
int dice_consumed(dice_t d);

static void test_dice_parse_none(void **data)
{
    dice_t d = dice_new();

    assert_false(dice_parse(d, ""));
    dice_free(d);
}

static void test_dice_parse_amount(void **data)
{
    dice_t d = dice_new();

    assert_false(dice_parse(d, "3d"));
    dice_free(d);
}

static void test_dice_parse_amount_sides(void **data)
{
    dice_t d = dice_new();
    int i = 0;

    assert_true(dice_parse(d, "5d10"));

    assert_true(dice_get(d, DICEOPTION_AMOUNT, &i));
    assert_int_equal(i, 5);

    assert_true(dice_get(d, DICEOPTION_SIDES, &i));
    assert_int_equal(i, 10);

    assert_int_equal(dice_consumed(d), 4);

    dice_free(d);
}

static void test_dice_parse_sides(void **data)
{
    dice_t d = dice_new();
    int i = 0;

    assert_true(dice_parse(d, "d12"));

    assert_true(dice_get(d, DICEOPTION_SIDES, &i));
    assert_int_equal(i, 12);

    assert_int_equal(dice_consumed(d), 3);

    dice_free(d);
}

static void test_dice_parse_big(void **data)
{
    char const *dice_str = "1000d120000";
    dice_t d = dice_new();
    int i = 0;

    assert_true(dice_parse(d, dice_str));

    assert_true(dice_get(d, DICEOPTION_SIDES, &i));
    assert_int_equal(i, 120000);

    assert_true(dice_get(d, DICEOPTION_AMOUNT, &i));
    assert_int_equal(i, 1000);

    assert_int_equal(dice_consumed(d), strlen(dice_str));

    dice_free(d);
}

int main(int ac, char **av)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_dice_parse_none),
        cmocka_unit_test(test_dice_parse_amount),
        cmocka_unit_test(test_dice_parse_amount_sides),
        cmocka_unit_test(test_dice_parse_sides),
        cmocka_unit_test(test_dice_parse_big),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
