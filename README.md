# ParseMaster - Compiler Construction Lab Project

---

# Team Members

| Name | Responsibilities | ID | GitHub |
|------|------------------| -- | ------ | 
| Mashuda Siddika Maisha | Lexer, Parser, Project Integration | 231-115-119 | @mashudasiddikamaisha |
| Nusrath Jahan Nowshin | Abstract Syntax Tree (AST) , Symbol Table | 231-115-088 | @Nowshin03 |
| Najmun Nahar | Three Address Code (TAC) | 231-115-112 | @najmuntushi-hue

---

## Project Summary

ParseMaster is a simple compiler developed as part of the Compiler Construction Lab course. The compiler is implemented using **Flex** and **Bison** and supports a small custom programming language with basic programming constructs.

The project is divided into six major compiler phases:

- Lexical Analysis
- Syntax Analysis
- Abstract Syntax Tree (AST)
- Symbol Table
- Semantic Analysis
- Three Address Code (TAC) Generation

The compiler recognizes declarations, assignments, arithmetic expressions, relational and logical expressions, print statements, conditional statements, and loops.

---

# Features

Current features include:

- Lexical analysis using Flex
- Syntax analysis using Bison
- Abstract Syntax Tree (AST) generation
- Support for:
  - Variable declarations
  - Assignments
  - Arithmetic expressions
  - Relational expressions
  - Logical expressions
  - print statements
  - if statements
  - if-else statements
  - while loops
- Syntax error reporting with line numbers
- Basic syntax error recovery

Modules currently under development:

- Symbol Table
- Semantic Analysis
- Three Address Code (TAC) Generation

---

# Build Instructions

## Requirements

- GCC
- Flex
- Bison
- GNU Make

### Ubuntu

Install the required packages:

```bash
sudo apt update
sudo apt install flex bison build-essential make
```

---

## Build

Clone the repository:

```bash
git clone https://github.com/mashudasiddikamaisha/ParseMaster-Compiler-Construction-Lab-Project.git
```

Enter the project directory:

```bash
cd ParseMaster-Compiler-Construction-Lab-Project
```

Compile the project:

```bash
make
```

To clean generated files:

```bash
make clean
```

---

# Usage Instructions

Run the compiler with an input source file:

```bash
./compiler < examples/full_program.txt
```

Example:

```bash
./compiler < examples/arithmetic.txt
```

If the program is syntactically correct, the compiler prints:

- Parsing status
- Abstract Syntax Tree (AST)

---

# Project Structure

```
src/
├── ast/
├── lexer/
├── parser/
├── semantic/
├── symbol_table/
├── tac/
└── main.c

examples/
```



# Technologies Used

- C
- Flex
- Bison
- GCC
- GNU Make

---

# Future Work

- Complete Symbol Table
- Implement Semantic Analysis
- Generate Three Address Code (TAC)
- Improve AST visualization
- Enhanced error reporting