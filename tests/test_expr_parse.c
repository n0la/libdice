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

static void test_expr_parse_none(void **arg)
{
    dice_expression_t e = NULL;
    int error = 0;

    e = dice_expression_parse("", &error);

    assert_null(e);
    assert_int_equal(error, 1);
}

static void test_expr_parse_simple(void **arg)
{
    dice_expression_t e = NULL;
    int error = 0, i = 0;
    int64_t result = 0;

    e = dice_expression_parse("4d6", &error);

    assert_non_null(e);
    assert_int_equal(error, 0);

    for (i = 0; i < 100000; i++) {
        assert_true(dice_expression_evaluate(e, &result));
        assert_true(result >= 4 && result <= 32);
    }

    dice_expression_free(e);
}

static void test_expr_parse_modifier(void **arg)
{
    dice_expression_t e = NULL;
    int error = 0, i = 0;
    int64_t result = 0;

    e = dice_expression_parse("1d20+3+5", &error);

    assert_non_null(e);
    assert_int_equal(error, 0);

    for (i = 0; i < 100000; i++) {
        assert_true(dice_expression_evaluate(e, &result));
        assert_true(result >= 9 && result <= 28);
    }

    dice_expression_free(e);
}

static void test_expr_parse_complex(void **arg)
{
    dice_expression_t e = NULL;
    int error = 0, i = 0;
    int64_t result = 0;

    e = dice_expression_parse("1d8+(3+5)+1d6+5d4", &error);

    assert_non_null(e);
    assert_int_equal(error, 0);

    for (i = 0; i < 100000; i++) {
        assert_true(dice_expression_evaluate(e, &result));
        assert_true(result >= 15 && result <= 42);
    }

    dice_expression_free(e);
}


int main(int ac, char **av)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_expr_parse_none),
        cmocka_unit_test(test_expr_parse_simple),
        cmocka_unit_test(test_expr_parse_modifier),
        cmocka_unit_test(test_expr_parse_complex),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
