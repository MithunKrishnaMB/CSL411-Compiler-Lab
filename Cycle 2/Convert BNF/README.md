### Theory Concepts Involved
* **Abstract Syntax Tree (AST):** A tree representation of the abstract syntactic structure of source code. Unlike a parse tree, which contains all grammar details (like parentheses and single-rule reductions), an AST strips away the clutter and only retains the core hierarchical operations (Operators as parent nodes, Operands as children).
* **BNF to Yacc Translation:** Backus-Naur Form (BNF) is a mathematical notation for context-free grammars. Yacc uses an almost identical syntax, allowing developers to directly translate BNF equations (e.g., `E ::= E + T`) into Yacc rules (`E : E '+' T`).
* **Semantic Records (`%union`):** By default, Yacc's `yylval` variable only holds integers. To build a tree, we must redefine `yylval` as a C `union` so it can hold both strings (for the operand text) and pointers (to pass tree nodes up the hierarchy).
* **Tree Traversals:** To verify the AST structure on a flat terminal screen, the tree is printed using Pre-order Traversal (Root, Left, Right). 

### Explanation of Logic
Instead of executing math (like in a calculator), the semantic actions in the Yacc file assemble data structures. 
We define a C `struct` named `node` containing a string (the operator or operand) and two pointers (left and right children).
When Lex finds a variable or number, Yacc applies the rule `F : OPERAND` and calls `mknode()`, creating a leaf node with no children.
When Yacc parses `E + T`, it calls `mknode("+", $1, $3)`. It creates a root node holding the `+` string, attaches the `E` sub-tree as its left child and attaches the `T` sub-tree as its right child. This progressively builds the tree from the bottom up.

### How the Program Works
1. **Compilation:** `yacc -d` generates the headers containing the `%union` definition so Lex can properly assign strings to `yylval.str`.
2. **Lexical Scanning:** If the input is `a+b*c`, Lex returns `OPERAND` (val: "a"), `+`, `OPERAND` (val: "b"), `*`, `OPERAND` (val: "c").
3. **AST Construction:**
   * `a` becomes a leaf node.
   * `b` and `c` become leaf nodes.
   * `b * c` is reduced first (due to grammar precedence). A new node `*` is created with `b` on the left and `c` on the right.
   * `a + (b*c)` is reduced next. A new node `+` is created with `a` on the left and the `*` subtree on the right.
4. **Execution & Printing:** Once the `Start` rule is reached, the root of the entire AST is passed to the `printtree()` function. The pre-order traversal prints the root operator before its children, visually validating the precedence hierarchy.

### Sample Input and Output

```text
Enter an expression to generate its AST (e.g., a+b*c):
a+b*c

Abstract Syntax Tree (Pre-order Traversal):
+ a * b c