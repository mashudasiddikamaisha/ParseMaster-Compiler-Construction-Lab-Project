#include <stdio.h>

extern int yyparse(void);

int main()
{
    printf("Parsing started...\n");

    if (yyparse() == 0)
    {
        printf("Program parsed successfully!\n");
    }
    printf("Parsing completed.\n");

    return 0;
}