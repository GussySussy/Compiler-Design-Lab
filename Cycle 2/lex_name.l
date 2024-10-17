%{
#include <stdio.h>
%}

%%

^(.*[Gg][Oo][Uu][Rr].*)\n     {}

^(.*)\n           { printf("Recognized: %s\n", yytext); }

%%

int main(int argc, char **argv)
{
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}
