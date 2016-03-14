#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "label_table.h"
#include "pile.h"



Pile * labelTable; // The stack

/*
 * Function that create the stack
 */
void create_table()
{
	//printf("function create_table\n");
	labelTable = malloc(sizeof *labelTable);
}

/*
 * Function that add to the stack a new entry composed by a name and an address
 */
void push_table_complet(char* name, int addr)
{
	//printf("function push_table_complet\n");
	labelStruct * data = malloc(sizeof *data);
	data->varName = strdup(name);
	data->adresseExec = addr;
	pile_push(&labelTable, (void *)data);
}

/*
 * Function that add to the stack a new entry composed only by a name
 */
void push_table_name(char* name)
{
	//printf("function push_table_name\n");
	labelStruct * data = malloc(sizeof *data);
	data->varName = strdup(name);
	data->adresseExec = -1;
	pile_push(&labelTable, (void*)data);
}

/*
 * Function that seek a label by its name and add an address to it
 */
void add_address_to_label(char* name, int addr)
{
	//printf("function add_address_to_label\n");
	int notFound = 1;
	Pile * tmp = labelTable;
	while (tmp->prec != NULL && notFound)
	{
		//printf("%d\n",strcmp(((labelStruct * )(tmp->data))->varName, name));
		if(strcmp(((labelStruct * )(tmp->data))->varName, name) == 0)
		{
			((labelStruct * )(tmp->data))->adresseExec = addr;
			notFound = 0;
		}
		else 
		{
			tmp = tmp->prec;
		}
	}
}

/*
 * Function that seek an address by the name of label
 * Return code : -1 if the label doesn't exist in the stack
 * address of the label if the label is in the table
 */
int seek_address_by_name(char * name)
{
	//printf("function seek_address_by_name\n");
	int ret = -1;
	int notFound = 1;
	Pile * tmp = labelTable;
	while (tmp->prec != NULL && notFound)
	{
		if(strcmp(((labelStruct * )(tmp->data))->varName, name) == 0)
		{
			ret = ((labelStruct * )(tmp->data))->adresseExec;
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
	push_table_complet("lab1", 16);
	push_table_complet("lab2", 32);
	push_table_complet("lab3", 64);
	push_table_name("lab4");
	push_table_name("lab5");
	add_address_to_label("lab4", 84);
	add_address_to_label("lab5", 124);
	int i = seek_address_by_name("lab3");
	int j = seek_address_by_name("lab8");
	printf("Addr lab3 : %d, Addr lab8 : %d\n",i, j);
	return 0;
}*/