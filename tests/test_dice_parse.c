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
    dice_t d = dice_parse("");
    assert_null(d);
}

static void test_dice_parse_amount(void **data)
{
    dice_t d = dice_parse("3d");
    assert_null(d);
}

static void test_dice_parse_amount_sides(void **data)
{
    dice_t d = dice_parse("5d10");
    int i = 0;

    assert_non_null(d);

    assert_true(dice_get(d, DICEOPTION_AMOUNT, &i));
    assert_int_equal(i, 5);

    assert_true(dice_get(d, DICEOPTION_SIDES, &i));
    assert_int_equal(i, 10);

    assert_int_equal(dice_consumed(d), 4);

    dice_free(d);
}

static void test_dice_parse_sides(void **data)
{
    dice_t d = dice_parse("d12");
    int i = 0;

    assert_non_null(d);

    assert_true(dice_get(d, DICEOPTION_SIDES, &i));
    assert_int_equal(i, 12);

    assert_int_equal(dice_consumed(d), 3);

    dice_free(d);
}

static void test_dice_parse_big(void **data)
{
    char const *dice_str = "1000d120000";
    dice_t d = dice_parse(dice_str);
    int i = 0;

    assert_non_null(d);

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
