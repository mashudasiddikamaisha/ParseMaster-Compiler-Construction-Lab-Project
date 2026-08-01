# Compiler Architecture

## Overview

The compiler follows a traditional multi-phase architecture. Each phase performs a specific task and passes its output to the next stage. This modular design makes the compiler easier to develop, debug, and extend.

```
                Source Program
                      │
                      ▼
              +----------------+
              |     Lexer      |
              |    (Flex)      |
              +----------------+
                      │
             Stream of Tokens
                      │
                      ▼
              +----------------+
              |     Parser     |
              |    (Bison)     |
              +----------------+
                      │
          Abstract Syntax Tree (AST)
                      │
          ┌───────────┴───────────┐
          ▼                       ▼
+------------------+     +------------------+
|   Symbol Table   |     | Semantic Analyzer|
+------------------+     +------------------+
          │                       │
          └───────────┬───────────┘
                      ▼
            Intermediate Representation
            (Three Address Code - TAC)
                      │
                      ▼
               Compiler Output
```

---

## Compiler Pipeline

### 1. Lexical Analysis

**Module:** `src/lexer/`

The lexical analyzer reads the source program character by character and groups them into meaningful tokens.

Responsibilities:

- Recognizes keywords (`int`, `float`, `bool`, `if`, `else`, `while`, `print`)
- Identifies identifiers
- Recognizes integer and floating-point literals
- Detects boolean literals (`true`, `false`)
- Recognizes operators and punctuation
- Ignores whitespace and comments
- Reports invalid characters

**Output:** Token stream for the parser.

---

### 2. Syntax Analysis

**Module:** `src/parser/`

The parser validates whether the token sequence follows the grammar of the language.

Responsibilities:

- Parses declarations
- Parses assignments
- Parses arithmetic expressions
- Parses conditional statements
- Parses loops
- Parses print statements
- Constructs the Abstract Syntax Tree (AST)

**Output:** Abstract Syntax Tree (AST).

---

### 3. Abstract Syntax Tree (AST)

**Module:** `src/ast/`

The AST provides a hierarchical representation of the program structure.

Each node represents a language construct such as:

- Variable declarations
- Assignments
- Expressions
- If-Else statements
- While loops
- Print statements

The AST serves as the primary input for later compiler phases.

---

### 4. Symbol Table

**Module:** `src/symbol_table/`

The symbol table stores information about identifiers encountered during compilation.

Stored information includes:

- Identifier name
- Data type
- Scope
- Declaration line number

The symbol table supports semantic analysis by allowing identifier lookup and validation.

---

### 5. Semantic Analysis

**Module:** `src/semantic/`

The semantic analyzer verifies that the program is logically correct beyond grammatical correctness.

Typical checks include:

- Multiple declarations
- Undeclared variables
- Type compatibility
- Assignment validation
- Expression type checking

Any semantic errors are reported with meaningful messages.

---

### 6. Intermediate Code Generation

**Module:** `src/tac/`

After successful semantic analysis, the compiler generates Three Address Code (TAC).

Responsibilities:

- Generates temporary variables
- Produces intermediate instructions
- Represents expressions in TAC form
- Simplifies later optimization or code generation

Example:

```
a = b + c * d
```

Generated TAC:

```
t1 = c * d
t2 = b + t1
a = t2
```

---

## Module Interaction

```
main.c
   │
   ▼
Lexer
   │
   ▼
Parser
   │
   ▼
AST
   │
   ├────────► Symbol Table
   │
   ├────────► Semantic Analyzer
   │
   ▼
Three Address Code Generator
   │
   ▼
Compiler Output
```

---

## Design Principles

The compiler is designed with the following goals:

- **Modularity:** Each compiler phase is implemented independently.
- **Maintainability:** Components can be modified without affecting the entire system.
- **Extensibility:** New language features can be added with minimal changes.
- **Clear Separation of Responsibilities:** Every module performs one well-defined task.

---

## Project Directory Structure

```
src/
├── ast/
├── lexer/
├── parser/
├── semantic/
├── symbol_table/
├── tac/
└── main.c
```

Each directory corresponds to one phase of the compiler pipeline, making the project organized and easy to navigate.