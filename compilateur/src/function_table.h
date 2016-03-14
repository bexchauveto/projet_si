#ifndef FUNCTION_TABLE_H
#define FUNCTION_TABLE_H


typedef struct 
{
	char * nameFun;
	//int type; type de retour de la fonction
	int nbParams;
	char * nameParams[30];
	//int tabParams[], tableau de type des paramètre (en DLC)
}structFunction;

void createTable();
void add_function_to_table(char * nameFunction);
void add_param_to_function(char * nameFun, char * nameParam);
int check_nbParams_by_nameFun(char * nameFunction, int nbParams);


#endif // FUNCTION_TABLE_H