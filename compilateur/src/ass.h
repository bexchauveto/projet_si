#ifndef ASS_H
#define ASS_H

#include <stdio.h>


void setFile(FILE* file);



void ass_progBegin();
void ass_progEnd();
void ass_fctBegin(char* fctName);
void ass_fctEnd();
void ass_blocBegin();
void ass_blocEnd();
void ass_declVar(char* varName, int value);
void ass_ldr(char* varName);
void ass_str(char* varName);
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
void ass_fctCallParam(int value);
void ass_fctCallJmp(char* fctName);
void ass_ifBegin();
void ass_ifThen();
void ass_ifEnd();
void ass_whileBegin();
void ass_whileDo();
void ass_whileEnd();
void ass_return();








#endif // ASS_H
