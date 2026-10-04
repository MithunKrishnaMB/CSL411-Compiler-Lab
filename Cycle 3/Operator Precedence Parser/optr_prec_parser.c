#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Operator Precedence Table for +, *, i (id), $
// Indices: 0 -> +, 1 -> *, 2 -> i, 3 -> $
char table[4][4] = {      // +    * i$
    {'>', '<', '<', '>'}, // +
    {'>', '>', '<', '>'}, // *
    {'>', '>', 'e', '>'}, // i
    {'<', '<', '<', 'A'}  // $  (A = Accept, e = Error)
}
;

// Function to map a character to its corresponding matrix index
int getIndex(char c) {
  switch (c) {
  case '+':
    return 0;
  case '*':
    return 1;
  case 'i':
    return 2;
  case '$':
    return 3;
  default:
    return -1;
  }
}

int main() {
  char input[30], stack[30];
  int i = 0, top = 0;

  printf("Enter the input string (use 'i' for id, append $ at end): ");
  scanf("%s", input);

  // Initialize stack with end marker '$'
  stack[top] = '$';
  stack[top + 1] = '\0';

  printf("\n%-15s %-15s %s\n", "Stack", "Input", "Action");
  printf("------------------------------------------------\n");

  while (1) {
    // In Operator Precedence Parsing, non-terminals (like 'E') are ignored
    // when checking precedence. We find the topmost terminal on the stack.
    int top_term_idx = top;
    while (top_term_idx >= 0 && stack[top_term_idx] == 'E') {
      top_term_idx--;
    }

    char a = stack[top_term_idx]; // Topmost terminal on stack
    char b = input[i];            // Current input symbol

    int row = getIndex(a);
    int col = getIndex(b);

    if (row == -1 || col == -1) {
      printf("Error: Invalid symbol encountered.\n");
      break;
    }

    char rel = table[row][col];

    // Print current state before taking action
    printf("%-15s %-15s ", stack, &input[i]);

    if (rel == '<' || rel == '=') {
      printf("Shift\n");
      stack[++top] = b; // Push input symbol to stack
      stack[top + 1] = '\0';
      i++; // Advance input pointer
    } else if (rel == '>') {
      printf("Reduce\n");
      // Basic reduction logic for 'i' -> E and 'E+E'/'E*E' -> E
      if (stack[top] == 'i') {
        stack[top] = 'E'; // Reduce identifier to non-terminal E
      } else if (top >= 2 && stack[top - 2] == 'E' && stack[top] == 'E' &&
                 (stack[top - 1] == '+' || stack[top - 1] == '*')) {
        top = top - 2;    // Pop two symbols, leaving one
        stack[top] = 'E'; // Replace the handle with E
        stack[top + 1] = '\0';
      } else {
        printf("\nError: Invalid syntax. Cannot reduce.\n");
        break;
      }
    } else if (rel == 'A') {
      printf("Accepted\n");
      break;
    } else {
      printf("Error: Invalid transition.\n");
      break;
    }
  }

  return 0;
}