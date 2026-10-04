%{
#include <stdio.h>
%}

%%

11[0|1]*101\n   { printf("Result: ACCEPTED\n"); }
.*\n            { printf("Result: REJECTED\n"); }

%%

int yywrap(void) {
    return 1; // Indicates the end of the input stream
}

int main() {
    printf("Enter strings to test (Press Ctrl+Z then Enter to exit):\n");
    // yylex() starts the lexical analysis process
    yylex(); 
    return 0;
}