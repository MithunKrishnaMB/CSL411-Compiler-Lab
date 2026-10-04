%{
#include <stdio.h>
%}

%%

" "     { printf("$"); }           /* If a space is found, print a dollar sign */
.       { printf("%s", yytext); }  /* If any other character is found, print it as is */
\n      { printf("\n"); return 0; } /* Preserve newlines and terminate */

%%

int yywrap(void) {
    return 1; // Indicates End of File
}

int main() {
    printf("Enter the string :\n");
    
    // yylex() starts the scanning and replacement process
    yylex(); 
    
    return 0;
}