#include <stdio.h>
#include <string.h>

char stack[50], input[50];
int top = 0, i = 0;

// Function to check the top of the stack and perform reductions
void check() {
  int reduced = 1;

  // Keep checking as long as reductions are happening (cascading reductions)
  while (reduced) {
    reduced = 0;

    // 1. Check for 'i' -> E (Identifier reduction)
    if (top >= 2 && stack[top - 1] == 'i') {
      stack[top - 1] = 'E';
      // input + i points to the remaining unparsed input
      printf("%-15s %-15s Reduce E -> i\n", stack, input + i);
      reduced = 1;
    }

    // 2. Check for E * E -> E (Multiplication reduction)
    else if (top >= 4 && stack[top - 3] == 'E' && stack[top - 2] == '*' &&
             stack[top - 1] == 'E') {
      stack[top - 3] = 'E';
      top -= 2;          // Pop two characters (* and E)
      stack[top] = '\0'; // Null terminate the new top
      printf("%-15s %-15s Reduce E -> E*E\n", stack, input + i);
      reduced = 1;
    }

    // 3. Check for E + E -> E (Addition reduction)
    else if (top >= 4 && stack[top - 3] == 'E' && stack[top - 2] == '+' &&
             stack[top - 1] == 'E') {
      // Precedence Handling / Lookahead:
      // If the next operator is '*', do not reduce '+' yet. Let the '*' shift.
      if (input[i] == '*') {
        break;
      }
      stack[top - 3] = 'E';
      top -= 2;
      stack[top] = '\0';
      printf("%-15s %-15s Reduce E -> E+E\n", stack, input + i);
      reduced = 1;
    }
  }
}

int main() {
  printf("Grammar:\nE -> E+E \nE -> E*E \nE -> i\n\n");
  printf("Enter input string (e.g., i+i*i): ");
  scanf("%s", input);

  // Append the end-of-input marker '$'
  strcat(input, "$");

  printf("\n%-15s %-15s %s\n", "Stack", "Input", "Action");
  printf("------------------------------------------------\n");

  // Initialize stack with '$'
  stack[0] = '$';
  stack[1] = '\0';
  top = 1;

  // Loop until we process all input characters (up to the '$' marker)
  while (i < strlen(input) - 1) {
    // Shift operation: Move the current input character to the stack
    stack[top] = input[i];
    stack[top + 1] = '\0';
    top++;

    // input + i + 1 gives the remaining input *after* the shift
    printf("%-15s %-15s Shift\n", stack, input + i + 1);
    i++; // Advance the input pointer

    // Check if a reduction is possible on the new stack state
    check();
  }

  // Validation: Stack should just contain "$E" and the next input should be "$"
  if (stack[1] == 'E' && stack[2] == '\0' && input[i] == '$') {
    printf("\n%-15s %-15s Accepted\n", stack, "$");
  } else {
    printf("\n%-15s %-15s Rejected: Syntax Error\n", stack, input + i);
  }

  return 0;
}