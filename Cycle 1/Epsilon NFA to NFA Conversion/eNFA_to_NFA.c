#include <stdio.h>
#include <string.h>

int main() {
  int n, m, num_trans, u, v;
  char symbol;
  char alphabet[10];

  // Matrices to store transitions and closures
  int e_closure[20][20] = {0};     // epsilon closures
  int trans[20][10][20] = {0};     // original transitions on alphabets
  int new_trans[20][10][20] = {0}; // new NFA transitions

  printf("Enter the number of states: ");
  scanf("%d", &n);

  printf("Enter the number of alphabet symbols (excluding epsilon): ");
  scanf("%d", &m);

  printf("Enter the alphabet symbols (e.g., ab): ");
  scanf("%s", alphabet);

  // Every state is in its own epsilon closure
  for (int i = 0; i < n; i++) {
    e_closure[i][i] = 1;
  }

  printf("Enter the total number of transitions: ");
  scanf("%d", &num_trans);

  printf("Enter transitions in format: from_state symbol to_state\n");
  printf("(Use 'e' for epsilon. States should be 0 to %d)\n", n - 1);

  for (int i = 0; i < num_trans; i++) {
    // Space before %c ensures we ignore trailing spaces/newlines
    scanf("%d %c %d", &u, &symbol, &v);

    if (symbol == 'e') {
      e_closure[u][v] = 1; // It's an epsilon transition
    } else {
      // Find the index of the alphabet symbol
      for (int j = 0; j < m; j++) {
        if (alphabet[j] == symbol) {
          trans[u][j][v] = 1; // It's a normal alphabet transition
          break;
        }
      }
    }
  }

  // 1. Calculate the transitive closure for epsilon transitions (Floyd-Warshall
  // Algorithm)
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        // If there's a path from i to k and k to j, then i to j is reachable
        e_closure[i][j] =
            e_closure[i][j] || (e_closure[i][k] && e_closure[k][j]);
      }
    }
  }

  // 2. Compute new transitions for the NFA without epsilon
  // Formula: δ'(q, a) = ε-closure(δ(ε-closure(q), a))
  for (int i = 0; i < n; i++) {     // Starting state 'i'
    for (int c = 0; c < m; c++) {   // For each input symbol 'c'
      for (int j = 0; j < n; j++) { // State 'j' in ε-closure of 'i'
        if (e_closure[i][j]) {
          for (int k = 0; k < n;
               k++) { // State 'k' reachable from 'j' via symbol 'c'
            if (trans[j][c][k]) {
              for (int l = 0; l < n; l++) { // State 'l' in ε-closure of 'k'
                if (e_closure[k][l]) {
                  new_trans[i][c][l] = 1; // Add to new transitions
                }
              }
            }
          }
        }
      }
    }
  }

  // 3. Print the new NFA transition table
  printf("\n--- NFA without Epsilon Transitions ---\n");
  printf("%-20s", "State");
  for (int c = 0; c < m; c++) {
    printf("%-20c", alphabet[c]);
  }
  printf("\n------------------------------------------------------------\n");

  for (int i = 0; i < n; i++) {
    char state_str[20];
    sprintf(state_str, "q%d", i);
    printf("%-20s", state_str);
    for (int c = 0; c < m; c++) {
      char buffer[100];
      int pos = 0;
      pos += sprintf(buffer + pos, "{ ");
      int empty = 1;
      for (int j = 0; j < n; j++) {
        if (new_trans[i][c][j]) {
          pos += sprintf(buffer + pos, "q%d ", j);
          empty = 0;
        }
      }
      if (empty)
        pos += sprintf(buffer + pos, "- "); // Represent empty set
      sprintf(buffer + pos, "}");
      printf("%-20s", buffer);
    }
    printf("\n");
  }

  return 0;
}