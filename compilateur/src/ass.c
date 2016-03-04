#include "ass.h"




//###################################################
//  DEFINITION UTILES
//###################################################


typedef enum {
	ADDR_RETURN = 0,
	ADDR_R1,
	ADDR_R2,
	ADDR_SP,
	ADDR_STACK,
} UsefullAddress;




FILE* file;







//###################################################
//  DEFINITION DES FONCTIONS
//###################################################

void setFile(FILE* outputFile)
{
	file = outputFile;
}







void ass_progBegin()
{
	fprintf(file, "6 %d 0\n"); // ADDR_STACK <- 0
	fprintf(file, "6 %d %d\n", ADDR_SP, ADDR_STACK+1); // SP <- ADDR_STACK + 1
	fprintf(file, "7 .main\n"); // goto main
}

void ass_progEnd()
{
}

void ass_fctBegin(char* fctName)
{
	fprintf(file, ":%s ", fctName);
}

void ass_fctEnd()
{
	// Depiler adresse de retour
}

void ass_blocBegin()
{

}

void ass_blocEnd()
{

}

void ass_declVar(char* varName, int value)
{

}

void ass_ldr(char* varName)
{

}

void ass_str(char* varName)
{

}

void ass_pushResult()
{

}

void ass_popResult(int reg)
{

}

void ass_add()
{

}

void ass_sub()
{

}

void ass_mul()
{

}

void ass_div()
{

}

void ass_and()
{

}

void ass_or()
{

}

void ass_inf()
{

}

void ass_sup()
{

}

void ass_equ()
{

}

void ass_fctCallParam(int value)
{

}

void ass_fctCallJmp(char* fctName)
{

}

void ass_ifBegin()
{

}

void ass_ifThen()
{

}

void ass_ifEnd()
{

}

void ass_whileBegin()
{

}

void ass_whileDo()
{

}

void ass_whileEnd()
{

}

void ass_return()
{

}







