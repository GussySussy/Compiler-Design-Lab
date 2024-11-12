%{
#include "for_loop_practice.tab.h"
%}

%%

"for" { return FOR; }

[a-zA-Z_][a-zA-Z0-9_]* {yylval.strval = strdup(yytext); return ID;}
[0-9]*              { yylval.intval = atoi(yytext); return NUM; }

"=="                { return EQ;   }
"!="                { return NE;   }
"<="                { return LE;   }
">="                { return GE;   }
"<"                 { return LT;   }
">"                 { return GT;   }
"++"                { return INC; }
"--"                { return DEC; }
"+"                 { return '+'; }
"-"                 { return '-'; }
"*"                 { return '*'; }
"/"                 { return '/'; }
"%"                 { return '%'; }
"="                 { return '='; }
";"                 { return ';'; }
","                 { return ','; }
"("                 { return '('; }
")"                 { return ')'; }
"{"                 { return '{'; }
"}"                 { return '}'; }
\n                  { return NEWLINE; }

[ \t\n]+            {}
.                   { printf("Invalid Character : %s\n", yytext);}

%%

int yywrap(){
    return 1;
}