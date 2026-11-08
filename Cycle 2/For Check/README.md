### Theory Concepts Involved
* **Context-Free Grammar (CFG) validation:** Yacc uses CFGs to map out the exact structural requirements of complex programming constructs, like the mandatory three-part header of a C `for` loop separated by semicolons.
* **Token Abstraction:** The parser does not care what a variable is named or what its value is. Lex strips that specific information away and simply feeds Yacc abstracted tokens (`ID`, `NUM`, `RELOP`), allowing the grammar rules to remain general and reusable.
* **Empty/Null Productions:** In C, a valid `for` loop can have empty sections (e.g., `for(;;)`). The Yacc grammar supports this by explicitly providing an `/* empty */` alternative rule for the expressions.
* **Recursive Grammars & Nested Loops:** The rule `Def -> Stmt` allows the body of the `for` loop to be *another* `for` loop, naturally supporting infinite levels of loop nesting.

### Explanation of Logic
The Lex file identifies the basic building blocks. It intercepts keywords (`for`), assignment/relational operators (`=`, `<=`, `++`) and generic identifiers or numbers.
The Yacc file takes these building blocks and enforces the strict C language structure. It dictates that a `FOR` token must be followed by `(`, then an optional expression, a `;`, another optional expression, a `;`, a final optional expression and `)`. 
After the `)`, it expects the definition (`Def`), which handles the loop's body. The body is defined recursively so it can accept a single-line statement ending in `;` or a multi-line block enclosed in `{ }`.

### How the Program Works
1. **Compilation:** Use `yacc -d for.y` to generate the headers, `lex for.l` to generate the scanner and `gcc lex.yy.c y.tab.c` to compile them together.
2. **Lexical Scanning:** When the user enters `for(i=0; i<10; i++)`, Lex tokenizes it into: `FOR`, `(`, `ID`, `=`, `NUM`, `;`, `ID`, `RELOP`, `NUM`, `;`, `ID`, `UNARY`, `)`.
3. **Syntax Checking (Yacc):**
   * The `Expr` rule collapses `ID = NUM` into `Expr`.
   * It collapses `ID RELOP NUM` into `Expr`.
   * It collapses `ID UNARY` into `Expr`.
   * The `E` rule accepts these `Expr` components.
   * The `Stmt` rule sees `FOR ( E ; E ; E )` and looks for the body.
   * If the user entered `{ }`, the `Def` rule satisfies the `{ Body }` path (using the empty rule for `Body`).
4. **Resolution:** If all tokens fit the puzzle perfectly, it reaches the `Start` rule, prints "ACCEPTED," and exits. If a semicolon or bracket is out of place, Yacc immediately throws a shift/reduce error, triggering `yyerror()` to print "REJECTED."

### Sample Input and Output

```text
Enter a C 'for' loop to check its syntax:
for(i=0; i<=10; i++) { a = a + 1; }
Result: ACCEPTED. Valid 'for' loop syntax.

Enter a C 'for' loop to check its syntax:
for(;;) { }
Result: ACCEPTED. Valid 'for' loop syntax.

Enter a C 'for' loop to check its syntax:
for(i=0, i<10, i++)
Result: REJECTED. Invalid Syntax. 

Enter a C 'for' loop to check its syntax:
for(i=0; i<10; i++) { for(j=0; j<5; j++) { } }
Result: ACCEPTED. Valid 'for' loop syntax.