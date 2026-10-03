#include <stdio.h>
#include <string.h>

char input[100];
int cursor = 0;
int error = 0;

// Function prototypes for non-terminals
void E();
void EP(); // Represents E'
void T();
void TP(); // Represents T'
void F();

// Helper function to match terminals
void match(char expected) {
  if (input[cursor] == expected) {
    cursor++; // Advance input pointer
  } else {
    error = 1; // Flag an error
  }
}

// E -> T E'
void E() {
  printf("E  -> T E'\n");
  T();
  EP();
}

// E' -> + T E' | epsilon
void EP() {
  if (input[cursor] == '+') {
    printf("E' -> + T E'\n");
    match('+');
    T();
    EP();
  } else {
    // Epsilon transition (do nothing, let it return)
    printf("E' -> epsilon\n");
  }
}

// T -> F T'
void T() {
  printf("T  -> F T'\n");
  F();
  TP();
}

// T' -> * F T' | epsilon
void TP() {
  if (input[cursor] == '*') {
    printf("T' -> * F T'\n");
    match('*');
    F();
    TP();
  } else {
    // Epsilon transition
    printf("T' -> epsilon\n");
  }
}

// F -> ( E ) | i
void F() {
  if (input[cursor] == 'i') {
    printf("F  -> i\n");
    match('i');
  } else if (input[cursor] == '(') {
    printf("F  -> ( E )\n");
    match('(');
    E();
    match(')');
  } else {
    error = 1; // Unrecognized character
  }
}

int main() {
  printf("Grammar for Arithmetic Expressions:\n");
  printf("E  -> T E'\n");
  printf("E' -> + T E' | epsilon\n");
  printf("T  -> F T'\n");
  printf("T' -> * F T' | epsilon\n");
  printf("F  -> ( E ) | i\n\n");

  printf("Enter the input string (use 'i' for identifiers): ");
  scanf("%s", input);

  printf("\n--- Parsing Steps ---\n");
  E(); // Start parsing from the start symbol

  // Validation: The entire string must be consumed and no errors encountered
  if (cursor == strlen(input) && error == 0) {
    printf("\nResult: String successfully parsed. ACCEPTED.\n");
  } else {
    printf("\nResult: Syntax Error. REJECTED.\n");
  }

  return 0;
}