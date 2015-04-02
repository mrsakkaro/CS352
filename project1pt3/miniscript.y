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
}
%token <string_val> ID QQUO 
%token <int_val> NUM
%token SCRIPTYPE SLASHSCRIPT NEWLINE VAR EQUAL COLON SEMICOLON DOCUWRITE OPENPARENT CLOSEPARENT COMMA WS DOT CUROPENBRAC CURCLOSEBRAC PLUS MINUS TIME DIVIDE BR
%start parse
%type<string_val> param
%%

parse 	: SCRIPTYPE lines SLASHSCRIPT
		| SCRIPTYPE lines SLASHSCRIPT NEWLINE {
		//	varType = 0;
		}
		;

lines 	: line/* {printf("LINE\n"); }*/ lines
		| /* It can be empty */
		;

line 	: VAR ID EQUAL exps over {
	  		// Declaire
			//printf("declaire ");
			struct block * temp = tbl[$2];
	//		printf("ID is %s\n", $2);
			if (temp != NULL) {
	//			printf("NOT NULL\n");
				temp->type = 0;
				temp->num = 0;
				temp->data = strdup("");
			}
			else {
				temp = (struct block*) malloc(sizeof(struct block));
			}
	//		printf("HIT %d\n", varType);
			temp->type = varType;
			if ( varType == 1 ) {
				temp->num = $<int_val>4;
			} else if (varType == 3 ) {
				temp->data = strdup($<string_val>4);
			} else if (varType == 0 ) {
				// this 
				temp->type = -1;
			}
			tbl[$2] = temp;
			
			//printf("exps is %d\n", $4);
			varType = -2;
		}
		| VAR ID over{			
			struct block * temp = tbl[$2];
			if (temp != NULL) {
			}
			else {
				temp = (struct block*) malloc(sizeof(struct block));
			}
			temp->type = 0;
			temp->num = 0;
			temp->data = strdup("");
			tbl[$2] = temp;
			varType = -2;
			
		}
		| VAR ID EQUAL CUROPENBRAC {
	//		printf("FULL OBJECT\n");
			struct block * temp = tbl[$2];
			if (temp != NULL) {
				fprintf(stderr, "Line %d, type violation\n", yylineno);
				lineQuit = 1;
			} else {
				temp = (struct block*) malloc(sizeof(struct block));
				curID = $2;
				temp->type = 2;
				tbl[$2] = temp;
			}
		} object CURCLOSEBRAC over { 
			lineQuit = 0;
		}
		| VAR ID EQUAL CUROPENBRAC CURCLOSEBRAC {
	//		printf("just Name\n");
			struct block * temp = tbl[$2];
			if (temp != NULL) {
				fprintf(stderr, "Line %d, type violation\n", yylineno);
				lineQuit = 1;
			} else {
				struct block * temp = (struct block*) malloc(sizeof(struct block));
				temp->type = 2;
				tbl[$2] = temp;
			}
		} over { varType = -2; lineQuit = 0;}
		| ID  EQUAL exps over {
			// Initialize
			char * token;
			string parent = $1;
			token = strtok(strdup($1), ".");
			if(strcmp(token, $1) == 0) {
			// There is no .
				struct block * temp = tbl[$1];
				if (temp == NULL) {
					fprintf(stderr, "Line %d, type violation\n", yylineno-1);
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
			// There is .
				struct block * temp = tbl[token];
				if(temp->type == 2) {
		//			printf("token is %s\n", token);
					parent = token;
					token = strtok(NULL, ".");
					string oName = parent + "." +token;
					if( (token = strtok(NULL, ".")) == NULL) {
		//			printf("Name of object is %s\n", oName.c_str());
					if(temp == NULL) {
						fprintf(stderr, "Line %d, type violation\n", yylineno);
					} else {
						temp = tbl[oName];
						if(temp == NULL) {
							temp = (struct block*) malloc(sizeof(struct block));
						}
						temp->type = varType;
						if ( varType == 1 ) {
					//		printf("object INT = %d\n", $<int_val>3);
							temp->num = $<int_val>3;
						} else if (varType == 3 ) {
					//		printf("object STRING = %s\n", $<string_val>3);
							temp->data = $<string_val>3;
						}
					//	printf("NAME is %s\n\n", oName.c_str());
						tbl[oName] = temp;
						oName = "";
					}
					} else {
						fprintf(stderr, "syntax error\n");
						return 0;
					}
				} else {
					fprintf(stderr, "Line %d, type violation\n", yylineno-1);
				}
			}
			varType = -2;
		}
/*		| ID */
		| DOCUWRITE OPENPARENT param CLOSEPARENT over 
		| NEWLINE
	  	;

over 	: SEMICOLON
	  	| NEWLINE
		;

param 	: exps {
	   		if ( varType  == -1 ) {
			//	fprintf(stderr, "Line %d, %s has no value\n", yylineno, strdup(curID.c_str()));
			}
			if ( varType ==  -2 || varType == 0 )
			{
				fprintf(stderr, "undefined");
			}
			
	   		if (varType==1) {
				yP = 1;
		//		printf("\nint\n");
		//		if (lineQuit == 0 ) {
	   				printf("%d", $<int_val>1);
					varType = -2;
		//		}
				lineQuit = 0;
			}
			if ( varType == 3 ) {
				yP = 1;
		//		printf("\nstring\n");
	//			if(lineQuit == 0) {

				string str = $<string_val>1;
				if(str.find("<br />") != std::string::npos) {
					printf("%s", $<string_val>1);
				} else {
					fprintf(stderr, "Line %d, type violation\n", yylineno);
					lineQuit = 1;
				}
				varType = -2;
	//			}
				lineQuit=0;
			}
		
		}
	    | exps { 
			if (varType == -1) {
			//	fprintf(stderr, "Line %d, %s has no value\n", yylineno, strdup(curID.c_str()));
			}
			if ( varType == -2 || varType == 0)
			{
			//		fprintf(stderr, "Line %d, %s has no value\n", yylineno, $1);
				fprintf(stderr, "undefined");
			}
			
	   		if (varType==1) {
				yP = 1;
		//		printf("\nint\n");
				if (lineQuit == 0 ) {
	   				printf("%d", $<int_val>1);
					varType = -2;
				}
			}
			if ( varType == 3 ) {
				yP = 1;
		//		printf("\nstring\n");
				if(lineQuit == 0) {
					string str = $<string_val>1;
					if(str.find("<br />") != std::string::npos) {
						printf("%s", $<string_val>1);
					} else {
						fprintf(stderr, "Line %d, type violation\n", yylineno);
						lineQuit = 1;
					}
					varType = -2;
				}
			}
		} COMMA param 
		|
	   	;

exp2 	: exp2 TIME exp3 {
	  		if(varType == 3) {
				fprintf(stderr, "Line %d, type violation\n", yylineno);
			}
			if(varType == 1) {
		//		printf("TIMES");
				$<int_val>$=$<int_val>1 * $<int_val>3;
			}
	  	}
	  	| exp2 DIVIDE exp3 {
			if(varType == 3) {
				fprintf(stderr, "Line %d, type violation\n", yylineno);
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
		/*	if(varType == 1) {
				fprintf(stderr, "Line %d, type violation2\n", yylineno);
			} else { */
			varType = 3;
	//		printf("QQUO = %s\n", $<string_val>1);
			$<string_val>$=$<string_val>1;
	//		}
		}
		;

exp3 	: OPENPARENT exps CLOSEPARENT {
	  		if(varType == 3) {
				fprintf(stderr, "Line %d, type violation\n", yylineno);
			}
			if (varType == 1) {
				$<int_val>$=$<int_val>2;
			}
	  	}
	  	| NUM {
	  /*		if(varType == 3) {
				fprintf(stderr, "Line %d, type violation\n", yylineno);
			} */
			varType = 1;
	  		$<int_val>$=$1;
			
	  	}
		| ID {
	//		printf("\nID in exp is %s\n", $1);
			struct block * temp = tbl[$1];
			if(temp == NULL) {
				
				if( yP == 1 ) {
					printf("\n");
				}
				fprintf(stderr, "Line %d, type violation\n", yylineno);
				curID = $1;
		//		printf("undefined");
				varType = -2;
				lineQuit = -1;
			} else {
				if (temp->type == 1) {
					varType = 1;
	//				printf("here D! = %d\n", temp->num);
					$<int_val>$ = (temp->num);
				} else if (temp->type == 3) {
					varType = 3;
	//				printf("here S! = %s\n", (char*)temp->data);
					$<string_val>$ = (char*)temp->data;
				} else if (temp->type == 0 ) {
					fprintf(stderr, "Line %d, %s has no value\n", yylineno, $1);
			//		printf("undefined");
					varType = 0;
				}
			}
		}
		;

exps 	: exps PLUS exp2 {
	  		if(varType == 1) {
	//			printf("%d PLUS %d ", $<int_val>1, $<int_val>3);
				$<int_val>$ = $<int_val>1 + $<int_val>3;
			}
			else if(varType == 3) {
				string temp = $<string_val>1;
				temp = temp + $<string_val>3;
			//	printf("temp is %s\n", strdup(temp.c_str()));
				$<string_val>$ = strdup(temp.c_str());
			} else if (varType == 0 ) {
			}
	  	}
	  	| exps MINUS exp2 {
			if(varType == 3) {
				fprintf(stderr, "Line %d, type violation\n", yylineno);
			}
			if (varType == 1) {
				$<int_val>$=$<int_val>1-$<int_val>3;
			}
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
	//		printf("Name of object is %s\n", oName.c_str());
			struct block * temp = tbl[oName];
			if(temp != NULL) {
				fprintf(stderr, "Error 1\n");
			} else {
				struct block * temp = (struct block*) malloc(sizeof(struct block));
	//			fprintf(stderr, "varType = %d\n", varType);
				temp->type = varType;
				if ( varType == 1 ) {
	//				printf("object INT = %d\n", $<int_val>3);
					temp->num = $<int_val>3;
				} else if (varType == 3 ) {
	//				printf("object STRING = %s\n", $<string_val>3);
					temp->data = $<string_val>3;
				}
				tbl[oName] = temp;
			}
			varType = 2;
		}
		;

object 	: object1
		| object1 NEWLINE 
		| NEWLINE object1
		| NEWLINE object1 NEWLINE
		| object COMMA object1 
		| object COMMA NEWLINE object1
		| object COMMA NEWLINE object1 NEWLINE 
	/*	| object COMMA NEWLINE object */
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


