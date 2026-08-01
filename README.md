# ParseMaster - Compiler Construction Lab Project

A simple compiler for a small custom programming language, built with **Flex** and **Bison** as part of the Compiler Construction Lab course. ParseMaster implements the full front-end pipeline: lexical analysis, parsing, AST construction, symbol table management, semantic analysis, and three-address code (TAC) generation.

---

## Team Members

| Name | Responsibilities | ID | GitHub |
|------|------------------|------------|--------|
| Mashuda Siddika Maisha | Lexer, Parser, Project Integration | 231-115-119 | [@mashudasiddikamaisha](https://github.com/mashudasiddikamaisha) |
| Nusrath Jahan Nowshin | Abstract Syntax Tree (AST), Symbol Table | 231-115-088 | [@Nowshin03](https://github.com/Nowshin03) |
| Najmun Nahar | Semantic Analysis, Three Address Code (TAC) Generation | 231-115-112 | [@najmuntushi-hue](https://github.com/najmuntushi-hue) |

---

## Project Summary

ParseMaster is a compiler that processes a small imperative language supporting variable declarations, assignments, arithmetic/relational/logical expressions, `print` statements, `if`/`if-else` statements, and `while` loops.

The compiler is organized into six phases:

1. **Lexical Analysis** — tokenizes source code (Flex)
2. **Syntax Analysis** — validates grammar and builds parse structure (Bison)
3. **Abstract Syntax Tree (AST)** — hierarchical program representation
4. **Symbol Table** — tracks identifiers, types, scope, and declaration line
5. **Semantic Analysis** — type checking, undeclared/redeclared variable detection
6. **Three Address Code (TAC) Generation** — intermediate code with temporaries and labels

---

## Features

- Lexical analysis using Flex (keywords, identifiers, int/float/bool literals, operators)
- Syntax analysis using Bison with syntax error reporting and recovery (reports line numbers, continues parsing after an error)
- Abstract Syntax Tree (AST) generation and pretty-printing
- Symbol table with name, type, declaration line, and scope
- Semantic analysis: type-mismatch detection (e.g. assigning `int` to `bool`), undeclared-variable checks
- Three Address Code (TAC) generation with temporaries (`t1`, `t2`, ...) and labels (`L1`, `L2`, ...) for control flow
- Support for:
  - Variable declarations (`int`, `float`, `bool`)
  - Assignments
  - Arithmetic expressions (`+ - * / %`)
  - Relational expressions (`< > <= >= == !=`)
  - Logical expressions (`&& || !`)
  - `print` statements
  - `if` / `if-else` statements
  - `while` loops

---

## Language Grammar (summary)

```
program          → statement_list
statement        → declaration | assignment | if_statement
                 | while_statement | print_statement | block
declaration      → type ID ;
type             → int | float | bool
assignment       → ID = expression ;
print_statement  → print expression ;
if_statement     → if ( expression ) block
                 | if ( expression ) block else block
while_statement  → while ( expression ) block
expression       → expression (+ - * / %) expression
                 | expression (< > <= >= == !=) expression
                 | expression (&& ||) expression
                 | ! expression | ( expression )
                 | ID | INT_LITERAL | FLOAT_LITERAL | BOOL_LITERAL
```

Full grammar: [`docs/grammar.md`](docs/grammar.md) · Token list: [`docs/tokens.md`](docs/tokens.md) · Architecture details: [`docs/architecture.md`](docs/architecture.md)

---

## Build Instructions

### Requirements

- GCC
- Flex
- Bison
- GNU Make

### Ubuntu

```bash
sudo apt update
sudo apt install flex bison build-essential make
```

### Build

Clone the repository:

```bash
git clone https://github.com/mashudasiddikamaisha/ParseMaster-Compiler-Construction-Lab-Project.git
cd ParseMaster-Compiler-Construction-Lab-Project
```

Compile the project:

```bash
make
```

Clean generated/build files:

```bash
make clean
```

---

## Usage

Run the compiler on a source file:

```bash
./compiler < tests/valid/full_program.txt
```

For a syntactically and semantically valid program, the compiler prints, in order:

1. Parsing status
2. Symbol Table
3. Abstract Syntax Tree (AST)
4. Semantic Analysis trace (and any semantic errors)
5. Three Address Code (TAC)

### Example

**Input** (`tests/valid/full_program.txt`):

```c
int x;
int y;

x = 10;
y = 5;

if (x > y)
{
    print x;
}
else
{
    print y;
}

while (x > 0)
{
    x = x - 1;
}
```

**Output** (abridged):

```
Parsing started...
Program parsed successfully!

===== SYMBOL TABLE =====
Name    Type    Line    Scope
x       int     1       global
y       int     2       global

===== ABSTRACT SYNTAX TREE =====
Declaration
│   ├── Type : int
│   ├── Identifier : x
...

===== SEMANTIC ANALYSIS =====
Declaration
Type (int)
...

===== THREE ADDRESS CODE =====
x = 10
y = 5
t1 = x > y
ifFalse t1 goto L1
print x
goto L2
L1:
print y
L2:
L3:
t2 = x > 0
ifFalse t2 goto L4
t3 = x - 1
x = t3
goto L3
L4:
==============================

Parsing completed.
```

More sample runs (valid and invalid programs) are available in [`examples/Sample_output/`](examples/Sample_output/).

### Error Reporting

Syntax errors are reported with line numbers, and the parser attempts recovery to continue checking the rest of the file:

```
Syntax Error at line 5: syntax error
Recovered from syntax error at line 5
```

Semantic errors are reported the same way, e.g.:

```
Semantic Error (line 2): Cannot assign int to bool variable 'flag'.
```

See [`examples/Sample_output/invalid.txt`](examples/Sample_output/invalid.txt) for a full example.

---

## Project Structure

```
src/
├── ast/            # AST node definitions and printing
├── lexer/          # Flex lexer (lexer.l)
├── parser/         # Bison grammar (parser.y)
├── semantic/       # Semantic analysis (type checking, error reporting)
├── symbol_table/   # Symbol table implementation
├── tac/            # Three Address Code generation
└── main.c          # Compiler driver

examples/
├── valid/          # Example valid source programs
├── invalid/        # Example invalid source programs
└── Sample_output/  # Corresponding compiler output

tests/
├── valid/          # Test programs covering each language feature
└── invalid/        # Test programs covering error handling

docs/
├── architecture.md # Compiler pipeline and design overview
├── grammar.md       # Full context-free grammar
└── tokens.md         # Full token list
```

---

## Documentation

- [Architecture](docs/architecture.md) — detailed phase-by-phase pipeline overview
- [Grammar](docs/grammar.md) — full CFG for the language
- [Tokens](docs/tokens.md) — complete token list
- [Install Guide](INSTALL.md)
- [FAQ](FAQ.md)
- [Changelog](CHANGELOG.md)
- [Contributing](Contributing.md)
- [Project Manual (PDF)](Compiler%20Construction%20Lab%20Project%20Manual.pdf)

---

## Technologies Used

- C
- Flex
- Bison
- GCC
- GNU Make

---

## Future Work

- Code optimization on the generated TAC (constant folding, dead-code elimination)
- Target/assembly code generation
- Support for functions and arrays
- Improved AST/TAC visualization (e.g. graphical output)
- Expanded standard library of built-in operations

---

## License

This project is licensed under the [MIT License](LICENSE).
