#include <stdio.h>
#include "symbol_table.h"

int main()
{

    SymbolTable table;

    // initialize symbol table
    initSymbolTable(&table);

    // insert some variables
    
    insertSymbol(&table,
             "x",
             "int",
             1,
             "global");

    insertSymbol(&table,
             "y",
             "float",
             5,
             "global");

    insertSymbol(&table,
             "name",
             "string",
             10,
             "local");             

    // display symbol table

    printSymbolTable(&table);

    return 0;
}