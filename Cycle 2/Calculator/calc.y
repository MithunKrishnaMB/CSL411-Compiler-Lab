%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(char *s);
%}

/* Declare tokens and Operator Precedence */
%token NUMBER
%left '+' '-'
%left '*' '/' '%'
%left '(' ')'

%%

// Grammar Definitions
Start   : 
        | Start Line
        ;

Line    : '\n'
        | E '\n'     { printf("Result: %d\n", $1); } 
        | error '\n' { yyerrok; }                    
        ;

// Syntax-Directed Translation for Expressions
E       : E '+' E    { $$ = $1 + $3; }
        | E '-' E    { $$ = $1 - $3; }
        | E '*' E    { $$ = $1 * $3; }
        | E '/' E    { 
                        if ($3 == 0) {
                            yyerror("Division by zero!");
                            $$ = 0;
                        } else {
                            $$ = $1 / $3; 
                        }
                     }
        | E '%' E    { $$ = $1 % $3; }
        | '(' E ')'  { $$ = $2; }
        | NUMBER     { $$ = $1; }
        ;

%%

void yyerror(char *s) {
    printf("Error: %s\n", s);
}

int main() {
    printf("Enter an arithmetic expression (Press Ctrl+D to exit):\n");
    yyparse(); 
    return 0;
}