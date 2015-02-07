%{
#include <stdio.h>
%}

%%

\n {
	return NEWLINE;
}

stop 	printf("Stop command received\n");
start 	printf("Start command received\n");
%%


