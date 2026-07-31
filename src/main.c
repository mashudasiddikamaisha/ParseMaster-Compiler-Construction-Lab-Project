#include <stdio.h>
#include "ast/ast.h"

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

        freeAST(root);
    }
    printf("Parsing completed.\n");

    return 0;
}