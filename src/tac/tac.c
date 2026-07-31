#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tac.h"

static int tempCount = 0;
static int labelCount = 0;

static char *newTemp()
{
    char *t = malloc(20);
    sprintf(t, "t%d", ++tempCount);
    return t;
}

static char *newLabel()
{
    char *l = malloc(20);
    sprintf(l, "L%d", ++labelCount);
    return l;
}

void resetTAC()
{
    tempCount = 0;
    labelCount = 0;
}

static const char *op(char *type)
{
    if (!strcmp(type, "PLUS")) return "+";
    if (!strcmp(type, "MINUS")) return "-";
    if (!strcmp(type, "MULTIPLY")) return "*";
    if (!strcmp(type, "DIVIDE")) return "/";
    if (!strcmp(type, "MOD")) return "%";
    if (!strcmp(type, "LT")) return "<";
    if (!strcmp(type, "GT")) return ">";
    if (!strcmp(type, "LE")) return "<=";
    if (!strcmp(type, "GE")) return ">=";
    if (!strcmp(type, "EQ")) return "==";
    if (!strcmp(type, "NE")) return "!=";
    if (!strcmp(type, "AND")) return "&&";
    if (!strcmp(type, "OR")) return "||";
    return "";
}

static char *expr(ASTNode *n)
{
    if (!n) return NULL;

    if (!strcmp(n->nodeType, "Identifier") ||
        !strcmp(n->nodeType, "IntLiteral") ||
        !strcmp(n->nodeType, "FloatLiteral") ||
        !strcmp(n->nodeType, "BoolLiteral"))
        return strdup(n->value);

    if (!strcmp(n->nodeType, "NOT"))
    {
        char *a = expr(n->left);
        char *t = newTemp();

        printf("%s = ! %s\n", t, a);

        free(a);
        return t;
    }

    char *a = expr(n->left);
    char *b = expr(n->right);
    char *t = newTemp();

    printf("%s = %s %s %s\n", t, a, op(n->nodeType), b);

    free(a);
    free(b);

    return t;
}

static void statements(ASTNode *n);

static void block(ASTNode *n)
{
    if (n && !strcmp(n->nodeType, "Block"))
        statements(n->left);
}

static void statement(ASTNode *n)
{
    if (!n) return;

    if (!strcmp(n->nodeType, "Declaration"))
        return;

    if (!strcmp(n->nodeType, "Assignment"))
    {
        char *r = expr(n->right);

        printf("%s = %s\n", n->left->value, r);

        free(r);
    }

    else if (!strcmp(n->nodeType, "Print"))
    {
        char *r = expr(n->left);

        printf("print %s\n", r);

        free(r);
    }

    else if (!strcmp(n->nodeType, "If"))
    {
        char *c = expr(n->left);
        char *l = newLabel();

        printf("ifFalse %s goto %s\n", c, l);
        block(n->right);
        printf("%s:\n", l);

        free(c);
        free(l);
    }

    else if (!strcmp(n->nodeType, "IfElse"))
    {
        char *c = expr(n->left);
        char *l1 = newLabel();
        char *l2 = newLabel();

        ASTNode *thenBlock = n->right;
        ASTNode *elseBlock = thenBlock ? thenBlock->next : NULL;

        printf("ifFalse %s goto %s\n", c, l1);
        block(thenBlock);
        printf("goto %s\n", l2);
        printf("%s:\n", l1);
        block(elseBlock);
        printf("%s:\n", l2);

        free(c);
        free(l1);
        free(l2);
    }

    else if (!strcmp(n->nodeType, "While"))
    {
        char *start = newLabel();
        char *end = newLabel();

        printf("%s:\n", start);

        char *c = expr(n->left);

        printf("ifFalse %s goto %s\n", c, end);
        block(n->right);
        printf("goto %s\n", start);
        printf("%s:\n", end);

        free(c);
        free(start);
        free(end);
    }
}

static void statements(ASTNode *n)
{
    while (n)
    {
        statement(n);
        n = n->next;
    }
}

void generateTAC(ASTNode *root)
{
    if (!root) return;

    resetTAC();

    printf("\n===== THREE ADDRESS CODE =====\n");
    statements(root);
    printf("==============================\n");
}