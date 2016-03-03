#include <stdlib.h>
#include <stdio.h>


typedef struct {
	unsigned int code;
	int op[3];
} Instruction;


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
int execInst(Instruction* ins);
// divers
void afficheData(int indice, int nb);
void afficheInst(int indice, int nb);





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
	//                          ERR,1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C
	const int tabInstInfo[] = { 0, 3, 3, 3, 3, 2, 2, 1, 2, 3, 3, 3, 1 };
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
		
		if(ins.code > 12) {
			error = -1;
			printf("Erreur : code operation inconnu (%c)\n", ins.code);
			continue;
		}
		
		// lectures operandes
		error = readInst(fichier, &ins, tabInstInfo[ins.code]);
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
	Instruction ins;
	R_IP = 1;
	while(!error)
	{
		ins = code[R_IP];
		error = execInst(&ins);
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

int execInst(Instruction* ins)
{
	R_IP++;
	// trace?
	/*if(ins->code != 0)
		printf("code : %c\n", ins->code);
	else
		printf("code : 0\n");*/
	// l'exe-switch!
	switch(ins->code)
	{
		case 0:
			return 1;
		case 0x1:
			if(!testData(ins,0) || !testData(ins,1) || !testData(ins,2))
				return -1;
			*p_val(ins,0) = val(ins,1) + val(ins,2);
			break;
		case 0x2:
			if(!testData(ins,0) || !testData(ins,1) || !testData(ins,2))
				return -1;
			*p_val(ins,0) = val(ins,1) * val(ins,2);
			break;
		case 0x3:
			if(!testData(ins,0) || !testData(ins,1) || !testData(ins,2))
				return -1;
			*p_val(ins,0) = val(ins,1) - val(ins,2);
			break;
		case 0x4:
			if(!testData(ins,0) || !testData(ins,1) || !testData(ins,2))
				return -1;
			*p_val(ins,0) = val(ins,1) / val(ins,2);
			break;
		case 0x5:
			if(!testData(ins,0) || !testData(ins,1))
				return -1;
			*p_val(ins,0) = val(ins,1);
			break;
		case 0x6:
			if(!testData(ins,0))
				return -1;
			*p_val(ins,0) = ins->op[1];
			break;
		case 0x7:
			R_IP = ins->op[0];
			break;
		case 0x8:
			if(!testData(ins,0))
				return -1;
			if(val(ins,0) == 0)
				R_IP = ins->op[1];
			break;
		case 0x9:
			if(!testData(ins,0) || !testData(ins,1) || !testData(ins,2))
				return -1;
			*p_val(ins,0) = val(ins,1) < val(ins,2);
			break;
		case 0xA:
			if(!testData(ins,0) || !testData(ins,1) || !testData(ins,2))
				return -1;
			*p_val(ins,0) = val(ins,1) > val(ins,2);
			break;
		case 0xB:
			if(!testData(ins,0) || !testData(ins,1) || !testData(ins,2))
				return -1;
			*p_val(ins,0) = val(ins,1) == val(ins,2);
			break;
		case 0xC:
			if(!testData(ins,0))
				return -1;
			printf("%d\n",val(ins,0));
			break;
		default:
			break;
	}
	if(R_IP<0 || R_IP>=SIZE_CODE)
		return -2;
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






