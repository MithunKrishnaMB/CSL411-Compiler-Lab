### Theory Concepts Involved
* **Lex Regular Expressions:** Lex uses standard regular expressions to match patterns in text. 
* **Character Classes (`[]`):** Square brackets match any one of the enclosed characters. For example, `[0|1]` matches `0`, `1` or the pipe `|` character.
* **Kleene Closure (`*`):** The `*` symbol matches zero or more occurrences of the preceding element. `[0|1]*` means any sequence of `0`s, `1`s or `|`s.
* **Wildcards (`.*`):** The `.` matches any single character (except a newline) and `*` means zero or more occurrences. Together, `.*` represents any arbitrary sequence of characters.

### Explanation of Logic
The program reads input line by line (terminated by `\n`). We define two prioritized rules:
1. `11[0|1]*101\n`: This rule checks for strings that begin with the prefix `11`, followed by any number of `0`s, `1`s (or `|`s) and ending with the suffix `101`, directly followed by the newline `\n` (Enter key).
2. `.*\n`: This is the fallback/catch-all rule. If the input does not match the first rule, it falls through to this rule and is rejected.

### How the Program Works
1. **Definitions Section (`%{ ... %}`):** Standard C input/output headers are included for the `printf` function.
2. **Rules Section (`%% ... %%`):** The Lexer intercepts user input. When you press Enter, it checks the string against the rules from top to bottom.
    * If you type `1100101`, it matches rule 1 (`11` + `00` + `101`) -> ACCEPTED.
    * If you type `11101`, it matches rule 1 (`11` + empty + `101`) -> ACCEPTED.
    * If you type `101101` or `23124`, it fails rule 1 and falls to rule 2 -> REJECTED.
3. **User Subroutines:** The `main()` function prompts the user and calls `yylex()`. The program remains in a loop accepting input until an End-of-File signal (Ctrl+Z then Enter on Windows) is sent, which triggers `yywrap()` to cleanly terminate the program.

### Sample Input and Output

*(Note: Compile and run this using: `flex filename.l` -> `gcc lex.yy.c` -> `./a.exe`)*

**Sample Console Interaction:**
```text
Enter strings to test (Press Ctrl+Z then Enter to exit):
1100101
Result: ACCEPTED

11101
Result: ACCEPTED

10122
Result: REJECTED

23124
Result: REJECTED
```