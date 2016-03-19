#include "ass.h"

#include "function_table.h"
#include "label_table.h"
#include "symbole_table.h"




//###################################################
//  DEFINITION UTILES
//###################################################


typedef enum {
	ADDR_R0 = 0,
	ADDR_R1,
	ADDR_R2,
	ADDR_SP,
	ADDR_CONTEXT,
	ADDR_STACK,
} UsefullAddress;




static FILE* file;
static int nbCurrentParams;
static int instructionNumber;
#define fprintf instructionNumber++;fprintf





void empiler(int addr)
{
	fprintf(file, "D %d %d\n", ADDR_SP, addr); // *SP = *addr
	fprintf(file, "6 %d 1\n", ADDR_R2); // R3 = 1
	fprintf(file, "1 %d %d %d\n", ADDR_SP, ADDR_SP, ADDR_R2); // SP++
}

void depiler(int addr)
{
	fprintf(file, "6 %d 1\n", ADDR_R2); // R3 = 1
	fprintf(file, "3 %d %d %d\n", ADDR_SP, ADDR_SP, ADDR_R2); // SP--
	fprintf(file, "D %d %d\n", addr, ADDR_SP); // *addr = *SP
}






//###################################################
//  DEFINITION DES FONCTIONS
//###################################################

void ass_setFile(FILE* outputFile)
{
	file = outputFile;
}







void ass_progBegin()
{
	instructionNumber = 1;
	fprintf(file, "6 %d 0\n", ADDR_STACK); // STACK[0] = 0
	fprintf(file, "6 %d %d\n", ADDR_SP, ADDR_STACK+1); // SP = ADDR_STACK + 1
	fprintf(file, "7 .main\n"); // goto main
}

void ass_progEnd()
{
}

void ass_fctBegin(char* fctName, int nbParams)
{
	labelT_pushTableComplet(fctName, instructionNumber);
	empiler(ADDR_CONTEXT); // sauver le contexte
	fprintf(file, "5 %d %d\n", ADDR_CONTEXT, ADDR_SP); // CONTEXT = SP
	symboleT_newBloc(); // parameters
	char** tabParams = funT_getParamsByFunName(fctName);
	for(int i=0; i<nbParams; i++)
	{
		symboleT_pushTable(tabParams[i], (-2-nbParams) + i );
	}
	nbCurrentParams = nbParams;
}

void ass_fctEnd()
{
	fprintf(file, "5 %d %d\n", ADDR_SP, ADDR_CONTEXT);
	depiler(ADDR_CONTEXT);
	// sauter a l'addresse de retour.
	fprintf(file, "D %d %d\n", ADDR_R1, ADDR_SP); // R1 = *SP
	fprintf(file, "F %d\n", ADDR_R1); // goto R2
	symboleT_endBloc(); // parameters
}

void ass_blocBegin()
{
	symboleT_newBloc();
}

void ass_blocEnd()
{
	symboleT_endBloc();
}

void ass_declVar(char* varName)
{
	int addr = symboleT_getSymboleNumber();
	symboleT_pushTable(varName, addr);
	empiler(ADDR_R0); // empiler varName
}

void ass_ldr(char* varName, int reg)
{
	int addr = symboleT_seekAddressByName(varName);
	if(addr == -1)
		return; // TODO error
	fprintf(file, "6 %d %d\n", ADDR_R0 + reg, addr); // reg = addr
	fprintf(file, "1 %d %d %d\n", ADDR_R0 + reg, ADDR_R0 + reg, ADDR_CONTEXT); // addr += CONTEXT
	fprintf(file, "D %d %d\n", ADDR_R0 + reg, ADDR_R0 + reg); // reg = *addr
}

void ass_str(char* varName)
{
	int addr = symboleT_seekAddressByName(varName);
	if(addr == -1)
		return; // TODO error
	fprintf(file, "6 %d %d\n", ADDR_R1, addr); // R1 = addr
	fprintf(file, "1 %d %d %d\n", ADDR_R1, ADDR_R1, ADDR_CONTEXT); // addr += CONTEXT
	fprintf(file, "D %d %d\n", ADDR_R1, ADDR_R0); // *addr = R0
}

