#include "error.h"

#include <stdlib.h>
#include <stdio.h>





static int currentLine = 1;
static int warningOccured = 0;
static int errorOccured = 0;




void error(ErrorType type, const char* message, int line)
{
	switch(type)
	{
		case ERR_WARNING:
			warningOccured++;
			printf("warning: ");
			break;
		case ERR_MINOR:
		case ERR_FATAL:
			errorOccured++;
			printf("error  : ");
			break;
		default:
			break;
	}
	printf("line %d: ", line);
	printf("%s\n", message);
	if(type == ERR_FATAL)
		exit(0);
}

void errorSymbol(ErrorType type, const char* message, char* symbolName, int line)
{
	switch(type)
	{
		case ERR_WARNING:
			warningOccured++;
			printf("warning: ");
			break;
		case ERR_MINOR:
		case ERR_FATAL:
			errorOccured++;
			printf("error  : ");
			break;
		default:
			break;
	}
	if(line > 0)
		printf("line %d: ", line);
	printf(message, symbolName);
	printf("\n");
	if(type == ERR_FATAL)
		exit(0);
}


int getNbError()
{
	return errorOccured;
}

int getNbWarning()
{
	return warningOccured;
}


void err_newLine()
{
	currentLine++;
}





