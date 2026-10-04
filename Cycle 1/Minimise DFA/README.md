### Theory Concepts Involved
* **DFA Minimization:** The process of reducing the number of states in a Deterministic Finite Automaton to its absolute minimum while ensuring it accepts the exact same language.
* **Myhill-Nerode Theorem / Table-Filling Method:** An algorithm based on identifying "distinguishable" states. Two states are distinguishable if a given string leads one state to an accepting/final condition and the other to a non-accepting/rejecting condition.
* **Equivalence Classes:** Groups of states that behave identically for all possible input strings. During minimization, all indistinguishable states in an equivalence class are merged into a single state.

### Explanation of Logic
The logic works backward through elimination. Initially, we assume all states might be identical (indistinguishable) unless proven otherwise. 
First, we mark the obvious difference: a final state can never be merged with a non-final state. 
Next, we iteratively check the transitions. If state `A` and state `B` both receive input `0` and `A` goes to a final state while `B` goes to a non-final state, `A` and `B` are proven distinguishable. This "distinguishability" bubbles backward until no new state pairs can be marked. Any pairs left unmarked are functionally identical and can be combined.

### How the Program Works
1. **Input Parsing:** Reads states, alphabet, final states and transition mappings. The transition logic assumes a fully defined DFA (every state has a transition for every symbol).
2. **Step A (Initial Marking):** Iterates through a 2D matrix (`dist[][]`). If `is_final[i]` does not match `is_final[j]`, it flags `dist[i][j] = 1`.
3. **Step B (Iterative Marking):** A `while(changed)` loop continually scans unmarked pairs. It checks their transition targets (`target_i` and `target_j`). If `dist[target_i][target_j]` is already marked as `1`, it means taking that path proves `i` and `j` are different, so `dist[i][j]` is updated to `1` and `changed = 1` forces another loop pass.
4. **Grouping:** Creates a `rep[]` (representative) array. If `dist[i][j] == 0`, it assigns both states to the same numerical representative index.
5. **Output Generation:** It loops through states, only printing those that are the "representative" of their group. It clusters all indistinguishable states inside braces `{ }`, using a `*` to label grouped final states.

### Sample Input and Output

**Sample Console Interaction & Input:**
*(A DFA where state 0 and 1 are identical in behavior, both going to a dead final state 2)*
```text
Enter number of states: 3
Enter number of alphabet symbols: 2
Enter the alphabet symbols (e.g., ab): ab
Enter number of final states: 1
Enter the final states (space separated): 2
Enter total number of transitions: 6
Enter transitions in format: from_state symbol to_state
0 a 1
0 b 2
1 a 1
1 b 2
2 a 2
2 b 2
```
**Sample Output:**
```text
--- Minimized DFA Transition Table ---
State               a                   b                   
------------------------------------------------------------
{ q0 q1 }           { q0 q1 }           { q2 }              
{ q2 }*             { q2 }              { q2 }              
```