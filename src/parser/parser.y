%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

/* ---------- TOKENS ---------- */

%token INT FLOAT BOOL
%token IF ELSE WHILE PRINT
%token TRUE FALSE

%token ID
%token INT_LITERAL
%token FLOAT_LITERAL

%token PLUS MINUS MULTIPLY DIVIDE MOD
%token ASSIGN

%token LT GT LE GE EQ NE
%token AND OR NOT

%token LPAREN RPAREN
%token LBRACE RBRACE
%token SEMICOLON

/* ---------- OPERATOR PRECEDENCE ---------- */

%left OR
%left AND
%left EQ NE
%left LT GT LE GE
%left PLUS MINUS
%left MULTIPLY DIVIDE MOD
%right NOT

%%

program
    : statement_list
    ;

statement_list
    : statement_list statement
    | statement
    ;

statement
    : declaration
    | assignment
    | print_statement
    | if_statement
    | if_else_statement
    | while_statement
    ;

declaration
    : type ID SEMICOLON
    ;

assignment
    : ID ASSIGN expression SEMICOLON
    ;

print_statement
    : PRINT expression SEMICOLON
    ;

block
    : LBRACE statement_list RBRACE
    ;

if_statement
    : IF LPAREN expression RPAREN block
    ;

if_else_statement
    : IF LPAREN expression RPAREN block ELSE block
    ;

while_statement
    : WHILE LPAREN expression RPAREN block
    ;

type
    : INT
    | FLOAT
    | BOOL
    ;

expression
    : expression OR expression
    | expression AND expression
    | NOT expression

    | expression LT expression
    | expression GT expression
    | expression LE expression
    | expression GE expression
    | expression EQ expression
    | expression NE expression

    | expression PLUS expression
    | expression MINUS expression
    | expression MULTIPLY expression
    | expression DIVIDE expression
    | expression MOD expression

    | LPAREN expression RPAREN
    | ID
    | INT_LITERAL
    | FLOAT_LITERAL
    | TRUE
    | FALSE
    ;

%%

void yyerror(const char *s)
{
    printf("Syntax Error: %s\n", s);
}