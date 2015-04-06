#include "AST.h"
#include <stdio.h>
#include <map>

int main(){
//	Number *idk = new Number(5);
	map <string, Value*> Table;


	Value * eh = new Value(5);
	Table["A"] = eh;

	Program P;
	Expression * s = new Assign(new SimpleVar( "A", Table), new Plus( new Number (3), new SimpleVar("A", Table))	);
	P.addStatement(new Assign(new SimpleVar( "A", Table), new Plus( new Number (3), new SimpleVar("A", Table))	));
	DocumentWrite * dw = new DocumentWrite();
	dw->addExpression(s);
	P.addStatement(dw);
	P.execute();

	printf("%d\n", Table["A"]->getInt());

}
