#ifndef AST_H
#define AST_H



/* NOEUDS */
// cree un node de l'arbre syntaxique
int st_root(int id1, int id2);
int st_function(int id1, int id2);
int st_prototype(int id1, int id2, int id3);
int st_params(int id1, int id2);
int st_param(int id1, int id2);
int st_bloc(int id1, int id2, int id3);
int st_bodyHead(int id1, int id2);
int st_bodyBelly(int id1, int id2);
int st_declVar(int id1, int id2);
int st_declVar2(int id1, int id2);
int st_declVarVar(int id1, int id2);
int st_exAdd(int id1, int id2);
int st_exSub(int id1, int id2);
int st_exMul(int id1, int id2);
int st_exDiv(int id1, int id2);
int st_exAffect(int id1, int id2);
int st_while(int id1, int id2);
int st_if(int id1, int id2);
int st_return(int id);


/* FEUILLES */
// cree une feuille de l'arbre syntaxique
int st_leaf(ast_NodeType nodeType, char* content);
int st_type(int type, int flags);
int st_id(char* id);
int st_exNb(int val);




/* LECTURE */
// lit l'arbre syntaxique et le compile
void st_compute();



#endif // AST_H
