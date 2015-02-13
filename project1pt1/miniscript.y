%{
#include<stdio.h>
#include "debug.h"
%}

%token ID NUM PLUS SCRIPTYPE SLASHSCRIPT NEWLINE VAR EQUAL SEMICOLON TIME MINUS DIVIDE QQUO DOCUWRITE OPENPARENT CLOSEPARENT COMMA WS DOT
%start parse

%%

parse 	: SCRIPTYPE lines SLASHSCRIPT
		| SCRIPTYPE lines SLASHSCRIPT NEWLINE
		;

lines 	: line lines
		| /* It can be empty */
		;

line 	: VAR leftequ over
		| leftequ over
		| docu over
		| NEWLINE
	  	;

over 	: SEMICOLON
	  	| NEWLINE
		;

docu 	: DOCUWRITE OPENPARENT param CLOSEPARENT
	  	;

param 	: exps
	    | exps COMMA param
		|
	   	;

leftequ	: ID EQUAL exps
		| ID
;

exps 	: OPENPARENT exps CLOSEPARENT
	  	| OPENPARENT exps CLOSEPARENT arith
		| NUM arith
		| ID arith
		| QQUO arith
	  	| NUM
	  	| QQUO
		| ID
	  	;

arith 	: arithT
	   	| arithD
		| arithP
		| arithM
		;

arithP 	: PLUS exps
		;

arithM 	: MINUS exps
		;

arithT 	: TIME exps
		;

arithD 	: DIVIDE exps
		;

%%

FILE *yyin;
int yylineno;
yyerror(char *s)
{
	fprintf(stderr, "error: %s, line: %d\n", s, yylineno);
	return 1;
}

int debug = 0;

int main(int argc, char *argv[])
{
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


