#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "symbole_table.h"
#include "pile.h"




int numBloc = 0; // The number of blocs in the stack
Pile * symboleTable; // The stck

/*
 * Function that create the stack
 */
void create_table()
{
	//printf("function create_table\n");
	symboleTable = malloc(sizeof *symboleTable);
}

/*
 * Function that create a new bloc in the stack
 */
void new_bloc()
{
	//printf("function new_bloc\n");
	numBloc++;
}

/*
 * Function that end a block a pop items for the current bloc and then decrease the numBloc
 */
void end_bloc()
{
	//printf("function end_bloc\n");
	int notFinish = 1;
	while(symboleTable->prec != NULL && notFinish)
	{
		//printf("%d\n", symboleTable != NULL);
		//printf("%d, %d\n", ((symboleStruct * )(symboleTable->data))->courantBloc, numBloc);
		if(((symboleStruct * )(symboleTable->data))->courantBloc == numBloc)
		{
			pop_table(&symboleTable);
		}
		else
		{
			notFinish = 0;
		}
	}
	numBloc--;
}

/*
 * Function that push into the stack a new entry composed by a name, a address and a bloc number
 */
void push_table(char * name, int addr)
{
	//printf("function push_table\n");
	symboleStruct * data = malloc (sizeof *data);
	data->varName = strdup(name);
	data->adresseExec = addr;
	data->courantBloc = numBloc;
	pile_push(&symboleTable, (void *) data);
}

/*
 * Function that pop a item from the stack and return it
 */
symboleStruct * pop_table()
{
	//printf("function pop_table\n");
	return (symboleStruct *)(pile_pop(&symboleTable));
}

/*
 * Function that seek an address by a name of a symbol
 */
int seek_address_by_name(char * name)
{
	//printf("function seek_address_by_name\n");
	int ret = -1;
	int notFound = 1;
	Pile * tmp = symboleTable;
	while (tmp->prec != NULL && notFound)
	{
		if(strcmp(((symboleStruct * )(tmp->data))->varName, name) == 0)
		{
			ret = ((symboleStruct * )(tmp->data))->adresseExec;
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
 * Test function
 */
/*int main(int argc, char const *argv[])
{
	create_table();
	new_bloc();
	push_table("sym1", 16);
	push_table("sym2", 24);
	push_table("sym3", 32);
	push_table("sym4", 42);
	new_bloc();
	push_table("sym5", 58);
	push_table("sym6", 64);
	push_table("sym7", 78);
	end_bloc();
	symboleStruct * sym = pop_table();
	printf("avant printf\n");
	printf("name : %s, addr : %d, bloc : %d\n", sym->varName, sym->adresseExec, sym->courantBloc);
	int i = seek_address_by_name("sym28");
	printf("%d\n", i);
	end_bloc();
	return 0;
}*/