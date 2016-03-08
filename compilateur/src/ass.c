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
	fprintf(file, "6 %d 0\n", ADDR_STACK); // STACK[0] = 0
	fprintf(file, "6 %d %d\n", ADDR_SP, ADDR_STACK+1); // SP = ADDR_STACK + 1
	fprintf(file, "7 .main\n"); // goto main
}

void ass_progEnd()
{
}

void ass_fctBegin(char* fctName)
{
	// TODO poser un label de fonction
	empiler(ADDR_CONTEXT);
	fprintf(file, "5 %d %d\n", ADDR_CONTEXT, ADDR_SP);
}

void ass_fctEnd()
{
	empiler(ADDR_CONTEXT); // sauver le contexte
	fprintf(file, "5 %d %d\n", ADDR_CONTEXT, ADDR_SP); // CONTEXT = SP
	// sauter a l'addresse de retour.
	fprintf(file, "D %d %d\n", ADDR_R1, ADDR_SP); // *addr = *SP
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

void ass_declVar(char* varName, int value)
{
	// TODO enregistrer dans la table des symboles (à l'addresse SP)
	fprintf(file, "6 %d %d\n", x, value); // *varName = value
	empiler(ADDR_R1);
}

void ass_ldr(char* varName)
{
	// TODO rechercher varName dans la table des symboles
	empiler(x);
}

void ass_str(char* varName)
{
	// TODO rechercher varName dans la table des symboles
	depiler(x);
}

void ass_ld(int value)
{
	fprintf(file, "6 %d %d\n", ADDR_R1, value);
	empiler(ADDR_R1);
}

void ass_loadResult(int reg)
{
	depiler(ADDR_R0 + reg);
}

void ass_add()
{
	fprintf(file, "1 %d %d %d\n", ADDR_R0, ADDR_R0, ADDR_R1);
	empiler(ADDR_R0);
}

void ass_sub()
{
	fprintf(file, "3 %d %d %d\n", ADDR_R0, ADDR_R0, ADDR_R1);
	empiler(ADDR_R0);
}

void ass_mul()
{
	fprintf(file, "2 %d %d %d\n", ADDR_R0, ADDR_R0, ADDR_R1);
	empiler(ADDR_R0);
}

void ass_div()
{
	fprintf(file, "4 %d %d %d\n", ADDR_R0, ADDR_R0, ADDR_R1);
	empiler(ADDR_R0);
}

void ass_and()
{
	// TODO
}

void ass_or()
{
	// TODO
}

void ass_inf()
{
	fprintf(file, "9 %d %d %d\n", ADDR_R0, ADDR_R0, ADDR_R1);
	empiler(ADDR_R0);
}

void ass_sup()
{
	fprintf(file, "A %d %d %d\n", ADDR_R0, ADDR_R0, ADDR_R1);
	empiler(ADDR_R0);
}

void ass_equ()
{
	fprintf(file, "B %d %d %d\n", ADDR_R0, ADDR_R0, ADDR_R1);
	empiler(ADDR_R0);
}

void ass_fctCallParam()
{
	// pas besoin de depiler pour re-empiler.
}

void ass_fctCallJmp(char* fctName)
{
	// TODO sauver l'adresse de retour
	empiler(ADDR_R1);
	fprintf(file, "7 .%s\n", fctName);
}

void ass_ifBegin()
{
}

void ass_ifThen()
{
	depiler(ADDR_R1);
	// TODO enregistrer la fin du if dans la table des labels
	fprintf(file, "jmf %d .%s", ADDR_R1, x);
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
	depiler(ADDR_R1);
	// TODO enregistrer la fin du while dans la table des labels
	fprintf(file, "jmf %d .%s", ADDR_R1, x);
}

void ass_whileEnd()
{
	// TODO trouver le nom du label
	fprintf(file, "jmp .%s", x);
	// TODO poser un label
}

void ass_return()
{
	depiler(ADDR_R0);
}







