#ifndef FUNCTION_TABLE_H
#define FUNCTION_TABLE_H


void funT_createTable();
void funT_addFunctionToTable(char * functionName);
void funT_addParamToFunction(char * functionName, char * paramName);
int funT_checkNbParamsByFunName(char * functionName, int nbParams);


#endif // FUNCTION_TABLE_H
