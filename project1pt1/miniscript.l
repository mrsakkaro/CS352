%{
#include <stdio.h>
#include "y.tab.h"


%}

%option yylineno

delim   [ \t]
ws      {delim}+
letter  [A-Za-z]
digit   [\d]
id      {letter}({letter}|{digit})*
num     {digit}+



%%

"<script type=\"text/JavaScript\">" {
	return SCRIPTYPE;
}

(["]^\n["]) {
	char * temp = strdup(yytext);
	temp++;
	temp[strlen(temp)-1] = '\0';
	yylval.string_val = strdup(temp);
	return QWORD;
}

";" {
	return SEMICOLON;
}

"*" {
	return TIME;
}

"+" {
	return PLUS;
}

\n {
	// Newline character is found.
	return NEWLINE;
}
1
"var" {
	return VAR;
}

{id} {
	return(ID);
}

{num} {
	return(NUM);
}
"+" {
	return(PLUS);
}



{ws} {
	
}



%%


