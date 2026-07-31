#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "../ast/ast.h"
#include "../symbol_table/symbol_table.h"

void semanticAnalysis(ASTNode *root, SymbolTable *table);
const char *getExpressionType(ASTNode *node, SymbolTable *table);

#endif
