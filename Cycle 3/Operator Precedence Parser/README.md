### Theory Concepts Involved
* **Operator Precedence Parser:** A type of Bottom-Up shift-reduce parser that can be applied to a class of grammars called operator grammars. An operator grammar has no $\epsilon$-productions and no two adjacent non-terminals on the right side of a production.
* **Precedence Relations:** The parser relies on predefined relations between operators: 
  * `<` implies "yields precedence to" (triggering a Shift).
  * `>` implies "takes precedence over" (triggering a Reduce).
  * `=` implies "has same precedence as".
* **Topmost Terminal:** Operator precedence ignores non-terminals (like `E`) when making decisions. The relation is strictly checked between the topmost *terminal* (operator) on the stack and the current incoming input symbol.

### Explanation of Logic
The program hardcodes a 4x4 precedence matrix for the operators `+`, `*`, `i` (identifier) and `$`. 
Identifiers (`i`) have the highest precedence, meaning they will always be reduced immediately. Multiplication (`*`) has higher precedence than addition (`+`). The `$` symbol acts as the stack bottom and input terminator with the lowest precedence.
During execution, the parser looks at the topmost terminal on the stack and the current input symbol to look up the relation in the matrix. If the relation is `<`, the input symbol is shifted onto the stack. If the relation is `>`, a reduction occurs (replacing the handle like `i` or `E+E` with the generic non-terminal `E`).

### How the Program Works
1. **Initialization:** The stack is initialized with the `$` symbol and the user is expected to input a string terminating with `$`.
2. **Terminal Search:** Inside the infinite `while` loop, a small inner loop scans down from the top of the stack, skipping any `E` (non-terminal) to find the actual topmost terminal character.
3. **Table Lookup:** The `getIndex()` function maps the stack terminal and input character to row and column indices. The relation (`<`, `>`, `A`, `e`) is fetched from the 2D array `table`.
4. **Action (Shift/Reduce):**
   * If `<`: The input symbol is pushed onto the `stack` and the input index `i` is incremented.
   * If `>`: The program identifies the pattern at the top of the stack. If it's an `i`, it replaces it with `E`. If it's `E+E` or `E*E`, it shrinks the stack pointer (`top = top - 2`) and places `E` at the new top, effectively replacing 3 stack elements with 1.
5. **Termination:** If the lookup yields `A`, the string is successfully syntactically parsed and the loop breaks.

### Sample Input and Output

**Sample Console Interaction & Input:**
```text
Enter the input string (use 'i' for id, append $ at end): i+i*i$
```

**Sample Output:**
```text
Stack           Input           Action
------------------------------------------------
$               i+i*i$          Shift
$i              +i*i$           Reduce
$E              +i*i$           Shift
$E+             i*i$            Shift
$E+i            *i$             Reduce
$E+E            *i$             Shift
$E+E*           i$              Shift
$E+E*i          $               Reduce
$E+E*E          $               Reduce
$E+E            $               Reduce
$E              $               Accepted
```