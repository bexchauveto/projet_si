#ifndef LINKER_H
#define LINKER_H

FILE * Linker_openFile(char * path);
void Linker_closeFile (FILE * file);
void Linker_readFileAndReplaceLabel(FILE * file);

#endif // LINKER_H