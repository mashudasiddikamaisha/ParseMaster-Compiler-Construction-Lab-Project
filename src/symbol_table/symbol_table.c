#include <stdio.h>
#include <string.h>

#include "symbol_table.h"

// Initialize table
void initSymbolTable(SymbolTable *table)
{
    table->count = 0;
}

int lookupSymbol(SymbolTable *table, char name[], char scope[])
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

// Insert symbol

void insertSymbol(SymbolTable *table,
                  char name[],
                  char type[],
                  int line,
                  char scope[])
{
    if (table->count >= MAX_SYMBOLS)
    {
        printf("Symbol table is full!\n");
        return;
    }

    /* Check for redeclaration in the same scope */
    if (lookupSymbol(table, name, scope) != -1)
    {
        printf("Semantic Error (line %d): '%s' is already declared in scope '%s'\n",
               line, name, scope);
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