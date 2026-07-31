#include <stdio.h>
#include <string.h>

#include "symbol_table.h"

// Initialize table
void initSymbolTable(SymbolTable *table)
{
    table->count = 0;
}

// Insert symbol

void insertSymbol(SymbolTable *table,
                  char name[],
                  char type[],
                  int line,
                  char scope[])
{
    if(table->count >= MAX_SYMBOLS)
    {
        printf("Symbol table is full!\n");
        return;
    }

    strcpy(table->symbols[table->count].name, name);
    strcpy(table->symbols[table->count].type, type);

    table->symbols[table->count].line = line;

    strcpy(table->symbols[table->count].scope, scope);

    table->count++;
}

// Print symbol table
void printSymbolTable(SymbolTable *table)
{

    printf("\n===== SYMBOL TABLE =====\n");

    printf("Name\tType\tLine\tScope\n");

    for(int i = 0; i < table->count; i++)
    {
        printf("%s\t%s\t%d\t%s\n",
           table->symbols[i].name,
           table->symbols[i].type,
           table->symbols[i].line,
           table->symbols[i].scope);
    }

}