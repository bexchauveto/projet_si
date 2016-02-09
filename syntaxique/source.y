%{

#include <stdio.h>
#include <stdlib.h>	
%}

%token tPO tPF tAO tAF tPLUS tMOINS tMUL tDIV tEQ tVIR tMAIN tINT tCONST tPRINT tID tNB tNBEXP tRETURN
%start Prg

%%

/* ---- DEFINITION DU FICHIER ---- */
Prg : Fct Prg
	| Fct ;

/* ---- DEFINITION UTILES ---- */
Type : tINT;

/* ---- DEFINITION DES FONCTIONS ---- */
Fct : DeclFct ABody;
DeclFct : Type tID tPO Params tPF;
Params : Type tID SuiteParams | ;
SuiteParams : tVIR Type tID SuiteParams | ;

/* ---- DEFINITION DES BLOCS ---- */
ABody : tAO Body tAF;
Body : BodyHead BodyBelly BodyFoot
BodyHead : DeclVar BodyHead | ;
BodyBelly : ExpAr ABody
//	| While ABody
//	| If ABody
//	| AppelFct BodyBelly
	| ABody
//	| Print ABody;
BodyFoot : Ret | ;

/* ---- DEFINITION DES INSTRUCTIONS ---- */
DeclVar : Type tID SuiteDeclVar
	| Type tID
	| Type tID tEQ ExpAr SuiteDeclVar;
SuiteDeclVar : tVIR tID SuiteDeclVar
	| tVIR tID tEQ ExpAr SuiteDeclVar
	| ;
ExpAr : ExpAr tPLUS ExpAr
	| ExpAr tMOINS ExpAr 
	| ExpAr tMUL ExpAr
	| ExpAr tDIV ExpAr
	| tNB 
	| tNBEXP
	| tID ;
//While : t
Ret : tRETURN ExpAr;
%%

int yyerror(char* s)
{
	printf("%s\n", s);
}

int main(void)
{
	yyparse();
	return 0;
}
