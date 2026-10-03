### Theory Concepts Involved
* **First Sets:** A set of terminals that begin the strings derivable from a given non-terminal. It tells the parser which production to choose based on the incoming token.
* **Follow Sets:** A set of terminals that can appear immediately to the right of a non-terminal in some valid derived string. It tells the parser when to use an $\epsilon$ (epsilon) production or flag a syntax error.
* **Top-Down Parsing (LL(1)):** Computing First and Follow sets is a prerequisite for constructing predictive parsing tables used by Top-Down parsers.
* **Epsilon ($\epsilon$) Derivations:** If a non-terminal can derive an empty string (represented here as `#`), it triggers specific fallback rules in both First and Follow set calculations.

### Explanation of Logic
The code relies on recursive evaluation of Context-Free Grammar rules:
* **FIRST:** If we need the First set of `A`, we look at what `A` produces (`A=...`). If the Right Hand Side (RHS) starts with a terminal, we record it. If it starts with another non-terminal `B`, we calculate First(`B`). If First(`B`) contains $\epsilon$, we must also look at the next symbol in `A`'s production.
* **FOLLOW:** If we need the Follow set of `B`, we search the RHS of all productions to see where `B` is used. If we find `A=xBy`, the symbols that follow `B` are determined by First(`y`). If `y` can derive $\epsilon$ or if there is nothing after `B` (e.g., `A=xB`), then whatever follows `A` will naturally follow `B`. Thus, Follow(`A`) is added to Follow(`B`).

### How the Program Works
1. **Input:** The program accepts the number of productions and the grammar rules themselves. It strictly parses them assuming index `0` is the Non-Terminal, index `1` is `=` and indices `2` onwards form the RHS.
2. **Set Tracking:** The `addToSet` function acts like a mathematical union operation; it prevents duplicate characters from being inserted into the result arrays.
3. **Execution of `findFirst`:** The function checks if the requested symbol is uppercase. If not, it's a terminal and returns itself. Otherwise, it iteratively runs through all characters of the corresponding RHS until it finds a sequence that *doesn't* produce epsilon.
4. **Execution of `findFollow`:** It first checks if the target is the start symbol (the first character of the first production) and adds the end-of-input marker `$`. Then it scans every RHS for the target symbol. Upon finding it, it triggers `findFirst` on the subsequent characters. If those derive epsilon or if the target is the last character, it triggers `findFollow` on the LHS.

### Sample Input and Output

**Sample Input:**
*(Representing a classic expression grammar: E -> TR, R -> +TR | #, T -> i | (E) )*
```text
Enter the number of productions: 5
Enter productions (Format A=aB or A=# for epsilon):
E=TR
R=+TR
R=#
T=i
T=(E)
```

**Sample Output:**
```text
--- First and Follow Sets ---
First(E)  = { i ( }
Follow(E) = { $ ) }

First(R)  = { + # }
Follow(R) = { $ ) }

First(T)  = { i ( }
Follow(T) = { + $ ) }
```