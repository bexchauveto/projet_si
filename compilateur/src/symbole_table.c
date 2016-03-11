#table des symboles
#include "symbole_table.h"
#include "pile.h"

//Structure de la table des symboles
typedef struct
{
	char * varName;
	int adresseExec;
	int courantBloc;
} symboleStruct;

int numBloc;

Pile * create_table()
{
	Pile * symboleTable = malloc(sizeof *symboleTable);
	numBloc = 0;
	return *symboleTable;	
}

//Nouveau bloc numbloc++;

void new_bloc()
{
	numBloc++;
}

//Bloc fini numbloc--;

void end_bloc(Pile ** symboleTable)
{
	int notFinish = 0;
	while(*symboleTable != NULL || notFinish)
	{
		if((symboleStruct * )(*tmp->data)->courantBloc == numBloc)
		{
			pop_table(**symboleTable);
		}
		else
		{
			numBloc--;
			notFinish = 1;
		}
	}
}

//Push une variable dans la table

void push_table(Pile ** symboleTable, char * name, int addr)
{
	symboleStruct * data = malloc (sizeof *data);
	data->varName = name;
	data->adresseExec = addr;
	data->courantBloc = numBloc;
	pile_push(**symboleTable, (void *) data);
}

//Pop une variable dans la table
symboleStruct * pop_table(Pile ** symboleTable)
{
	return (symboleStruct *)(pile_pop(**symboleTable));
}

//rechercher une adresse à partir d'un nom

int seek_address_by_name(Pile ** symboleTable, char * name)
{
	int ret = -1;
	int notFound = 0;
	Pile * tmp = *symboleTable
	while (*tmp != NULL || notFound)
	{
		if((symboleStruct * )(*tmp->data)->varName == name)
		{
			ret = (symboleStruct * )(*tmp->data)->adresseExec;
			notFound = 1;
		}
		else {
			*tmp = *tmp->prec;
		}
	}
	return ret;
}