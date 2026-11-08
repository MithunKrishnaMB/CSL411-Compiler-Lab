### Theory Concepts Involved
* **Lex & Yacc Cooperation:** Lex acts as the tokenizer, reading raw character streams and grouping them into tokens (like `NUMBER`). Yacc acts as the parser, using a Context-Free Grammar (CFG) to validate the arrangement of those tokens and compute their mathematical values.
* **Semantic Values (`yylval`):** A global variable shared between Lex and Yacc. When Lex finds the string `"25"`, it uses `atoi()` to convert it to the integer `25` and stores it in `yylval` so Yacc can perform actual arithmetic rather than just string concatenation.
* **Operator Precedence and Associativity:** In mathematics, multiplication happens before addition. Yacc handles this via the `%left` directives. Directives listed lower in the file have higher precedence. `%left` also ensures left-to-right associativity (e.g., $10 - 5 - 2$ is evaluated as $(10 - 5) - 2$).
* **Syntax-Directed Translation:** The C code enclosed in `{ }` next to the grammar rules. When Yacc successfully parses a rule like `E -> E + E`, it immediately executes the block `$$ = $1 + $3`, replacing the two operands with their calculated sum.

### Explanation of Logic
A calculator cannot be built purely with regular expressions because regular expressions cannot count or handle nested parentheses. 
Lex is programmed strictly to identify digits, spaces and mathematical symbols. It strips the spaces out and hands the numbers and symbols to Yacc.
Yacc maintains a parsing stack. When it receives a sequence like `NUMBER '+' NUMBER`, it reduces it to a generic Expression (`E`) and adds their values together. If it sees a `*`, it holds off on reducing any previous `+` operations until the `*` operation is fully reduced, ensuring BODMAS/PEMDAS rules are strictly followed.

### How the Program Works
1. **Compilation:** Both files must be compiled in tandem. `yacc -d` generates a header file `y.tab.h` that contains the definition of the `NUMBER` token so Lex knows what it is.
2. **Lexical Scanning:** When the user enters `4 + 5 * 2`, Lex sends `NUMBER` (val: 4), `+`, `NUMBER` (val: 5), `*`, `NUMBER` (val: 2).
3. **Shift-Reduce Parsing:** 
   * Yacc shifts `4` and reduces it to `E`.
   * It shifts `+` and `5` (reduced to `E`). 
   * It looks ahead and sees `*`. Because `*` has higher precedence than `+`, it does not perform the addition yet.
   * It shifts `*` and `2` (reduced to `E`).
   * It reduces `E * E` using `$$ = 5 * 2`, placing `10` on the stack.
   * Finally, it reduces `E + E` using `$$ = 4 + 10`, placing `14` on the stack.
4. **Execution:** The `\n` rule triggers, printing the final stack value `14`.

### Sample Input and Output

```text
Enter an arithmetic expression (Press Ctrl+D to exit):
10 + 20
Result: 30

2 + 3 * 4
Result: 14

(2 + 3) * 4
Result: 20

10 / 0
Error: Division by zero!
Result: 0