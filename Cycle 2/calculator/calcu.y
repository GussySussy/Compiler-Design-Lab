%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void yyerror(const char *s);
int yylex();

%}

%union{
    double dval;
}

%token <dval> NUMBER
%token EOL

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
      expression EOL { printf("Result : %g\n", $1); }
    | EOL
    ;

expression:
      expression '+' expression { $$ = $1 + $3; }
    | expression '-' expression { $$ = $1 - $3; }
    | expression '*' expression { $$ = $1 * $3; }
    | expression '/' expression {
                                    if ($3 == 0) 
                                        yyerror("Division by Zero");
                                    else 
                                        $$ = $1 / $3;
                                }
    | '-' expression %prec UMINUS { $$ = -$2; }
    | '(' expression ')' { $$ = $2; }
    | NUMBER { $$ = $1; }
    ;

%%

void yyerror(const char *s){
    fprintf(stderr,"Error : %s\n", s);
}

int main(){
    printf("Enter expressions: (Press Ctrl+D to exit.)\n");
    yyparse();
    return 0;
}
