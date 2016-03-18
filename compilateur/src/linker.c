#include <stdio.h>


/*
 * Return the file opened
 */
FILE * open_file (char * path)
{
	return fopen(path, "r+");
}
