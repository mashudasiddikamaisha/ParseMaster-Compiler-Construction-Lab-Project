%{
#include <stdio.h>
#include <stdlib.h>
#include "src/ast/ast.h"
#include "src/symbol_table/symbol_table.h"

int yylex(void);
void yyerror(const char *s);
extern int yylineno;
extern SymbolTable symbolTable;

/* Root of the AST */
ASTNode *root = NULL;

/* Global Symbol Table */

int scopeCounter = 0;
char currentScope[20] = "global";
char previousScope[20][20];
%}

/* ---------- TOKENS ---------- */

%token INT FLOAT BOOL
%token IF ELSE WHILE PRINT
%token TRUE FALSE

%union
{
    ASTNode *node;
    char *text;
}

%token <text> ID
%token <text> INT_LITERAL
%token <text> FLOAT_LITERAL

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

%type <node> program
%type <node> statement_list
%type <node> statement
%type <node> declaration
%type <node> assignment
%type <node> print_statement
%type <node> if_statement
%type <node> if_else_statement
%type <node> while_statement
%type <node> block
%type <node> expression
%type <node> type

%%

program
    : statement_list
    {
        root = $1;
        $$ = root;
    }
    ;

statement_list
    : statement_list statement
    {
        if ($1 == NULL)
            $$ = $2;

        else if ($2 == NULL)
            $$ = $1;

        else
        {
            ASTNode *temp = $1;

            while (temp->next != NULL)
                temp = temp->next;

            temp->next = $2;

            $$ = $1;
        }
    }

    | statement
    {
        $$ = $1;
    }
    ;

statement
    : declaration
        { $$ = $1; }
    | assignment
        { $$ = $1; }
    | print_statement
        { $$ = $1; }
    | if_statement
        { $$ = $1; }
    | if_else_statement
        { $$ = $1; }
    | while_statement
        { $$ = $1; }
    | block
        { $$ = $1; }
    | error SEMICOLON
    {
        printf("Recovered from syntax error at line %d\n", yylineno);
        $$ = NULL;
        yyerrok;
    }
    ;

declaration
    : type ID SEMICOLON
    {
        ASTNode *idNode = createNode("Identifier", $2, NULL, NULL);
        strcpy(idNode->scope, currentScope);
        $$ = createNode("Declaration", "", $1, idNode);

        insertSymbol(
            &symbolTable,
            $2,
            $1->value,
            yylineno,
            currentScope
        );
    }
    ;

assignment
    : ID ASSIGN expression SEMICOLON
    {
        ASTNode *idNode = createNode("Identifier", $1, NULL, NULL);
        strcpy(idNode->scope, currentScope);
        $$ = createNode("Assignment", "", idNode, $3);
    }
    ;

print_statement
    : PRINT expression SEMICOLON
    {
        $$ = createNode("Print", "", $2, NULL);
    }
    ;

block
    : LBRACE
    {
        strcpy(previousScope[scopeCounter], currentScope);

        scopeCounter++;

        sprintf(currentScope, "S%d", scopeCounter);
    }
    statement_list
    RBRACE
    {
        $$ = createNode("Block", "", $3, NULL);

        strcpy(currentScope, previousScope[scopeCounter - 1]);

        scopeCounter--;
    }
    ;

if_statement
    : IF LPAREN expression RPAREN block
    {
        $$ = createNode("If", "", $3, $5);
    }
    ;

if_else_statement
    : IF LPAREN expression RPAREN block ELSE block
    {
        $5->next = $7;
        $$ = createNode("IfElse", "", $3, $5);
    }
    ;

while_statement
    : WHILE LPAREN expression RPAREN block
    {
        $$ = createNode("While", "", $3, $5);
    }
    ;

type
    : INT
        {
            $$ = createNode("Type", "int", NULL, NULL);
        }
    | FLOAT
        {
            $$ = createNode("Type", "float", NULL, NULL);
        }
    | BOOL
        {
            $$ = createNode("Type", "bool", NULL, NULL);
        }
    ;

expression
    : expression OR expression
    {
        $$ = createNode("OR", "", $1, $3);
    }
    | expression AND expression
    {
        $$ = createNode("AND", "", $1, $3);
    }
    | NOT expression
    {
        $$ = createNode("NOT", "", $2, NULL);
    }

    | expression LT expression
    {
        $$ = createNode("LT", "", $1, $3);
    }

    | expression GT expression
    {
        $$ = createNode("GT", "", $1, $3);
    }
    | expression LE expression
    {
        $$ = createNode("LE", "", $1, $3);
    }

    | expression GE expression
    {
        $$ = createNode("GE", "", $1, $3);
    }
    | expression EQ expression
    {
        $$ = createNode("EQ", "", $1, $3);
    }

    | expression NE expression
    {
        $$ = createNode("NE", "", $1, $3);
    }

    | expression PLUS expression
    {
        $$ = createNode("PLUS", "", $1, $3);
    }
    | expression MINUS expression
    {
        $$ = createNode("MINUS", "", $1, $3);
    }

    | expression MULTIPLY expression
    {
        $$ = createNode("MULTIPLY", "", $1, $3);
    }

    | expression DIVIDE expression
    {
        $$ = createNode("DIVIDE", "", $1, $3);
    }
    | expression MOD expression
    {
        $$ = createNode("MOD", "", $1, $3);
    }

    | LPAREN expression RPAREN
    {
        $$ = $2;
    }
    | ID
    {
        $$ = createNode("Identifier", $1, NULL, NULL);
        strcpy($$->scope, currentScope);
    }
    | INT_LITERAL
    {
        $$ = createNode("IntLiteral", $1, NULL, NULL);
    }
    | FLOAT_LITERAL
    {
        $$ = createNode("FloatLiteral", $1, NULL, NULL);
    }
    | TRUE
    {
        $$ = createNode("BoolLiteral", "true", NULL, NULL);
    }

    | FALSE
    {
        $$ = createNode("BoolLiteral", "false", NULL, NULL);
    }
    ;

%%

void yyerror(const char *s)
{
    printf("Syntax Error at line %d: %s\n", yylineno, s);
}