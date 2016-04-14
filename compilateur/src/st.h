#ifndef ST_H
#define ST_H



//###################################################
//  TYPES DE NODES
//###################################################

typedef enum {
	NT_ROOT = 1, // : node, next
	NT_FUNCTION, // : prototype, bloc
	NT_PROTOTYPE, // : type, id, params
	NT_PARAMS, // : param, next
	NT_PARAM, // : type, id, arraySize
	NT_BLOC, // : belly, foot
	NT_BODY, // : instruction, next
	NT_DECLVAR, // : type, vars
	NT_DECLVAR2, // : var, next
	NT_DECLVARVAR, // : id, value, arraySize
	NT_EXADD, // : exp1, exp2
	NT_EXSUB, // : exp1, exp2
	NT_EXMUL, // : exp1, exp2
	NT_EXDIV, // : exp1, exp2
	NT_EXOR, // : exp1, exp2
	NT_EXAND, // : exp1, exp2
	NT_EXINF, // : exp1, exp2
	NT_EXINFEQ, // : exp1, exp2
	NT_EXSUP, // : exp1, exp2
	NT_EXSUPEQ, // : exp1, exp2
	NT_EXDIFF, // : exp1, exp2
	NT_EXEQU, // : exp1, exp2
	NT_EXTAB, // : exp1, exp2
	NT_EXNOT, // : exp
	NT_EXDEREF, // : exp
	NT_EXREF, // : id
	NT_EXAFFECT, // : id, value
	NT_FCTCALL, // : id, params
	NT_CALLPARAMS, // : param, next
	NT_WHILE, // : condition, instruction
	NT_IF, // : condition, instruction, else
	NT_RETURN, // : exp
	NT_TYPE,
	NT_ID,
	NT_EXNB
} st_NodeType;


#define ST_UNDEFINED 0







typedef void* st_Node_t;



/* NOEUDS */
// cree un node de l'arbre syntaxique
st_Node_t st_createNode(st_NodeType type, st_Node_t n1, st_Node_t n2, st_Node_t n3);
#define st_node__(type, n1, n2, n3, ...) st_createNode(type, n1, n2, n3)
#define st_node(type, ...) st_node__(type, __VA_ARGS__ , 0, 0, 0, 0, 0)



/* FEUILLES */
// cree une feuille de l'arbre syntaxique
st_Node_t st_type(int type, int flags, int nbPtr);
st_Node_t st_id(char* id, int line);
st_Node_t st_exNb(int value);




/* AUTRES */
// lit l'arbre syntaxique et le compile
void st_compute(st_Node_t node);

void st_printTree(st_Node_t node, int indent);



#endif // ST_H


