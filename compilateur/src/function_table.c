//table des fonctions

//nom fonction
//type retour
//nombre params
//type param
//nom param

//ajouter dans la table
//verifier le nombre du param à partir d'un nom de fonction

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "function_table.h"
#include "pile.h"

Pile * functionTable; // The stack

/*
 * Function that create the stack
 */
void createTable()
{
	printf("function_table\n");
	functionTable = malloc(sizeof *functionTable);
}

/*
 * Function that add to the function table a new entry composed by a name
 */
void add_function_to_table(char * nameFunction)
{
	printf("function add_function_to_table\n");
	structFunction * data = malloc(sizeof *data);
	data->nameFun = strdup(nameFunction);
	pile_push(&functionTable, (void*) data);
}

/*
 * Function that add a parameter to a function
 */
void add_param_to_function(char * nameFunction, char * nameParam)
{
	printf("function add_param_to_function\n");
	int notFound = 1;
	Pile * tmp = functionTable;
	while(tmp->prec != NULL && notFound)
	{
		if(strcmp(((structFunction * )(tmp->data))->nameFun, nameFunction) == 0)
		{
			((structFunction *)(tmp->data))->nameParams[((structFunction *)(tmp->data))->nbParams] = strdup(nameParam);
			((structFunction *)(tmp->data))->nbParams = ((structFunction *)(tmp->data))->nbParams + 1;
			notFound = 0;
		}
		else
		{
			tmp = tmp->prec;
		}
	}
}

/*
 * function that check if the number of parameters is the one that was given when the entry was create
 * Return code : -2 if the function given isn't in the stack
 * -1 if the function given is in the table but the number of parameters is wrong
 * 0 if the function given is in the table and the number of parameters is right
 */
int check_nbParams_by_nameFun(char * nameFunction, int nbParams)
{
	printf("function check_nbParams_by_nameFun\n");
	int ret = -2;
	int notFound = 1;
	Pile * tmp = functionTable;
	while(tmp->prec != NULL && notFound)
	{
		printf("%s\n", ((structFunction * )(tmp->data))->nameFun);
		if(strcmp(((structFunction * )(tmp->data))->nameFun, nameFunction) == 0)
		{
			if (((structFunction * )(tmp->data))->nbParams == nbParams)
			{
				ret = 0;
			}
			else
			{
				ret = -1;
			}
			notFound = 0;
		}
		else
		{
			tmp = tmp->prec;
		}
	}
	return ret;
}

/*
 * Test funtion
 */

int main(int argc, char const *argv[])
{
	createTable();
	add_function_to_table("fun1");
	add_param_to_function("fun1", "param1_1");
	add_param_to_function("fun1", "param1_2");
	add_param_to_function("fun1", "param1_3");
	//add_param_to_function("fun1", "param1_4");
	add_function_to_table("fun2");
	add_param_to_function("fun2", "param2_1");
	add_function_to_table("fun3");
	add_function_to_table("fun4");
	int i = check_nbParams_by_nameFun("fun1", 3);
	int j = check_nbParams_by_nameFun("fun2", 1);
	int k = check_nbParams_by_nameFun("fun3", 0);
	int l = check_nbParams_by_nameFun("fun4", 1);
	int m = check_nbParams_by_nameFun("fun5", 28);
	printf("%d, %d, %d, %d, %d\n", i,j,k,l,m);
	return 0;
}