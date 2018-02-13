#ifndef LIBDICE_DICE_H
#define LIBDICE_DICE_H

#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>

struct dice_;
typedef struct dice_ * dice_t;

typedef struct {
    int64_t result;
} dice_result_t;

typedef enum {
    DICEOPTION_AMOUNT = 0,
    DICEOPTION_SIDES,
} dice_option_t;

void dice_result_free(dice_result_t *r);
void dice_result_freev(dice_result_t *r, size_t len);

void dice_free(dice_t t);
dice_t dice_simple(uint32_t amount, uint32_t sides);
dice_t dice_parse(char const *s);

bool dice_set(dice_t d, dice_option_t opt, ...);
bool dice_get(dice_t d, dice_option_t opt, ...);

int64_t dice_roll(dice_t d);
bool dice_evaluate(dice_t d, dice_result_t **res, size_t *reslen);

#endif
