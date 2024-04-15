%{
#include <stdio.h>
%}

// Regular expressions for tokens
DIGIT   [0-9]
INTEGER {DIGIT}+
IDENTIFIER [a-zA-Z][a-zA-Z0-9]*
OPERATOR [+|\-|*|/]

%%

{INTEGER}   { printf("INTEGER: %s\n", yytext); }
{IDENTIFIER} { printf("IDENTIFIER: %s\n", yytext); }
{OPERATOR}   { printf("OPERATOR: %s\n", yytext); }
[ \t\n]     ; // Ignore whitespace
.           { printf("Invalid character: %s\n", yytext); }

%%

int main() {
    yyin = stdin;
    yylex();
    return 0;
}
