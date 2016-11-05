%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"
#include "error.h"

%}

%option yylineno

NB 		[0-9]+
TEXT 	[a-zA-Z_][a-zA-Z0-9_]*
EXP		[0-9]+[eE][+-]?[0-9]+
COMM	"/*"([^*]|(\*[^/]))*\**"/"
COM_LINE "//"[^\n]*


%%
"("		return tPO;
")"		return tPF;
"{"		return tAO;
"}"		return tAF;
"["		return tCO;
"]"		return tCF;
"+"		return tPLUS;
"-"		return tMOINS;
"*"		return tMUL;
"/"		return tDIV;
"="		return tEQ;
"!"		return tNOT;
"&"		return tREF;
","		return tVIR;
";"		return tPTVIR;
">"		return tSUP;
"<"		return tINF;
">="	return tSUPEQ;
"<="	return tINFEQ;
"!="	return tDIFF;
"=="	return tEQU;
"&&"	return tAND;
"||"	return tOR;
" "		;
[\t]	;
[\n]	err_newLine();
"int"	return tINT;
"const"	return tCONST;
"return" return tRETURN;
"if"	return tIF;
"else"	return tELSE;
"while"	return tWHILE;
{TEXT}	{
			char* p = malloc(strlen(yytext)+1);
			yylval.string = p? strcpy(p,yytext) : 0;
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
{COMM}	;
{COM_LINE} ;
. ;



