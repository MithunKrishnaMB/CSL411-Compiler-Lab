%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(char *s);
%}

/* Declare tokens received from Lex */
%token LETTER DIGIT

%%

// The main rule: Expects a valid variable followed by the Enter key (\n)
line    : var '\n'  { printf("Result: ACCEPTED. Valid Variable.\n"); return 0; }
        ;

// Grammar rules for a valid variable
var     : LETTER        /* A variable can be just a single letter */
        | var LETTER    /* Or it can be a valid variable followed by another letter */
        | var DIGIT     /* Or it can be a valid variable followed by a digit */
        ;

%%

// Error handling function
void yyerror(char *s) {
    printf("Result: REJECTED. Invalid Variable.\n");
}

int main() {
    printf("Enter a variable name: ");
    yyparse(); // Start parsing the input
    return 0;
}