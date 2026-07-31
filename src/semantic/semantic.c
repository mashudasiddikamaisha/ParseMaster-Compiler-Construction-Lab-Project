#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "semantic.h"

/*
 * ---------------------------------------------------------
 * Symbol Lookup
 * ---------------------------------------------------------
 */


int lookupSymbol(SymbolTable *table, const char *name)
{
    for (int i = table->count - 1; i >= 0; i--)
    {
        if (strcmp(table->symbols[i].name, name) == 0)
        {
            return i;
        }
    }

    return -1;
}

int lookupSymbolInScope(SymbolTable *table,
                        const char *name,
                        const char *scope)
{
    for (int i = 0; i < table->count; i++)
    {
        if (strcmp(table->symbols[i].name, name) == 0 &&
            strcmp(table->symbols[i].scope, scope) == 0)
        {
            return i;
        }
    }

    return -1;
}
/*
 * ---------------------------------------------------------
 * Scope Helper Functions
 * ---------------------------------------------------------
 */
static int isScopeVisible(const char *declScope,
                          const char *currentScope)
{
    char temp[200];

    strcpy(temp, currentScope);

    while (1)
    {
        if (strcmp(temp, declScope) == 0)
            return 1;

        char *lastSlash = strrchr(temp, '/');

        if (lastSlash == NULL)
            break;

        *lastSlash = '\0';
    }

    return 0;
}
static int lookupVisibleSymbol(SymbolTable *table,
                               const char *name,
                               const char *currentScope)
{
    for (int i = table->count - 1; i >= 0; i--)
    {
        if (strcmp(table->symbols[i].name, name) == 0 &&
            isScopeVisible(table->symbols[i].scope, currentScope))
        {
            return i;
        }
    }

    return -1;
}

/*
 * ---------------------------------------------------------
 * Expression Type Checking
 * ---------------------------------------------------------
 */

const char *getExpressionType(ASTNode *node, SymbolTable *table)
{
    if (node == NULL)
        return "unknown";

    if (strcmp(node->nodeType, "IntLiteral") == 0)
        return "int";

    if (strcmp(node->nodeType, "FloatLiteral") == 0)
        return "float";

    if (strcmp(node->nodeType, "BoolLiteral") == 0)
        return "bool";

    if (strcmp(node->nodeType, "Identifier") == 0)
    {
        int index = lookupSymbol(table, node->value);

        if (index == -1)
        {
            printf("SEMANTIC ERROR: Variable '%s' is not declared.\n",
                   node->value);

            return "unknown";
        }

        return table->symbols[index].type;
    }

    /*
     * -----------------------------------------------------
     * Arithmetic Operators
     * -----------------------------------------------------
     */

    if (strcmp(node->nodeType, "PLUS") == 0 ||
        strcmp(node->nodeType, "MINUS") == 0 ||
        strcmp(node->nodeType, "MULTIPLY") == 0 ||
        strcmp(node->nodeType, "DIVIDE") == 0 ||
        strcmp(node->nodeType, "MOD") == 0)
    {
        const char *leftType =
            getExpressionType(node->left, table);

        const char *rightType =
            getExpressionType(node->right, table);

        if (strcmp(node->nodeType, "MOD") == 0)
        {
            if (strcmp(leftType, "int") == 0 &&
                strcmp(rightType, "int") == 0)
            {
                return "int";
            }

            printf(
                "SEMANTIC ERROR: Modulus operator requires integer operands.\n");

            return "unknown";
        }

        /*
         * + - * / accept int and float
         */
        if ((strcmp(leftType, "int") == 0 ||
             strcmp(leftType, "float") == 0) &&
            (strcmp(rightType, "int") == 0 ||
             strcmp(rightType, "float") == 0))
        {
            if (strcmp(leftType, "float") == 0 ||
                strcmp(rightType, "float") == 0)
            {
                return "float";
            }

            return "int";
        }

        printf(
            "SEMANTIC ERROR: Arithmetic operator requires numeric operands.\n");

        return "unknown";
    }

    /*
     * -----------------------------------------------------
     * Relational Operators
     * -----------------------------------------------------
     */

    if (strcmp(node->nodeType, "LT") == 0 ||
        strcmp(node->nodeType, "GT") == 0 ||
        strcmp(node->nodeType, "LE") == 0 ||
        strcmp(node->nodeType, "GE") == 0)
    {
        const char *leftType =
            getExpressionType(node->left, table);

        const char *rightType =
            getExpressionType(node->right, table);

        if ((strcmp(leftType, "int") == 0 ||
             strcmp(leftType, "float") == 0) &&
            (strcmp(rightType, "int") == 0 ||
             strcmp(rightType, "float") == 0))
        {
            return "bool";
        }

        printf(
            "SEMANTIC ERROR: Relational operator requires numeric operands.\n");

        return "unknown";
    }

    /*
     * -----------------------------------------------------
     * Equality Operators
     * -----------------------------------------------------
     */

    if (strcmp(node->nodeType, "EQ") == 0 ||
        strcmp(node->nodeType, "NE") == 0)
    {
        const char *leftType =
            getExpressionType(node->left, table);

        const char *rightType =
            getExpressionType(node->right, table);

        if (strcmp(leftType, rightType) == 0 &&
            strcmp(leftType, "unknown") != 0)
        {
            return "bool";
        }

        printf(
            "SEMANTIC ERROR: Equality operands must have compatible types.\n");

        return "unknown";
    }

    /*
     * -----------------------------------------------------
     * Logical AND / OR
     * -----------------------------------------------------
     */

    if (strcmp(node->nodeType, "AND") == 0 ||
        strcmp(node->nodeType, "OR") == 0)
    {
        const char *leftType =
            getExpressionType(node->left, table);

        const char *rightType =
            getExpressionType(node->right, table);

        if (strcmp(leftType, "bool") == 0 &&
            strcmp(rightType, "bool") == 0)
        {
            return "bool";
        }

        printf(
            "SEMANTIC ERROR: Logical operator requires boolean operands.\n");

        return "unknown";
    }

    /*
     * -----------------------------------------------------
     * Logical NOT
     * -----------------------------------------------------
     */

    if (strcmp(node->nodeType, "NOT") == 0)
    {
        const char *type =
            getExpressionType(node->left, table);

        if (strcmp(type, "bool") == 0)
        {
            return "bool";
        }

        printf(
            "SEMANTIC ERROR: NOT operator requires a boolean operand.\n");

        return "unknown";
    }

    return "unknown";
}

