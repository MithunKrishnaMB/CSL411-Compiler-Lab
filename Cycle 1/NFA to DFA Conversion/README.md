### Theory Concepts Involved
* **Subset Construction Algorithm (Powerset Construction):** The standard algorithmic technique used to convert an NFA into an equivalent DFA. Because an NFA can be in multiple states simultaneously, a DFA simulates this by grouping those simultaneous states into a single "subset" state.
* **Deterministic Behavior:** In a DFA, every state has exactly one path for every given input symbol. We achieve this by uniting all non-deterministic branches of the NFA into combined subset states.
* **State Queuing / Processing:** The algorithm systematically discovers new state combinations. When a transition generates a combination of NFA states that hasn't been seen before, it is queued as a new DFA state to be processed.

### Explanation of Logic
The core logic tracks states as *arrays of combinations*.
If NFA state `q0` goes to `q0` and `q1` on input `b`, the DFA will treat the subset `{q0, q1}` as a single, brand-new state. 
To figure out where `{q0, q1}` goes on input `a`, we check where `q0` goes on `a` and where `q1` goes on `a` and take the union of those results. If this union creates yet another unique combination, we register it as another new state. This repeats iteratively until no new combinations are generated.

### How the Program Works
1. **Data Structures:** 
   * `nfa[][][]` holds the original NFA transitions.
   * `dfa_states[][]` holds the unique subsets (each row is a DFA state, each column acts as a boolean flag indicating if an NFA state is part of that subset).
   * `dfa_trans[][]` points a DFA state to another DFA state index based on the alphabet.
2. **Initialization:** The DFA starts at the NFA's initial state `{q0}`. This is added to `dfa_states` as the first entry (index 0).
3. **The `while` loop Queue:** `num_dfa_states` keeps track of how many unique states we have found and `processed_states` acts as a queue pointer. The loop continues as long as there are newly discovered subsets left to process.
4. **Subset Union:** For a given DFA state and alphabet symbol, the nested `for` loops check all NFA states inside the current DFA subset and logically OR (`1`) their target states into `new_state`.
5. **State deduplication:** The `add_dfa_state` function checks if `new_state` matches any row already in `dfa_states`. If it's new, it appends it and increases `num_dfa_states`.
6. **Output Display:** Formats the subsets using `{ }` and maps out the transitions. Any transition going nowhere is printed as `{ - }`, representing the empty set or a dead state.

### Sample Input and Output

**Sample Console Interaction & Input:**
*(An NFA that accepts strings ending in 'b')*
```text
Enter number of NFA states: 2
Enter number of alphabet symbols: 2
Enter the alphabet symbols (e.g., ab): ab
Enter the total number of transitions: 3
Enter transitions in format: from_state symbol to_state
0 a 0
0 b 0
0 b 1
```

**Output:**
```text
--- DFA Transition Table ---
State               a                   b                   
------------------------------------------------------------
{ q0 }              { q0 }              { q0 q1 }           
{ q0 q1 }           { q0 }              { q0 q1 }           
```