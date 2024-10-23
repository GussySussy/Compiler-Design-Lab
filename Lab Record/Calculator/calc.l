%{
#include "calc.tab.h"
%}

%%

[ \t]+              ;   /* Ignore whitespace */
[0-9]+(\.[0-9]+)?   {
                      yylval.dval = atof(yytext);
                      return NUMBER;
                    }
"+"                 { return '+'; }
"-"                 { return '-'; }
"*"                 { return '*'; }
"/"                 { return '/'; }
"("                 { return '('; }
")"                 { return ')'; }
\n                  { return EOL; }
.                   { printf("Unknown character: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}
