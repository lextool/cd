#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char lookahead;
char token[100];

void match(char expected) {
    if (lookahead == expected)
        lookahead = getchar();
    else {
        fprintf(stderr, "Syntax error: Expected '%c' but found '%c'\n", expected, lookahead);
        exit(EXIT_FAILURE);
    }
}

void identifier() {
    int i = 0;
    while (isalnum(lookahead) || lookahead == '_') {
        token[i++] = lookahead;
        lookahead = getchar();
    }
    token[i] = '\0';
}

void statement();
void declaration();
void assignment();

void statement() {
    if (lookahead == '\n') {
        lookahead = getchar();
        return;
    }
    if (isalpha(lookahead)) {
        identifier();
        if (lookahead == '=') {
            assignment();
        } else {
            fprintf(stderr, "Syntax error: Expected '=' but found '%c'\n", lookahead);
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "Syntax error: Expected identifier but found '%c'\n", lookahead);
        exit(EXIT_FAILURE);
    }
}

void declaration() {
    match('int');
    identifier();
    printf("Declare %s as integer\n", token);
    match(';');
}

void assignment() {
    printf("Assign %s\n", token);
    match('=');
    // Assume a simple expression for demonstration
    printf("Expression\n");
    match(';');
}

int main() {
    printf("Enter code (end with Ctrl+D):\n");
    lookahead = getchar();
    while (lookahead != EOF) {
        statement();
    }
    printf("Parsing completed.\n");
    return 0;
}
