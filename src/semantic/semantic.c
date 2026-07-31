#include <stdio.h>
#include <string.h>

#include "semantic.h"

int findSymbol(SymbolTable *table, char name[], char scope[])
{
    for (int i = 0; i < table->count; i++)
    {
        if (strcmp(table->symbols[i].name, name) == 0  && strcmp(table->symbols[i].scope, scope) == 0)
            return i;
    }

    return -1;
}


int findVisibleSymbol(SymbolTable *table, char name[], char scope[])
{
    char currentScope[20];

    strcpy(currentScope, scope);

    while(1)
    {
        int index = findSymbol(table, name, currentScope);

        if(index != -1)
            return index;


        if(strcmp(currentScope, "global") == 0)
            break;


        int scopeNumber;

        sscanf(currentScope, "S%d", &scopeNumber);


        if(scopeNumber > 1)
        {
            sprintf(currentScope, "S%d", scopeNumber - 1);
        }
        else
        {
            strcpy(currentScope, "global");
        }
    }


    return -1;
}


const char *getExpressionType(ASTNode *node, SymbolTable *table)
{
    if (node == NULL)
        return "unknown";

    /* Integer literal */
    if (strcmp(node->nodeType, "IntLiteral") == 0)
        return "int";

    /* Float literal */
    if (strcmp(node->nodeType, "FloatLiteral") == 0)
        return "float";

    /* Boolean literal */
    if (strcmp(node->nodeType, "BoolLiteral") == 0)
        return "bool";

    /* Identifier */
    if (strcmp(node->nodeType, "Identifier") == 0)
    {
         
int index = findVisibleSymbol(table, node->value, node->scope);
        if (index == -1)
        {
            printf("Semantic Error: Variable '%s' is not declared.\n", node->value);
            return "unknown";
        }

        return table->symbols[index].type;
    }

    /* Arithmetic operators */

    if (strcmp(node->nodeType, "PLUS") == 0 ||
        strcmp(node->nodeType, "MINUS") == 0 ||
        strcmp(node->nodeType, "MULTIPLY") == 0 ||
        strcmp(node->nodeType, "DIVIDE") == 0)
    {
        const char *leftType = getExpressionType(node->left, table);
        const char *rightType = getExpressionType(node->right, table);

        if ((strcmp(leftType, "int") == 0 || strcmp(leftType, "float") == 0) &&
            (strcmp(rightType, "int") == 0 || strcmp(rightType, "float") == 0))
        {
            if (strcmp(leftType, "float") == 0 || strcmp(rightType, "float") == 0)
                return "float";

            return "int";
        }

        printf("Semantic Error: Arithmetic operators require numeric operands.\n");
        return "unknown";
    }

    if (strcmp(node->nodeType, "MOD") == 0)
    {
        const char *leftType = getExpressionType(node->left, table);
        const char *rightType = getExpressionType(node->right, table);

        if (strcmp(leftType, "int") == 0 &&
            strcmp(rightType, "int") == 0)
            return "int";

        printf("Semantic Error: Modulus operator requires integer operands.\n");
        return "unknown";
    }

    /* Relational operators */

    if (strcmp(node->nodeType, "LT") == 0 || strcmp(node->nodeType, "GT") == 0 || strcmp(node->nodeType, "LE") == 0 || strcmp(node->nodeType, "GE") == 0)
    {
        const char *leftType = getExpressionType(node->left, table);
        const char *rightType = getExpressionType(node->right, table);

        if ((strcmp(leftType, "int") == 0 || strcmp(leftType, "float") == 0) &&
            (strcmp(rightType, "int") == 0 || strcmp(rightType, "float") == 0))
        {
            return "bool";
        }

        printf("Semantic Error: Relational operators require numeric operands.\n");
        return "unknown";
    }

    /* Equality operators */

    if (strcmp(node->nodeType, "EQ") == 0 || strcmp(node->nodeType, "NE") == 0)
    {
        const char *leftType = getExpressionType(node->left, table);
        const char *rightType = getExpressionType(node->right, table);

        if (strcmp(leftType, rightType) == 0 && strcmp(leftType, "unknown") != 0)
        {
            return "bool";
        }

        printf("Semantic Error: Equality operands must have the same type.\n");
        return "unknown";
    }

    /* Logical operators */

    if (strcmp(node->nodeType, "AND") == 0 || strcmp(node->nodeType, "OR") == 0)
    {
        const char *leftType = getExpressionType(node->left, table);
        const char *rightType = getExpressionType(node->right, table);

        if (strcmp(leftType, "bool") == 0 && strcmp(rightType, "bool") == 0)
        {
            return "bool";
        }

        printf("Semantic Error: Logical operators require boolean operands.\n");
        return "unknown";
    }

    /* NOT operator */

    if (strcmp(node->nodeType, "NOT") == 0)
    {
        const char *type = getExpressionType(node->left, table);

        if (strcmp(type, "bool") == 0)
            return "bool";

        printf("Semantic Error: NOT operator requires a boolean operand.\n");
        return "unknown";
    }


    return "unknown";
}

void analyzeNode(ASTNode *node, SymbolTable *table)
{
    if (node == NULL)
        return;

    printf("Visiting: %s", node->nodeType);

    if (strlen(node->value) > 0)
        printf(" (%s)", node->value);

    printf("\n");

    /* Assignment */
if (strcmp(node->nodeType, "Assignment") == 0)
{
    ASTNode *idNode = node->left;
    ASTNode *exprNode = node->right;

    int index = findVisibleSymbol(table, idNode->value, idNode->scope);

    if (index == -1)
    {
        printf("Semantic Error: Variable '%s' is not declared.\n",
               idNode->value);
    }
    else
    {
        const char *variableType = table->symbols[index].type;
        const char *expressionType = getExpressionType(exprNode, table);

        if (strcmp(expressionType, "unknown") != 0)
        {
            /*
              Allow:
              int = int
              float = int
              float = float
            */

            if (strcmp(variableType, expressionType) != 0)
            {
                if (!(strcmp(variableType,"float")==0 &&
                      strcmp(expressionType,"int")==0))
                {
                    printf(
                    "Semantic Error (line %d): Cannot assign %s to %s variable '%s'.\n",
                    table->symbols[index].line,
                    expressionType,
                    variableType,
                    idNode->value);
                }
            }
        }
    }
}
    /* Print statement */
    if (strcmp(node->nodeType, "Print") == 0)
    {
        getExpressionType(node->left, table);
    }
    /* If */
if (strcmp(node->nodeType, "If") == 0)
{
    const char *conditionType =
        getExpressionType(node->left, table);

    if(strcmp(conditionType,"bool")!=0)
    {
        printf("Semantic Error: If condition must be boolean.\n");
    }
}

    /* IfElse */
if (strcmp(node->nodeType, "IfElse") == 0)
{
    const char *conditionType =
        getExpressionType(node->left, table);

    if(strcmp(conditionType,"bool")!=0)
    {
        printf("Semantic Error: If condition must be boolean.\n");
    }
}

    /* While */
if (strcmp(node->nodeType, "While") == 0)
{
    const char *conditionType =
        getExpressionType(node->left, table);

    if(strcmp(conditionType,"bool")!=0)
    {
        printf("Semantic Error: While condition must be boolean.\n");
    }
}
   analyzeNode(node->left, table);
analyzeNode(node->right, table);
analyzeNode(node->next, table);
}
 
void semanticAnalysis(ASTNode *root, SymbolTable *table)
{
analyzeNode(root, table);
}