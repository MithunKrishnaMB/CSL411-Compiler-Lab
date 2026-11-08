%{
#include "y.tab.h"
#include <stdlib.h>
// yylval passes the semantic value (the actual number) to Yacc
extern int yylval; 
%}

%%

[0-9]+      { yylval = atoi(yytext); return NUMBER; } /* Extract integers */
[ \t]+      { /* Ignore redundant whitespace */ }
\n          { return '\n'; }                          /* Trigger evaluation on Enter */
.           { return yytext[0]; }                     /* Return operators (+, -, *) as is */

%%

int yywrap(void) {
    return 1;
}