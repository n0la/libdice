#include "dice.h"
#include "dice_parse.h"

#include <stdlib.h>
#include <string.h>

#ifndef HAVE_ARC4RANDOM_UNIFORM
#include <bsd/stdlib.h>
#endif

extern void *yy_scan_string(char const *s);
extern void yy_delete_buffer(void *b);

struct dice_
{
    uint32_t amount;
    uint32_t sides;

    char *errmsg;
};

static dice_t dice_new(void)
{
    dice_t tmp = calloc(1, sizeof(struct dice_));

    if (tmp == NULL) {
        return NULL;
    }

    return tmp;
}

void dice_free(dice_t t)
{
    if (t == NULL) {
        return;
    }

    free(t);
}

void dice_result_free(dice_result_t *r)
{
    if (r == NULL) {
        return;
    }

    free(r);
}

void dice_result_freev(dice_result_t *r, size_t len)
{
    if (r == NULL || len == 0) {
        return;
    }

    free(r);
}

dice_t dice_simple(uint32_t amount, uint32_t sides)
{
    dice_t tmp = dice_new();

    if (amount == 0 || sides == 0) {
        return NULL;
    }

    if (tmp == NULL) {
        return NULL;
    }

    tmp->amount = amount;
    tmp->sides = sides;

    return tmp;
}

dice_t dice_parse(char const *s)
{
    dice_t d = NULL;
    void *buffer = NULL;
    int ret = 0;

    d = dice_new();
    if (d == NULL) {
        return NULL;
    }

    buffer = yy_scan_string(s);
    ret = yyparse(d);
    yy_delete_buffer(buffer);

    if (ret) {
        dice_free(d);
        return NULL;
    }

    return d;
}

bool dice_set(dice_t d, dice_option_t opt, ...)
{
    va_list lst;

    va_start(lst, opt);
    switch (opt) {
    case DICEOPTION_AMOUNT: d->amount = va_arg(lst, uint32_t); break;
    case DICEOPTION_SIDES: d->sides = va_arg(lst, uint32_t); break;

    default: return false;
    }
    va_end(lst);

    return true;
}

bool dice_get(dice_t d, dice_option_t opt, ...)
{
    va_list lst;

    va_start(lst, opt);
    switch (opt) {
    case DICEOPTION_AMOUNT:
    {
        uint32_t *ptr = va_arg(lst, uint32_t*);
        *ptr = d->amount;
    } break;

    case DICEOPTION_SIDES:
    {
        uint32_t *ptr = va_arg(lst, uint32_t*);
        *ptr = d->sides;
    } break;

    default: return false;
    }
    va_end(lst);

    return true;
}

int64_t dice_roll(dice_t d)
{
    int64_t result = 0;
    uint32_t i = 0;

    for (i = 0; i < d->amount; i++) {
        result += arc4random_uniform(d->sides) + 1;
    }

    return result;
}

bool dice_evaluate(dice_t d, dice_result_t **res, size_t *reslen)
{
    size_t len = 0;
    dice_result_t *r = NULL;
    uint32_t i = 0;

    if (d == NULL || d->amount <= 0 || d->sides <= 0) {
        return false;
    }

    len = d->amount;
    r = calloc(len, sizeof(dice_result_t));
    if (r == NULL) {
        return NULL;
    }

    for (i = 0; i < d->amount; i++) {
        r[i].result = arc4random_uniform(d->sides) + 1;
    }

    *reslen = len;
    *res = r;

    return true;
}
