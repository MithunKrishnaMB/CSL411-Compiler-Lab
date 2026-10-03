%{
#include <stdio.h>
%}

%%

.*john.*\n { printf("Result: REJECTED (Contains the substring)\n"); }
.*\n { printf("Result: ACCEPTED (Does not contain the substring)\n"); }

%%

int yywrap(void) {
  return 1; // Indicates the end of input
}

int main() {
  printf("Enter strings to test (Press Ctrl+Z then Enter to exit):\n");
  // yylex() starts the lexical analysis process
  yylex();
  return 0;
}
