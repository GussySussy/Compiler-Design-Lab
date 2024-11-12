%{
#include <stdio.h>
%}

%%
^(.*[Gg][oO][Uu][Rr].*)\n {printf("Not Recognized\n");}
^(.*) {printf("Recognized");}
%%

int main(){
    printf("Enter sentences : \n");
    yylex();
    return 0;
}

int yywrap(){
    return 1;
}