%{

#include <stdio.h>
#include <stdlib.h>

#include "st.h"

int yylex();
int yyerror(char *s);	



%}

%token tPO tPF tAO tAF tPLUS tMOINS tMUL tDIV tEQ tVIR tINT tCONST tPRINT tRETURN tPTVIR tIF tWHILE

%union 
{
        int integer;
        float exp;
        char *string;
}
%token <integer> tNB
%token <real> tNBEXP
%token <string> tID




%start Prg

%right tEQ
%left tPLUS tMOINS
%left tMUL tDIV

/*

TODO:
- mot clé const
- opperateurs && ||
- affectation lors de la declaration

*/








%%

/* ---- DEFINITION DU FICHIER ---- */
Prg :
	  Fct Prg
	  		{ $$ = st_root($1, $2); }
	| 		{ $$=0; };

/* ---- DEFINITION DES FONCTIONS ---- */
Fct : 
	  Prototype Bloc 
	  		{ $$ = st_function($1, $2) };
Prototype : 
	  tINT tID tPO Params tPF 
	  		{
	  			int type = st_type(0, 0);
	  			int id = st_id($2);
	  			$$ = st_prototype(type, id, $4);
			} ;
Params : 
	  DeclParam SuiteParams
	  		{ $$=st_params($1, $2); }
	| 		{ $$=0; };
DeclParam :
	  tINT tID 
	  		{
	  			int type = st_type(0, 0);
	  			int id = st_id($2);
	  			$$ = st_param(type, id);
			};
SuiteParams :
	  tVIR DeclParam SuiteParams
	  		{ $$ = st_params($2, $3); }
	| 		{ $$=0; };

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
	| 		{ $$=0; };
BodyBelly : 
	  Instruction BodyBelly
	  		{ $$ = st_bodyBelly($1, $2); }
	| ;
BodyFoot :
	  Ret	{ $$ = $1; }
	| 		{ $$=0; };

/* ---- DEFINITION DES DECLARATIONS ---- */
DeclVar : 
	  tINT tID SuiteDeclVar
	  		{
	  			int type = st_type(0,0);
	  			int id = st_id($2);
	  			int v = st_declVarVar(id, 0);
	  			int d2 = st_declVar2(v, $3);
	  			$$ = st_declVar(type, d2);
	  		}
	| tINT tID
//	| tINT tID tEQ Expr SuiteDeclVar;
SuiteDeclVar : 
	  tVIR tID SuiteDeclVar
	  		{
	  			int id = st_id($2);
	  			int v = st_declVarVar(id, 0);
	  			$$ = st_declVar2(v, $3);
			}
//	| tVIR tID tEQ Expr SuiteDeclVar
	| ;

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
	  		{ $$ = $2 }
	| Expr tPLUS Expr
	  		{ $$ = st_exAdd($1, $3); }
	| Expr tMOINS Expr
	  		{ $$ = st_exSub($1, $3); }
	| Expr tMUL Expr
	  		{ $$ = st_exMul($1, $3); }
	| Expr tDIV Expr
	  		{ $$ = st_exDiv($1, $3); }
	| tID tEQ Expr
	  		{
	  			int id = st_id($1);
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
	  			int id = st_id($1);
	  			$$ = st_fctCall(id, $3);
			};
AppelParams : 
	  Expr SuiteAppelParams
	  		{ $$ = st_callParams($1, $2); }
	| 		{ $$=0; };
SuiteAppelParams : 
	  tVIR Expr SuiteAppelParams
	  		{ $$ = st_callParams($2, $3); }
	| 		{ $$=0; };
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
	tRETURN Expr
			{ $$ = st_return($2); };



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
