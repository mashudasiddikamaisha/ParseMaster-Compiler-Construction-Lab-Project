%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/ast/ast.h"
#include "parser.tab.h"
%}

%option noyywrap
%option yylineno

LETTER      [a-zA-Z]
DIGIT       [0-9]

ID          ({LETTER}|_)(({LETTER}|{DIGIT}|_))*
INTNUM      {DIGIT}+
FLOATNUM    {DIGIT}+"."{DIGIT}+
SINGLE_COMMENT     "//".*
MULTI_COMMENT      "/*"([^*]|\*+[^*/])*\*+"/"

%%

"int"           { return INT; }
"float"         { return FLOAT; }
"bool"          { return BOOL; }

"if"            { return IF; }
"else"          { return ELSE; }
"while"         { return WHILE; }
"print"         { return PRINT; }

"true"          { return TRUE;}
"false"         { return FALSE; }

{FLOATNUM}      { yylval.text = strdup(yytext);
                  return FLOAT_LITERAL; }
{INTNUM}        { yylval.text = strdup(yytext);
                  return INT_LITERAL; }

{ID}            { yylval.text = strdup(yytext);
                  return ID; }
{SINGLE_COMMENT}   ;

{MULTI_COMMENT}    ;

"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return MULTIPLY; }
"/"             { return DIVIDE; }
"%"             { return MOD; }

"=="            { return EQ; }
"!="            { return NE; }
"<="            { return LE; }
">="            { return GE; }
"<"             { return LT; }
">"             { return GT; }

"&&"            { return AND; }
"||"            { return OR; }
"!"             { return NOT; }

"="             { return ASSIGN; }

";"             { return SEMICOLON; }

"("             { return LPAREN; }
")"             { return RPAREN; }

"{"             { return LBRACE; }
"}"             { return RBRACE; }

[ \t\r\n]+      ;

. {
    printf("LEXICAL ERROR: Invalid character '%s'\n", yytext);
}

%%