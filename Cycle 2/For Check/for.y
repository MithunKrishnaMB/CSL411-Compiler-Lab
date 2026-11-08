%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(char *s);
%}

/* Tokens received from Lex */
%token FOR ID NUM RELOP UNARY

/* Operator Precedence to resolve shift/reduce conflicts */
%right '='
%left RELOP
%left '+' '-'
%left '*' '/'

%%

// 1. The starting rule expects a valid statement followed by Enter
Start   : Stmt '\n'  { printf("Result: ACCEPTED. Valid 'for' loop syntax.\n"); exit(0); }
        ;

// 2. Structure of a 'for' loop: for ( Expression ; Expression ; Expression ) Body
Stmt    : FOR '(' E ';' E ';' E ')' Def
        ;

// 3. The Body of the loop can be a block { }, a single expression or a nested loop
Def     : '{' Body '}'
        | Expr ';'
        | Stmt
        | ';'
        ;

// 4. A block can contain multiple statements or be empty
Body    : Body BlockStmt
        | /* empty */
        ;

BlockStmt : Expr ';'
          | Stmt
          | ';'
          ;

// 5. The 3 parts of the for loop header can be empty (e.g., for(;;))
E       : Expr
        | /* empty */
        ;

// 6. Valid expressions inside the loop header and body
Expr    : ID '=' Expr
        | Expr RELOP Expr
        | Expr '+' Expr
        | Expr '-' Expr
        | ID UNARY
        | UNARY ID
        | ID
        | NUM
        ;

%%

void yyerror(char *s) {
    printf("Result: REJECTED. Invalid Syntax.\n");
    exit(0);
}

int main() {
    printf("Enter a C 'for' loop to check its syntax:\n");
    yyparse(); 
    return 0;
}