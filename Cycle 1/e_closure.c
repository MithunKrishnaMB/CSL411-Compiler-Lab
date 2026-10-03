#include <stdio.h>

// Global variables for simplicity in recursive function access
int n;                     // Total number of states
int epsilon_graph[20][20]; // Adjacency matrix to store epsilon transitions
int visited[20]; // Array to keep track of visited states during traversal to
                 // avoid infinite loops

// Recursive Depth First Search (DFS) function to find reachable states via
// epsilon transitions
void find_closure(int state) {
  // A state is always in its own closure. Print it and mark as visited.
  printf("q%d ", state);
  visited[state] = 1;

  // Check all other states to see if there is an epsilon transition to them
  for (int i = 0; i < n; i++) {
    // If there is an epsilon transition AND the state hasn't been visited yet
    if (epsilon_graph[state][i] == 1 && !visited[i]) {
      find_closure(i); // Recursively find the closure of the connected state
    }
  }
}

int main() {
  int transitions, u, v;
  char symbol;

  printf("Enter the number of states: ");
  scanf("%d", &n);

  // Initialize the adjacency matrix to 0 (no transitions initially)
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      epsilon_graph[i][j] = 0;
    }
  }

  printf("Enter the total number of transitions: ");
  scanf("%d", &transitions);

  printf("Enter transitions in format: from_state symbol to_state\n");
  printf("(Use 'e' for epsilon. States should be integers 0 to %d)\n", n - 1);

  // Read all transitions
  for (int i = 0; i < transitions; i++) {
    // Note: The space before %c ensures we ignore whitespace/newlines from
    // previous inputs
    scanf("%d %c %d", &u, &symbol, &v);

    // We only care about epsilon transitions for finding epsilon closure
    if (symbol == 'e') {
      epsilon_graph[u][v] = 1; // Mark the directed edge in our matrix
    }
  }

  printf("\n--- Epsilon Closures ---\n");

  // Calculate and print the epsilon closure for each state sequentially
  for (int i = 0; i < n; i++) {
    // Reset the visited array to 0 before calculating closure for a new state
    for (int j = 0; j < n; j++) {
      visited[j] = 0;
    }

    printf("e-closure(q%d): { ", i);
    find_closure(i); // Start the recursive DFS traversal from state i
    printf("}\n");
  }

  return 0;
}