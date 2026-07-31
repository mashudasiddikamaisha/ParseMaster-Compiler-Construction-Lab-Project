#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#define MAX_SYMBOLS 100


typedef struct Symbol
{
    char name[50];
    char type[20];
    int line;
    char scope[20];

} Symbol;


typedef struct SymbolTable
{
    Symbol symbols[MAX_SYMBOLS];
    int count;

} SymbolTable;


// Functions

int lookupSymbol(SymbolTable *table, char name[], char scope[]);

void initSymbolTable(SymbolTable *table);

void insertSymbol(SymbolTable *table,
                  char name[],
                  char type[],
                  int line,
                  char scope[]);

void printSymbolTable(SymbolTable *table);


#endif