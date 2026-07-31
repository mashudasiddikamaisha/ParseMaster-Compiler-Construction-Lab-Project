#include <stdio.h>
#include "ast/ast.h"
#include "symbol_table/symbol_table.h"

extern int yyparse(void);
extern ASTNode *root;
extern SymbolTable symbolTable;

int main()
{
    initSymbolTable(&symbolTable);
    printf("Parsing started...\n");

    if (yyparse() == 0)
    {
        printf("Program parsed successfully!\n");
        printSymbolTable(&symbolTable);

        printf("\n===== ABSTRACT SYNTAX TREE =====\n");

        printAST(root, 0);

        freeAST(root);
    }
    printf("Parsing completed.\n");

    return 0;
}