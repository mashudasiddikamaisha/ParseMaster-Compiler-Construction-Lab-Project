#include <stdio.h>
#include "../src/ast/ast.h"

int main()
{
    ASTNode *id = createNode("Identifier", "x", NULL, NULL);
    ASTNode *num = createNode("Integer", "5", NULL, NULL);

    ASTNode *assign = createNode("Assignment", "=", id, num);

    printf("===== AST Test =====\n\n");

    printAST(assign, 0);

    freeAST(assign);

    return 0;
}