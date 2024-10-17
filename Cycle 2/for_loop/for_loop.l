%{
#include "for_loop.tab.h"
%}

%%

"for"               { return FOR; }

[a-zA-Z_][a-zA-Z0-9_]*    { yylval.str = strdup(yytext); return IDENTIFIER; }

[0-9]+              { yylval.str = strdup(yytext); return NUMBER; }

"=="                { return EQ; }
"!="                { return NE; }
"<="                { return LE; }
">="                { return GE; }
"++"                { return INC; }
"--"                { return DEC; }
"+"                 { return '+'; }
"-"                 { return '-'; }
"*"                 { return '*'; }
"/"                 { return '/'; }
"%"                 { return '%'; }
"="                 { return '='; }
"<"                 { return '<'; }
">"                 { return '>'; }
";"                 { return ';'; }
","                 { return ','; }
"("                 { return '('; }
")"                 { return ')'; }

[ \t\n]+            { /* Ignore whitespace */ }

.                   { printf("Invalid character: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}
