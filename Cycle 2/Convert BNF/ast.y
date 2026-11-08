%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char *token;
    struct node *left;
    struct node *right;
} node;

node* mknode(char *token, node *left, node *right);
void printtree(node *tree);
int yylex(void);
void yyerror(char *s);
%}

%union {
    char *str;
    struct node *nd;
}

%token <str> OPERAND
%type <nd> E T F

%%

Start   : E '\n' { 
            printf("\nAbstract Syntax Tree (Pre-order Traversal):\n");
            printtree($1); 
            printf("\n");
            exit(0); 
          }
        ;

E       : E '+' T { $$ = mknode("+", $1, $3); }
        | E '-' T { $$ = mknode("-", $1, $3); }
        | T       { $$ = $1; }
        ;

T       : T '*' F { $$ = mknode("*", $1, $3); }
        | T '/' F { $$ = mknode("/", $1, $3); }
        | F       { $$ = $1; }
        ;

F       : '(' E ')' { $$ = $2; }
        | OPERAND   { $$ = mknode($1, NULL, NULL); }
        ;

%%

node* mknode(char *token, node *left, node *right) {
    node *newnode = (node*)malloc(sizeof(node));
    newnode->token = strdup(token);
    newnode->left = left;
    newnode->right = right;
    return newnode;
}

void printtree(node *tree) {
    if (tree == NULL) return;
    printf("%s ", tree->token);
    printtree(tree->left);
    printtree(tree->right);
}

void yyerror(char *s) {
    printf("Error: %s\n", s);
}

int main() {
    printf("Enter an expression to generate its AST (e.g., a+b*c):\n");
    yyparse();
    return 0;
}