%{
#include <stdio.h>
#include "y.tab.h"
#include <string.h>
#include "debug.h"
%}

%option yylineno

delim   [ \t]
ws      {delim}+
letter  [A-Za-z]
digit   [0-9]
id      {letter}({letter}|{digit}|_)*
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

"." {
	debug("dot ");
	return DOT;
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

";" {
	debug("SEMICOLON");
	return SEMICOLON;
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

{id} {
	debug("ID ");
	return ID;
}

[0-9]+ {
	debug("NUMBER ");
	return NUM;
}

["].*["] {
	debug("QQUO ");
	return QQUO;
}

{ws} {

}

%%


