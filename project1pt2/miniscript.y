%{
#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include <map>
#include <string>
#include <vector>
#include <iostream>

using namespace std;


extern "C" int yylex();
extern "C" FILE *yyin;
extern "C" int yylineno;
int yyerror(const char *s);

struct block {
	int type;
	void * data;
	int num;
};

map < string, struct block* > tbl;
vector <int>  arithTable;
int varType;
int quit;
string curID;
%}
%union {
	char * string_val;
	int int_val;
}
%token <string_val> ID QQUO 
%token <int_val> NUM
%token SCRIPTYPE SLASHSCRIPT NEWLINE VAR EQUAL SEMICOLON DOCUWRITE OPENPARENT CLOSEPARENT COMMA WS DOT BR CUROPENBRAC CURCLOSEBRAC
%left PLUS MINUS
%left TIME DIVIDE
%start parse
%type<string_val> param
%%

parse 	: SCRIPTYPE lines SLASHSCRIPT
		| SCRIPTYPE lines SLASHSCRIPT NEWLINE {
		//	varType = 0;
		}
		;

lines 	: line lines
		| /* It can be empty */
		;

line 	: VAR ID EQUAL exps over {
	  		// Declaire
			//printf("declaire ");
			struct block * temp = tbl[$2];
			if (temp != NULL) {
				printf("string \"undefined\" must be printed\n");
			}
			else {
				struct block * temp = (struct block*) malloc(sizeof(struct block));
				temp->type = varType;
				if ( varType == 1 ) {
					temp->num = $<int_val>4;
				} else if (varType = 3 ) {
					temp->data = strdup($<string_val>4);
				}
				tbl[$2] = temp;
			}
			//printf("exps is %d\n", $4);
		}
	/*	| VAR ID {
			struct block * temp = tbl[$2];
			if (temp == NULL) {
				
			}
		} EQUAL CUROPENBRAC object CURCLOSEBRAC SEMICOLON */
		| VAR ID
		| ID EQUAL exps over {
			// Initialize
			//printf("initialize ");
			struct block * temp = tbl[$1];
			if (temp == NULL) {
				printf("ID doesn't exist\n");
			} else {
				struct block * temp = (struct block*) malloc(sizeof(struct block));
				temp->type = varType;
				if ( varType == 1 ) {
					temp->num = $<int_val>4;
				} else if (varType = 3 ) {
					temp->data = $<string_val>4;
				}
				tbl[$1] = temp;
			}
		}
		| ID
		| DOCUWRITE OPENPARENT param CLOSEPARENT over 
		| NEWLINE
	  	;

over 	: SEMICOLON
	  	| NEWLINE
		;

param 	: exps {
	   		if (varType==1) {
				printf("\nint\n");
	   			printf("%d\n", $<int_val>1);
				varType = 0;
			}
			if ( varType == 3 ) {
				printf("\nstring\n");
				printf("%s\n", $<string_val>1);
				varType = 0;
			}
		}
	    | exps { 
			if(varType==1) {
				printf("\nint\n");
				printf("%d", $<int_val>1);
			} 
			if (varType==3) { 
				printf("\nstirng\n");
				printf("%s", $<string_val>1);
			} 
		} COMMA param
		|
	   	;

exps 	: NUM {
	  		if(varType == 3) {
				fprintf(stderr, "line:%d, Type Violation\n", yylineno);
			}
			varType = 1;
	  		$<int_val>$=$1;
	  	}
		| ID {
			struct block * temp = tbl[$1];
			if(temp == NULL) {
				printf("string \"undefined\" must be printed\n");
			} else {
				if (temp->type == 1) {
					varType = 1;
				//	printf("here! = %d\n", temp->num);
					$<int_val>$ = (temp->num);
				} else if (temp->type == 3) {
					varType = 3;
					$<string_val>$ = (char*)temp->data;
				}
			}
			//temp->type;
		}
		| QQUO {
			if(varType == 1) {
				fprintf(stderr, "line:%d, Type Violation\n", yylineno);
			}
			varType = 3;
			$<string_val>$=$<string_val>1;
		}
		| exps PLUS exps {
	  		if(varType == 3) {
				string temp = $<string_val>1 + $<string_val>2;
				$<string_val>$ = temp;
			}
			else if (varType == 1) {
				varType = 1;
				$<int_val>$=$<int_val>1+$<int_val>3;
			}
		}
		| exps MINUS exps {
	  		if(varType == 3) {
				fprintf(stderr, "line:%d, Type Violation\n", yylineno);
			}
			varType = 1;
			$<int_val>$=$<int_val>1-$<int_val>3;
		}
		| exps TIME exps {
	  		if(varType == 3) {
				fprintf(stderr, "line:%d, Type Violation\n", yylineno);
			}
			varType = 1;
			$<int_val>$=$<int_val>1*$<int_val>3;
		}
		| exps DIVIDE exps {
	  		if(varType == 3) {
				fprintf(stderr, "line:%d, Type Violation\n", yylineno);
			}
			varType = 1;
			$<int_val>$=$<int_val>1/$<int_val>3;
		}
		| OPENPARENT exps CLOSEPARENT {
	  		if(varType == 3) {
				fprintf(stderr, "line:%d, Type Violation\n", yylineno);
			}
			varType = 1;
			$<int_val>$=$<int_val>2;
		}
		;

object 	: ID EQUAL exps COMMA object
		;
%%

int yyerror(const char *s)
{
	fprintf(stderr, "line:%d, %s\n", yylineno, s);
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


