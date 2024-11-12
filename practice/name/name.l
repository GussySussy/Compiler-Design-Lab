%{
#include <stdio.h>
%}

%%

^(.*[Gg][Oo][Uu][Rr].*)\n {printf("Unrecognized\n");}
^(.*)\n {printf("Recognized\n");}

%%

int main(){
    printf("Enter sentences : \n");
    yylex();
    return 0;
}

int yywrap(){
    return 1;
}