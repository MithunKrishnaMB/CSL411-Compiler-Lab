### Theory Concepts Involved
* **Lexical Analysis:** The first phase of a compiler, responsible for scanning the source program character by character and grouping them into meaningful sequences called lexemes.
* **Tokens:** The output of the lexical analyzer. A token represents a category of a lexeme (e.g., Identifier, Keyword, Operator, Constant, Special Character).
* **Deterministic Finite Automata (DFA) logic simulation:** While we aren't explicitly drawing a DFA, the logic of reading characters until a certain condition fails (like reading letters until a space or operator is hit) mimics DFA state transitions.
* **File Handling in C:** Reading from an external source file (`input.txt`) sequentially using pointers and character extraction functions.

### Explanation of Logic
The program reads a C source code file character by character. To achieve the main constraint of ignoring redundant spaces, tabs and newlines, it uses the built-in `isspace()` function which checks for `\n`, `\t` and ` ` (space) and simply skips them using the `continue` statement. 

When it encounters a valid character, it categorizes it based on predefined rules:
1. If it's a symbol like `+` or `=`, it is flagged as an operator.
2. If it's punctuation like `{` or `;`, it is flagged as a special character.
3. If it starts with a letter, it reads subsequent alphanumeric characters into a buffer. It then checks this buffer against a dictionary of standard C keywords. If a match is found, it's a keyword; otherwise, it's an identifier.
4. If it starts with a digit, it reads subsequent digits to form a constant.

### How the Program Works
1. **Initialization:** The program opens `input.txt` using `fopen()`. It defines a 2D array of strings containing the 32 standard C keywords in the `isKeyword()` function.
2. **Scanning:** A `while` loop runs with `fgetc()` extracting one character at a time until `EOF` (End of File) is reached.
3. **Skipping Whitespace:** The `isspace(ch)` condition intercepts any space, newline or tab and forces the loop to the next iteration, effectively ignoring them.
4. **Buffer Accumulation (Lookahead):** When an alphabet or digit is found, the program enters a secondary `while` loop to gather the full word or number into a `buffer`. 
5. **Backtracking (`ungetc`):** To know that a word or number has ended, the program accidentally reads the *first character of the next token* (e.g., reading the space after a word). The `ungetc(ch, fp)` function pushes that character back into the file stream so it isn't skipped in the next pass of the main `while` loop.
6. **Termination:** Once `EOF` is reached, `fclose()` releases the file pointer.

### Sample Input and Output

**Sample `input.txt`:**
```text
int main() {
    int sum = 10 + 20;
}
```

**Output:**
```text
Token               Type                
----------------------------------------
int                 Keyword             
main                Identifier          
(                   Special Character   
)                   Special Character   
{                   Special Character   
int                 Keyword             
sum                 Identifier          
=                   Operator            
10                  Constant            
+                   Operator            
20                  Constant            
;                   Special Character   
}                   Special Character   