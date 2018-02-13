%{
#include "dice.h"
#include "dice_parse.h"
%}

%%
[0-9]+ { yylval.integer = atoi(yytext); return TOK_INTEGER; }
[d] return TOK_DICESEP;
%%
