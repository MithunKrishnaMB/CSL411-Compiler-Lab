#include <stdio.h>
#include <string.h>

// Global variables to store the automaton data
int nfa[10][5][10] = {0};      // nfa[state][alphabet][target_state]
int dfa_states[100][10] = {0}; // Stores which NFA states make up each DFA state
int dfa_trans[100][5] = {
    0}; // dfa_trans[dfa_state_index][alphabet] = target_dfa_state_index

int n, m;
char alphabet[5];

// Helper function to get the index of an alphabet symbol
int get_alpha_index(char a) {
  for (int i = 0; i < m; i++) {
    if (alphabet[i] == a)
      return i;
  }
  return -1;
}

// Function to check if two DFA states are identical
int is_equal(int state1[], int state2[]) {
  for (int i = 0; i < n; i++) {
    if (state1[i] != state2[i])
      return 0;
  }
  return 1;
}

// Function to add a newly discovered state to the DFA state list
// Returns the index of the state (either newly added or existing)
int add_dfa_state(int new_state[], int *num_dfa_states) {
  // Check if the state already exists in our recorded DFA states
  for (int i = 0; i < *num_dfa_states; i++) {
    if (is_equal(dfa_states[i], new_state)) {
      return i; // State already exists, return its index
    }
  }

  // If it doesn't exist, add it to the list
  for (int i = 0; i < n; i++) {
    dfa_states[*num_dfa_states][i] = new_state[i];
  }
  (*num_dfa_states)++;
  return (*num_dfa_states) - 1; // Return the index of the newly added state
}

int main() {
  int num_trans, u, v;
  char sym;

  printf("Enter number of NFA states: ");
  scanf("%d", &n);

  printf("Enter number of alphabet symbols: ");
  scanf("%d", &m);

  printf("Enter the alphabet symbols (e.g., ab): ");
  scanf("%s", alphabet);

  printf("Enter the total number of transitions: ");
  scanf("%d", &num_trans);

  printf("Enter transitions in format: from_state symbol to_state\n");
  for (int i = 0; i < num_trans; i++) {
    scanf("%d %c %d", &u, &sym, &v);
    int a_idx = get_alpha_index(sym);
    if (a_idx != -1) {
      nfa[u][a_idx][v] = 1; // Mark the NFA transition
    }
  }

  int num_dfa_states = 0;
  int processed_states = 0;

  // 1. Initialize DFA with the start state of NFA (State q0)
  int start_state[10] = {0};
  start_state[0] = 1;
  add_dfa_state(start_state, &num_dfa_states);

  // 2. Process DFA states one by one (Subset Construction Algorithm)
  while (processed_states < num_dfa_states) {

    // For each input symbol in the alphabet
    for (int a = 0; a < m; a++) {
      int new_state[10] = {0};
      int is_empty = 1; // Flag to track if the new state is a dead/empty state

      // For every NFA state that is part of the current DFA state
      for (int i = 0; i < n; i++) {
        if (dfa_states[processed_states][i] == 1) {

          // Find all NFA transitions from state 'i' using symbol 'a'
          for (int j = 0; j < n; j++) {
            if (nfa[i][a][j] == 1) {
              new_state[j] = 1; // Add target NFA state to the new DFA state
              is_empty = 0;
            }
          }
        }
      }

      // If the transition leads to a valid subset of states
      if (!is_empty) {
        int target_idx = add_dfa_state(new_state, &num_dfa_states);
        dfa_trans[processed_states][a] =
            target_idx; // Record the DFA transition
      } else {
        dfa_trans[processed_states][a] =
            -1; // -1 represents a Dead State (empty set)
      }
    }
    processed_states++; // Move to the next DFA state in the queue
  }

  // 3. Print the resulting DFA Transition Table
  printf("\n--- DFA Transition Table ---\n");
  printf("%-20s", "State");
  for (int a = 0; a < m; a++)
    printf("%-20c", alphabet[a]);
  printf("\n------------------------------------------------------------\n");

  for (int i = 0; i < num_dfa_states; i++) {
    char buffer[100];
    int pos = 0;
    // Print the source DFA state
    pos += sprintf(buffer + pos, "{ ");
    for (int j = 0; j < n; j++) {
      if (dfa_states[i][j])
        pos += sprintf(buffer + pos, "q%d ", j);
    }
    sprintf(buffer + pos, "}");
    printf("%-20s", buffer);

    // Print the target DFA states for each alphabet symbol
    for (int a = 0; a < m; a++) {
      int target = dfa_trans[i][a];
      pos = 0;
      if (target != -1) {
        pos += sprintf(buffer + pos, "{ ");
        for (int j = 0; j < n; j++) {
          if (dfa_states[target][j])
            pos += sprintf(buffer + pos, "q%d ", j);
        }
        sprintf(buffer + pos, "}");
        printf("%-20s", buffer);
      } else {
        printf("%-20s", "{ - }"); // Empty subset / Dead State
      }
    }
    printf("\n");
  }

  return 0;
}