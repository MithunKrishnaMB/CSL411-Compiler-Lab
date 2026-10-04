### Theory Concepts Involved
* **Lex Global Variables:** Lex allows the declaration of standard C global variables inside the `%{ ... %}` block. These variables persist across multiple pattern matches, making them ideal for running counters.
* **Regular Expressions (Regex) in Lex:** 
  * `[^ ... ]` is a negated character class. It matches any character *not* listed inside the brackets. 
  * `+` is a quantifier meaning "one or more times".
* **Word Boundary Recognition:** In lexical analysis, a "word" is typically defined as any continuous sequence of characters bounded by whitespace (spaces, tabs or newlines).

### Explanation of Logic
The program operates by scanning the input string character by character (or sequence by sequence) and categorizing what it finds using three primary rules:
1. If it sees a literal space `" "`, it increments the `spaces` counter.
2. If it sees a literal tab `\t`, it increments the `tabs` counter.
3. If it sees one or more characters that are explicitly *not* a space, not a tab and not a newline (`[^ \t\n]+`), it considers that entire cluster a single "word" and increments the `words` counter. 

### How the Program Works
1. **Definitions Section (`%{ ... %}`):** The C integer variables `words`, `spaces` and `tabs` are initialized to `0`.
2. **Rules Section (`%% ... %%`):** The lexer reads the standard input. When you type a sentence, it tokenizes the input based on the rules. For example, "Hello world" is matched as: `[^ \t\n]+` (Hello) -> `words++`, `" "` (space) -> `spaces++`, `[^ \t\n]+` (world) -> `words++`. The `\n` rule returns `0`, causing `yylex()` to immediately terminate and finish processing when you press Enter.
3. **User Subroutines:** `main()` prints a prompt and hands control over to `yylex()`. The lexer runs until a newline is encountered (i.e., pressing Enter). Once `yylex()` terminates, control returns to `main()`, which then prints the final accumulated counts.

### Sample Input and Output

*(Note: To compile and run this, use the commands: `lex filename.l` -> `gcc lex.yy.c` -> `./a.out`)*

**Sample Console Interaction:**
```text
Enter the string:
Hello   world.	This is a test.

--- Results ---
Words: 5
Spaces: 6
Tabs: 1