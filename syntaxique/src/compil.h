#ifndef COMPIL_H
#define COMPIL_H



void c_progBegin(); // empiler @retour 0, et appel de main

void c_fctBegin(); // tout empiler
void c_fctEnd(); // tout depiler
void c_return();

void c_putLabel(char* label);
void c_linkToLabel(char* label);

void c_openBloc(); // maj table des symboles
void c_closeBloc(); // maj table des symboles

void c_fctCall();

void c_ldrVal(int val); // ldr d'une valeur constante
void c_ldrVar(char* var); // ldr d'une variable
void c_strVal(char* var); // str d'une valeur

void c_mov(); // deplace une valeur déjà loadé
void c_add(); // additions de variables déjà loadées
void c_sub(); // soustraction de variables déjà loadées
void c_mul(); // multiplication de variables déjà loadées
void c_div(); // division de variables déjà loadées








#endif // COMPIL_H
