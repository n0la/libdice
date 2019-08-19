%option bison-bridge
%option reentrant

%{
#define YYSTYPE DPSTYPE
#include "dice.h"
#include "dice_parse.h"

extern void dice_update_consumed(dice_t d, int off);

%}

%%
[0-9]+ {
    dice_t d = yyget_extra(yyscanner);
    dice_update_consumed(d, yyleng);
    yylval->integer = atoi(yytext);
    return TOK_INTEGER;
}

[d] {
    dice_t d = yyget_extra(yyscanner);
    dice_update_consumed(d, yyleng);
    return TOK_DICESEP;
}

[fF] {
    dice_t d = yyget_extra(yyscanner);
    dice_update_consumed(d, yyleng);
    return TOK_FUDGE;
}

%%
