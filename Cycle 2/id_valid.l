%{
#include "id_valid.tab.h"
%}

%%

[ \t\n]+                   ;   /* Ignore whitespace */
[a-zA-Z][a-zA-Z0-9]*       { yylval.str = strdup(yytext); return IDENTIFIER; }
.                          { return yytext[0]; }

%%

int yywrap() {
    return 1;
}
