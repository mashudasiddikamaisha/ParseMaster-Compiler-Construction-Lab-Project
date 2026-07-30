%{
#include <stdio.h>
#include <stdlib.h>

/* parser.tab.h will be added later */
%}

%option noyywrap

LETTER      [a-zA-Z]
DIGIT       [0-9]

ID          {LETTER}({LETTER}|{DIGIT}|_)*
INTNUM      {DIGIT}+
FLOATNUM    {DIGIT}+"."{DIGIT}+

%%

"int"       { printf("KEYWORD: int\n"); }
"float"     { printf("KEYWORD: float\n"); }
"bool"      { printf("KEYWORD: bool\n"); }

%%
