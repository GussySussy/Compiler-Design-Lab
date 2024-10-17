%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int yylex(void);
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

%type <str> expression assignment expression_list

%%

program:
    FOR_LOOP
    ;

FOR_LOOP:
    FOR '(' optional_expression ';' optional_expression ';' optional_expression ')' /* empty */ {
        printf("Valid 'for' loop syntax.\n");
    }
    ;

optional_expression:
    /* Empty */
    | expression
    ;

expression_list:
    expression
    | expression_list ',' expression
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
    fprintf(stderr, "Error: %s\n", s);
    exit(1);  /* Exit on syntax error */
}

int main(void) {
    printf("Enter a 'for' loop statement:\n");
    yyparse();
    return 0;
}
