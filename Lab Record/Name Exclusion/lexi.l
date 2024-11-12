%{
#include <stdio.h>
%}

%%

^(.*[Gg][Oo][Uu][Rr].*)\n     {}

^(.*)\n           { printf("Recognized: %s\n", yytext); }

%%

int main()
{
    printf("Enter a sentence : \n");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}
