%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"

%}

NB 		[0-9]+
TEXT 	[a-zA-Z_][a-zA-Z0-9_]*
EXP		[0-9]+[eE][+-]?[0-9]+

%%
"("		return tPO;
")"		return tPF;
"{"		return tAO;
"}"		return tAF;
"+"		return tPLUS;
"-"		return tMOINS;
"*"		return tMUL;
"/"		return tDIV;
"="		return tEQ;
","		return tVIR;
";"		return tPTVIR;
" "		;
[\t]	;
[\n]	;
"int"	return tINT;
"const"	return tCONST;
"print"	return tPRINT;
"return" return tRETURN;
"if"	return tIF;
"while"	return tWHILE;
{TEXT}	{
			yylval.string = strdup(yytext);
			return tID;
		}
{NB}	{
			yylval.integer = atoi(yytext);
			return tNB;
		}
{EXP}	{
			yylval.exp = atof(yytext);
			return tNBEXP;
		}
. ;



