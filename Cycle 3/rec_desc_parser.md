### Theory Concepts Involved
* **Recursive Descent Parser:** A type of Top-Down parser built from a set of mutually recursive procedures (or a non-recursive equivalent) where each such procedure implements one of the non-terminals of the grammar. 
* **Left Recursion Elimination:** A standard arithmetic grammar (like `E -> E + T`) is left-recursive. A top-down parser would loop infinitely trying to resolve `E`. To fix this, the grammar is rewritten to be right-recursive using prime notation (`E'`), creating `E -> T E'` and `E' -> + T E'`.
* **Predictive Parsing (LL):** The parser looks ahead at the current input token to decide which production rule to apply (e.g., choosing `F -> ( E )` if it sees a parenthesis or `F -> i` if it sees an identifier).
* **Epsilon ($\epsilon$) Transitions:** If a non-terminal rule can derive an empty string, the recursive function simply returns without advancing the input cursor.

### Explanation of Logic
The code maps every non-terminal symbol in the grammar (`E`, `E'`, `T`, `T'`, `F`) to a specific `void` function. 
When a function is called, it attempts to follow its grammar rules from left to right. If the rule calls for another non-terminal, it triggers that function recursively. If the rule calls for a terminal (like `+`, `*`, `i`, `(`), it uses a `match()` function to check if the current character in the input string matches what is expected. If it matches, the pointer (`cursor`) advances. If not, a global `error` flag is thrown. 

### How the Program Works
1. **Initialization:** The user inputs a string (e.g., `i+i`). The `cursor` starts at index 0 and the `error` flag is 0.
2. **Start Symbol:** The `main()` function kicks off the process by calling `E()`. 
3. **Execution Tree:** `E()` prints its derivation step and immediately calls `T()`. `T()` calls `F()`.
4. **Matching Terminals:** Inside `F()`, the program checks `input[cursor]`. If it is `'i'`, it matches and advances the `cursor`. 
5. **Handling Epsilon:** When the cursor points to `+` and the program is inside `TP()` (which only handles `*`), it falls into the `else` block, prints "epsilon" and safely returns back up the call chain to let `EP()` handle the `+`.
6. **Final Validation:** After all recursive calls return to `main()`, the parser checks two things: 
   * Is `error == 0`?
   * Has the `cursor` reached the end of the string length? (This ensures trailing garbage characters like `i+i$#@` are rejected).
   If both conditions are met, the string is accepted.

### Sample Input and Output

**Sample Input:**
```text
Grammar for Arithmetic Expressions:
E  -> T E'
E' -> + T E' | epsilon
T  -> F T'
T' -> * F T' | epsilon
F  -> ( E ) | i

Enter the input string (use 'i' for identifiers): i+i*i
```

**Sample Output:**
```text
--- Parsing Steps ---
E  -> T E'
T  -> F T'
F  -> i
T' -> epsilon
E' -> + T E'
T  -> F T'
F  -> i
T' -> * F T'
F  -> i
T' -> epsilon
E' -> epsilon

Result: String successfully parsed. ACCEPTED.
```