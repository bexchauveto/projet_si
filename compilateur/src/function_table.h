#ifndef FUNCTION_TABLE_H
#define FUNCTION_TABLE_H


/*
 * Function that create the stack
 */
void funT_createTable();

/*
 * Function that add to the function table a new entry composed by a name
 */
void funT_addFunctionToTable(char * functionName);

/*
 * Function that add a parameter to a function
 */
void funT_addParamToFunction(char * functionName, char * paramName);

/*
 * Function that return the parameters of a function
 */
char** funT_getParamsByFunName(char * functionName);

/*
 * function that check if the number of parameters is the one that was given when the entry was create
 * return the number of parameters
 *        or -1 if the function doesn't exist
 */
int funT_getNbParamsByFunName(char * functionName);


#endif // FUNCTION_TABLE_H
