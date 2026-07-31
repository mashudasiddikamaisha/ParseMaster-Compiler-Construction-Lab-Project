// #ifndef SEMANTIC_H
// #define SEMANTIC_H

// #include "../ast/ast.h"
// #include "../symbol_table/symbol_table.h"

// void semanticAnalysis(ASTNode *root, SymbolTable *table);
// const char *getExpressionType(ASTNode *node, SymbolTable *table);
// int lookupSemanticSymbol(SymbolTable *table, const char *name);


// int lookupSymbolInScope(SymbolTable *table,
//                         const char *name,
//                         const char *scope);

// #endif
#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "../ast/ast.h"
#include "../symbol_table/symbol_table.h"

void semanticAnalysis(ASTNode *root, SymbolTable *table);
const char *getExpressionType(ASTNode *node, SymbolTable *table);

#endif