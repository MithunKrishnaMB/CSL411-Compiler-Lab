### Theory Concepts Involved
* **Context-Free Grammars (CFG):** Used by Yacc to define the structural rules of a language. Here, the grammar defines that a valid variable must be rooted in a `LETTER`.
* **Left Recursion:** The rule `var : var LETTER | var DIGIT` is left-recursive. Yacc (which uses LALR Bottom-Up parsing) handles left recursion very efficiently without stack overflow, making it the preferred way to parse repeating sequences of tokens.
* **Separation of Concerns (Lex vs Yacc):** Lex does not know what a "variable" is; it only knows how to categorize individual characters into `LETTER` or `DIGIT`. Yacc acts as the gatekeeper that enforces the *order* in which those characters are allowed to appear.

### Explanation of Logic
To enforce the rule "starts with a letter, followed by letters or numbers", we define a recursive grammar.
The base case is simply `LETTER`. This guarantees that the very first character evaluated *must* be a letter. 
Once that base case is established (we now have a `var`), the recursive cases (`var LETTER` and `var DIGIT`) allow the parser to accept any subsequent characters, as long as they are letters or digits. If the user types a digit first, Yacc will look for a rule that starts with `DIGIT`, fail to find one and immediately throw a syntax error.

### How the Program Works
1. **Compilation:** 
   * `yacc -d var.y` (Generates `y.tab.c` and `y.tab.h`)
   * `lex var.l` (Generates `lex.yy.c`)
   * `gcc lex.yy.c y.tab.c -w` (Compiles both into `a.out`)
2. **Execution Flow:** The user types `age1`.
3. **Lexical Analysis:** Lex reads `a`, returns `LETTER`. Reads `g`, returns `LETTER`. Reads `e`, returns `LETTER`. Reads `1`, returns `DIGIT`. Reads `\n`, returns `\n`.
4. **Syntax Analysis (Bottom-Up Shift-Reduce):**
   * Yacc sees `LETTER` (a) and reduces it to `var` (Base case).
   * Yacc sees `var` followed by `LETTER` (g) and reduces it to a new `var`.
   * Yacc sees `var` followed by `LETTER` (e) and reduces it to a new `var`.
   * Yacc sees `var` followed by `DIGIT` (1) and reduces it to a new `var`.
   * Yacc sees `var` followed by `\n` and triggers the `line` rule, printing "ACCEPTED".
5. **Rejection:** If the user types `1age`, Lex sends `DIGIT` first. Yacc's grammar dictates that `var` must start with `LETTER`. It throws a syntax error, calling `yyerror()` and prints "REJECTED".

### Sample Input and Output

```text
Enter a variable name: count123
Result: ACCEPTED. Valid Variable.