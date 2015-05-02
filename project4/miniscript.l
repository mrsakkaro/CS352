%{
#include <stdio.h>
#include "AST.h"
#include "y.tab.h"
#include <string.h>
#include "debug.h"

void yyerror(char *);
extern "C" int yylex();
%}

%option yylineno

delim   [ \t]
ws      {delim}+
letter  [A-Za-z]
digit   [0-9]
id      ([A-Za-z]([A-Za-z]|[0-9]|_)*)
num     {digit}*



%%

"<script type=\"text/JavaScript\">" {
	debug("<text/Javascript>\n");
	return SCRIPTYPE;
}

"</script>" {
	debug("</script>\n");
	return SLASHSCRIPT;
}

(document.write) {
	debug("docu.write");
	return DOCUWRITE;
}

"(" {
	debug("(");
	return OPENPARENT;
}

")" {
	debug(")");
	return CLOSEPARENT;
}

"{" {
	debug("CUROPENBRAC");
	return CUROPENBRAC;
}

"}" {
	debug("CURCLOSEBRAC");
	return CURCLOSEBRAC;
}

";" {
	debug("SEMICOLON");
	return SEMICOLON;
}

":" {
	debug("COLON");
	return COLON;
}

"." {
	debug("DOT");
	return DOT;
}

"=" {
	debug("EQUAL ");
	return EQUAL;
}

"," {
	debug("PAUSE ");
	return COMMA;
}

"*" {
	return TIME;
}

"+" {
	debug("PLUS ");
	return PLUS;
}

"-" {
	return MINUS;
}

"/" {
	return DIVIDE;
}

"\n" {
	// Newline character is found.
	debug("\n");
	return NEWLINE;
}

"var" {
	debug("var ");
	return VAR;
}

"if" {
	debug("IF");
	return IF;
}

"else" {
	debug("ELSE");
	return ELSE;
}

"<" {
	debug("LESS");
	return LESS;
}

">" {
	debug("GREAT");
	return GREAT;
}

"<=" {
	debug("LESSEQUAL");
	return LESSEQUAL;
}

">=" {
	debug("GREATEQUAL");
	return GREATEQUAL;
}

"==" {
	debug("EQEQUAL");
	return EQEQUAL;
}

"!=" {
	debug("NOTEQUAL");
	return NOTEQUAL;
}

"&&" {
	debug("ANDAND");
	return ANDAND;
}

"||" {
	debug("OROR");
	return OROR;
}

"!" {
	debug("EXCLAMATION");
	return EXCLAMATION;
}

"[" {
	debug("OPENBRAC");
	return OPENBRAC;
}

"]" {
	debug("CLOSEBRAC");
	return CLOSEBRAC;
}

"while" {
	debug("WHILE");
	return WHILE;
}

"break" {
	debug("BREAK");
	return BREAK;
}

"continue" {
	debug("CONTINUE");
	return CONTINUE;
}

"function" {
	debug("FUNCTION");
	return FUNCTION;
}

"return" {
	debug("RETURN");
	return RETURN;
}

{id} {
	debug("ID ");
	char * temp = strdup(yytext);
	yylval.string_val = strdup(temp);
	return ID;
}

[0-9]+ {
	debug("NUMBER ");
	char * temp = strdup(yytext);
	yylval.int_val = atoi(temp);
	return NUM;
}

["].[^\n"]*["] {
	debug("QQUO ");
	char * temp = strdup(yytext);
	temp++;
	char * brCheck;
	while(strstr(temp, "<br />")) {
		strncpy(temp, "\n", 6);
	}
//	fprintf(stderr, "temp is %s\n", temp);
	if (temp[strlen(temp)-1] == '\"') {
		temp[strlen(temp)-1] = '\0';
	}
	yylval.string_val = strdup(temp);
//	fprintf(stderr, "yyval is %s\n", yylval.string_val);
	return QQUO;
}

{ws} {

}

%%
