%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int yylex();

%}

%union {
    char *str;
}

%token <str> IDENTIFIER

%%

input:
    /* Empty */
    | input line
    ;

line:
    IDENTIFIER          { printf("Valid variable: %s\n", $1); free($1); }
    | error             { yyerrok; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    printf("Enter variable names (Ctrl+D to end):\n");
    yyparse();
    return 0;
}
