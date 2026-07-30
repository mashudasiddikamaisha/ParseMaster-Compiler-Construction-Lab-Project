CC = gcc
LEX = flex

TARGET = compiler

all: $(TARGET)

$(TARGET): lex.yy.c src/main.c
	$(CC) lex.yy.c src/main.c -lfl -o $(TARGET)

lex.yy.c: src/lexer/lexer.l
	$(LEX) src/lexer/lexer.l

clean:
	rm -f $(TARGET) lex.yy.c