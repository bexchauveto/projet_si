#include <stdlib.h>
#include <stdio.h>


#define SIZE_TABS 1000

typedef struct {
	char code;
	int op[3];
} Instruction;

typedef struct {
	char code;
	int nbOp;
} InstInfo;



FILE* fichier;

int R_IP;
Instruction code[SIZE_TABS];
int data[SIZE_TABS];


const InstInfo tabInstInfo[] = {
	{ '1', 3 },
	{ '2', 3 },
	{ '3', 3 },
	{ '4', 3 },
	{ '5', 3 },
	{ '6', 3 },
	{ '7', 3 },
	{ '8', 3 },
	{ '9', 3 },
	{ 'A', 3 },
	{ 'B', 3 },
	{ 'C', 3 },
	{ '\0', 0 },
};



int test(int addr) { return addr>=0 && addr<SIZE_TABS; }
int readInst(Instruction* ins, int nbOp);
int readFile();
int execute();
int execInst(Instruction* ins);
void afficheData(int indice, int nb);
void afficheInst(int indice, int nb);





int main(int argc, char *argv[])
{
	int error;
    fichier = NULL;
	
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
    
    printf("Lecture du fichier...\n");
    error = readFile();
    switch(error)
    {
    	case -1:
    		printf("Erreur : code operation\n");
    		break;
    	case -2:
    		printf("Erreur : operande manquante\n");
    		break;
    	case -3:
    		printf("Erreur : mauvaise operande\n");
    		break;
    	default:
    		break;
    }
    
    fclose(fichier);
    
    printf("Interpretation du code...\n");
    error = execute();
    
    return 0;
}




/******         Lecture         ******/

int readFile()
{
	int i, j;
	int error = 0;
	char c = 0;
	for(i=1; 1; i++)
	{
		Instruction ins;
		
		error = fscanf(fichier, "%c",&c);
		if(error != 1)
			return -1;
		ins.code = c;
		
		for(j=0; tabInstInfo[j].code != '\0'; j++)
		{
			if(tabInstInfo[j].code == c)
			{
				error = readInst(&ins, tabInstInfo[j].nbOp);
				break;
			}
		}
		if(tabInstInfo[j].code == '\0')
			error = -1;
		if(error != 0)
			break;
		
		code[i] = ins;
	}
	
	i++;
	code[i].code = '\0';
	
	return error;
}

int readInst(Instruction* ins, int nbOp)
{
	int error, i;
	for(i=0; i<nbOp; i++)
	{
		error = fscanf(fichier, "%d", &(ins->op[i]));
		if(error != 1)
			return -2;
		if(!test(ins->op[i]))
			return -3;
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
	return error;
}

int val(Instruction* ins, int op)
{ return data[ins->op[op]]; }

int* p_val(Instruction* ins, int op)
{ return &data[ins->op[op]]; }

int execInst(Instruction* ins)
{
	R_IP++;
	if(ins->code != 0)
		printf("code : %c\n", ins->code);
	else
		printf("code : 0\n");
	switch(ins->code)
	{
		case 0:
			return 1;
		case '1':
			*p_val(ins,0) = val(ins,1) + val(ins,2);
			break;
		case '2':
			*p_val(ins,0) = val(ins,1) * val(ins,2);
			break;
		case '3':
			*p_val(ins,0) = val(ins,1) - val(ins,2);
			break;
		case '4':
			*p_val(ins,0) = val(ins,1) / val(ins,2);
			break;
		case '5':
			*p_val(ins,0) = val(ins,1);
			break;
		case '6':
			*p_val(ins,0) = ins->op[1];
			break;
		case '7':
			R_IP = ins->op[0];
			break;
		case '8':
			if(val(ins,0) == 0)
				R_IP = ins->op[1];
			break;
		case '9':
			*p_val(ins,0) = val(ins,1) < val(ins,2);
			break;
		case 'A':
			*p_val(ins,0) = val(ins,1) > val(ins,2);
			break;
		case 'B':
			*p_val(ins,0) = val(ins,1) == val(ins,2);
			break;
		case 'C':
			printf("%d\n",val(ins,0));
			break;
		default:
			break;
	}
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
	printf("code : \n");
	for(int i=indice; i<indice+nb; i++)
	{
		printf("  %d : %c\n", i, code[i].code);
	}
}






