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
	//printf("function_table\n");
	functionTable = malloc(sizeof *functionTable);
}

/*
 * Function that add to the function table a new entry composed by a name and a number of parameters
 */
void add_function_to_table(char * nameFunction, int nbParams)
{
	//printf("function add_function_to_table\n");
	structFunction * data = malloc(sizeof *data);
	data->nameFun = nameFunction;
	data->nbParams = nbParams;
	pile_push(&functionTable, (void*) data);
}

/*
 * function that check if the number of parameters is the one that was given when the entry was create
 * Return code : -2 if the function given isn't in the stack
 * -1 if the function given is in the table but the number of parameters is wrong
 * 0 if the function given is in the table and the number of parameters is right
 */
int check_nbParams_by_nameFun(char * nameFunction, int nbParams)
{
	//printf("function check_nbParams_by_nameFun\n");
	int ret = -2;
	int notFound = 1;
	Pile * tmp = functionTable;
	while(tmp->prec != NULL && notFound)
	{
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

/*int main(int argc, char const *argv[])
{
	createTable();
	add_function_to_table("fun1", 2);
	add_function_to_table("fun2", 3);
	add_function_to_table("fun3", 1);
	add_function_to_table("fun4", 0);
	int i = check_nbParams_by_nameFun("fun1", 2);
	int j = check_nbParams_by_nameFun("fun2", 3);
	int k = check_nbParams_by_nameFun("fun3", 0);
	int l = check_nbParams_by_nameFun("fun4", 1);
	int m = check_nbParams_by_nameFun("fun5", 28);
	printf("%d, %d, %d, %d, %d\n", i,j,k,l,m);
	return 0;
}*/