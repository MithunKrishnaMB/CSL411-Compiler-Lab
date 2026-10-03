### Theory Concepts Involved
* **NFA with ε-transitions:** A Nondeterministic Finite Automaton (NFA) that allows transitions from one state to another without consuming any input symbol (represented by Epsilon/ε).
* **ε-closure:** The set of all states reachable from a given state using zero or more ε-transitions. A fundamental rule of ε-closure is that a state is always a member of its own ε-closure.
* **Graph Traversal (DFS):** In this context, states act as nodes/vertices and ε-transitions act as directed edges. We use a Depth First Search (DFS) algorithm to explore all reachable nodes from a starting node.
* **Adjacency Matrix:** A 2D array used to represent the finite automaton's state connections, making it easy to look up if a transition exists between state `u` and state `v`.

### Explanation of Logic
The problem requires us to find paths connected exclusively by `ε` (represented as `e`). The logic ignores any standard alphabet transitions (like `a` or `b`) because they do not contribute to an ε-closure.
We represent the ε-transitions as a directed graph using an adjacency matrix called `epsilon_graph`. If there is an ε-transition from $q_0$ to $q_1$, we set `epsilon_graph[0][1] = 1`. 
To find the closure for a specific state, we trigger a recursive DFS. The DFS marks the current state as visited (preventing infinite loops if there are cyclical ε-transitions, e.g., $q_0 \to q_1 \to q_0$) and then recursively calls itself on any connected state that hasn't been visited yet.

### How the Program Works
1. **Initialization:** The program prompts the user for the total number of states (`n`) and total transitions. It initializes an $n \times n$ adjacency matrix with zeros.
2. **Filtering Input:** It loops to read each transition. When reading `from_state symbol to_state`, it specifically checks if `symbol == 'e'`. If it is, it updates the adjacency matrix; otherwise, it safely ignores it.
3. **Calculating Closure:** A `for` loop iterates through each state `i` from $0$ to $n-1$.
4. **Resetting Visited Flags:** Before calling the DFS for state `i`, the `visited` array is wiped clean (all set to 0) so the traversal starts fresh without being blocked by previous iterations.
5. **DFS Execution:** The `find_closure(i)` function is called. It prints `i`, marks `visited[i] = 1` and loops through all possible states to find an outgoing edge `epsilon_graph[i][j] == 1`. If an unvisited edge is found, it traverses down that path recursively.

### Sample Input and Output

**Sample Input:**
```text
Enter the number of states: 4
Enter the total number of transitions: 4
Enter transitions in format: from_state symbol to_state
(Use 'e' for epsilon. States should be integers 0 to 3)
0 e 1
1 e 2
2 a 3
0 e 3
```

**Output:**
```text
--- Epsilon Closures ---
e-closure(q0): { q0 q1 q2 q3 }
e-closure(q1): { q1 q2 }
e-closure(q2): { q2 }
e-closure(q3): { q3 }
```