#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#define MAX_SYMBOLS 100

typedef struct Symbol
{
    char name[50];
    char type[20];

} Symbol;

typedef struct SymbolTable
{
    Symbol symbols[MAX_SYMBOLS];
    int count;

} SymbolTable;

// Functions

void initSymbolTable(SymbolTable *table);

void insertSymbol(SymbolTable *table,
                  char name[],
                  char type[]);

void printSymbolTable(SymbolTable *table);


#endif