### Theory Concepts Involved
* **Lex Preprocessing:** In compiler design, removing comments and whitespaces is typically the first action taken by the lexical analyzer before token generation begins.
* **Output Buffering:** Instead of printing characters directly to the console one-by-one as they are matched, we can store them in a buffer (like a large `char` array). This allows us to accumulate the fully processed text and only print the final result after the user has finished entering the entire code.
* **Complex Regular Expressions:** Writing a single regex for multi-line `/* ... */` comments is notoriously difficult because standard Lex does not support non-greedy wildcards (like `.*?`). The correct regex requires matching any character that is not a `*` or a `*` that is not followed by a `/`.

### Explanation of Logic
The program handles two types of comments in C-like languages: single-line (`//`) and multi-line (`/* ... */`).
- For single-line comments, a standard regular expression `"//".*` matches the `//` and everything after it until the end of the line. The action is empty, so it simply disappears.
- For multi-line comments, the complex regex `"/*"([^*]|\*+[^*/])*\*+"/"` accurately matches the block comment. 
- For all other text (`.|\n`), instead of printing it immediately, we store each character into a global array `output` at the current `out_idx`.

### How the Program Works
1. **Definitions Section:** A global character array `output` is initialized to act as a buffer and an integer `out_idx` keeps track of the current insertion point.
2. **Rules Section:**
   * `"//".*`: Matches single-line comments and discards them.
   * `"/*"([^*]|\*+[^*/])*\*+"/"`: Matches block comments and discards them.
   * `.|\n`: Matches any valid code character (including newlines). The character `yytext[0]` is appended to the `output` array.
3. **Execution:** `main()` prompts the user. The lexer filters the input in the background. The user pastes their code and signals the end of file (EOF) by pressing `Ctrl+Z then Enter` (on Windows). `yylex()` terminates and control returns to `main()`, which then null-terminates and prints the accumulated `output` buffer to the console.

### Sample Input and Output

*(Note: To compile and run this, use the commands: `flex filename.l` -> `gcc lex.yy.c` -> `./a.exe`)*

**Sample Console Interaction:**
```text
Enter the code (Press Ctrl+Z then Enter to exit):
#include<stdio.h>

int main(){
	int x=50;		//initialise x
	printf("%d\n",&x);	//print x
}


--- Output ---
#include<stdio.h>

int main(){
	int x=50;		
	printf("%d\n",&x);	
}
```