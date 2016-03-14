#ifndef ST_H
#define ST_H




#define ST_UNDEFINED 0



typedef void* st_Node_t;



/* NOEUDS */
// cree un node de l'arbre syntaxique
void st_root(st_Node_t node, st_Node_t next);
st_Node_t st_function(st_Node_t prototype, st_Node_t bloc);
st_Node_t st_prototype(st_Node_t type, st_Node_t id, st_Node_t params);
st_Node_t st_params(st_Node_t param, st_Node_t next);
st_Node_t st_param(st_Node_t type, st_Node_t id);
st_Node_t st_bloc(st_Node_t head, st_Node_t belly, st_Node_t foot);
st_Node_t st_bodyHead(st_Node_t inst, st_Node_t next);
st_Node_t st_bodyBelly(st_Node_t inst, st_Node_t next);
st_Node_t st_declVar(st_Node_t type, st_Node_t vars);
st_Node_t st_declVar2(st_Node_t var, st_Node_t next);
st_Node_t st_declVarVar(st_Node_t id, st_Node_t value);
st_Node_t st_exAdd(st_Node_t exp1, st_Node_t exp2);
st_Node_t st_exSub(st_Node_t exp1, st_Node_t exp2);
st_Node_t st_exMul(st_Node_t exp1, st_Node_t exp2);
st_Node_t st_exDiv(st_Node_t exp1, st_Node_t exp2);
st_Node_t st_exOr(st_Node_t exp1, st_Node_t exp2);
st_Node_t st_exAnd(st_Node_t exp1, st_Node_t exp2);
st_Node_t st_exInf(st_Node_t exp1, st_Node_t exp2);
st_Node_t st_exInfEq(st_Node_t exp1, st_Node_t exp2);
st_Node_t st_exSup(st_Node_t exp1, st_Node_t exp2);
st_Node_t st_exSupEq(st_Node_t exp1, st_Node_t exp2);
st_Node_t st_exDiff(st_Node_t exp1, st_Node_t exp2);
st_Node_t st_exEqu(st_Node_t exp1, st_Node_t exp2);
st_Node_t st_exAffect(st_Node_t id, st_Node_t value);
st_Node_t st_fctCall(st_Node_t id, st_Node_t params);
st_Node_t st_callParams(st_Node_t param, st_Node_t next);
st_Node_t st_while(st_Node_t cond, st_Node_t body);
st_Node_t st_if(st_Node_t cond, st_Node_t body);
st_Node_t st_return(st_Node_t expr);


/* FEUILLES */
// cree une feuille de l'arbre syntaxique
st_Node_t st_type(int type, int flags);
st_Node_t st_id(char* id);
st_Node_t st_exNb(int value);




/* LECTURE */
// lit l'arbre syntaxique et le compile
int st_compute(st_Node_t node);



#endif // ST_H
