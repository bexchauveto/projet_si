#ifndef SYMBOLE_TABLE_H
#define SYMBOLE_TABLE_H

//Structure de la table des symboles
typedef struct
{
	char * varName;
	int adresseExec;
	int courantBloc;
} symboleStruct;
void create_table();
void new_bloc();
void end_bloc();
void push_table(char * name, int addr);
symboleStruct * pop_table();
int seek_address_by_name(char * name);

#endif // SYMBOLE_TABLE_H