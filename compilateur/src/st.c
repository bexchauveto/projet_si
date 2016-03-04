#include <stdlib.h>

#include "st.h"



//###################################################
//  TYPES DE NODES
//###################################################

typedef enum {
	NT_ROOT,
	NT_FUNCTION,
	NT_PROTOTYPE,
	NT_PARAMS,
	NT_PARAM,
	NT_BLOC,
	NT_BODYHEAD,
	NT_BODYBELLY,
	NT_DECLVAR,
	NT_DECLVAR2,
	NT_DECLVARVAR,
	NT_EXADD,
	NT_EXSUB,
	NT_EXMUL,
	NT_EXDIV,
	NT_EXOR,
	NT_EXAND,
	NT_EXAFFECT,
	NT_FCTCALL,
	NT_CALLPARAMS,
	NT_WHILE,
	NT_IF,
	NT_RETURN,
	NT_TYPE,
	NT_ID,
	NT_EXNB
} NodeType;




//###################################################
//  DECLARATIONS LOCALES
//###################################################


typedef struct {
	NodeType type;
} AbstractNode;

typedef struct {
	AbstractNode _;
	int value;
} LeafNb;

typedef struct {
	AbstractNode _;
	char* id;
} LeafID;

typedef struct {
	AbstractNode _;
	int type;
	int flags;
} LeafType;

typedef struct {
	AbstractNode _;
	st_Node_t children[3];
} Node;




st_Node_t treeRoot = 0;










st_Node_t createAN(NodeType type, st_Node_t handler)
{
	AbstractNode* node = (AbstractNode*) handler;
	node->type = type;
	return node;
}

NodeType getNodeType(st_Node_t handler)
{
	AbstractNode* node = (AbstractNode*) handler;
	return node->type;
}





//******** Node
st_Node_t createNode(NodeType type, st_Node_t* children)
{
	Node* node = malloc(sizeof(Node));
	for(int i=0; i<3; i++)
		node->children[i] = children[i];
	return createAN(type, node);
}

void freeNode(st_Node_t handler)
{
	Node* node = (Node*) handler;
	for(int i=0; i<3; i++)
		free(node->children[i]);
	free(node);
}

//******** Nb
st_Node_t createNb(int value)
{
	LeafNb* node = malloc(sizeof(LeafNb));
	node->value = value;
	return createAN(NT_EXNB, node);
}

void freeNb(st_Node_t handler)
{
	LeafNb* node = (LeafNb*) handler;
	free(node);
}

//******** Type
st_Node_t createType(int type, int flags)
{
	LeafType* node = malloc(sizeof(LeafType));
	node->type = type;
	node->flags = flags;
	return createAN(NT_TYPE, node);
}

void freeType(st_Node_t handler)
{
	LeafType* node = (LeafType*) handler;
	free(node);
}

//******** ID
st_Node_t createID(char* id)
{
	LeafID* node = malloc(sizeof(LeafID));
	node->id = id;
	return createAN(NT_ID, node);
}

void freeID(st_Node_t handler)
{
	LeafID* node = (LeafID*) handler;
	free(node->id);
	free(node);
}




//###################################################
//  DEFINITION DES FONCTIONS
//###################################################

void st_compute()
{
	
}







/* --- Noeuds --- */
void st_root(st_Node_t node, st_Node_t next)
{
	st_Node_t children[] = {node, next, 0};
	treeRoot = createNode(NT_ROOT, children);
}

st_Node_t st_function(st_Node_t prototype, st_Node_t bloc)
{
	st_Node_t children[] = {prototype, bloc, 0};
	return createNode(NT_FUNCTION, children);
}

st_Node_t st_prototype(st_Node_t type, st_Node_t id, st_Node_t params)
{
	st_Node_t children[] = {type, id, params};
	return createNode(NT_PROTOTYPE, children);
}

st_Node_t st_params(st_Node_t param, st_Node_t next)
{
	st_Node_t children[] = {param, next, 0};
	return createNode(NT_PARAMS, children);
}

