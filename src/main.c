#include <stdio.h>

#include "ast/ast.h"
#include "symbol_table/symbol_table.h"
#include "semantic/semantic.h"

extern int yyparse(void);
extern ASTNode *root;
extern SymbolTable symbolTable;
SymbolTable symbolTable;

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

        // /* Create symbol table */
        // SymbolTable table;
        // initSymbolTable(&table);

        /* Perform semantic analysis */
        printf("\n===== SEMANTIC ANALYSIS =====\n");
        semanticAnalysis(root, &symbolTable);

        /* Display symbol table */
        // printSymbolTable(&symbolTable);

        freeAST(root);
    }

    printf("\nParsing completed.\n");

    return 0;
}