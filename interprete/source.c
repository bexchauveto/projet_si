#include <stdlib.h>
#include <stdio.h>


typedef struct {
	unsigned int code;
	int op[3];
} Instruction;

typedef int (*InstCallback)(Instruction*);
typedef struct {
	int nbOp;
	InstCallback cb;
} InstInfo;


#define SIZE_CODE 1000
#define SIZE_DATA 1000
Instruction code[SIZE_CODE];
int data[SIZE_DATA];
int R_IP;





// lecture
int readInst(FILE* fichier, Instruction* ins, int nbOp);
int readFile(FILE* fichier);
// execute
int execute();
int Ierror(Instruction* ins);
int Iadd(Instruction* ins);
int Imul(Instruction* ins);
int Isub(Instruction* ins);
int Idiv(Instruction* ins);
int Icop(Instruction* ins);
int Iafc(Instruction* ins);
int Ijmp(Instruction* ins);
int Ijmf(Instruction* ins);
int Iinf(Instruction* ins);
int Isup(Instruction* ins);
int Iequ(Instruction* ins);
int Ipri(Instruction* ins);
int Icopa(Instruction* ins);
int Icopb(Instruction* ins);
int Ijmp2(Instruction* ins);
// divers
void afficheData(int indice, int nb);
void afficheInst(int indice, int nb);



const int tabInstInfoSize = 16;
InstInfo tabInstInfo[] = {
	{ 0, Ierror },
	{ 3, Iadd },
	{ 3, Imul },
	{ 3, Isub },
	{ 3, Idiv },
	{ 2, Icop },
	{ 2, Iafc },
	{ 1, Ijmp },
	{ 2, Ijmf },
	{ 3, Iinf },
	{ 3, Isup },
	{ 3, Iequ },
	{ 1, Ipri },
	{ 2, Icopa},
	{ 2, Icopb},
	{ 1, Ijmp2}
};















int main(int argc, char *argv[])
{
    FILE* fichier = NULL;
	
	if(argc != 2)
	{
		printf("mauvais arguments\n");
		printf("usage : %s [fichier]\n", argv[0]);
		exit(0);
	}
	
    fichier = fopen(argv[1], "r");

    if (fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", argv[1]);
        exit(0);
    }
    
    // lecture du fichier
    readFile(fichier);
    
    fclose(fichier);
    
    // Interpretation du code
    execute();
    
    return 0;
}




/******         Lecture         ******/

int readFile(FILE* fichier)
{
	int i = 1;
	int error = 0;
	char line[100]; // to skip
	Instruction ins;
	
	do {
		// lecture code operation
		error = fscanf(fichier, "%x",&(ins.code));
		if(error != 1) {
			//printf("Erreur : lecture code operation\n");
			continue;
		}
		
		if(ins.code >= tabInstInfoSize) {
			error = -1;
			printf("Erreur : code operation inconnu (%c)\n", ins.code);
			continue;
		}
		
		// lectures operandes
		error = readInst(fichier, &ins, tabInstInfo[ins.code].nbOp);
		if(error == -2) {
			printf("Erreur : nombre d'operandes invalide pour le code (%c)\n", ins.code);
			continue;
		}
		
		code[i] = ins;
		i++;
	} while((error = fgets(line,sizeof(line)-1,fichier)));
	
	i++;
	code[i].code = 0;
	code[0].code = 0;
	
	return 0;
}

int readInst(FILE* fichier, Instruction* ins, int nbOp)
{
	int error, i;
	for(i=0; i<nbOp; i++)
	{
		error = fscanf(fichier, "%d", &(ins->op[i]));
		if(error != 1)
			return -2;
	}
	return 0;
}



/******         Execute         ******/


int execute()
{
	int error = 0;
	Instruction* ins;
	R_IP = 1;
	while(!error)
	{
		ins = &(code[R_IP]);
		// trace?
		/*if(ins->code != 0)
			printf("code : %c\n", ins->code);
		else
			printf("code : 0\n");*/
		R_IP++;
		error = tabInstInfo[ins->code].cb(ins);
		if(R_IP<0 || R_IP>=SIZE_CODE)
			error = -2;
	}
	if(error == -1)
		printf("Erreur : addresse invalide (data)\n");
	if(error == -2)
		printf("Erreur : addresse invalide (code)\n");
	return error;
}


