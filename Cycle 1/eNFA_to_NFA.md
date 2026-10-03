### Theory Concepts Involved
* **NFA (Nondeterministic Finite Automaton):** A finite state machine where for a particular state and input symbol, the next state may be nothing, one state or multiple states.
* **$\epsilon$-closure:** The set of all states reachable from a specific state by strictly following $\epsilon$ (epsilon/empty) transitions, including the state itself.
* **State Transition Formula:** To eliminate $\epsilon$-transitions, the new transition function $\delta'$ for a state $q$ and input symbol $a$ is calculated using the formula: $\delta'(q, a) = \epsilon\text{-closure}(\delta(\epsilon\text{-closure}(q), a))$.
* **Floyd-Warshall Algorithm (Transitive Closure):** A graph algorithm used here to efficiently compute the entire $\epsilon$-closure matrix by finding all direct and indirect $\epsilon$ paths between all pairs of nodes.

### Explanation of Logic
The goal is to bypass the need for $\epsilon$-jumps. To figure out where state $A$ can go on input `0` without using $\epsilon$, we trace a three-part journey:
1. Find everywhere state $A$ can sneak to using *only* $\epsilon$ (its $\epsilon$-closure). Let's say this reaches states $A$ and $B$.
2. From those states ($A$ and $B$), apply the actual input symbol `0`. Let's say this lands us on state $C$.
3. From state $C$, find everywhere it can sneak to using *only* $\epsilon$ again (the $\epsilon$-closure of $C$). Let's say this reaches $C$ and $D$.
Therefore, the new NFA will simply say: From $A$ on input `0`, directly go to $C$ and $D$. The code systematically applies this 3-step jump to every state and every alphabet symbol.

### How the Program Works
1. **Input & Initialization:** The program reads the number of states and alphabet symbols. It stores normal transitions in a 3D array `trans[state][symbol_index][target_state]` and $\epsilon$-transitions in a 2D boolean matrix `e_closure`.
2. **Finding all $\epsilon$-closures:** By default, `e_closure[i][i]` is set to `1` (a state can reach itself). The Floyd-Warshall nested loops iterate through all nodes to establish transitive $\epsilon$-paths (e.g., if $0 \xrightarrow{\epsilon} 1$ and $1 \xrightarrow{\epsilon} 2$, then $0 \xrightarrow{\epsilon} 2$).
3. **Applying the Formula:** A deeply nested loop structure evaluates $\delta'(q, a)$. 
    * It looks at starting state `i`.
    * It finds `j` (reachable via $\epsilon$ from `i`).
    * It finds `k` (reachable via alphabet `c` from `j`).
    * It finds `l` (reachable via $\epsilon$ from `k`).
    * It flags `new_trans[i][c][l] = 1`, combining the three legs of the journey into one direct jump.
4. **Output Generation:** The program formats the `new_trans` array into a readable NFA transition table, utilizing braces `{ }` to denote the sets of target states.

### Sample Input and Output

**Sample Input:**
```text
Enter the number of states: 3
Enter the number of alphabet symbols (excluding epsilon): 2
Enter the alphabet symbols (e.g., ab): ab
Enter the total number of transitions: 4
Enter transitions in format: from_state symbol to_state
(Use 'e' for epsilon. States should be 0 to 2)
0 e 1
1 a 2
2 e 0
2 b 1
```

**Output:**
```text
--- NFA without Epsilon Transitions ---
State               a                   b                   
------------------------------------------------------------
q0                  { q0 q1 q2 }        { - }               
q1                  { q0 q1 q2 }        { - }               
q2                  { q0 q1 q2 }        { q1 }              
```