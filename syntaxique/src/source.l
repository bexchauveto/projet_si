%{

#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"

%}

NB 		[0-9]+
TEXT 	[a-zA-Z_][a-zA-Z0-9_]*
EXP		[0-9]+[eE][+-]?[0-9]+

%%
"(" {printf("tPO"); return tPO;}
")" {printf("tPF"); return tPF;}
"{" {printf("tAO"); return tAO;}
"}" {printf("tAF"); return tAF;}
"+" {printf("tPLUS"); return tPLUS;}
"-" {printf("tMOINS"); return tMOINS;}
"*" {printf("tMUL"); return tMUL;}
"/" {printf("tDIV"); return tDIV;}
"=" {printf("tEQ"); return tEQ;}
" " ;
[ \t] ;
[ ,] {printf("tVIR"); return tVIR;}
[ \n] ;
"main" {printf("tMAIN"); return tMAIN;}
"int" {printf("tINT"); return tINT;}
"const" {printf("tCONST"); return tCONST;}
"print" {printf("tPRINT"); return tPRINT;}
"return" {printf("tRETURN"); return tRETURN;}
{TEXT} {printf("tID"); return tID;}
{NB} {printf("tNB"); return tNB;}
{EXP} {printf("tNBEXP"); return tNBEXP;}
. ;


%%


void main()
{
	yylex();

}