#include <stdio.h>

typedef struct {
	char code;
	int var[3];
} Instruction;



FILE* fichier;
Instruction code[1000];
int data[1000];
int test(int addr) { return addr>=0 && addr<1000 }



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

int readInst(Instruction* ins, int nbVar)
{
	int error, i;
	for(i=0; i<nbVar; i++)
	{
		error = fscanf(fichier, "%d", &(ins->var[i]));
		if(error != 1)
			return -2;
		if(!test(ins->var[i]))
			return -3;
	}
	return 0;
}

int readFile()
{
	int i;
	int error = 0;
	char c = 0;
	for(i=0; 1; i++)
	{
		Instruction ins;
		
		error = fscanf(fichier, "%c",&c);
		if(error != 1)
			return -1;
		ins.code = c;
		switch(c)
		{
			case '1':
				error = readInst(ins, 3);
				break;
			case '2':
				error = readInst(ins, 3);
				break;
			case '3':
				error = readInst(ins, 3);
				break;
			case '4':
				error = readInst(ins, 3);
				break;
			case '5':
				error = readInst(ins, 2);
				break;
			case '6':
				error = readInst(ins, 2);
				break;
			case '7':
				error = readInst(ins, 1);
				break;
			case '8':
				error = readInst(ins, 2);
				break;
			case '9':
				error = readInst(ins, 3);
				break;
			case 'A':
				error = readInst(ins, 3);
				break;
			case 'B':
				error = readInst(ins, 3);
				break;
			case 'C':
				error = readInst(ins, 1);
				break;
			default:
				error = -1;
				break;
		}
		if(error != 0)
			break;
		
		code[i] = ins;
	}
	return error;
}

void execute()
{
	
}




