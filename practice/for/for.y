%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
%}

%union {
    char *str;
}

%token <str> IDENTIFIER NUMBER
%token FOR
%token EQ NE LE GE INC DEC

%left '+' '-'
%left '*' '/' '%'
%right '='
%right INC DEC

%%

program:
    FOR_LOOP
    ;

FOR_LOOP:
    FOR '(' optional_expression ';' optional_expression ';' optional_expression ')' '{' NESTED_FOR_LOOP '}' {printf("Valid 'for' loop syntax.\n");}
    ;

NESTED_FOR_LOOP:
    /* Empty */
    | NESTED_FOR_LOOP FOR_LOOP
    ;

optional_expression:
    /* Empty */
    | expression
    ;

expression:
    assignment
    | comparison
    | increment_expression
    | decrement_expression
    ;

assignment:
    IDENTIFIER '=' expression
    ;

comparison:
    expression comparison_operator expression
    ;

comparison_operator:
    '<' | '>' | LE | GE | EQ | NE
    ;

increment_expression:
    IDENTIFIER INC
    | INC IDENTIFIER
    ;

decrement_expression:
    IDENTIFIER DEC
    | DEC IDENTIFIER
    ;

expression:
    expression '+' expression
    | expression '-' expression
    | expression '*' expression
    | expression '/' expression
    | expression '%' expression
    | '(' expression ')'
    | IDENTIFIER
    | NUMBER
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "INVALID 'for' loop: %s\n", s);
}

int main(void) {
    printf("Enter a 'for' loop statement:\n");
    yyparse();
    return 0;
}
