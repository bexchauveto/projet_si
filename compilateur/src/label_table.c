#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "label_table.h"
#include "pile.h"


typedef struct
{
	char * varName;
	int adresseExec;
} LabelStruct;




Pile * labelTable; // The stack

/*
 * Function that create the stack
 */
void labelT_createTable()
{
	//printf("function createTable\n");
	labelTable = malloc(sizeof *labelTable);
}

/*
 * Function that add to the stack a new entry composed by a name and an address
 */
void labelT_pushTableComplet(char* name, int addr)
{
	//printf("function pushTableComplet\n");
	LabelStruct * data = malloc(sizeof *data);
	char* p = malloc(strlen(name)+1);
	data->varName = p? strcpy(p,name) : 0;
	data->adresseExec = addr;
	pile_push(&labelTable, (void *)data);
}

/*
 * Function that add to the stack a new entry composed only by a name
 */
void labelT_pushTableName(char* name)
{
	//printf("function pushTableName\n");
	LabelStruct * data = malloc(sizeof *data);
	char* p = malloc(strlen(name)+1);
	data->varName = p? strcpy(p,name) : 0;
	data->adresseExec = -1;
	pile_push(&labelTable, (void*)data);
}

/*
 * Function that seek a label by its name and add an address to it
 */
void labelT_addAddressToLabel(char* name, int addr)
{
	//printf("function addAddressToLabel\n");
	for (Pile * tmp = labelTable; tmp->prec != NULL; tmp = tmp->prec)
	{
		LabelStruct * element = (LabelStruct *) (tmp->data);
		//printf("%d\n",strcmp(element->varName, name));
		if(strcmp(element->varName, name) == 0)
		{
			element->adresseExec = addr;
			break;
		}
	}
}

/*
 * Function that seek an address by the name of label
 * Return code : -1 if the label doesn't exist in the stack
 * address of the label if the label is in the table
 */
int labelT_seekAddressByName(char * name)
{
	//printf("function seekAddressByName\n");
	for (Pile * tmp = labelTable; tmp->prec != NULL; tmp = tmp->prec)
	{
		LabelStruct * element = (LabelStruct *) (tmp->data);
		if(strcmp(element->varName, name) == 0)
		{
			return element->adresseExec;
		}
	}
	return -1;
}

/*
 * Test function
 */
/*int main(int argc, char const *argv[])
{
	labelT_createTable();
	labelT_pushTableComplet("lab1", 16);
	labelT_pushTableComplet("lab2", 32);
	labelT_pushTableComplet("lab3", 64);
	labelT_pushTableName("lab4");
	labelT_pushTableName("lab5");
	labelT_addAddressToLabel("lab4", 84);
	labelT_addAddressToLabel("lab5", 124);
	int i = labelT_seekAddressByName("lab3");
	int j = labelT_seekAddressByName("lab8");
	printf("Addr lab3 : %d, Addr lab8 : %d\n",i, j);
	return 0;
}*/
