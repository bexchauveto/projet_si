#ifndef SYMBOLE_TABLE_H
#define SYMBOLE_TABLE_H


void symboleT_createTable();
void symboleT_newBloc();
void symboleT_endBloc();
void symboleT_pushTable(char * name, int addr);
void symboleT_popTable();
int symboleT_seekAddressByName(char * name);

#endif // SYMBOLE_TABLE_H
