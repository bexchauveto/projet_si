#ifndef ERROR_H
#define ERROR_H


typedef enum {
	ERR_WARNING,
	ERR_MINOR,
	ERR_FATAL,
} ErrorType;




void error(ErrorType type, const char* message, int line);
void errorSymbol(ErrorType type, const char* message, char* symbolName, int line);

int getNbError();
int getNbWarning();

void err_newLine();
void err_getLine();






#endif // ERROR_H
