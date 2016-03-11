#include "ass.h"




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




FILE* file;
int instructionNumber;
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

void setFile(FILE* outputFile)
{
	file = outputFile;
}







void ass_progBegin()
{
	instructionNumber = 0;
	fprintf(file, "6 %d 0\n", ADDR_STACK); // STACK[0] = 0
	fprintf(file, "6 %d %d\n", ADDR_SP, ADDR_STACK+1); // SP = ADDR_STACK + 1
	fprintf(file, "7 .main\n"); // goto main
}

void ass_progEnd()
{
}

void ass_fctBegin(char* fctName)
{
	// TODO enregistrer les parametres dans la table des symboles
	// TODO poser un label de fonction
	empiler(ADDR_CONTEXT); // sauver le contexte
	fprintf(file, "5 %d %d\n", ADDR_CONTEXT, ADDR_SP); // CONTEXT = SP
}

void ass_fctEnd()
{
	fprintf(file, "5 %d %d\n", ADDR_SP, ADDR_CONTEXT);
	depiler(ADDR_CONTEXT);
	// sauter a l'addresse de retour.
	fprintf(file, "D %d %d\n", ADDR_R1, ADDR_SP); // R1 = *SP
	fprintf(file, "F %d\n", ADDR_R1); // goto R2
}

void ass_blocBegin()
{
	// TODO maj de la table des symboles
}

void ass_blocEnd()
{
	// TODO maj de la table des symboles
}

void ass_declVar(char* varName)
{
	// TODO enregistrer dans la table des symboles (à l'addresse SP)
	empiler(ADDR_R0); // empiler varName
}

void ass_ldr(char* varName, int reg)
{
	// TODO rechercher varName dans la table des symboles
	fprintf(file, "5 %d %d\n", ADDR_R0 + reg, x);
}

void ass_str(char* varName)
{
	// TODO rechercher varName dans la table des symboles
	fprintf(file, "5 %d %d\n", x, ADDR_R0);
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
	// TODO depîler les parametres
}

void ass_ifBegin()
{
}

void ass_ifThen()
{
	// TODO enregistrer la fin du if dans la table des labels
	fprintf(file, "jmf %d .%s", ADDR_R0, x);
}

void ass_ifEnd()
{
	// TODO poser un label
}

void ass_whileBegin()
{
	// TODO poser un label
}

void ass_whileDo()
{
	// TODO enregistrer la fin du while dans la table des labels
	fprintf(file, "8 %d .%s", ADDR_R0, x); // if(!R0) goto whileEnd
}

void ass_whileEnd()
{
	// TODO trouver le nom du label
	fprintf(file, "7 .%s", x); // goto whileBegin
	// TODO poser un label
}

void ass_return()
{
}







