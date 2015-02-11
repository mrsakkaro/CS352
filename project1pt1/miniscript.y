%{
#include<stdio.h>
%}

%token ID NUM PLUS SCRIPTYPE SLASHSCRIPT NEWLINE VAR EQUAL SEMICOLON TIME MINUS DIVIDE
%start parse

%%

parse 	: SCRIPTYPE exps SLASHSCRIPT
		| SCRIPTYPE exps SLASHSCRIPT NEWLINE
		;

exps 	: exps exp
	  	| exp
		;

exp 	: NEWLINE
		| VAR leftequ
		| leftequ
	  	;

leftequ	: ID EQUAL rightequ
;

rightequ : NUM
		 | equ
		 ;

equ 	: ID EQUAL plussign
	 	| ID EQUAL minusign
		| ID EQUAL timesign
		| ID EQUAL dividesign
;

plussign : NUM PLUS NUM
		 ;

minusign : NUM MINUS NUM
		 ;

timesign : NUM TIME NUM
		 ;

dividesign : NUM DIVIDE NUM
		   ;

%%

FILE *yyin;
int yylineno;
yyerror(char *s)
{
	fprintf(stderr, "error: %s, line: %d\n", s, yylineno);
}

main(int argc, char *argv[])
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
}


