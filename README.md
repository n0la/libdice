[![Build Status](https://travis-ci.org/n0la/libdice.svg?branch=master)](https://travis-ci.org/n0la/libdice)

# libdice

``libdice`` is a small C library for rolling P&P style dice and for
evaluating dice expressions.

## Features

* Written in ANSI C99
* Uses solid and reliable RNG, no need for seeding
* Mathematic expression library for advanced dice rolling

## Dice syntax

Currently the supported syntax in ``libdice`` is rather limited. It only
supports variable amount, variable sides and fudge dice at the moment:

* Roll four six sided dices: ``4d6``
* Roll one twenty sided die: ``d20``
* Roll six fudge dice: ``6dF``

## Build

``libdice`` requires:

* libbsd (on systems without a native ``arc4random_uniform``)
* bison
* flex
* cmocka >= 1.0.1
* cmake

To build ``libdice`` run:

```shell
$ mkdir build; cd build
$ cmake .. -DCMAKE_INSTALL_PREFIX=/usr
$ make
$ make test
$ sudo make install
```

## Dice API

The core api relies on ``dice_new`` which creates a new dice (or a set of dice),
which is then freed by ``dice_free``. Dice can be initialised through the proper
``dice_set`` function, or by using either ``dice_simple`` or ``dice_parse``:

```C
#include <dice.h>

dice_t d = dice_new();

dice_set(d, DICEOPTION_AMOUNT, 4);
dice_set(d, DICEOPTION_SIDES, 6);

/* or simpler:
 * d = dice_simple(4, 6);
 */


printf("%ld\n", dice_roll(d));
dice_free(d);
```

There is also an easier API:

```C
dice_t d20 = dice_simple(1, 20);

printf("%ld\n", dice_roll(d20));
dice_free(d20);
```

And a more advanced API:

```C
dice_t d = dice_simple(4, 6);
dice_result_t *res = NULL;
size_t reslen = 0, i = 0;

if (!dice_evaluate(d, &res, &reslen)) {
    goto fail;
}

for (; i < reslen; i++) {
    printf("%ld\n", res[i].result);
}

fail:
dice_result_freev(res, reslen);
dice_free(d);
```

You can also parse dice strings:

```C
dice_t d20 = dice_new();

if (!dice_parse(d20, "5d20")) {
   char const *err = NULL;
   dice_get(d20, DICEOPTION_ERROR, &err);
   fprintf(stderr, "error: %s\n", err);
}

printf("%ld\n", dice_roll(d20));
dice_free(d20);
```

## Expression API

The expression API supports multiple die within one mathematical expression.
Expressions are parsed using [tinyexpr](https://github.com/codeplea/tinyexpr)
library. The API works with objects of the type ``dice_expression_t``, which
are allocated using ``dice_expression_new``, and must be freed by using
``dice_expression_free``. Expressions in the format of a C string, can be
parsed by using ``dice_expression_parse``, and a result can be evaluated
by using ``dice_expression_roll``.

```C
int error = 0;
char const *expr = "1d20+8+4+3-1";
dice_expression_t e = dice_expression_new();
int64_t result = 0;

if (!dice_expression_parse(e, expr, &err)) {
    fprintf(stderr, "error in expression: \"%s\": at %d\n", expr, err);
    goto fail;
}

if (!dice_expression_roll(e, &result)) {
    goto fail;
}

printf("%ld\n", result);

fail:
dice_expression_free(e);
```

## Copyright

``libdice`` is dual licenced. The ``tinyexpr`` is licenced under the zlib
licence (see ``LICENSE.tinyexpr``), and the rest of ``libdice`` is available
under the LGPLv3.

``tinyexpr`` Copyright (C) 2015, 2016 Lewis Van Winkle

``libdice`` Copyright (C) 2018 Florian Stinglmayr
