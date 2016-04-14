#ifndef ASS_H
#define ASS_H

#include <stdio.h>


void ass_setFile(FILE* outputFile);



void ass_progBegin();
void ass_progEnd();
void ass_fctBegin(char* fctName, int nbParams);
void ass_fctEnd(char* fctName);
void ass_blocBegin();
void ass_blocEnd();
void ass_declVar(char* varName, int arraySize);
void ass_ldr(char* varName, int reg);
void ass_str(char* varName);
void ass_ld(int value, int reg);
void ass_pushResult();
void ass_popResult(int reg);
void ass_add();
void ass_sub();
void ass_mul();
void ass_div();
void ass_and();
void ass_or();
void ass_inf();
void ass_sup();
void ass_equ();
void ass_not();
void ass_ref(char* varName, int reg);
void ass_deref();
void ass_fctCallParam();
void ass_fctCallJmp(char* fctName);
void ass_fctCallEnd();
void ass_ifBegin(int numLabel);
void ass_ifThen(int numLabel);
void ass_ifElse(int numLabel);
void ass_ifEnd(int numLabel);
void ass_whileBegin(int numLabel);
void ass_whileDo(int numLabel);
void ass_whileEnd(int numLabel);
void ass_return();
void ass_print();







#endif // ASS_H
