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

#ifndef LIBDICE_DICE_H
#define LIBDICE_DICE_H

#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>

struct dice_;
typedef struct dice_ * dice_t;

struct dice_expression_;
typedef struct dice_expression_ * dice_expression_t;

typedef struct {
    int64_t result;
} dice_result_t;

typedef enum {
    /* The amount of dice to roll.
     * get: uint32_t
     * set: uint32_t *
     */
    DICEOPTION_AMOUNT = 0,

    /* The sides the dice have.
     * get: uint32_t
     * set: uint32_t *
     */
    DICEOPTION_SIDES,

    /* The error that as occoured when parsing dice strings.
     * get: char **
     * set: char const *
     */
    DICEOPTION_ERROR,
} dice_option_t;

/* Creates a new dice object that is not initialised yet.
 * You need to call dice_parse(), dice_set() to initialise
 * it properly.
 */
dice_t dice_new(void);

/* Frees a previously allocated dice object. The object should
 * no longer be used after it has been freed.
 */
void dice_free(dice_t t);

/* Creates a new dice object, and initialises amount and sides
 * with the given parameters. It is a convenience function to
 * avoid calling dice_new() and then dice_set().
 */
dice_t dice_simple(uint32_t amount, uint32_t sides);

/* Parses the given string and stores the results of the parse
 * in the given dice object (which must be allocated by using
 * dice_new()). The string of the dice is given by the parameter
 * s. It must be null terminated.
 * The function returns true if the parsing was sucessful, and
 * false otherwise.
 */
bool dice_parse(dice_t d, char const *s);

/* Allows to set various options to the dice object. The stdarg
 * parameter depends on the option being set. See the enum definitions
 * for additional details.
 * The function returns true if it succeeds, and false if it fails.
 */
bool dice_set(dice_t d, dice_option_t opt, ...);

/* Allows you to retrieve options from the dice object. The stdarg
 * parameter depends on the optional being retrieved. See the enum
 * definitions for further details.
 * The function returns true if it succeeds, and false if it fails.
 */
bool dice_get(dice_t d, dice_option_t opt, ...);

/* Rolls the given dice object once, and returns the result.
 */
int64_t dice_roll(dice_t d);

/* Rolls the given dice object once, and returns the result as an
 * array of results. Often dice_roll() is sufficient, unless you
 * wish to know each exact result of the dice. The result should
 * be freed by using dice_result_freev().
 */
bool dice_evaluate(dice_t d, dice_result_t **res, size_t *reslen);

/* Frees one dice result.
 */
void dice_result_free(dice_result_t *r);

/* Fress an array of dice results. As returned by dice_evaluate.
 */
void dice_result_freev(dice_result_t *r, size_t len);

/* Allocates a new empty dice expression object. It should be freed
 * by calling dice_expression_free(), and can be used on other functions
 * such as dice_expression_parse() and dice_expression_roll().
 */
dice_expression_t dice_expression_new(void);

/* Frees one dice expression object and all its associated data. Do
 * not use the object after freeing it.
 */
void dice_expression_free(dice_expression_t e);

/* Evaluate a string containing dice expression, and store it in the given
 * dice object that was provided. If an error occours the function will return
 * false, and will store an offset (in the string) in error, if the pointer
 * is non-NULL.
 */
bool dice_expression_parse(dice_expression_t d, char const *s, int *error);

/* Evaluates the previously parsed dice expression and returns the result.
 * The function returns false if it fails, and true if it succeeds.
 */
bool dice_expression_roll(dice_expression_t e, int64_t *result);

#endif
