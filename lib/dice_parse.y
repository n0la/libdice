%define api.pure full

%parse-param {void *scanner} {dice_t dice}
%lex-param {void *scanner}

%{
#include "dice.h"

extern int yylex(void *lval, void *scanner);

void yyerror(void *scanner, dice_t dice, char const *err)
{
    dice_set(dice, DICEOPTION_ERROR, err);
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

%token TOK_DICESEP TOK_FUDGE
%token  <integer>           TOK_INTEGER

%%

dice:           TOK_INTEGER TOK_DICESEP TOK_INTEGER
                {
                    dice_set(dice, DICEOPTION_AMOUNT, $1);
                    dice_set(dice, DICEOPTION_SIDES, $3);

                    YYACCEPT;
                }
        |       TOK_DICESEP TOK_INTEGER
                {
                    dice_set(dice, DICEOPTION_AMOUNT, 1);
                    dice_set(dice, DICEOPTION_SIDES, $2);

                    YYACCEPT;
                }
        |       TOK_DICESEP TOK_FUDGE
                {
                    dice_set(dice, DICEOPTION_AMOUNT, 1L);
                    dice_set(dice, DICEOPTION_FUDGE, 1L);

                    YYACCEPT;
                }
        |       TOK_INTEGER TOK_DICESEP TOK_FUDGE
                {
                    dice_set(dice, DICEOPTION_AMOUNT, $1);
                    dice_set(dice, DICEOPTION_FUDGE, 1L);

                    YYACCEPT;
                }
        ;
