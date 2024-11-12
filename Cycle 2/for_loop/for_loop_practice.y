%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char* s);
int yylex(void);
%}

%union {
    int intval;
    char* strval;
}

%token <strval> ID FOR
%token <intval> NUM
%token INC DEC GT LT GE LE EQ NE NEWLINE

%left '+' '-'
%left '*' '/' '%'
%right INC DEC
%right '='

%%

program:
    FOR_LOOP
    ;

FOR_LOOP:
    FOR '(' optional_expression ';' optional_expression ';' optional_expression ')' for_loop_body
    {
printf("Valid For Loop Syntax\n");}
    ;

optional_expression:
    /* empty */
    | expression
    ;

for_loop_body:
    /* empty */                 /* Allows for loops with empty bodies */
    | '{' FOR_LOOP '}'          /* Allows a for loop containing another for loop */
    ;

expression_list:
    assignment
    | comparison
    | increment
    | decrement
    ;

assignment:
    ID '=' expression
    ;

comparison:
    expression comparison_operator expression
    ;

comparison_operator:
    GE | LE | GT | LT | EQ | NE
    ;

increment:
    ID INC
    | INC ID
    ;

decrement:
    ID DEC
    | DEC ID
    ;

expression:
    expression_list
    | expression '+' expression
    | expression '-' expression
    | expression '*' expression
    | expression '/' expression
    | expression '%' expression
    | '(' expression ')'
    | ID
    | NUM
    ;

%%

int main() {
    printf("Enter a For Loop statement:\n");
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
    exit(1);
}
