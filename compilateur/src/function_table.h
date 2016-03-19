#ifndef FUNCTION_TABLE_H
#define FUNCTION_TABLE_H


void funT_createTable();
void funT_addFunctionToTable(char * functionName);
void funT_addParamToFunction(char * functionName, char * paramName);
char** funT_getParamsByFunName(char * functionName);
int funT_getNbParamsByFunName(char * functionName);


#endif // FUNCTION_TABLE_H
