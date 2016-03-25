#include "ass.h"

#include <stdio.h>
#include "function_table.h"
#include "label_table.h"
#include "symbole_table.h"




#define ASS_DEBUG

#ifdef ASS_DEBUG
#    define PRINT_DEBUG() printf("=> %s\n",__func__)
#else
#    define PRINT_DEBUG() ((void) 0)
#endif




//###################################################
//  DEFINITION UTILES
//###################################################


typedef enum {
	ADDR_R0 = 0,
	ADDR_R1,
	ADDR_SP,
	ADDR_CONTEXT,
	ADDR_STACK,
} UsefullAddress;




static FILE* file = 0;
static int nbCurrentParams = 0;
static int instructionNumber;


#define printInst(...) instructionNumber++;printf(__VA_ARGS__)



void empiler(int reg)
{
	printInst("E %d %d\n", ADDR_SP, reg); // *SP = reg
	printInst("6 %d 1\n", reg); // reg = 1
	printInst("1 %d %d %d\n", ADDR_SP, ADDR_SP, reg); // SP++
}

void depiler(int reg)
{
	printInst("6 %d 1\n", reg); // *reg = 1
	printInst("3 %d %d %d\n", ADDR_SP, ADDR_SP, reg); // SP--
	printInst("D %d %d\n", reg, ADDR_SP); // *reg = *SP
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
	PRINT_DEBUG();
	instructionNumber = 1;
	printInst("6 %d 0\n", ADDR_STACK); // STACK[0] = 0
	printInst("6 %d %d\n", ADDR_SP, ADDR_STACK+1); // SP = ADDR_STACK + 1
	printInst("7 .main\n"); // goto main
}

void ass_progEnd()
{
	PRINT_DEBUG();
}

void ass_fctBegin(char* fctName, int nbParams)
{
	PRINT_DEBUG();
	labelT_pushTableComplet(fctName, instructionNumber);
	empiler(ADDR_CONTEXT); // sauver le contexte
	printInst("5 %d %d\n", ADDR_CONTEXT, ADDR_SP); // CONTEXT = SP
	
	symboleT_newBloc(); // parameters
	char** tabParams = funT_getParamsByFunName(fctName);
	for(int i=0; i<nbParams; i++)
	{
		symboleT_pushTable(tabParams[i], (-2-nbParams) + i );
	}
}

void ass_fctEnd(char* fctName)
{
	PRINT_DEBUG();
	printInst("5 %d %d\n", ADDR_SP, ADDR_CONTEXT);
	depiler(ADDR_CONTEXT);
	depiler(ADDR_R1); // depiler adresse de retour
	printInst("F %d\n", ADDR_R1); // goto R2
	symboleT_endBloc(); // parameters
}

void ass_blocBegin()
{
	PRINT_DEBUG();
	symboleT_newBloc();
}

void ass_blocEnd()
{
	PRINT_DEBUG();
	symboleT_endBloc();
}

void ass_declVar(char* varName)
{
	PRINT_DEBUG();
	int addr = symboleT_getSymboleNumber();
	symboleT_pushTable(varName, addr);
	empiler(ADDR_R0); // empiler varName
}

void ass_ldr(char* varName, int reg)
{
	PRINT_DEBUG();
	int addr = symboleT_seekAddressByName(varName);
	if(addr == -1)
		return; // TODO error
	printInst("6 %d %d\n", ADDR_R0 + reg, addr); // reg = addr
	printInst("1 %d %d %d\n", ADDR_R0 + reg, ADDR_R0 + reg, ADDR_CONTEXT); // addr += CONTEXT
	printInst("D %d %d\n", ADDR_R0 + reg, ADDR_R0 + reg); // reg = *addr
}

void ass_str(char* varName)
{
	PRINT_DEBUG();
	int addr = symboleT_seekAddressByName(varName);
	if(addr == -1)
		return; // TODO error
	printInst("6 %d %d\n", ADDR_R1, addr); // R1 = addr
	printInst("1 %d %d %d\n", ADDR_R1, ADDR_R1, ADDR_CONTEXT); // addr += CONTEXT
	printInst("E %d %d\n", ADDR_R1, ADDR_R0); // *addr = R0
}

void ass_ld(int value, int reg)
{
	PRINT_DEBUG();
	printInst("6 %d %d\n", ADDR_R0 + reg, value);
}

void ass_pushResult()
{
	PRINT_DEBUG();
	empiler(ADDR_R0);
}

void ass_popResult(int reg)
{
	PRINT_DEBUG();
	depiler(ADDR_R0 + reg);
}

