%{
#include <stdio.h>
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
id      ([A-Za-z]([A-Za-z]|[0-9]|_)*)(\.([A-Za-z]([A-Za-z]|[0-9]|_)*))*
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

"<br />" {
	debug("<br />");
	return BR;
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
	temp[strlen(temp)-1] = '\0';
	yylval.string_val = strdup(temp);
	return QQUO;
}

{ws} {

}

%%


