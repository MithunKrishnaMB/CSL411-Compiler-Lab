### Theory Concepts Involved
* **Lex as a Text Filter:** Lex can be used not just for tokenizing, but also as a stream editor or filter. It reads an input stream, identifies patterns and dynamically translates or alters the output.
* **The `yytext` Variable:** A built-in Lex string pointer (array of characters) that holds the exact text that was matched by the current rule. 
* **The `.` (Dot) Metacharacter:** In Lex regular expressions, a dot matches absolutely any single character *except* a newline (`\n`).

### Explanation of Logic
The program acts as a simple find-and-replace tool. It scans the input string character by character. 
If it encounters a literal space `" "`, instead of keeping the space, it prints a `$`. 
If it encounters any other character (letters, numbers, symbols, punctuation), it falls into the `.` rule and simply prints that exact character back to the screen using `yytext`. Newlines are handled explicitly to ensure the console output stays cleanly formatted.

### How the Program Works
1. **Definitions Section (`%{ ... %}`):** The standard I/O library is included to allow printing.
2. **Rules Section (`%% ... %%`):** 
   * Rule 1 (`" "`): Intercepts space characters and prints `$`.
   * Rule 2 (`.`): Intercepts everything else (except newlines). `printf("%s", yytext)` outputs whatever was matched, passing it through unchanged. *(Note: Lex actually has a default fallback rule that echoes unmatched characters to the screen, but defining `.` explicitly is safer and shows clearer logic).*
   * Rule 3 (`\n`): Captures the Enter key press, prints a newline and returns `0` to immediately terminate the scanning process.
3. **User Subroutines:** `main()` prints a prompt and hands control over to `yylex()`. The lexer processes the text and immediately terminates when the user presses Enter (due to the `return 0;` on newline).

### Sample Input and Output

*(Note: To compile and run this, use the commands: `lex filename.l` -> `gcc lex.yy.c` -> `./a.out`)*

**Sample Console Interaction:**
```text
Enter the string :
I am a good boy.
I$am$a$good$boy.