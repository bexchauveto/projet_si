#ifndef LABEL_TABLE_H
#define LABEL_TABLE_H

typedef struct
{
	char * varName;
	int adresseExec;
} labelStruct;

void createTable();
void push_table_complet(char* name, int addr);
void push_table_name(char* name);
void add_address_to_label(char* name, int addr);
int seek_address_by_name(char * name);

#endif // LABEL_TABLE_H