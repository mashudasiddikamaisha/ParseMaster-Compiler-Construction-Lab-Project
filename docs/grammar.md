# ParseMaster Language Grammar (CFG)

## Program

```
program → statement_list
```

## Statement List

```
statement_list → statement statement_list
statement_list → ε
```

## Statement

```
statement → declaration
statement → assignment
statement → if_statement
statement → while_statement
statement → print_statement
statement → block
```

## Block

```
block → { statement_list }
```

## Declaration

```
declaration → type ID ;
```

## Type

```
type → int
type → float
type → bool
```

## Assignment

```
assignment → ID = expression ;
```

## Print

```
print_statement → print expression ;
```

## If

```
if_statement → if ( expression ) block
if_statement → if ( expression ) block else block
```

## While

```
while_statement → while ( expression ) block
```

## Expression

```
expression → expression + expression
expression → expression - expression
expression → expression * expression
expression → expression / expression
expression → expression % expression

expression → expression < expression
expression → expression > expression
expression → expression <= expression
expression → expression >= expression
expression → expression == expression
expression → expression != expression

expression → expression && expression
expression → expression || expression
expression → ! expression

expression → ( expression )

expression → ID
expression → INT_LITERAL
expression → FLOAT_LITERAL
expression → BOOL_LITERAL
```