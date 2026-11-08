%{
#include "y.tab.h"
%}

%%

"for"                       { return FOR; }
"++"|"--"                   { return UNARY; }
"<="|">="|"=="|"!="|"<"|">" { return RELOP; }
[a-zA-Z_][a-zA-Z0-9_]*      { return ID; }
[0-9]+                      { return NUM; }
[ \t]+                      { /* Ignore spaces and tabs */ }
\n                          { return '\n'; }
.                           { return yytext[0]; } /* Return '{', '}', ';', '(', ')', '=' */

%%

int yywrap(void) {
    return 1;
}