%{

#include <stdio.h>
#include <stdlib.h>

#include "compil.h"

int yylex();
int yyerror(char *s);	



%}

%token tPO tPF tAO tAF tPLUS tMOINS tMUL tDIV tEQ tVIR tINT tCONST tPRINT tID tNB tNBEXP tRETURN tPTVIR tIF tWHILE

%start Prg

%right tEQ
%left tPLUS tMOINS
%left tMUL tDIV


%%

/* ---- DEFINITION DU FICHIER ---- */
Prg : // !! lancer c_progBegin()
	  Fct Prg
	| ;

/* ---- DEFINITION DES FONCTIONS ---- */
Fct : 
	  Prototype Bloc { c_fctEnd(); };
Prototype : 
	  tINT tID tPO Params tPF { /* table des fonctions && label */ } ;
Params : 
	  DeclParam
	| ;
DeclParam :
	  tINT tID;
SuiteParams :
	  tVIR DeclParam SuiteParams
	| ;

/* ---- DEFINITION DES BLOCS ---- */
Bloc : 
	  tAO      { c_openbloc(); }
	  Body tAF { c_closebloc(); };
Body : 
	  BodyHead BodyBelly BodyFoot;
BodyHead : 
	  DeclVar BodyHead
	| ;
BodyBelly : 
	  Instruction BodyBelly
	| ;
BodyFoot :
	  Ret
	| ;

/* ---- DEFINITION DES DECLARATIONS ---- */
DeclVar : 
	  tINT tID SuiteDeclVar
	| tINT tID
//	| tINT tID tEQ Expr SuiteDeclVar;
SuiteDeclVar : 
	  tVIR tID SuiteDeclVar
//	| tVIR tID tEQ Expr SuiteDeclVar
	| ;

/* ---- DEFINITION DES INSTRUCTIONS ---- */
Instruction :
	  Expr tPTVIR
	| Bloc
	| While
	| If;
Expr : 
	  Expr tPLUS { c_mov(); }
	  		Expr { c_add(); }
	| Expr tMOINS { c_mov(); }
			Expr { c_sub(); }
	| Expr tMUL { c_mov(); }
			Expr { c_mul(); }
	| Expr tDIV { c_mov(); }
			Expr { c_div(); }
	| tID tEQ Expr { /* c_strVal(???); */ }
	| AppelFct { /* c_fctCall(???); */ }
	| tNB { /* c_ldrVal(???); */ }
	| tNBEXP { /* c_ldrVal(???); */ }
	| tID { /* c_ldrVar(???); */ };
While : 
	  tWHILE tPO Condition tPF Instruction;
If : 
	  tIF tPO Condition tPF Instruction;
Condition : 
	  Expr;
Ret : tRETURN Expr { c_return() };



%%

int yyerror(char* s)
{
	printf("%s\n", s);
}

#if YY_MAIN
int main(void)
{
	yyparse();
	return 0;
}
#endif