void ass_ld(int value, int reg)
{
	fprintf(file, "6 %d %d\n", ADDR_R0 + reg, value);
}

void ass_pushResult()
{
	empiler(ADDR_R0);
}

void ass_popResult(int reg)
{
	depiler(ADDR_R0 + reg);
}

void ass_add()
{
	fprintf(file, "1 %d %d %d\n", ADDR_R0, ADDR_R0, ADDR_R1);
}

void ass_sub()
{
	fprintf(file, "3 %d %d %d\n", ADDR_R0, ADDR_R0, ADDR_R1);
}

void ass_mul()
{
	fprintf(file, "2 %d %d %d\n", ADDR_R0, ADDR_R0, ADDR_R1);
}

void ass_div()
{
	fprintf(file, "4 %d %d %d\n", ADDR_R0, ADDR_R0, ADDR_R1);
}

void ass_and()
{
	fprintf(file, "8 %d %d\n", ADDR_R0, instructionNumber+3); // if(!R0)  goto false;
	fprintf(file, "8 %d %d\n", ADDR_R1, instructionNumber+2); // if(!R1)  goto false;
	fprintf(file, "7 %d\n", instructionNumber+2);             // true:  goto end;
	fprintf(file, "6 %d %d\n", ADDR_R0, 0);                   // false: R0 = 0
}

void ass_or()
{
	fprintf(file, "8 %d %d\n", ADDR_R0, instructionNumber+2); // if(!R0)  goto testR1;
	fprintf(file, "7 %d\n", instructionNumber+3);             // goto end;
	fprintf(file, "8 %d %d\n", ADDR_R0, instructionNumber+2); // if(!R1)  goto end;
	fprintf(file, "6 %d %d\n", ADDR_R0, 1);                   // R0 = 1
}

void ass_inf()
{
	fprintf(file, "9 %d %d %d\n", ADDR_R0, ADDR_R0, ADDR_R1);
}

void ass_sup()
{
	fprintf(file, "A %d %d %d\n", ADDR_R0, ADDR_R0, ADDR_R1);
}

void ass_equ()
{
	fprintf(file, "B %d %d %d\n", ADDR_R0, ADDR_R0, ADDR_R1);
}

void ass_not()
{
	fprintf(file, "11 %d %d\n", ADDR_R0, ADDR_R0);
}

void ass_fctCallParam()
{
	empiler(ADDR_R0);
}

void ass_fctCallJmp(char* fctName)
{
	fprintf(file, "10 %d\n", ADDR_R1);
	empiler(ADDR_R1);
	fprintf(file, "7 .%s\n", fctName);
}

void ass_fctCallEnd()
{
	depiler(ADDR_R1); // depiler adresse de retour
	fprintf(file, "6 %d %d\n", ADDR_R2, nbCurrentParams); // R3 = nbCurrentParams
	fprintf(file, "3 %d %d %d\n", ADDR_SP, ADDR_SP, ADDR_R2); // SP = SP - nbCurrentParams
}

void ass_ifBegin(int numLabel)
{
}

void ass_ifThen(int numLabel)
{
	char label[10];
	sprintf(label, "eif%d",numLabel);
	labelT_pushTableName(label);
	fprintf(file, "jmf %d .%s", ADDR_R0, label); // goto ifEnd
}

void ass_ifEnd(int numLabel)
{
	char label[10];
	sprintf(label, "eif%d",numLabel);
	labelT_addAddressToLabel(label, instructionNumber);
}

void ass_whileBegin(int numLabel)
{
	char label[10];
	sprintf(label, "bwhl%d",numLabel);
	labelT_pushTableComplet(label, instructionNumber);
}

void ass_whileDo(int numLabel)
{
	char label[10];
	sprintf(label, "ewhl%d",numLabel);
	labelT_pushTableComplet(label, instructionNumber);
	fprintf(file, "8 %d .%s", ADDR_R0, label); // if(!R0) goto whileEnd
}

void ass_whileEnd(int numLabel)
{
	char label[10];
	sprintf(label, "bwhl%d",numLabel);
	fprintf(file, "7 .%s", label); // goto whileBegin
	
	sprintf(label, "ewhl%d",numLabel);
	labelT_addAddressToLabel(label, instructionNumber);
}

void ass_return()
{
}







