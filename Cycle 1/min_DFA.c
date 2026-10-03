#include <stdio.h>
#include <string.h>
// Helper function to find the index of an alphabet symbol
int get_alpha_index(char a, char alphabet[], int m) {
  for (int i = 0; i < m; i++) {
    if (alphabet[i] == a)
      return i;
  }
  return -1;
}

int main() {
  int n, m, num_trans, num_final, u, v;
  char sym;
  char alphabet[10];

  int dfa_trans[20][10] = {
      0};                 // Transitions: [state][symbol_index] = target_state
  int is_final[20] = {0}; // Array to flag final states
  int dist[20][20] = {0}; // Table to mark distinguishable states
  int rep[20];            // Representative state for each equivalence class

  // 1. Read DFA Properties
  printf("Enter number of states: ");
  scanf("%d", &n);

  printf("Enter number of alphabet symbols: ");
  scanf("%d", &m);

  printf("Enter the alphabet symbols (e.g., ab): ");
  scanf("%s", alphabet);

  printf("Enter number of final states: ");
  scanf("%d", &num_final);

  if (num_final > 0) {
    printf("Enter the final states (space separated): ");
    for (int i = 0; i < num_final; i++) {
      int f;
      scanf("%d", &f);
      is_final[f] = 1;
    }
  }

  printf("Enter total number of transitions: ");
  scanf("%d", &num_trans);

  printf("Enter transitions in format: from_state symbol to_state\n");
  for (int i = 0; i < num_trans; i++) {
    scanf("%d %c %d", &u, &sym, &v);
    int a_idx = get_alpha_index(sym, alphabet, m);
    if (a_idx != -1) {
      dfa_trans[u][a_idx] = v;
    }
  }

  // 2. Table-Filling Algorithm (Myhill-Nerode)
  // Step A: Mark pairs where one is a final state and the other is not
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (is_final[i] != is_final[j]) {
        dist[i][j] = 1;
        dist[j][i] = 1;
      }
    }
  }

  // Step B: Iteratively mark pairs whose transitions lead to distinguishable
  // states
  int changed = 1;
  while (changed) {
    changed = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < i; j++) {
        // If they are not currently marked distinguishable
        if (dist[i][j] == 0) {
          // Check transitions for all alphabet symbols
          for (int a = 0; a < m; a++) {
            int target_i = dfa_trans[i][a];
            int target_j = dfa_trans[j][a];

            if (dist[target_i][target_j] == 1) {
              dist[i][j] = 1;
              dist[j][i] = 1;
              changed = 1; // A new pair was marked, run the loop again
              break;
            }
          }
        }
      }
    }
  }

  // 3. Group Indistinguishable States
  // Initialize each state as its own representative
  for (int i = 0; i < n; i++) {
    rep[i] = i;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (dist[i][j] == 0) { // i and j are indistinguishable
        int rep_i = rep[i];
        int rep_j = rep[j];
        // Merge state i's class into state j's class
        for (int k = 0; k < n; k++) {
          if (rep[k] == rep_i) {
            rep[k] = rep_j;
          }
        }
      }
    }
  }

  // 4. Output the Minimized DFA
  printf("\n--- Minimized DFA Transition Table ---\n");
  printf("%-20s", "State");
  for (int a = 0; a < m; a++) {
    printf("%-20c", alphabet[a]);
  }
  printf("\n------------------------------------------------------------\n");

  for (int i = 0; i < n; i++) {
    // Only print if state 'i' is the representative of its equivalence class
    if (rep[i] == i) {
      char buffer[100];
      int pos = 0;

      // Print the merged state (e.g., { q0 q1 })
      pos += sprintf(buffer + pos, "{ ");
      for (int k = 0; k < n; k++) {
        if (rep[k] == i)
          pos += sprintf(buffer + pos, "q%d ", k);
      }
      sprintf(buffer + pos, "}");
      if (is_final[i])
        strcat(buffer, "*"); // denote final state
      printf("%-20s", buffer);

      // Print transitions for this representative state
      for (int a = 0; a < m; a++) {
        int target = dfa_trans[i][a];
        int target_rep = rep[target]; // Get the class of the target

        pos = 0;
        pos += sprintf(buffer + pos, "{ ");
        for (int k = 0; k < n; k++) {
          if (rep[k] == target_rep)
            pos += sprintf(buffer + pos, "q%d ", k);
        }
        sprintf(buffer + pos, "}");
        printf("%-20s", buffer);
      }
      printf("\n");
    }
  }

  return 0;
}