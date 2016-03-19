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
	  		{ st_root($1, $2); }
	| 		{ $$=ST_UNDEFINED; };

/* ---- DEFINITION DES FONCTIONS ---- */
Fct : 
	  Prototype Bloc 
	  		{ $$ = st_function($1, $2); };
Prototype : 
	  tINT tID tPO Params tPF 
	  		{
	  			st_Node_t type = st_type(0, 0);
	  			st_Node_t id = st_id($2);
	  			$$ = st_prototype(type, id, $4);
			} ;
Params : 
	  DeclParam SuiteParams
	  		{ $$=st_params($1, $2); }
	| 		{ $$=ST_UNDEFINED; };
DeclParam :
	  tINT tID 
	  		{
	  			st_Node_t type = st_type(0, 0);
	  			st_Node_t id = st_id($2);
	  			$$ = st_param(type, id);
			};
SuiteParams :
	  tVIR DeclParam SuiteParams
	  		{ $$ = st_params($2, $3); }
	| 		{ $$=ST_UNDEFINED; };

/* ---- DEFINITION DES BLOCS ---- */
Bloc : 
	  tAO Body tAF
	  		{ $$ = $2; };
Body : 
	  BodyHead BodyBelly BodyFoot
	  		{ $$ = st_bloc($1, $2, $3); };
BodyHead : 
	  DeclVar BodyHead
	  		{ $$ = st_bodyHead($1, $2); }
	| 		{ $$=ST_UNDEFINED; };
BodyBelly : 
	  Instruction BodyBelly
	  		{ $$ = st_bodyBelly($1, $2); }
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
	  			st_Node_t v = st_declVarVar(id, 0);
	  			st_Node_t d2 = st_declVar2(v, $3);
	  			$$ = st_declVar(type, d2);
	  		};
//	| tINT tID tEQ Expr SuiteDeclVar;
SuiteDeclVar : 
	  tVIR tID SuiteDeclVar
	  		{
	  			st_Node_t id = st_id($2);
	  			st_Node_t v = st_declVarVar(id, 0);
	  			$$ = st_declVar2(v, $3);
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
	  		{ $$ = st_exAdd($1, $3); }
	| Expr tMOINS Expr
	  		{ $$ = st_exSub($1, $3); }
	| Expr tMUL Expr
	  		{ $$ = st_exMul($1, $3); }
	| Expr tDIV Expr
	  		{ $$ = st_exDiv($1, $3); }
	| Expr tOR Expr
			{ $$ = st_exOr($1, $3); }
	| Expr tAND Expr
			{ $$ = st_exAnd($1, $3); }
	| tNOT Expr
			{ $$ = st_exNot($2);}
	| Expr tSUP Expr
			{ $$ = st_exSup($1, $3); }
	| Expr tINF Expr
			{ $$ = st_exInf($1, $3); }
	| Expr tSUPEQ Expr
			{ $$ = st_exSupEq($1, $3); }
	| Expr tINFEQ Expr
			{ $$ = st_exInfEq($1, $3); }
	| Expr tDIFF Expr
			{ $$ = st_exDiff($1, $3); }
	| Expr tEQU Expr
			{ $$ = st_exEqu($1, $3); }
	| tID tEQ Expr
	  		{
	  			st_Node_t id = st_id($1);
	  			$$ = st_exAffect(id, $3);
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
	  			$$ = st_fctCall(id, $3);
			};
AppelParams : 
	  Expr SuiteAppelParams
	  		{ $$ = st_callParams($1, $2); }
	| 		{ $$=ST_UNDEFINED; };
SuiteAppelParams : 
	  tVIR Expr SuiteAppelParams
	  		{ $$ = st_callParams($2, $3); }
	| 		{ $$=ST_UNDEFINED; };
While : 
	  tWHILE tPO Condition tPF Instruction
	  		{ $$ = st_while($3, $5); };
If : 
	  tIF tPO Condition tPF Instruction
	  		{ $$ = st_if($3, $5); };
Condition : 
	  Expr
	  		{ $$ = $1; };
Ret :
	tRETURN Expr tPTVIR
			{ $$ = st_return($2); };



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
	//st_compute(0);
	return 0;
}

