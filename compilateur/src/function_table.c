#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function_table.h"
#include "pile.h"


//table des fonctions


typedef struct 
{
	char * funName;
	//int type; type de retour de la fonction
	int nbParams;
	char * nameParams[30];
	//int tabParams[], tableau de type des paramètre (en DLC)
} FunctionStruct;



//nom fonction
//type retour
//nombre params
//type param
//nom param

//ajouter dans la table
//verifier le nombre du param à partir d'un nom de fonction




Pile * functionTable; // The stack

/*
 * Function that create the stack
 */
void funT_createTable()
{
	//printf("function_table\n");
	functionTable = malloc(sizeof *functionTable);
}

/*
 * Function that add to the function table a new entry composed by a name
 */
void funT_addFunctionToTable(char * functionName)
{
	//printf("function addFunctionToTable\n");
	FunctionStruct * data = malloc(sizeof *data);
	char* p = malloc(strlen(functionName)+1);
	data->funName = p? strcpy(p,functionName) : 0;
	pile_push(&functionTable, (void*) data);
}

/*
 * Function that add a parameter to a function
 */
void funT_addParamToFunction(char * functionName, char * paramName)
{
	//printf("function addParamToFunction\n");
	for(Pile * tmp = functionTable; tmp->prec != NULL; tmp = tmp->prec)
	{
		FunctionStruct * element = (FunctionStruct *) (tmp->data);
		if(strcmp(element->funName, functionName) == 0)
		{
			char* p = malloc(strlen(paramName)+1);
			element->nameParams[element->nbParams] = p? strcpy(p,paramName) : 0;
			element->nbParams++;
			break;
		}
	}
}

/*
 * function that check if the number of parameters is the one that was given when the entry was create
 * Return code : -2 if the function given isn't in the table
 * -1 if the function given is in the table but the number of parameters is wrong
 * 0 if the function given is in the table and the number of parameters is right
 */
int funT_checkNbParamsByFunName(char * functionName, int nbParams)
{
	//printf("function checkNbParamsByFunName\n");
	for(Pile * tmp = functionTable; tmp->prec != NULL; tmp = tmp->prec)
	{
		FunctionStruct * element = (FunctionStruct *) (tmp->data);
		//printf("%s\n", element->funName);
		if(strcmp(element->funName, functionName) == 0)
		{
			if (element->nbParams == nbParams)
				return 0;
			else
				return -1;
		}
	}
	return -2;
}

/*
 * Test funtion
 */
/*
int main(int argc, char const *argv[])
{
	funT_createTable();
	funT_addFunctionToTable("fun1");
	funT_addParamToFunction("fun1", "param1_1");
	funT_addParamToFunction("fun1", "param1_2");
	funT_addParamToFunction("fun1", "param1_3");
	//funT_addParamToFunction("fun1", "param1_4");
	funT_addFunctionToTable("fun2");
	funT_addParamToFunction("fun2", "param2_1");
	funT_addFunctionToTable("fun3");
	funT_addFunctionToTable("fun4");
	int i = funT_checkNbParamsByFunName("fun1", 3);
	int j = funT_checkNbParamsByFunName("fun2", 1);
	int k = funT_checkNbParamsByFunName("fun3", 0);
	int l = funT_checkNbParamsByFunName("fun4", 1);
	int m = funT_checkNbParamsByFunName("fun5", 28);
	printf("%d, %d, %d, %d, %d\n", i,j,k,l,m);
	return 0;
}
*/
