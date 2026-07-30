%{
#include <stdio.h>
#include <stdlib.h>

/* parser.tab.h will be added later */
%}

%option noyywrap

LETTER      [a-zA-Z]
DIGIT       [0-9]

ID          ({LETTER}|_)(({LETTER}|{DIGIT}|_))*
INTNUM      {DIGIT}+
FLOATNUM    {DIGIT}+"."{DIGIT}+
SINGLE_COMMENT     "//".*
MULTI_COMMENT      "/*"([^*]|\*+[^*/])*\*+"/"

%%

"int"           { printf("KEYWORD: int\n"); }
"float"         { printf("KEYWORD: float\n"); }
"bool"          { printf("KEYWORD: bool\n"); }

"if"            { printf("KEYWORD: if\n"); }
"else"          { printf("KEYWORD: else\n"); }
"while"         { printf("KEYWORD: while\n"); }
"print"         { printf("KEYWORD: print\n"); }

"true"          { printf("TRUE\n"); }
"false"         { printf("FALSE\n"); }

{FLOATNUM}      { printf("FLOAT_LITERAL: %s\n", yytext); }
{INTNUM}        { printf("INT_LITERAL: %s\n", yytext); }

{ID}            { printf("IDENTIFIER: %s\n", yytext); }
{SINGLE_COMMENT}   ;

{MULTI_COMMENT}    ;

"+"             { printf("PLUS\n"); }
"-"             { printf("MINUS\n"); }
"*"             { printf("MULTIPLY\n"); }
"/"             { printf("DIVIDE\n"); }
"%"             { printf("MOD\n"); }

"=="            { printf("EQ\n"); }
"!="            { printf("NE\n"); }
"<="            { printf("LE\n"); }
">="            { printf("GE\n"); }
"<"             { printf("LT\n"); }
">"             { printf("GT\n"); }

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

. {
    printf("LEXICAL ERROR: Invalid character '%s'\n", yytext);
}

%%
