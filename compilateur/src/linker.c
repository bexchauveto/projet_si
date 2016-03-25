#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linker.h"
#include "label_table.h"

#define SIZEMAXLABEL 30

/*
 * Return the file opened
 */
FILE * Linker_openFile (char * path)
{
	//printf("Function Linker_openFile\n");
	return fopen(path, "r+");
}

/*
 * Close the file
 */
void Linker_closeFile (FILE * file)
{
	//printf("Function Linker_closeFile\n");
	fclose(file);
}


/*
 * Function that read the file, when it finds '.', it means there is a label,
 * so it checks in the label table and replaces it in the file.
 */
void Linker_readFileAndReplaceLabel(FILE * file)
{
	//printf("Function Linker_readFileAndReplaceLabel\n");
	char label[SIZEMAXLABEL];
	int addrLabel;
	for(char c; c != EOF; c = fgetc(file))
	{
		if(c == '.')
		{
			fscanf(file,"%s", label);
			addrLabel = labelT_seekAddressByName(label);
			//TODO : Check if addrLabel is different from -1
			fseek(file, -(strlen(label)+1), SEEK_CUR);
			fprintf(file, "%*d",(int)(strlen(label)+1),addrLabel);
		}
	}
	fflush(file);
}

/*
 * Test function
 */
/*
int main(int argc, char const *argv[])
{
	labelT_createTable();
	labelT_pushTableComplet("test", 16);
	labelT_pushTableComplet("lab2", 32);
	labelT_pushTableComplet("lab3", 64);
	FILE * file = Linker_openFile("./test.txt");
	Linker_readFileAndReplaceLabel(file);
	Linker_closeFile(file);
	return 0;
}
*/
