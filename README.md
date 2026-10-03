# CSL411 Compiler Lab

This repository contains my practice implementations for the **CSL411 Compiler Lab** course. It serves as a study and preparation resource for the upcoming university lab examination.

## Repository Contents

The repository is structured based on the lab cycle experiments provided in the course syllabus (`Lab Cycle.pdf`). For each implemented algorithm, there is a C source file along with a corresponding Markdown (`.md`) documentation file containing the theoretical concepts, logic explanation and perfectly aligned sample input/output.

Currently, the repository covers the core concepts from **Cycle 1** (Automata Theory & Lexical Analysis) and **Cycle 3** (Syntax Analysis & Parsing).

### Cycle 1
This directory contains C implementations for introductory compiler phases and finite automata transformations:
- **Lexical Analyzer** (`lexical_analyser.c`): A custom lexical analyzer in C that categorizes tokens and ignores redundant spaces, tabs and newlines.
- **$\epsilon$-Closure** (`e_closure.c`): Computes the epsilon-closure of all states in a given NFA.
- **$\epsilon$-NFA to NFA** (`eNFA_to_NFA.c`): Converts an NFA with $\epsilon$-transitions to an equivalent NFA without $\epsilon$-transitions.
- **NFA to DFA** (`NFA_to_DFA.c`): Converts a Non-deterministic Finite Automaton (NFA) to a Deterministic Finite Automaton (DFA) using subset construction.
- **DFA Minimization** (`min_DFA.c`): Minimizes a given DFA using the Myhill-Nerode (table-filling) algorithm.

### Cycle 3
This directory focuses on various parsing techniques and grammatical computations:
- **Operator Precedence Parser** (`optr_prec_parser.c`): A bottom-up parser using a predefined operator precedence matrix.
- **First and Follow Sets** (`first_follow.c`): Computes the First and Follow sets for a given context-free grammar.
- **Recursive Descent Parser** (`rec_desc_parser.c`): A top-down predictive parser that recursively evaluates arithmetic expressions.
- **Shift Reduce Parser** (`shift_red_parser.c`): A basic bottom-up parser simulating shift and reduce actions using a stack.

## Work in Progress

The implementation of this repository is not yet complete. The following lab cycles will be added at a later time:
- **Cycle 2:** Implementations using the LEX and YACC tools (calculators, variable recognition, syntax trees, etc).
- **Cycle 4:** Intermediate code generation and compiler backend assembly generation (8086).

## Usage

Each C program can be compiled using a standard C compiler (e.g., `gcc <filename>.c`) and run directly from the terminal. Make sure to refer to the corresponding `.md` file for each program to understand the expected input format, terminal interaction and theoretical background.
