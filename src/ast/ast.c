#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"

/* Create a new AST node */
ASTNode *createNode(char *nodeType, char *value,
                    ASTNode *left, ASTNode *right)
{
    ASTNode *newNode = (ASTNode *)malloc(sizeof(ASTNode));

    if (newNode == NULL)
    {
        printf("Error: Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    strcpy(newNode->nodeType, nodeType);

    if (value != NULL)
        strcpy(newNode->value, value);
    else
        strcpy(newNode->value, "");

    newNode->left = left;
    newNode->right = right;
    newNode->next = NULL;

    return newNode;
}

/* Helper function for indentation */
static void printIndent(int level)
{
    int i;

    for (i = 0; i < level; i++)
        printf("    ");
}

/* Print AST recursively */
void printAST(ASTNode *root, int level)
{
    if (root == NULL)
        return;

    printIndent(level);

    if (strlen(root->value) > 0)
        printf("%s : %s\n", root->nodeType, root->value);
    else
        printf("%s\n", root->nodeType);

    printAST(root->left, level + 1);
    printAST(root->right, level + 1);

    if (root->next != NULL)
        printAST(root->next, level);
}

/* Free all nodes */
void freeAST(ASTNode *root)
{
    if (root == NULL)
        return;

    freeAST(root->left);
    freeAST(root->right);
    freeAST(root->next);

    free(root);
}