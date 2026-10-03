#include <ctype.h>
#include <stdio.h>
#include <string.h>

int count;
char productions[20][20];

// Helper function to add a character to a set only if it doesn't already exist
void addToSet(char *set, char val) {
  for (int i = 0; i < strlen(set); i++) {
    if (set[i] == val)
      return;
  }
  int len = strlen(set);
  set[len] = val;
  set[len + 1] = '\0';
}

// Helper function to print sets beautifully
void printSet(char *set) {
  printf("{ ");
  for (int i = 0; i < strlen(set); i++) {
    printf("%c ", set[i]);
  }
  printf("}\n");
}

// Recursive function to find First of a symbol
void findFirst(char *firstSet, char c) {
  // If the symbol is a terminal (not an uppercase letter), First is the symbol
  // itself
  if (!isupper(c)) {
    addToSet(firstSet, c);
    return;
  }

  // Check all productions for the non-terminal
  for (int i = 0; i < count; i++) {
    if (productions[i][0] == c) {
      if (productions[i][2] == '#') {
        addToSet(firstSet, '#'); // '#' represents epsilon
      } else {
        // If it's not epsilon, evaluate the symbols on the RHS one by one
        for (int j = 2; productions[i][j] != '\0'; j++) {
          char tempFirst[20] = "";
          findFirst(tempFirst, productions[i][j]);

          int hasEpsilon = 0;
          for (int k = 0; k < strlen(tempFirst); k++) {
            if (tempFirst[k] == '#') {
              hasEpsilon = 1; // Mark that epsilon was found
            } else {
              addToSet(firstSet, tempFirst[k]); // Add non-epsilon symbols
            }
          }

          // If the current symbol doesn't derive epsilon, we stop going right
          if (!hasEpsilon)
            break;

          // If we reached the last symbol and all previous derived epsilon
          if (productions[i][j + 1] == '\0') {
            addToSet(firstSet, '#');
          }
        }
      }
    }
  }
}

// Recursive function to find Follow of a symbol
void findFollow(char *followSet, char c) {
  // If it's the start symbol, add '$'
  if (productions[0][0] == c) {
    addToSet(followSet, '$');
  }

  for (int i = 0; i < count; i++) {
    for (int j = 2; productions[i][j] != '\0'; j++) {
      // Find the character on the RHS
      if (productions[i][j] == c) {
        int next = j + 1;

        // Evaluate the First sets of the following symbols
        while (productions[i][next] != '\0') {
          char tempFirst[20] = "";
          findFirst(tempFirst, productions[i][next]);

          int hasEpsilon = 0;
          for (int k = 0; k < strlen(tempFirst); k++) {
            if (tempFirst[k] == '#') {
              hasEpsilon = 1;
            } else {
              addToSet(followSet, tempFirst[k]);
            }
          }

          if (!hasEpsilon)
            break; // Stop if the symbol cannot derive epsilon
          next++;
        }

        // If nothing follows 'c' or everything following 'c' derives epsilon,
        // then Follow(LHS) belongs in Follow(c).
        if (productions[i][next] == '\0' && productions[i][0] != c) {
          findFollow(followSet, productions[i][0]);
        }
      }
    }
  }
}

int main() {
  char nonTerminals[20];
  int ntCount = 0;

  printf("Enter the number of productions: ");
  scanf("%d", &count);

  printf("Enter productions (Format A=aB or A=# for epsilon):\n");
  for (int i = 0; i < count; i++) {
    scanf("%s", productions[i]);

    // Track unique non-terminals to print their First/Follow sets later
    int found = 0;
    for (int j = 0; j < ntCount; j++) {
      if (nonTerminals[j] == productions[i][0])
        found = 1;
    }
    if (!found) {
      nonTerminals[ntCount++] = productions[i][0];
    }
  }

  printf("\n--- First and Follow Sets ---\n");
  for (int i = 0; i < ntCount; i++) {
    char firstSet[20] = "";
    char followSet[20] = "";

    findFirst(firstSet, nonTerminals[i]);
    findFollow(followSet, nonTerminals[i]);

    printf("First(%c)  = ", nonTerminals[i]);
    printSet(firstSet);

    printf("Follow(%c) = ", nonTerminals[i]);
    printSet(followSet);
    printf("\n");
  }

  return 0;
}