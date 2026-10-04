%{
#include <stdio.h>
// Global variables to hold the counts
int words = 0;
int spaces = 0;
int tabs = 0;
%}

%%

" "         { spaces++; }      /* Match a single space and increment space count */
\t          { tabs++; }        /* Match a single tab and increment tab count */
[^ \t\n]+   { words++; }       /* Match any sequence of characters that are NOT space, tab or newline */
\n          { return 0; }

%%

int yywrap(void) {
    return 1; // Indicates End of File
}

int main() {
    printf("Enter the string:\n");
    
    // yylex() continuously reads the input and applies the rules until EOF
    yylex(); 
    
    // Print the final counts after yylex() finishes
    printf("\n--- Results ---\n");
    printf("Words: %d\n", words);
    printf("Spaces: %d\n", spaces);
    printf("Tabs: %d\n", tabs);
    
    return 0;
}