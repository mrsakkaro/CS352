all: miniscript lex.yy

miniscript: miniscript.l
	lex miniscript.l

lex.yy: lex.yy.c
	cc lex.yy.c -o miniscript -ll

clean:
	rm miniscript lex.yy.c
