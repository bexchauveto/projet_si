%{

#include <stdio.h>
#include <stdlib.h>

#include "st.h"
#include "ass.h"


int yylex();
int yyerror(char *s);	



%}
%start Prg


/* ---- DEFINITIONS TOKENS ---- */
%token tPO tPF tAO tAF tPLUS tMOINS tMUL tDIV tEQ tVIR tINT tCONST tPRINT tRETURN tPTVIR tIF tWHILE tOR tAND tINF tSUP tSUPEQ tINFEQ tEQU tDIFF tNOT

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

%type <nodeID> Prg Fct Prototype Params DeclParam SuiteParams 
%type <nodeID> Bloc Body BodyHead BodyBelly BodyFoot DeclVar SuiteDeclVar 
%type <nodeID> Instruction Expr AppelFct AppelParams SuiteAppelParams While If Condition Ret



/* ---- OPERATEURS ---- */

%right tEQ
%left tOR
%left tAND
%left tEQU tDIFF
%left tINF tINFEQ tSUP tSUPEQ
%left tPLUS tMOINS
%left tMUL tDIV
%right tNOT




/* ---- TODO LIST ---- */
/*

TODO:
- mot clé const
- affectation lors de la declaration
- return n'importe ou
- affectation n'importe ou

*/






%%

/* ---- DEFINITION DU FICHIER ---- */
Prg :
	  Fct Prg
	  		{ st_node(NT_ROOT, $1, $2); }
	| 		{ $$=ST_UNDEFINED; };

/* ---- DEFINITION DES FONCTIONS ---- */
Fct : 
	  Prototype Bloc 
	  		{ $$ = st_node(NT_FUNCTION, $1, $2); };
Prototype : 
	  tINT tID tPO Params tPF 
	  		{
	  			st_Node_t type = st_type(0, 0);
	  			st_Node_t id = st_id($2);
	  			$$ = st_node(NT_PROTOTYPE, type, id, $4);
			} ;
Params : 
	  DeclParam SuiteParams
	  		{ $$=st_node(NT_PARAMS, $1, $2); }
	| 		{ $$=ST_UNDEFINED; };
DeclParam :
	  tINT tID 
	  		{
	  			st_Node_t type = st_type(0, 0);
	  			st_Node_t id = st_id($2);
	  			$$ = st_node(NT_PARAM, type, id);
			};
SuiteParams :
	  tVIR DeclParam SuiteParams
	  		{ $$ = st_node(NT_PARAMS, $2, $3); }
	| 		{ $$=ST_UNDEFINED; };

/* ---- DEFINITION DES BLOCS ---- */
Bloc : 
	  tAO Body tAF
	  		{ $$ = $2; };
Body : 
	  BodyHead BodyBelly BodyFoot
	  		{ $$ = st_node(NT_BLOC, $1, $2, $3); };
BodyHead : 
	  DeclVar BodyHead
	  		{ $$ = st_node(NT_BODYHEAD, $1, $2); }
	| 		{ $$=ST_UNDEFINED; };
BodyBelly : 
	  Instruction BodyBelly
	  		{ $$ = st_node(NT_BODYBELLY, $1, $2); }
	| 		{ $$=ST_UNDEFINED; };
BodyFoot :
	  Ret	{ $$ = $1; }
	| 		{ $$=ST_UNDEFINED; };

/* ---- DEFINITION DES DECLARATIONS ---- */
DeclVar : 
	  tINT tID SuiteDeclVar tPTVIR
	  		{
	  			st_Node_t type = st_type(0,0);
	  			st_Node_t id = st_id($2);
	  			st_Node_t v = st_node(NT_DECLVARVAR, id, 0);
	  			st_Node_t d2 = st_node(NT_DECLVAR2, v, $3);
	  			$$ = st_node(NT_DECLVAR, type, d2);
	  		};
//	| tINT tID tEQ Expr SuiteDeclVar;
SuiteDeclVar : 
	  tVIR tID SuiteDeclVar
	  		{
	  			st_Node_t id = st_id($2);
	  			st_Node_t v = st_node(NT_DECLVARVAR, id, 0);
	  			$$ = st_node(NT_DECLVAR2, v, $3);
			}
//	| tVIR tID tEQ Expr SuiteDeclVar
	| 		{ $$=ST_UNDEFINED; };

/* ---- DEFINITION DES INSTRUCTIONS ---- */
Instruction :
	  Expr tPTVIR
	  		{ $$ = $1; }
	| Bloc
			{ $$ = $1; }
	| While
			{ $$ = $1; }
	| If
			{ $$ = $1; };
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
	  			st_Node_t id = st_id($1);
	  			$$ = st_node(NT_EXAFFECT, id, $3);
			}
	| AppelFct
	  		{ $$ = $1; }
	| tNB
	  		{ $$ = st_exNb($1); }
	| tNBEXP
	  		{ $$ = st_exNb($1); }
	| tID
	  		{ $$ = st_id($1); };
AppelFct : 
	  tID tPO AppelParams tPF
	  		{
	  			st_Node_t id = st_id($1);
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
While : 
	  tWHILE tPO Condition tPF Instruction
	  		{ $$ = st_node(NT_WHILE, $3, $5); };
If : 
	  tIF tPO Condition tPF Instruction
	  		{ $$ = st_node(NT_IF, $3, $5); };
Condition : 
	  Expr
	  		{ $$ = $1; };
Ret :
	tRETURN Expr tPTVIR
			{ $$ = st_node(NT_RETURN, $2); };



%%

int yyerror(char* s)
{
	printf("%s\n", s);
	exit(0);
}


int main(void)
{
	ass_setFile(stdin);
	yyparse();
	st_printTree(0,0);
	st_compute(0);
	return 0;
}

