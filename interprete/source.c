#include <stdio.h>

typedef struct {
	char code;
	int op[3];
} Instruction;



FILE* fichier;
Instruction code[1000];
int data[1000];
int test(int addr) { return addr>=0 && addr<1000 }

typedef struct {
	char code;
	int nbOp;
} InstInfo;
const InstInfo tabInstInfo[] = [
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
]


void execute;


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
    
    execute();
    
    return 0;
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

int readFile()
{
	int i, j;
	int error = 0;
	char c = 0;
	for(i=0; 1; i++)
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
				error = readInst(ins, tabInstInfo[j].nbOp);
				break;
			}
		}
		if(tabInstInfo[j].code == '\0')
			error = -1;
		if(error != 0)
			break;
		
		code[i] = ins;
	}
	return error;
}

void execute()
{
	
}




