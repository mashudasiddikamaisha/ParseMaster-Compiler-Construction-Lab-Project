CC = gcc
LEX = flex
YACC = bison

TARGET = compiler

all: $(TARGET)

$(TARGET): parser.tab.c lex.yy.c src/main.c src/ast/ast.c src/semantic/semantic.c src/symboltable/symbol_table.c
	$(CC) parser.tab.c lex.yy.c src/main.c src/ast/ast.c src/semantic/semantic.c src/symboltable/symbol_table.c -lfl -o $(TARGET)

parser.tab.c parser.tab.h: src/parser/parser.y
	$(YACC) -d src/parser/parser.y

lex.yy.c: src/lexer/lexer.l parser.tab.h
	$(LEX) src/lexer/lexer.l

clean:
	rm -f $(TARGET) lex.yy.c parser.tab.c parser.tab.h