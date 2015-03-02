%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	char *string_val;
	int int_val;
}
%token <string_val> ID QQUO 
%token <int_val> NUM
%token SCRIPTYPE SLASHSCRIPT NEWLINE VAR EQUAL COLON SEMICOLON DOCUWRITE OPENPARENT CLOSEPARENT COMMA WS DOT BR CUROPENBRAC CURCLOSEBRAC PLUS MINUS TIME DIVIDE
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
			varType = 0;
		}
		| VAR ID
		| VAR ID EQUAL {
			struct block * temp = tbl[$2];
			if (temp != NULL) {
				printf("error!!\n");
				quit = 1;
			} else {
				struct block * temp = (struct block*) malloc(sizeof(struct block));
				curID = $2;
				temp->type = 2;
				tbl[$2] = temp;
			}
		} CUROPENBRAC object CURCLOSEBRAC over { 
			quit = 0;
		}
		| ID EQUAL exps over {
			// Initialize
			//printf("initialize ");
			char * token;
			if((token = strtok($1, ".")) == NULL) {
				struct block * temp = tbl[$1];
				if (temp == NULL) {
					printf("ID doesn't exist\n");
				} else {
				//	struct block * temp = (struct block*) malloc(sizeof(struct block));
					temp->type = varType;
					if ( varType == 1 ) {
						temp->num = $<int_val>3;
					} else if (varType == 3 ) {
						temp->data = $<string_val>3;
					}
					tbl[$1] = temp;
				}
			} else {
				struct block * temp = tbl[token];
				printf("token is %s\n", token);
				string parent = token;
				token = strtok(NULL, ".");
				string oName = parent + "." +token;
				printf("Name of object is %s\n", oName.c_str());
				if(temp == NULL) {
					fprintf(stderr, "Error 1\n");
				} else {
					temp = tbl[oName];
					if(temp == NULL) {
						printf("NEW\n");
						temp = (struct block*) malloc(sizeof(struct block));
					}
					temp->type = varType;
					if ( varType == 1 ) {
						printf("object INT = %d\n", $<int_val>3);
						temp->num = $<int_val>3;
					} else if (varType == 3 ) {
						printf("object STRING = %s\n", $<string_val>3);
						temp->data = $<string_val>3;
					}
					printf("NAME is %s\n\n", oName.c_str());
					tbl[oName] = temp;
					oName = "";
				}

			}
			varType = 0;
		}
		| ID
		| DOCUWRITE {printf("\ndocuwrite");}OPENPARENT param CLOSEPARENT over 
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
			if (varType==1) {
				printf("\nint\n");
				printf("%d", $<int_val>1);
				varType = 0;
			} 
			if (varType==3) { 
				printf("\nstirng\n");
				printf("%s", $<string_val>1);
				varType = 0;
			} 
		} COMMA param
		|
	   	;

exp2 	: exp2 TIME exp3 {
	  		if(varType == 3) {
				fprintf(stderr, "line:%d, Type Violation6\n", yylineno);
			}
			if(varType == 1) {
		//		printf("TIMES");
				$<int_val>$=$<int_val>1*$<int_val>3;
			}
	  	}
	  	| exp2 DIVIDE exp3 {
			if(varType == 3) {
				fprintf(stderr, "line:%d, Type Violation5\n", yylineno);
			}
			if(varType == 1) {
				$<int_val>$=$<int_val>1/$<int_val>3;
			}
		}
		| exp3 {
			if(varType == 1) {
				$<int_val>$=$<int_val>1;
			}
			if(varType == 3) {
				$<string_val>$=$<string_val>1;
			}
		}
		| QQUO {
			if(varType == 1) {
				fprintf(stderr, "line:%d, Type Violation4\n", yylineno);
			}
			varType = 3;
			printf("QQUO = %s\n", $<string_val>1);
			$<string_val>$=$<string_val>1;
		}
		;

exp3 	: OPENPARENT exps CLOSEPARENT {
	  		if(varType == 3) {
				fprintf(stderr, "line:%d, Type Violation3\n", yylineno);
			}
	//		varType = 1;
			$<int_val>$=$<int_val>2;
	  	}
	  	| NUM {
	  		if(varType == 3) {
				fprintf(stderr, "line:%d, Type Violation2\n", yylineno);
			}
			varType = 1;
	//		printf("NUM is %d\n", $1);
	  		$<int_val>$=$1;
	  	}
		| ID {
			printf("\nID in exp is %s\n", $1);
			struct block * temp = tbl[$1];
			if(temp == NULL) {
				printf("string \"undefined\" must be printed\n");
			} else {
				if (temp->type == 1) {
					varType = 1;
					printf("here D! = %d\n", temp->num);
					$<int_val>$ = (temp->num);
				} else if (temp->type == 3) {
					varType = 3;
					printf("here S! = %s\n", (char*)temp->data);
					$<string_val>$ = (char*)temp->data;
				}
			}
		}
		;

exps 	: exps PLUS exp2 {
	  		if(varType == 1) {
	//			printf("%d PLUS %d ", $<int_val>1, $<int_val>3);
				$<int_val>$ = $<int_val>1 + $<int_val>3;
			}
			if(varType == 3) {
				string temp = $<string_val>1;
				temp = temp + $<string_val>3;
			//	printf("temp is %s\n", strdup(temp.c_str()));
				$<string_val>$ = strdup(temp.c_str());
			}
	  	}
	  	| exps MINUS exp2 {
			if(varType == 3) {
				fprintf(stderr, "line:%d, Type Violation1\n", yylineno);
			}
			varType = 1;
			$<int_val>$=$<int_val>1-$<int_val>3;
		}
		| exp2 {
	  		if(varType == 1) {
				$<int_val>$ = $<int_val>1;
			}
			if(varType == 3) {
				$<string_val>$ = $<string_val>1;
			}
		}
		;

object1 : ID COLON exps {
			string oName = curID + "." +$1;
			printf("Name of object is %s\n", oName.c_str());
			struct block * temp = tbl[oName];
			if(temp != NULL) {
				fprintf(stderr, "Error 1\n");
			} else {
				struct block * temp = (struct block*) malloc(sizeof(struct block));
				temp->type = varType;
				if ( varType == 1 ) {
					printf("object INT = %d\n", $<int_val>3);
					temp->num = $<int_val>3;
				} else if (varType == 3 ) {
					printf("object STRING = %s\n", $<string_val>3);
					temp->data = $<string_val>3;
				}
				tbl[oName] = temp;
			}
			varType = 0;
		}
		;

object 	: object1
		| object COMMA object1  
		| object NEWLINE 	
	/*	| object COMMA NEWLINE object */
		|
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


