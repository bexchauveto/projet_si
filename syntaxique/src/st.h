#ifndef AST_H
#define AST_H



/* NOEUDS */
// cree un node de l'arbre syntaxique
int st_root(int node, int next);
int st_function(int prototype, int bloc);
int st_prototype(int type, int id, int params);
int st_params(int param, int next);
int st_param(int type, int id);
int st_bloc(int head, int belly, int foot);
int st_bodyHead(int inst, int next);
int st_bodyBelly(int inst, int next);
int st_declVar(int type, int vars);
int st_declVar2(int var, int next);
int st_declVarVar(int id, int value);
int st_exAdd(int exp1, int exp2);
int st_exSub(int exp1, int exp2);
int st_exMul(int exp1, int exp2);
int st_exDiv(int exp1, int exp2);
int st_exAffect(int id, int value);
int st_fctCall(int id, int params);
int st_callParams(int param, int next);
int st_while(int cond, int body);
int st_if(int cond, int body);
int st_return(int expr);


/* FEUILLES */
// cree une feuille de l'arbre syntaxique
int st_leaf(ast_NodeType nodeType, char* content);
int st_type(int type, int flags);
int st_id(char* id);
int st_exNb(int value);




/* LECTURE */
// lit l'arbre syntaxique et le compile
void st_compute();



#endif // AST_H
