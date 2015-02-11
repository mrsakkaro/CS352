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

";" {
	printf("SEMICOLON");
	return SEMICOLON;
}

"=" {
	printf("EQUAL ");
	return EQUAL;
}

"*" {
	return TIME;
}

"+" {
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

{ws} {
	
}



%%


