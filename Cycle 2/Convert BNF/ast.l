%{
#include "y.tab.h"
#include <string.h>
%}

%%

[a-zA-Z0-9]+    { 
                  // Pass the actual string value of the operand to Yacc
                  yylval.str = strdup(yytext); 
                  return OPERAND; 
                }
[ \t]+          { /* Ignore whitespace */ }
\n              { return '\n'; }
.               { return yytext[0]; } /* Return operators (+, -, *, /, etc.) */

%%

int yywrap(void) {
    return 1;
}