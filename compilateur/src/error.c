#include "error.h"

#include <stdlib.h>
#include <stdio.h>





static int line = 1;




void error(ErrorType type, char* message)
{
	switch(type)
	{
		case ERR_WARNING:
			printf("warning: line %d: %s\n", line, message);
			break;
		case ERR_MINOR:
			printf("error  : line %d: %s\n", line, message);
			break;
		case ERR_FATAL:
			printf("error  : line %d: %s\n", line, message);
			exit(0);
			break;
		default:
			break;
	}
}


void err_newLine()
{
	line++;
}