st_Node_t st_param(st_Node_t type, st_Node_t id)
{
	st_Node_t children[] = {type, id, 0};
	return createNode(NT_PARAM, children);
}

st_Node_t st_bloc(st_Node_t head, st_Node_t belly, st_Node_t foot)
{
	st_Node_t children[] = {head, belly, foot};
	return createNode(NT_BLOC, children);
}

st_Node_t st_bodyHead(st_Node_t inst, st_Node_t next)
{
	st_Node_t children[] = {inst, next, 0};
	return createNode(NT_BODYHEAD, children);
}

st_Node_t st_bodyBelly(st_Node_t inst, st_Node_t next)
{
	st_Node_t children[] = {inst, next, 0};
	return createNode(NT_BODYBELLY, children);
}

st_Node_t st_declVar(st_Node_t type, st_Node_t vars)
{
	st_Node_t children[] = {type, vars, 0};
	return createNode(NT_DECLVAR, children);
}

st_Node_t st_declVar2(st_Node_t var, st_Node_t next)
{
	st_Node_t children[] = {var, next, 0};
	return createNode(NT_DECLVAR2, children);
}

st_Node_t st_declVarVar(st_Node_t id, st_Node_t value)
{
	st_Node_t children[] = {id, value, 0};
	return createNode(NT_DECLVARVAR, children);
}

st_Node_t st_exAdd(st_Node_t exp1, st_Node_t exp2)
{
	st_Node_t children[] = {exp1, exp2, 0};
	return createNode(NT_EXADD, children);
}

st_Node_t st_exSub(st_Node_t exp1, st_Node_t exp2)
{
	st_Node_t children[] = {exp1, exp2, 0};
	return createNode(NT_EXSUB, children);
}

st_Node_t st_exMul(st_Node_t exp1, st_Node_t exp2)
{
	st_Node_t children[] = {exp1, exp2, 0};
	return createNode(NT_EXMUL, children);
}

st_Node_t st_exDiv(st_Node_t exp1, st_Node_t exp2)
{
	st_Node_t children[] = {exp1, exp2, 0};
	return createNode(NT_EXDIV, children);
}

st_Node_t st_exOr(st_Node_t exp1, st_Node_t exp2)
{
	st_Node_t children[] = {exp1, exp2, 0};
	return createNode(NT_EXOR, children);
}

st_Node_t st_exAnd(st_Node_t exp1, st_Node_t exp2)
{
	st_Node_t children[] = {exp1, exp2, 0};
	return createNode(NT_EXAND, children);
}

st_Node_t st_exAffect(st_Node_t id, st_Node_t value)
{
	st_Node_t children[] = {id, value, 0};
	return createNode(NT_EXAFFECT, children);
}

st_Node_t st_fctCall(st_Node_t id, st_Node_t params)
{
	st_Node_t children[] = {id, params, 0};
	return createNode(NT_FCTCALL, children);
}

st_Node_t st_callParams(st_Node_t param, st_Node_t next)
{
	st_Node_t children[] = {param, next, 0};
	return createNode(NT_CALLPARAMS, children);
}

st_Node_t st_while(st_Node_t cond, st_Node_t body)
{
	st_Node_t children[] = {cond, body, 0};
	return createNode(NT_WHILE, children);
}

st_Node_t st_if(st_Node_t cond, st_Node_t body)
{
	st_Node_t children[] = {cond, body, 0};
	return createNode(NT_IF, children);
}

st_Node_t st_return(st_Node_t expr)
{
	st_Node_t children[] = {expr, 0, 0};
	return createNode(NT_RETURN, children);
}

/* --- Feuilles --- */
st_Node_t st_type(int type, int flags)
{
	return createType(type,flags);
}

st_Node_t st_id(char* id)
{
	return createID(id);
}

st_Node_t st_exNb(int val)
{
	return createNb(val);
}








