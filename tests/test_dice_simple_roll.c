#include <dice.h>

#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void test_dice_simple_null(void **data)
{
    dice_t d = dice_simple(0, 0);
    assert_null(d);
}

static void test_dice_simple_one(void **data)
{
    dice_t d = dice_simple(1, 20);
    assert_non_null(d);
    dice_free(d);
}

static void test_dice_simple_roll(void **data)
{
    dice_t d = dice_simple(1, 20);
    int i = 0;

    assert_non_null(d);

    for (i = 0; i < 100000; i++) {
        int64_t res = dice_roll(d);
        assert_true(res >= 1 && res <= 20);
    }

    dice_free(d);
}

static void test_dice_simple_multi(void **data)
{
    dice_t d = dice_simple(3, 6);
    int i = 0;

    assert_non_null(d);

    for (i = 0; i < 100000; i++) {
        int64_t res = dice_roll(d);
        assert_true(res >= 3 && res <= 18);
    }

    dice_free(d);
}

static void test_dice_simple_get(void **data)
{
    dice_t d = dice_simple(8, 10);
    int i = 0;

    assert_non_null(d);

    assert_true(dice_get(d, DICEOPTION_AMOUNT, &i));
    assert_int_equal(i, 8);

    assert_true(dice_get(d, DICEOPTION_SIDES, &i));
    assert_int_equal(i, 10);

    dice_free(d);
}

static void test_dice_simple_set(void **data)
{
    dice_t d = dice_simple(1, 20);
    int i = 0;

    assert_non_null(d);

    assert_true(dice_set(d, DICEOPTION_AMOUNT, 20));
    assert_true(dice_set(d, DICEOPTION_SIDES, 4));

    assert_true(dice_get(d, DICEOPTION_AMOUNT, &i));
    assert_int_equal(i, 20);

    assert_true(dice_get(d, DICEOPTION_SIDES, &i));
    assert_int_equal(i, 4);

    dice_free(d);
}

static void test_dice_simple_invalid_getset(void **data)
{
    dice_t d = dice_simple(1, 20);
    int i = 0;

    assert_non_null(d);

    assert_false(dice_set(d, 9001, 20));
    assert_false(dice_get(d, 9001, &i));

    dice_free(d);
}

int main(int ac, char **av)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_dice_simple_null),
        cmocka_unit_test(test_dice_simple_one),
        cmocka_unit_test(test_dice_simple_roll),
        cmocka_unit_test(test_dice_simple_multi),
        cmocka_unit_test(test_dice_simple_set),
        cmocka_unit_test(test_dice_simple_get),
        cmocka_unit_test(test_dice_simple_invalid_getset),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
