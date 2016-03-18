#ifndef LABEL_TABLE_H
#define LABEL_TABLE_H


void labelT_createTable();
void labelT_pushTableComplet(char* name, int addr);
void labelT_pushTableName(char* name);
void labelT_addAddressToLabel(char* name, int addr);
int labelT_seekAddressByName(char * name);

#endif // LABEL_TABLE_H
