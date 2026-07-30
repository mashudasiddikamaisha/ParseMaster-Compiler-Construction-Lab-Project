all:
	flex -o lexer.c src/lexer/lexer.l
	gcc lexer.c src/main.c -lfl -o compiler

clean:
	rm -f compiler lexer.c