int val(Instruction* ins, int op)
{ return data[ins->op[op]]; }

int* p_val(Instruction* ins, int op)
{ return &data[ins->op[op]]; }

int testData(Instruction* ins, int op)
{ return (ins->op[op])>=0 && (ins->op[op])<SIZE_DATA; }

int Ierror(Instruction* ins)
{
	return 1;
}

int Iadd(Instruction* ins)
{
	if(!testData(ins,0) || !testData(ins,1) || !testData(ins,2))
		return -1;
	*p_val(ins,0) = val(ins,1) + val(ins,2);
	return 0;
}

int Imul(Instruction* ins)
{
	if(!testData(ins,0) || !testData(ins,1) || !testData(ins,2))
		return -1;
	*p_val(ins,0) = val(ins,1) * val(ins,2);
	return 0;
}

int Isub(Instruction* ins)
{
	if(!testData(ins,0) || !testData(ins,1) || !testData(ins,2))
		return -1;
	*p_val(ins,0) = val(ins,1) - val(ins,2);
	return 0;
}

int Idiv(Instruction* ins)
{
	if(!testData(ins,0) || !testData(ins,1) || !testData(ins,2))
		return -1;
	*p_val(ins,0) = val(ins,1) / val(ins,2);
	return 0;
}

int Icop(Instruction* ins)
{
	if(!testData(ins,0) || !testData(ins,1))
		return -1;
	*p_val(ins,0) = val(ins,1);
	return 0;
}

int Iafc(Instruction* ins)
{
	if(!testData(ins,0))
		return -1;
	*p_val(ins,0) = ins->op[1];
	return 0;
}

int Ijmp(Instruction* ins)
{
	R_IP = ins->op[0];
	return 0;
}

int Ijmf(Instruction* ins)
{
	if(!testData(ins,0))
		return -1;
	if(val(ins,0) == 0)
		R_IP = ins->op[1];
	return 0;
}

int Iinf(Instruction* ins)
{
	if(!testData(ins,0) || !testData(ins,1) || !testData(ins,2))
		return -1;
	*p_val(ins,0) = val(ins,1) < val(ins,2);
	return 0;
}

int Isup(Instruction* ins)
{
	if(!testData(ins,0) || !testData(ins,1) || !testData(ins,2))
		return -1;
	*p_val(ins,0) = val(ins,1) > val(ins,2);
	return 0;
}

int Iequ(Instruction* ins)
{
	if(!testData(ins,0) || !testData(ins,1) || !testData(ins,2))
		return -1;
	*p_val(ins,0) = val(ins,1) == val(ins,2);
	return 0;
}

int Ipri(Instruction* ins)
{
	if(!testData(ins,0))
		return -1;
	printf("%d\n",val(ins,0));
	return 0;
}

int Icopa(Instruction* ins)
{
	if(!testData(ins,0) || !testData(ins,1))
		return -1;
	ins->op[1] = val(ins,1);
	if(!testData(ins,1))
		return -1;
	*p_val(ins,0) = val(ins,1);
	return 0;
}

int Icopb(Instruction* ins)
{
	if(!testData(ins,0) || !testData(ins,1))
		return -1;
	ins->op[0] = val(ins,0);
	if(!testData(ins,0))
		return -1;
	*p_val(ins,0) = val(ins,1);
	return 0;
}

int Ijmp2(Instruction* ins)
{
	if(!testData(ins,0))
		return -1;
	R_IP = val(ins,0);
	return 0;
}




/******         Divers         ******/

void afficheData(int indice, int nb)
{
	printf("data => \n");
	for(int i=indice; i<indice+nb; i++)
	{
		printf("  %d : %d\n", i, data[i]);
	}
}

void afficheInst(int indice, int nb)
{
	printf("code => \n");
	for(int i=indice; i<indice+nb; i++)
	{
		printf("  %d : %c\n", i, code[i].code);
	}
}






