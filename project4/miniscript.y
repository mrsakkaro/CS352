%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "AST.h"
#include <map>
#include <string>
#include <vector>
#include <iostream>

using namespace std;


extern "C" int yylex();
extern "C" FILE *yyin;
extern "C" int yylineno;
int yyerror(const char *s);

bool simpleStmt = false;
bool isDecl = false;

map < string, Value* > tbl;
vector <int>  arithTable;

stack <vector <Statement*> * > blocks;
stack <IfStmt *> ifStmt;
vector <Statement*> block;
stack <FuncCall *> fcstack;

Function * func;

Program prog;
DocumentWrite * docuwrite;
ObjectDef * objDef;
ArrayDef * arrDef;
string parent;

void addStatement(Statement * stmt){
	blocks.top() -> push_back(stmt);
}

void pushBlock( vector <Statement *> * newBlock ) {
	blocks.push(newBlock);
}

void popBlock() {
	blocks.pop();
}

void getTop(vector <Statement * > & block)
{
	block = *blocks.top();
}

/*
 * varType
 */
int varType;
int lineQuit;
string curID;

int yP = 0;

%}
%union {
	char *string_val;
	int int_val;
	Expression *expr_val;
	Variable * var_val;
	Block * block_val;
	FuncCall * func_val;
}
%token <string_val> ID QQUO
%token <int_val> NUM
%token SCRIPTYPE SLASHSCRIPT NEWLINE VAR EQUAL COLON SEMICOLON DOCUWRITE OPENPARENT CLOSEPARENT COMMA WS DOT CUROPENBRAC CURCLOSEBRAC PLUS MINUS TIME DIVIDE IF ELSE LESS GREAT LESSEQUAL GREATEQUAL EQEQUAL NOTEQUAL ANDAND OROR EXCLAMATION OPENBRAC CLOSEBRAC WHILE BREAK CONTINUE FUNCTION RETURN
%start parse
%type<expr_val> exp3 exp2 exps exp0 exp1 exp4 exp5 cond
%type<var_val> id
%type<block_val> body
%type<func_val> funcCall
%%

parse 	: SCRIPTYPE {pushBlock(&prog.nodes);} lines end {
			popBlock();
		//	prog.printAST();
			//fprintf(stderr, "DONE\n");
			prog.execute();
		}
		;

end 	: SLASHSCRIPT NEWLINE
	 	| SLASHSCRIPT
		;

lines 	: line  lines
		| /* It can be empty */
		;

line 	: VAR ID over{
			addStatement(new Var_Decl($2, yylineno));
		}
		| id EQUAL CUROPENBRAC {
			objDef = new ObjectDef(yylineno);
			addStatement(new Assign($1, objDef, yylineno));
		}  object CURCLOSEBRAC over {
		}
		| id EQUAL CUROPENBRAC CURCLOSEBRAC  over {
			addStatement(new Assign($1, new ObjectDef(yylineno),yylineno));
		}
		| id EQUAL OPENBRAC {
			arrDef = new ArrayDef(yylineno);
			addStatement(new Assign($1, arrDef,yylineno));
		} array over{}
		| id  EQUAL exps over {
			addStatement(new Assign($1, $3, yylineno));
		}
		| DOCUWRITE {docuwrite = new DocumentWrite(yylineno);} OPENPARENT param CLOSEPARENT over {
			addStatement(docuwrite);
		}
		| ifstmt 
		| while
		| break
		| continue
		| funcDecl
		| funcCall over {
			addStatement($1);
		}
		| RETURN exps over {
			addStatement(new ReturnStmt($2, yylineno));
		}
		| RETURN over {
			addStatement(new ReturnStmt(NULL, yylineno));
		}
		| NEWLINE
	  	;

while 	: WHILE OPENPARENT cond CLOSEPARENT {
	   		WhileStmt * temp = new WhileStmt($3, yylineno);
			addStatement(temp);
			pushBlock(&temp->whileBlock);
	   	} 
		body { 
			popBlock();
		}
	   	;

funcCall : ID OPENPARENT {
		 	FuncCall * fc = new FuncCall($1, yylineno);
			fcstack.push(fc);
		 } fcparam CLOSEPARENT {
		 	FuncCall * fc = fcstack.top();
			fcstack.pop();
			$$ = fc;
		}
		 ;

fcparam : exps { 
			FuncCall *fc = fcstack.top();
			fc->expressions.push_back($1);
		}
		| exps {
			FuncCall *fc = fcstack.top();
			fc->expressions.push_back($1);
		}
		COMMA fcparam
		;

funcDecl : FUNCTION ID OPENPARENT {
	  			func = new Function();
				funcTable[$2] = func;
				pushBlock(&func->funcBlock);
			}
	  		funcparam CLOSEPARENT body {
				popBlock();

			}
			NEWLINE
	  	;

funcparam : funcparam2
		  |
		  ;

funcparam2 : ID {
		  	func->params.push_back($1);
		  }
		  | ID {
		  	func->params.push_back($1);
		  } COMMA funcparam
		  ;

break 	: BREAK {
	   		addStatement(new BreakStmt(yylineno));
	   	}
		;

continue : CONTINUE {
		 	addStatement(new ContStmt(yylineno));
		 }
		 ;

