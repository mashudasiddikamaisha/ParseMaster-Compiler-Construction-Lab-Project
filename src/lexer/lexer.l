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

"int"           { printf("KEYWORD: int\n"); }
"float"         { printf("KEYWORD: float\n"); }
"bool"          { printf("KEYWORD: bool\n"); }

"if"            { printf("KEYWORD: if\n"); }
"else"          { printf("KEYWORD: else\n"); }
"while"         { printf("KEYWORD: while\n"); }
"print"         { printf("KEYWORD: print\n"); }

"true"          { printf("BOOL: true\n"); }
"false"         { printf("BOOL: false\n"); }

{FLOATNUM}      { printf("FLOAT: %s\n", yytext); }
{INTNUM}        { printf("INTEGER: %s\n", yytext); }

{ID}            { printf("IDENTIFIER: %s\n", yytext); }

"+"             { printf("PLUS\n"); }
"-"             { printf("MINUS\n"); }
"*"             { printf("MULTIPLY\n"); }
"/"             { printf("DIVIDE\n"); }
"%"             { printf("MOD\n"); }

"=="            { printf("EQUAL\n"); }
"!="            { printf("NOT EQUAL\n"); }
"<="            { printf("LESS EQUAL\n"); }
">="            { printf("GREATER EQUAL\n"); }

"<"             { printf("LESS THAN\n"); }
">"             { printf("GREATER THAN\n"); }

"&&"            { printf("AND\n"); }
"||"            { printf("OR\n"); }
"!"             { printf("NOT\n"); }

"="             { printf("ASSIGN\n"); }

";"             { printf("SEMICOLON\n"); }

"("             { printf("LPAREN\n"); }
")"             { printf("RPAREN\n"); }

"{"             { printf("LBRACE\n"); }
"}"             { printf("RBRACE\n"); }

[ \t\r\n]+      ;

.               { printf("LEXICAL ERROR: %s\n", yytext); }

%%
