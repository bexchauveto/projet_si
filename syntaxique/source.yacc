%{
#include<stdio.h>	
%}

%token tPO tPF tAO tAF tPLUS tMOINS tMUL tDIV tEQ tVIR tMAIN tINT tCONST tPRINT tID tNB tNBEXP tRETURN
%start Prg
%%
Prg : Fct Prg
	| ;
Fct : DeclFct ABody;
DeclFct : tINT tID tPO Params tPF;
Params : tINT tID SuiteParams | ;
SuiteParams : tVIR tINT tID SuiteParams | ;
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
DeclVar : tINT tID SuiteDeclVar
	| tINT tID
	| tINT tID tEQ ExpAr SuiteDeclVar;
SuiteDeclVar : tVIR tID SuiteDeclVar
	| tVIR tID tEQ ExpAr SuiteDeclVar
	| ;
ExpAr : ExpAr tPLUS ExpAr
	| ExpAr tMOINS ExpAr
	| ExpAr tMUL ExpAr
	| ExpAr tDIV ExpAr
	| tNB
	| tNBEXP
	| tID;
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
}