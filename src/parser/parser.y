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
    ;

declaration
    : type ID SEMICOLON
    ;

assignment
    : ID ASSIGN expression SEMICOLON
    ;

type
    : INT
    | FLOAT
    | BOOL
    ;

expression
    : ID
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