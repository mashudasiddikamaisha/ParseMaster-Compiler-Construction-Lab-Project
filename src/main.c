
#include <stdio.h>

#include "ast/ast.h"
#include "symbol_table/symbol_table.h"
#include "semantic/semantic.h"
#include "tac/tac.h"

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
        
        /* Perform semantic analysis */
        printf("\n===== SEMANTIC ANALYSIS =====\n");
        semanticAnalysis(root, &symbolTable);

        
        generateTAC(root);
        freeAST(root);
    }

    printf("\nParsing completed.\n");

    return 0;
}