void ass_add()
{
	PRINT_DEBUG();
	printInst("1 %d %d %d\n", ADDR_R0, ADDR_R0, ADDR_R1);
}

void ass_sub()
{
	PRINT_DEBUG();
	printInst("3 %d %d %d\n", ADDR_R0, ADDR_R0, ADDR_R1);
}

void ass_mul()
{
	PRINT_DEBUG();
	printInst("2 %d %d %d\n", ADDR_R0, ADDR_R0, ADDR_R1);
}

void ass_div()
{
	PRINT_DEBUG();
	printInst("4 %d %d %d\n", ADDR_R0, ADDR_R0, ADDR_R1);
}

void ass_and()
{
	PRINT_DEBUG();
	printInst("8 %d %d\n", ADDR_R0, instructionNumber+3); // if(!R0)  goto false;
	printInst("8 %d %d\n", ADDR_R1, instructionNumber+2); // if(!R1)  goto false;
	printInst("7 %d\n", instructionNumber+2);             // true:  goto end;
	printInst("6 %d %d\n", ADDR_R0, 0);                   // false: R0 = 0
}

void ass_or()
{
	PRINT_DEBUG();
	printInst("8 %d %d\n", ADDR_R0, instructionNumber+2); // if(!R0)  goto testR1;
	printInst("7 %d\n", instructionNumber+3);             // goto end;
	printInst("8 %d %d\n", ADDR_R1, instructionNumber+2); // if(!R1)  goto end;
	printInst("6 %d %d\n", ADDR_R0, 1);                   // R0 = 1
}

void ass_inf()
{
	PRINT_DEBUG();
	printInst("9 %d %d %d\n", ADDR_R0, ADDR_R0, ADDR_R1);
}

void ass_sup()
{
	PRINT_DEBUG();
	printInst("A %d %d %d\n", ADDR_R0, ADDR_R0, ADDR_R1);
}

void ass_equ()
{
	PRINT_DEBUG();
	printInst("B %d %d %d\n", ADDR_R0, ADDR_R0, ADDR_R1);
}

void ass_not()
{
	PRINT_DEBUG();
	printInst("11 %d %d\n", ADDR_R0, ADDR_R0);
}

void ass_fctCallParam()
{
	PRINT_DEBUG();
	empiler(ADDR_R0);
	nbCurrentParams++;
}

void ass_fctCallJmp(char* fctName)
{
	PRINT_DEBUG();
	printInst("10 %d\n", ADDR_R1); // R1 = adresse de retour
	empiler(ADDR_R1);
	printInst("7 .%s\n", fctName);
}

void ass_fctCallEnd()
{
	PRINT_DEBUG();
	printInst("6 %d %d\n", ADDR_R1, nbCurrentParams); // R3 = nbCurrentParams
	printInst("3 %d %d %d\n", ADDR_SP, ADDR_SP, ADDR_R1); // SP = SP - nbCurrentParams
	nbCurrentParams = 0;
}

void ass_ifBegin(int numLabel)
{
	PRINT_DEBUG();
}

void ass_ifThen(int numLabel)
{
	PRINT_DEBUG();
	char label[10];
	sprintf(label, "%deif",numLabel);
	labelT_pushTableName(label);
	printInst("8 %d .%s\n", ADDR_R0, label); // if(!R0) goto ifEnd
}

void ass_ifEnd(int numLabel)
{
	PRINT_DEBUG();
	char label[10];
	sprintf(label, "%deif",numLabel);
	labelT_addAddressToLabel(label, instructionNumber);
}

void ass_whileBegin(int numLabel)
{
	PRINT_DEBUG();
	char label[10];
	sprintf(label, "%dbwhl",numLabel);
	labelT_pushTableComplet(label, instructionNumber);
}

void ass_whileDo(int numLabel)
{
	PRINT_DEBUG();
	char label[10];
	sprintf(label, "%dewhl",numLabel);
	labelT_pushTableComplet(label, instructionNumber);
	printInst("8 %d .%s\n", ADDR_R0, label); // if(!R0) goto whileEnd
}

void ass_whileEnd(int numLabel)
{
	PRINT_DEBUG();
	char label[10];
	sprintf(label, "%dbwhl",numLabel);
	printInst("7 .%s\n", label); // goto whileBegin
	
	sprintf(label, "%dewhl",numLabel);
	labelT_addAddressToLabel(label, instructionNumber);
}

void ass_return()
{
	PRINT_DEBUG();
}

void ass_print()
{
	PRINT_DEBUG();
	depiler(ADDR_R0);
	printInst("C %d\n", ADDR_R0);
}







