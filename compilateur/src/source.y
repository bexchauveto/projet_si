%{

#include <stdio.h>
#include <stdlib.h>

#include "st.h"
#include "ass.h"
#include "linker.h"
#include "error.h"


extern int yylineno;

int yylex();
void yyerror(const char *s);	



%}
%start Prg


/* ---- DEFINITIONS TOKENS ---- */
%token tPO tPF tAO tAF tPLUS tMOINS tMUL tDIV tEQ tVIR tINT tCONST tRETURN tPTVIR tIF tELSE tWHILE tOR tAND tINF tSUP tSUPEQ tINFEQ tEQU tDIFF tNOT tREF tCO tCF

%union 
{
	// terminaux
	int integer;
	float exp;
	char *string;
	
	// non terminaux
	void* nodeID;
}
%token <integer> tNB
%token <exp> tNBEXP
%token <string> tID

%type <integer> PtrsDef
%type <nodeID> Prg Fct Prototype Params DeclParam SuiteParams Type
%type <nodeID> Bloc Body BlocRet DeclVar SuiteDeclVar DeclVarVar DeclVarExp
%type <nodeID> Instruction Expr AppelFct AppelParams SuiteAppelParams While If Return



/* ---- OPERATEURS ---- */

%right tEQ
%left tOR
%left tAND
%left tEQU tDIFF
%left tINF tINFEQ tSUP tSUPEQ
%left tPLUS tMOINS
%left tMUL tDIV
%right tNOT tREF DEREFERENCE
%left tCO tCF




/* ---- TODO LIST ---- */
/*

TODO:
- tableaux
- pointeurs

*/






%%

/* ------ DEFINITION DIVERSES ------ */
Type :
	  tINT PtrsDef
	  		{ $$=st_type(0, 0, $2); };
PtrsDef :
	  tMUL PtrsDef
	  		{ $$ = $2 + 1; }
	| 		{ $$ = 0; };

/* ------ DEFINITION DU FICHIER ------ */
Prg :
	  Fct Prg
	  		{ $$=st_node(NT_ROOT, $1, $2); }
	| 		{ $$=ST_UNDEFINED; };

/* ------ DEFINITION DES FONCTIONS ------ */
Fct : 
	  Prototype Bloc 
	  		{
	  			$$ = st_node(NT_FUNCTION, $1, $2);
	  			error(ERR_WARNING, "reach end of non-void function without return statement", yylineno);
	  		}
	| Prototype BlocRet 
	  		{ $$ = st_node(NT_FUNCTION, $1, $2); }
	| Prototype tPTVIR
			{ $$ = st_node(NT_FUNCTION, $1, ST_UNDEFINED); };
Prototype : 
	  Type tID tPO Params tPF 
	  		{
	  			st_Node_t id = st_id($2, yylineno);
	  			$$ = st_node(NT_PROTOTYPE, $1, id, $4);
			} ;
Params : 
	  DeclParam SuiteParams
	  		{ $$=st_node(NT_PARAMS, $1, $2); }
	| 		{ $$=ST_UNDEFINED; };
DeclParam :
	  Type tID 
	  		{
	  			st_Node_t id = st_id($2, yylineno);
	  			$$ = st_node(NT_PARAM, $1, id, ST_UNDEFINED);
			};
/*	| Type tID tCO tCF
			{
	  			st_Node_t id = st_id($2, yylineno);
	  			st_Node_t size = st_exNb(0); // TODO Array Size
	  			$$ = st_node(NT_PARAM, $1, id, size);
			};*/
SuiteParams :
	  tVIR DeclParam SuiteParams
	  		{ $$ = st_node(NT_PARAMS, $2, $3); }
	| 		{ $$=ST_UNDEFINED; };

/* ------ DEFINITION DES BLOCS ------ */
Bloc : 
	  tAO Body tAF
	  		{ $$ = st_node(NT_BLOC, $2, ST_UNDEFINED); };
BlocRet : 
	  tAO Body Return tAF
	  		{ $$ = st_node(NT_BLOC, $2, $3); };
Body : 
	  Instruction Body
	  		{ $$ = st_node(NT_BODY, $1, $2); }
	| 		{ $$=ST_UNDEFINED; };

/* ------ DEFINITION DES DECLARATIONS ------ */
DeclVar : 
	  Type DeclVarVar SuiteDeclVar
	  		{
	  			st_Node_t d2 = st_node(NT_DECLVAR2, $2, $3);
	  			$$ = st_node(NT_DECLVAR, $1, d2);
	  		};
SuiteDeclVar : 
	  tVIR DeclVarVar SuiteDeclVar
	  		{ $$ = st_node(NT_DECLVAR2, $2, $3); }
	| 		{ $$=ST_UNDEFINED; };
