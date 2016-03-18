#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "symbole_table.h"
#include "pile.h"



//Structure de la table des symboles
typedef struct
{
	char * varName;
	int adresseExec;
	int courantBloc;
} SymboleStruct;







int numBloc = 0; // The number of blocs in the stack
Pile * symboleTable; // The stck

/*
 * Function that create the stack
 */
void symboleT_createTable()
{
	//printf("function create_table\n");
	symboleTable = malloc(sizeof *symboleTable);
}

/*
 * Function that create a new bloc in the stack
 */
void symboleT_newBloc()
{
	//printf("function newBloc\n");
	numBloc++;
}

/*
 * Function that end a block a pop items for the current bloc and then decrease the numBloc
 */
void symboleT_endBloc()
{
	//printf("function endBloc\n");
	while(symboleTable->prec != NULL)
	{
		SymboleStruct * element = (SymboleStruct *) (symboleTable->data);
		//printf("%d\n", symboleTable != NULL);
		//printf("%d, %d\n", element->courantBloc, numBloc);
		if(element->courantBloc != numBloc)
			break;
		symboleT_popTable();
	}
	numBloc--;
}

/*
 * Function that push into the stack a new entry composed by a name, a address and a bloc number
 */
void symboleT_pushTable(char * name, int addr)
{
	//printf("function push_table\n");
	SymboleStruct * data = malloc (sizeof *data);
	char* p = malloc(strlen(name)+1);
	data->varName = p? strcpy(p,name) : 0;
	data->adresseExec = addr;
	data->courantBloc = numBloc;
	pile_push(&symboleTable, (void *) data);
}

/*
 * Function that pop a item from the stack and return it
 */
void symboleT_popTable()
{
	//printf("function pop_table\n");
	SymboleStruct* e = (SymboleStruct *)(pile_pop(&symboleTable));
	free(e->varName);
	free(e);
}

/*
 * Function that seek an address by a name of a symbol
 */
int symboleT_seekAddressByName(char * name)
{
	//printf("function seek_address_by_name\n");
	for (Pile * tmp = symboleTable; tmp->prec != NULL; tmp = tmp->prec)
	{
		SymboleStruct * element = (SymboleStruct *) (tmp->data);
		if(strcmp(element->varName, name) == 0)
			return element->adresseExec;
	}
	return -1;
}


/*
 * Test function
 */
/*
int main(int argc, char const *argv[])
{
	symboleT_createTable();
	symboleT_newBloc();
	symboleT_pushTable("sym1", 16);
	symboleT_pushTable("sym2", 24);
	symboleT_pushTable("sym3", 32);
	symboleT_pushTable("sym4", 42);
	symboleT_newBloc();
	symboleT_pushTable("sym5", 58);
	symboleT_pushTable("sym6", 64);
	symboleT_pushTable("sym7", 78);
	symboleT_endBloc();
	symboleT_popTable();
	printf("avant printf\n");
	printf("name : %s, addr : %d, bloc : %d\n", sym->varName, sym->adresseExec, sym->courantBloc);
	int i = seek_address_by_name("sym28");
	printf("%d\n", i);
	symboleT_endBloc();
	return 0;
}*/
