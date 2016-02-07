%{

#include<stdio.h>

%}

NB 		[0-9]+
TEXT 	[a-zA-Z_][a-zA-Z0-9_]*
EXP		[0-9]+[eE][+-]?[0-9]+

%%
"(" {printf("tPO ");}
")" {printf("tPF ");}
"{" {printf("tAO ");}
"}" {printf("tAF ");}
"+" {printf("tPLUS ");}
"-" {printf("tMOINS ");}
"*" {printf("tMUL ");}
"/" {printf("tDIV ");}
"=" {printf("tEQ ");}
" " ;
[ \t] ;
[ ,] {printf("tVIR ");}
[ \n] ;
"main" {printf("tMAIN ");}
"int" {printf("tINT ");}
"const" {printf("tCONST ");}
"print" {printf("tPRINT ");}
"return" {printf("tReturn");}
{TEXT} {printf("tID ");}
{NB} {printf("tNB ");}
{EXP} {printf("tNBEXP ");}
. ;


%%


void main()
{
	yylex();

}
