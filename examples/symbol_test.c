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
                 "int");


    insertSymbol(&table,
                 "y",
                 "float");


    insertSymbol(&table,
                 "name",
                 "string");

    // display symbol table

    printSymbolTable(&table);

    return 0;
}