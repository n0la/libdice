%parse-param {dice_t dice}

%{
#include "dice.h"

extern int yylex(void);

void yyerror(dice_t dice, char const *err)
{
}

int yywrap(void)
{
    return 1;
}
%}

%union {
    char *str;
    int integer;
    double number;
}

%token TOK_DICESEP
%token  <integer>           TOK_INTEGER

%%

dice:           TOK_INTEGER TOK_DICESEP TOK_INTEGER
                {
                    dice_set(dice, DICEOPTION_AMOUNT, $1);
                    dice_set(dice, DICEOPTION_SIDES, $3);
                }
        |       TOK_DICESEP TOK_INTEGER
                {
                    dice_set(dice, DICEOPTION_AMOUNT, 1);
                    dice_set(dice, DICEOPTION_SIDES, $2);
                }
        ;
