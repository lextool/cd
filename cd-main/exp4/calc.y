%{
#include <stdio.h>
#include <stdlib.h>
%}

%token NUMBER
%left '+' '-'
%left '*' '/'

%%

calc:   /* empty */
        | calc expr '\n' { printf("= %d\n", $2); }
        ;

expr:   NUMBER              { $$ = $1; }
        | expr '+' expr     { $$ = $1 + $3; }
        | expr '-' expr     { $$ = $1 - $3; }
        | expr '*' expr     { $$ = $1 * $3; }
        | expr '/' expr     { 
                                if ($3 != 0)
                                    $$ = $1 / $3;
                                else {
                                    fprintf(stderr, "Division by zero!\n");
                                    exit(EXIT_FAILURE);
                                }
                            }
        | '(' expr ')'      { $$ = $2; }
        ;

%%

int main() {
    yyparse();
    return 0;
}

int yyerror(const char *s) {
    fprintf(stderr, "error: %s\n", s);
    return 0;
}
