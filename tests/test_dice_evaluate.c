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