DeclVarVar : 
	  tID DeclVarExp
	  		{
	  			st_Node_t id = st_id($1, yylineno);
	  			$$ = st_node(NT_DECLVARVAR, id, $2, ST_UNDEFINED);
	  		}
	| tID tCO tNB tCF
			{
	  			st_Node_t id = st_id($1, yylineno);
	  			st_Node_t size = st_exNb($3);
	  			$$ = st_node(NT_DECLVARVAR, id, ST_UNDEFINED, size);
	  		};
DeclVarExp :
	  tEQ Expr
	  		{ $$=$2; }
	| 		{ $$=ST_UNDEFINED; };
	

/* ------ DEFINITION DES INSTRUCTIONS ------ */
Instruction :
	  Expr tPTVIR
	  		{ $$ = $1; }
	| DeclVar tPTVIR
			{ $$ = $1; }
	| Bloc
			{ $$ = $1; }
	| While
			{ $$ = $1; }
	| If
			{ $$ = $1; };
While : 
	  tWHILE tPO Expr tPF Instruction
	  		{ $$ = st_node(NT_WHILE, $3, $5); };
If : 
	  tIF tPO Expr tPF Instruction
	  		{ $$ = st_node(NT_IF, $3, $5, ST_UNDEFINED); }
	| tIF tPO Expr tPF Instruction tELSE Instruction
			{ $$ = st_node(NT_IF, $3, $5, $7); };
Return :
	tRETURN Expr tPTVIR
			{ $$ = st_node(NT_RETURN, $2); };
Expr : 
	  tPO Expr tPF 
	  		{ $$ = $2; }
	| Expr tPLUS Expr
	  		{ $$ = st_node(NT_EXADD, $1, $3); }
	| Expr tMOINS Expr
	  		{ $$ = st_node(NT_EXSUB, $1, $3); }
	| Expr tMUL Expr
	  		{ $$ = st_node(NT_EXMUL, $1, $3); }
	| Expr tDIV Expr
	  		{ $$ = st_node(NT_EXDIV, $1, $3); }
	| Expr tOR Expr
			{ $$ = st_node(NT_EXOR, $1, $3); }
	| Expr tAND Expr
			{ $$ = st_node(NT_EXAND, $1, $3); }
	| tNOT Expr
			{ $$ = st_node(NT_EXNOT, $2);}
	| Expr tSUP Expr
			{ $$ = st_node(NT_EXSUP, $1, $3); }
	| Expr tINF Expr
			{ $$ = st_node(NT_EXINF, $1, $3); }
	| Expr tSUPEQ Expr
			{ $$ = st_node(NT_EXSUPEQ, $1, $3); }
	| Expr tINFEQ Expr
			{ $$ = st_node(NT_EXINFEQ, $1, $3); }
	| Expr tDIFF Expr
			{ $$ = st_node(NT_EXDIFF, $1, $3); }
	| Expr tEQU Expr
			{ $$ = st_node(NT_EXEQU, $1, $3); }
	| tID tEQ Expr
	  		{
	  			st_Node_t id = st_id($1, yylineno);
	  			$$ = st_node(NT_EXAFFECT, id, $3);
			}
	| Expr tCO Expr tCF
			{ $$ = st_node(NT_EXTAB,$1,$3); }
	| tMUL Expr %prec DEREFERENCE
			{ $$ = st_node(NT_EXDEREF,$2); }
	| tREF tID
			{
				st_Node_t id = st_id($2, yylineno);
				$$ = st_node(NT_EXREF,id);
			}
	| AppelFct
	  		{ $$ = $1; }
	| tNB
	  		{ $$ = st_exNb($1); }
	| tNBEXP
	  		{ $$ = st_exNb($1); }
	| tID
	  		{ $$ = st_id($1, yylineno); };
AppelFct : 
	  tID tPO AppelParams tPF
	  		{
	  			st_Node_t id = st_id($1, yylineno);
	  			$$ = st_node(NT_FCTCALL, id, $3);
			};
AppelParams : 
	  Expr SuiteAppelParams
	  		{ $$ = st_node(NT_CALLPARAMS, $1, $2); }
	| 		{ $$=ST_UNDEFINED; };
SuiteAppelParams : 
	  tVIR Expr SuiteAppelParams
	  		{ $$ = st_node(NT_CALLPARAMS, $2, $3); }
	| 		{ $$=ST_UNDEFINED; };





%%

void yyerror(const char* s)
{
	error(ERR_FATAL, s, yylineno);
}


int main(int argc, char * argv[])
{
	if(argc < 2)
	{
		printf("Usage : %s [OUTPUT_FILE] < [INPUT_FILE] \n", argv[0]);
		return -1;
	}
	// --- Lecture du fichier
	yyparse();
	//st_printTree(0,0);
	
	// --- Compilation
	
	FILE * file = fopen(argv[1], "w");
	if(file == NULL)
	{
		printf("\Error : Cannot open output file.\n");
		return -1;
	}
	ass_setFile(file);
	st_compute(0);
	fflush(file);
	fclose(file);
	
	// --- Linkage
	linker_openFile(argv[1]);
	linker_readFileAndReplaceLabel(file);
	linker_closeFile(file);
	
	return 0;
}




