%{
#include "id_valid.tab.h"
%}

%%

[ \t\n]+                   ;   /* Ignore whitespace */
[a-zA-Z_][a-zA-Z0-9_]*       { yylval.str = strdup(yytext); return IDENTIFIER; }
.                          { yyerror("Invalid input: Expected a valid identifier");}

%%

int yywrap() {
    return 1;
}
