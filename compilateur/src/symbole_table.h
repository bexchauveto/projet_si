#ifndef SYMBOLE_TABLE_H
#define SYMBOLE_TABLE_H

Pile * create_table();
void new_bloc();
void end_bloc(Pile ** symboleTable);
void push_table(Pile ** symboleTable, char * name, int addr);
symboleStruct * pop_table(Pile ** symboleTable);
int seek_address_by_name(Pile ** symboleTable, char * name);

#endif SYMBOLE_TABLE_H