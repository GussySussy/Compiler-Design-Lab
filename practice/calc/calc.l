%{
#include "calc.tab.h"
%}

%%

[ \t]+              { /* Ignore spaces and tabs */ }
[0-9]+(\.[0-9]+)?   {yylval.dval = atof(yytext);return NUMBER;}
"+"                 {return ADD;}
"-"                 {return SUB;}
"*"                 {return MUL;}
"/"                 {return DIV;}
"%"                 {return MOD;}
"("                 {return '(';}
")"                 {return ')';}
\n                  {return EOL;}
.                   {printf("\nInvalid character : %s\n", yytext);}


%%

int yywrap(){
    return 1;
}