ifstmt 	: IF OPENPARENT cond CLOSEPARENT {
		//	pushBlock();
			IfStmt * temp = new IfStmt($3, yylineno);
			addStatement(temp);
			ifStmt.push(temp);
			pushBlock(&temp->ifBlock);
		} body {popBlock();
			IfStmt * temp = ifStmt.top();
			ifStmt.pop();
			pushBlock(&temp->elseBlock);
		}elsestmt {
			popBlock();
		} 
		;

elsestmt : ELSE body NEWLINE
		 | ELSE ifstmt
		 | NEWLINE
		 ;

cond 	: exps {
	  		$$ = $1;
	  	}
	  	;

body 	: CUROPENBRAC NEWLINE lines {
	  // $$ = block;
	  }CURCLOSEBRAC
	  	;

id 		:
	 	ID DOT ID {
			$$ = new ObjectVar($3,new SimpleVar($1, yylineno), yylineno);

		}
		| ID OPENBRAC exps CLOSEBRAC {
			$$ = new ArrayVar($3, new SimpleVar($1, yylineno), yylineno);
		}
		| ID {
			$$ = new SimpleVar($1, yylineno);
			parent = $<string_val>1;
		}
		| VAR ID {
			SimpleVar * sv = new SimpleVar($2, yylineno);
			sv -> setDecl(true);
			$$ = sv;

		}
		;

over 	: SEMICOLON
	  	| NEWLINE
		;

param 	: exps {
	   		docuwrite->addExpression($1);
		}
	    | exps {
			docuwrite->addExpression($1);
		} COMMA param
		|
	   	;

exp4 	: exp4 TIME exp5 {
	  		$$ = new Times($1, $3, yylineno);
	  	}
	  	| exp4 DIVIDE exp5 {
			$$ = new Divide($1, $3, yylineno);
		}
		| exp5 {
			$$ = $1;
		}
		| QQUO {
			$$ = new Word($1, yylineno);
		}
		;

exp5 	: OPENPARENT exps CLOSEPARENT {
	  		$$ = $2;
	  	}
	  	| NUM {
			$$ = new Number($1, yylineno);
	  	}
		| id {
			$$ = $1;
		}
		| funcCall {
			$$ = $1;
		}
		;

exp3 	: exp3 PLUS exp4 {
	  		$$ = new Plus($1, $3, yylineno);
	  	}
	  	| exp3 MINUS exp4 {
			$$ = new Minus($1, $3, yylineno);
		}
		| exp4 {
			$$ = $1;
		}
		;

exp2 	: exp2 GREAT exp3 {
			$$ = new Comparison(GT, $1, $3, yylineno);
		}
		| exp2 GREATEQUAL exp3 {
			$$ = new Comparison(GE, $1, $3, yylineno);
		}
		| exp2 LESS exp3 {
			$$ = new Comparison(LT, $1, $3, yylineno);
		}
		| exp2 LESSEQUAL exp3 {
			$$ = new Comparison(LE, $1, $3, yylineno);
		}
		| exp3 {
			$$ = $1;
		}

exp1 	: exp1 EQEQUAL exp2 {
			$$ = new Comparison(EQ, $1, $3, yylineno);
		}
		| exp1 NOTEQUAL exp2 {
			$$ = new Comparison(NE, $1, $3, yylineno);
		}
		| exp2 {
			$$ = $1;
		}

exp0 	: exp0 ANDAND exp1 {
			$$ = new Comparison(AND, $1, $3, yylineno);
		}
		| exp1 {
			$$ = $1;
		}

exps 	: exps OROR exp0{
			$$ = new Comparison(OR, $1, $3, yylineno);
		}
		| exp0 {
			$$ = $1;
		}

object1 : ID COLON exps {
			objDef->addProperty($1, $3);
		}
		;

object 	: object1 {
		}
		| object1 NEWLINE
		| NEWLINE object1
		| NEWLINE object1 NEWLINE
		| object COMMA object1
		| object COMMA NEWLINE object1
		| object COMMA NEWLINE object1 NEWLINE
	/*	| object COMMA NEWLINE object */
		;

arrayE 	: exps {
			arrDef->addProperty($1);
		}
		;

array 	: arrayL NEWLINE CLOSEBRAC
	   	| NEWLINE arrayL NEWLINE CLOSEBRAC
		| NEWLINE arrayL CLOSEBRAC
		| arrayL CLOSEBRAC
		| NEWLINE CLOSEBRAC
		| CLOSEBRAC
		;

arrayL 	: arrayE
		| arrayL COMMA NEWLINE arrayE
		| arrayL COMMA arrayE
/*
		| NEWLINE arrayE
		| NEWLINE arrayE NEWLINE
		| array NEWLINE  */
		;

%%

int yyerror(const char *s)
{
	fprintf(stderr, "%s\n", s);
//	fprintf(stderr, "line:%d, %s\n", yylineno, s);
	return 1;
}

int debug = 0;

int main(int argc, char *argv[])
{
setbuf(stdout, NULL);
	//yydebug = 1;
	if (argc == 2) {
		FILE *file;
		file = fopen(argv[1], "r");
		if (!file) {
			fprintf(stderr, "could not open %s\n", argv[1]);
		} else{
			yyin = file;
			//yyparse() will call yylex()
			yyparse();
		}
	} else {
		fprintf(stderr, "format: ./yacc_example [filename]\n");
	}
	return 0;
}
