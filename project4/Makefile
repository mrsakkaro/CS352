all: miniscript lex.yy.c

miniscript: y.tab.c lex.yy.c
	g++ -g y.tab.c lex.yy.c AST.cpp -o parser -lfl

y.tab.c: miniscript.y
	bison -y -d -g -t -v --debug miniscript.y

lex.yy.c: miniscript.l
	lex miniscript.l

clean:
	rm -f lex.yy.c y.tab.c y.tab.h y.dot y.outputM@
