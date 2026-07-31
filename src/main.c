
#include <stdio.h>

#include "ast/ast.h"
#include "semantic/semantic.h"
#include "symboltable/symbol_table.h"
#include "tac/tac.h"
extern int yyparse(void);
extern ASTNode *root;

int main()
{
    printf("Parsing started...\n");

    if (yyparse() == 0)
    {
        printf("Program parsed successfully!\n");

        printf("\n===== ABSTRACT SYNTAX TREE =====\n");
        printAST(root, 0);

        /* Create symbol table */
        SymbolTable table;
        initSymbolTable(&table);

        /* Perform semantic analysis */
        printf("\n===== SEMANTIC ANALYSIS =====\n");
        semanticAnalysis(root, &table);

        /* Display symbol table */
        printSymbolTable(&table);
        generateTAC(root);
        freeAST(root);
    }

    printf("\nParsing completed.\n");

    return 0;
}