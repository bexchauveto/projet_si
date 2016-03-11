#include "label_table.h"
#include "pile.h"


typedef struct
{
	char * varName;
	int adresseExec;
} labelStruct;


Pile * createTable()
{
	Pile * labelTable = malloc(sizeof *labelTable);
	return *labelTable;
}

void push_table_complet(Pile ** labelTable, char* name, int addr)
{
	labelStruct * data = malloc(sizeof *data);
	data->varName = name;
	data->adresseExec = addr;
	pile_push(**labelTable, (void *)data);
}

void push_table_name(Pile ** labelTable, char* name)
{
	labelStruct * data = malloc(sizeof *data);
	data->varName = name;
	data->adresseExec = -1;
	pile_push(**labelTable, (void*)data);
}

void add_address_to_label(Pile ** labelTable, char* name, int addr)
{
	int notFound = 0;
	Pile * tmp = *labelTable
	while (*tmp != NULL || notFound)
	{
		if((labelStruct * )(*tmp->data)->varName == name)
		{
			(labelStruct * )(*tmp->data)->adresseExec = addr;
			notFound = 1;
		}
		else {
			*tmp = *tmp->prec;
		}
	}
}

int seek_address_by_name(Pile ** labelTable, char * name)
{
	int ret = -1;
	int notFound = 0;
	Pile * tmp = *labelTable
	while (*tmp != NULL || notFound)
	{
		if((labelStruct * )(*tmp->data)->varName == name)
		{
			ret = (labelStruct * )(*tmp->data)->adresseExec;
			notFound = 1;
		}
		else {
			*tmp = *tmp->prec;
		}
	}
	return ret;
}