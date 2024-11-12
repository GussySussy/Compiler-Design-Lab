%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void yyerror(const char *s);
int yylex();

%}

%union {
    double dval;
}

%token <dval> NUMBER
%token MUL DIV ADD SUB MOD EOL

%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%type <dval> expression

%%

input:
      /* Empty */
    | input line
    ;

line:
      expression EOL      { printf("Result: %g\n", $1); }
    | EOL                 { /* Ignore empty lines */ }
    ;

expression:
      expression ADD expression     { $$ = $1 + $3; }
    | expression SUB expression     { $$ = $1 - $3; }
    | expression MUL expression     { $$ = $1 * $3; }
    | expression DIV expression     {
                                      if ($3 == 0) {
                                        yyerror("Division by zero");
                                        YYABORT;
                                      } else {
                                        $$ = $1 / $3;
                                      }
                                    }
    | expression MOD expression                { $$ = fmod($1, $3); }
    | SUB expression %prec UMINUS   { $$ = -$2; }
    | '(' expression ')'            { $$ = $2; }
    | NUMBER                        { $$ = $1; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    printf("Enter expressions (Ctrl+D to exit):\n");
    yyparse();
    return 0;
}
