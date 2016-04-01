#ifndef ERROR_H
#define ERROR_H


typedef enum {
	ERR_WARNING,
	ERR_MINOR,
	ERR_FATAL,
} ErrorType;




void error(ErrorType type, char* message, int printLine);
void errorSymbol(ErrorType type, char* message, char* symbolName, int printLine);

int getNbError();
int getNbWarning();

void err_newLine();






#endif // ERROR_H
