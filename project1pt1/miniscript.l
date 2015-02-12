%{
#include <stdio.h>
#include "y.tab.h"
#include <string.h>
%}

%option yylineno

delim   [ \t]
ws      {delim}+
letter  [A-Za-z]
digit   [0-9]
id      {letter}({letter}|{digit})*
num     {digit}*



%%

"<script type=\"text/JavaScript\">" {
	printf("<text/Javascript>\n");
	return SCRIPTYPE;
}

"</script>" {
	printf("</script>\n");
	return SLASHSCRIPT;
}

(document.write) {
	printf("docu.write");
	return DOCUWRITE;
}

"(" {
	printf("(");
	return OPENPARENT;
}

")" {
	printf(")");
	return CLOSEPARENT;
}

";" {
	printf("SEMICOLON");
	return SEMICOLON;
}

"=" {
	printf("EQUAL ");
	return EQUAL;
}

"," {
	printf("PAUSE ");
	return COMMA;
}

"*" {
	return TIME;
}

"+" {
	printf("PLUS ");
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
	printf("\n");
	return NEWLINE;
}

"var " {
	printf("var ");
	return VAR;
}

{id} {
	printf("ID ");
	return ID;
}

[0-9]+ {
	printf("NUMBER ");
	return NUM;
}

["].*["] {
	printf("QQUO ");
	return QQUO;
}

{ws} {
	
}



%%


