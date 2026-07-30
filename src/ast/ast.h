#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ASTNode
{
    char nodeType[50];      // Assignment, If, While, Identifier, etc.
    char value[100];         // Variable name, literal value, operator

    struct ASTNode *left;
    struct ASTNode *right;
    struct ASTNode *next;

} ASTNode;

/* Function declarations */

ASTNode *createNode(const char *nodeType,
                    const char *value,
                    ASTNode *left,
                    ASTNode *right);
void printAST(ASTNode *root, int level);

void freeAST(ASTNode *root);

#endif