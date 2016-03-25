#ifndef LINKER_H
#define LINKER_H

FILE * linker_openFile(char * path);
void linker_closeFile (FILE * file);
void linker_readFileAndReplaceLabel(FILE * file);

#endif // LINKER_H