/*
 * ---------------------------------------------------------
 * Semantic Analysis
 * ---------------------------------------------------------
 */

static int scopeCounter = 0;

static void analyzeStatements(ASTNode *root,
                              SymbolTable *table,
                              const char *currentScope);

static void analyzeBlock(ASTNode *block,
                         SymbolTable *table,
                         const char *parentScope)
{
    if (block == NULL)
        return;

    char newScope[200];

    scopeCounter++;

    snprintf(newScope,
             sizeof(newScope),
             "%s/B%d",
             parentScope,
             scopeCounter);

    analyzeStatements(block->left,
                       table,
                       newScope);
}

/*
 * Analyze statements
 */
static void analyzeStatements(ASTNode *root,
                              SymbolTable *table,
                              const char *currentScope)
{
    ASTNode *current = root;

    while (current != NULL)
    {
        /*
         * -------------------------------------------------
         * Declaration
         * -------------------------------------------------
         */

        if (strcmp(current->nodeType, "Declaration") == 0)
        {
            ASTNode *typeNode = current->left;
            ASTNode *idNode = current->right;

            if (typeNode != NULL && idNode != NULL)
            {
            
                if (lookupSymbolInScope(table,
                                        idNode->value,
                                        currentScope) != -1)
                {
                    printf(
                        "SEMANTIC ERROR: Variable '%s' is already declared in scope '%s'.\n",
                        idNode->value,
                        currentScope);
                }
                else
                {
                    
                    insertSymbol(table,
                                 idNode->value,
                                 typeNode->value,
                                 0,
                                 (char *)currentScope);

                    printf(
                        "Semantic: Declared %s '%s' in scope '%s'.\n",
                        typeNode->value,
                        idNode->value,
                        currentScope);
                }
            }
        }

        /*
         * -------------------------------------------------
         * Assignment
         * -------------------------------------------------
         */

        else if (strcmp(current->nodeType, "Assignment") == 0)
        {
            ASTNode *idNode = current->left;
            ASTNode *expression = current->right;

            if (idNode != NULL)
            {
                int index =
                    lookupVisibleSymbol(table,
                                         idNode->value,
                                         currentScope);

                if (index == -1)
                {
                    printf(
                        "SEMANTIC ERROR: Variable '%s' is not declared in the current scope.\n",
                        idNode->value);
                }
                else
                {
                    const char *variableType =
                        table->symbols[index].type;

                    const char *expressionType =
                        getExpressionType(expression, table);

                    if (strcmp(expressionType, "unknown") != 0 &&
                        strcmp(variableType, expressionType) != 0)
                    {
                        printf(
                            "SEMANTIC ERROR: Type mismatch. Cannot assign %s to %s variable '%s'.\n",
                            expressionType,
                            variableType,
                            idNode->value);
                    }
                    else
                    {
                        printf(
                            "Semantic: Assignment to '%s' is valid.\n",
                            idNode->value);
                    }
                }
            }
        }

        /*
         * -------------------------------------------------
         * Print
         * -------------------------------------------------
         */

        else if (strcmp(current->nodeType, "Print") == 0)
        {
            const char *type =
                getExpressionType(current->left, table);

            if (strcmp(type, "unknown") != 0)
            {
                printf("Semantic: Print statement is valid.\n");
            }
        }


        else if (strcmp(current->nodeType, "If") == 0)
        {
            const char *conditionType =
                getExpressionType(current->left, table);

            if (strcmp(conditionType, "bool") != 0 &&
                strcmp(conditionType, "unknown") != 0)
            {
                printf(
                    "SEMANTIC ERROR: If condition must be boolean.\n");
            }

            analyzeBlock(current->right,
                         table,
                         currentScope);
        }

        else if (strcmp(current->nodeType, "IfElse") == 0)
        {
            const char *conditionType =
                getExpressionType(current->left, table);

            if (strcmp(conditionType, "bool") != 0 &&
                strcmp(conditionType, "unknown") != 0)
            {
                printf(
                    "SEMANTIC ERROR: If-Else condition must be boolean.\n");
            }

            ASTNode *thenBlock = current->right;

            ASTNode *elseBlock = NULL;

            if (thenBlock != NULL)
                elseBlock = thenBlock->next;

            analyzeBlock(thenBlock,
                         table,
                         currentScope);

            analyzeBlock(elseBlock,
                         table,
                         currentScope);
        }

        else if (strcmp(current->nodeType, "While") == 0)
        {
            const char *conditionType =
                getExpressionType(current->left, table);

            if (strcmp(conditionType, "bool") != 0 &&
                strcmp(conditionType, "unknown") != 0)
            {
                printf(
                    "SEMANTIC ERROR: While condition must be boolean.\n");
            }

            analyzeBlock(current->right,
                         table,
                         currentScope);
        }

        current = current->next;
    }
}

void semanticAnalysis(ASTNode *root, SymbolTable *table)
{
    if (root == NULL)
        return;

    scopeCounter = 0;

    analyzeStatements(root,
                      table,
                      "global");
}