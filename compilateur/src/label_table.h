#ifndef LABEL_TABLE_H
#define LABEL_TABLE_H

Pile * createTable();
void push_table_complet(Pile ** labelTable, char* name, int addr);
void push_table_name(Pile ** labelTable, char* name);
void add_address_to_label(Pile ** labelTable, char* name, int addr);
int seek_address_by_name(Pile ** labelTable, char * name);

#endif // LABEL_TABLE_H