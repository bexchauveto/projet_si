%{
#include<stdio.h>	
%}

%token tPO, tPA, tAO, tAF, tPLUS, tMOINS, tMUL, tDIV, tEQ, tVIR, tMAIN, tINT, tCONST, tPRINT, tID, tNB, tNBEXP;

%%




%%

int yyerror(char* s)
{
	printf("%s\n", s);
}

int main(void)
{
	yyparse();
}