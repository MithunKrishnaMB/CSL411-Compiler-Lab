### Theory Concepts Involved
* **Bottom-Up Parsing:** A shift-reduce parser constructs the parse tree from the leaves (input symbols) to the root (Start symbol) by progressively replacing parts of the input with non-terminals.
* **Shift Action:** Moving the next unconsumed input symbol onto the top of the parsing stack.
* **Reduce Action:** Identifying a string on the top of the stack that matches the right-hand side (RHS) of a grammar rule (a "handle") and replacing it with the left-hand side (LHS) non-terminal.
* **Shift-Reduce Conflict & Lookahead:** When the parser could theoretically either shift a new token or reduce the current stack, it uses lookahead to decide. In this program, it looks ahead at the `*` operator to enforce operator precedence over `+`.

### Explanation of Logic
The program simulates a shift-reduce parser using an explicit stack and an input buffer for a basic mathematical expression grammar (`E -> E+E | E*E | i`).
The logic follows a simple greedy cycle: 
1. **Shift** one character from the input onto the stack.
2. **Reduce** aggressively. The `check()` function examines the top of the stack. If it sees `i`, it replaces it with `E`. If it sees `E*E`, it replaces it with `E`. 
3. If it sees `E+E`, it performs a lookahead check. If the next incoming character is `*`, it intentionally aborts the reduction, allowing the `*` to be shifted onto the stack first. This ensures `i+i*i` is evaluated as `i+(i*i)` rather than `(i+i)*i`.

### How the Program Works
1. **Initialization:** The string is accepted from the user and an end-marker `$` is appended to the input. The `stack` is initialized with `$`.
2. **Processing Loop:** The `while` loop runs until the input pointer `i` reaches the end marker. In each iteration, it copies `input[i]` to `stack[top]` and increments `top`.
3. **The `check()` Cycle:** After every shift, `check()` is called. It uses a `while (reduced)` loop because one reduction might trigger another (e.g., reducing `i` to `E` might create `E*E` which immediately reduces to `E`).
4. **Pointer Math for Alignment:** Inside the loop, `input + i` is used in the `printf` statements. This smoothly prints the substring of the input buffer starting from the current index, creating the visual effect of characters leaving the input buffer as they enter the stack.
5. **Acceptance Criteria:** Once the loop ends, if the stack has been perfectly reduced to exactly `$E` and the only remaining input is `$`, the parser halts and prints "Accepted."

### Sample Input and Output

**Sample Input:**
```text
Grammar:
E -> E+E 
E -> E*E 
E -> i

Enter input string (e.g., i+i*i): i+i*i
```

**Sample Output:**
```text
Stack           Input           Action
------------------------------------------------
$i              +i*i$           Shift
$E              +i*i$           Reduce E -> i
$E+             i*i$            Shift
$E+i            *i$             Shift
$E+E            *i$             Reduce E -> i
$E+E*           i$              Shift
$E+E*i          $               Shift
$E+E*E          $               Reduce E -> i
$E+E            $               Reduce E -> E*E
$E              $               Reduce E -> E+E

$E              $               Accepted
```