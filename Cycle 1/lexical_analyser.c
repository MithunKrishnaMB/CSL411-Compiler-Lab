#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to check if a given string is a C keyword
int isKeyword(char buffer[]) {
  // Array of standard C keywords
  char keywords[32][10] = {
      "auto",     "break",  "case",    "char",   "const",    "continue",
      "default",  "do",     "double",  "else",   "enum",     "extern",
      "float",    "for",    "goto",    "if",     "int",      "long",
      "register", "return", "short",   "signed", "sizeof",   "static",
      "struct",   "switch", "typedef", "union",  "unsigned", "void",
      "volatile", "while"};

  // Compare buffer against all keywords
  for (int i = 0; i < 32; ++i) {
    if (strcmp(keywords[i], buffer) == 0) {
      return 1; // It is a keyword
    }
  }
  return 0; // It is not a keyword
}

int main() {
  char ch, buffer[30], operators[] = "+-*/%=";
  FILE *fp;
  int i, j = 0;

  // Open the source code file in read mode
  fp = fopen("input.txt", "r");
  if (fp == NULL) {
    printf("Error: Cannot open input.txt\n");
    exit(0);
  }

  printf("%-20s%-20s\n", "Token", "Type");
  printf("----------------------------------------\n");

  // Read file character by character until End Of File (EOF)
  while ((ch = fgetc(fp)) != EOF) {

    // 1. Ignore redundant spaces, tabs and newlines
    if (isspace(ch)) {
      continue; // Skip to the next iteration
    }

    // 2. Check for operators
    for (i = 0; i < 6; ++i) {
      if (ch == operators[i]) {
        printf("%-20c%-20s\n", ch, "Operator");
        break;
      }
    }

    // 3. Check for special characters (punctuation)
    if (ch == ';' || ch == ',' || ch == '{' || ch == '}' || ch == '(' ||
        ch == ')') {
      printf("%-20c%-20s\n", ch, "Special Character");
    }

    // 4. Check for Identifiers and Keywords
    if (isalpha(ch)) {
      buffer[j++] = ch;
      ch = fgetc(fp); // Read next character

      // Continue reading as long as it's alphanumeric
      while (isalnum(ch)) {
        buffer[j++] = ch;
        ch = fgetc(fp);
      }
      buffer[j] = '\0'; // Null-terminate the string
      j = 0;            // Reset buffer index for next use

      // Classify the gathered string
      if (isKeyword(buffer) == 1) {
        printf("%-20s%-20s\n", buffer, "Keyword");
      } else {
        printf("%-20s%-20s\n", buffer, "Identifier");
      }

      // Push the last read character (which failed the isalnum check) back into
      // the stream
      ungetc(ch, fp);
    }

    // 5. Check for numeric constants
    else if (isdigit(ch)) {
      buffer[j++] = ch;
      ch = fgetc(fp);

      // Continue reading as long as it's a digit
      while (isdigit(ch)) {
        buffer[j++] = ch;
        ch = fgetc(fp);
      }
      buffer[j] = '\0';
      j = 0;

      printf("%-20s%-20s\n", buffer, "Constant");

      // Push the non-digit character back into the stream
      ungetc(ch, fp);
    }
  }

  fclose(fp); // Close the file
  return 0;
}