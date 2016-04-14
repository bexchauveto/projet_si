#include "st.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "ass.h"
#include "function_table.h"
#include "label_table.h"
#include "symbole_table.h"




//###################################################
//  DECLARATIONS LOCALES
//###################################################


typedef struct {
	st_NodeType type;
} AbstractNode;

typedef struct {
	AbstractNode _;
	int value;
} LeafNb;

typedef struct {
	AbstractNode _;
	char* id;
	int line;
} LeafID;

typedef struct {
	AbstractNode _;
	int type;
	int flags;
	int nbPtr;
} LeafType;

#define NB_CHILDREN_MAX 3
typedef struct {
	AbstractNode _;
	st_Node_t children[NB_CHILDREN_MAX];
} Node;



static int firstCompute = 1;
static st_Node_t treeRoot = ST_UNDEFINED;
static int labelNumber = 0;








//******** AbstractNode
st_Node_t createAN(st_NodeType type, st_Node_t handler)
{
	AbstractNode* node = (AbstractNode*) handler;
	node->type = type;
	return node;
}

st_NodeType getNodeType(st_Node_t handler)
{
	AbstractNode* node = (AbstractNode*) handler;
	return node->type;
}

int isNodeExpression2Op(st_Node_t node)
{
	st_NodeType type = getNodeType(node);
	return type >= NT_EXADD && type <= NT_EXTAB;
}

int isNodeExpression1Op(st_Node_t node)
{
	st_NodeType type = getNodeType(node);
	return type >= NT_EXNOT && type <= NT_EXNOT;
}

//******** Nb
st_Node_t createNb(int value)
{
	LeafNb* node = malloc(sizeof(LeafNb));
	if(!node) return node;
	node->value = value;
	return createAN(NT_EXNB, node);
}

int nb_getValue(st_Node_t node)
{
	LeafNb* nb = (LeafNb*) node;
	return nb->value;
}

void freeNb(st_Node_t handler)
{
	LeafNb* node = (LeafNb*) handler;
	free(node);
}

//******** Type
st_Node_t createType(int type, int flags, int nbPtr)
{
	LeafType* node = malloc(sizeof(LeafType));
	if(!node) return node;
	node->type = type;
	node->flags = flags;
	node->nbPtr = nbPtr;
	return createAN(NT_TYPE, node);
}

void freeType(st_Node_t handler)
{
	free(handler);
}

//******** ID
st_Node_t createID(char* id, int line)
{
	LeafID* node = malloc(sizeof(LeafID));
	if(!node) return node;
	node->id = id;
	node->line = line;
	return createAN(NT_ID, node);
}

char* id_getName(st_Node_t node)
{
	LeafID* id = (LeafID*) node;
	return id->id;
}

int id_getLine(st_Node_t node)
{
	LeafID* id = (LeafID*) node;
	return id->line;
}

void freeID(st_Node_t handler)
{
	LeafID* node = (LeafID*) handler;
	free(node->id);
	free(node);
}

//******** Node
st_Node_t createNode(st_NodeType type, st_Node_t* children)
{
	Node* node = malloc(sizeof(Node));
	if(!node) return node;
	for(int i=0; i<NB_CHILDREN_MAX; i++)
		node->children[i] = children[i];
	return createAN(type, node);
}

st_Node_t node_getChild(st_Node_t node, int numChild)
{
	Node* father = (Node*) node;
	return father->children[numChild];
}

void node_setChild(st_Node_t node, int numChild, st_Node_t child)
{
	Node* father = (Node*) node;
	father->children[numChild] = child;
}

void freeNode(st_Node_t handler)
{
	free(handler);
}

void freeNodeAll(st_Node_t handler)
{
	for(int i=0; i<NB_CHILDREN_MAX; i++)
	{
		if(!node_getChild(handler,i))
			continue;
		switch(getNodeType(node_getChild(handler,i)))
		{
			case NT_EXNB:
				freeNb(node_getChild(handler,i));
				break;
			case NT_TYPE:
				freeType(node_getChild(handler,i));
				break;
			case NT_ID:
				freeID(node_getChild(handler,i));
				break;
			default:
				freeNodeAll(node_getChild(handler,i));
				break;
		}
	}
	free(handler);
}






void st_init()
{
	// Create tables
	funT_createTable();
	symboleT_createTable();
	labelT_createTable();
	
	// Create language defined functions
	funT_addFunctionToTable("print");
	funT_addParamToFunction("print", "");
	
	// Begin program
	ass_progBegin();
}

void st_free()
{
	ass_progEnd();
}





//###################################################
//  LECTURE DE L'ARBRE
//###################################################
void st_computeExpression(st_Node_t node, int destination);
void st_computeFctCall(st_Node_t node);
void st_computeFunction(st_Node_t node);
void st_computeDeclVar(st_Node_t node);


void st_computeExpression(st_Node_t node, int destination)
{
	if(node == ST_UNDEFINED)
		return;
	
	if(isNodeExpression2Op(node))
	{
		// Compute operands
		st_NodeType nodeType = getNodeType(node_getChild(node,0));
		st_computeExpression(node_getChild(node,1), 1);
		if(nodeType != NT_ID && nodeType != NT_EXNB && nodeType != NT_EXREF)
			ass_pushResult();
		st_computeExpression(node_getChild(node,0), 0);
		if(nodeType != NT_ID && nodeType != NT_EXNB && nodeType != NT_EXREF)
			ass_popResult(1);
	}
	
	switch(getNodeType(node))
	{
		case NT_EXADD:
			ass_add();
			break;
		case NT_EXSUB:
			ass_sub();
			break;
		case NT_EXMUL:
			ass_mul();
			break;
		case NT_EXDIV:
			ass_div();
			break;
		case NT_EXOR:
			ass_or();
			break;
		case NT_EXAND:
			ass_and();
			break;
		case NT_EXINF:
			ass_inf();
			break;
		case NT_EXINFEQ:
			ass_sup();
			ass_not();
			break;
		case NT_EXSUP:
			ass_sup();
			break;
		case NT_EXSUPEQ:
			ass_inf();
			ass_not();
			break;
		case NT_EXDIFF:
			ass_equ();
			ass_not();
			break;
		case NT_EXEQU:
			ass_equ();
			break;
		case NT_EXTAB:
			ass_add();
			ass_deref();
			break;
		case NT_EXNOT:
			st_computeExpression(node_getChild(node,0), 0);
			ass_not();
			break;
		case NT_EXDEREF:
			st_computeExpression(node_getChild(node,0), 0);
			ass_deref();
			break;
		case NT_EXREF:
			ass_ref(id_getName(node_getChild(node,0)), destination); // error? (from ass.c)
			freeID(node_getChild(node,0));
			break;
		case NT_EXAFFECT:
			st_computeExpression(node_getChild(node,1), 0);
			ass_str(id_getName(node_getChild(node,0))); // error? (from ass.c)
			freeID(node_getChild(node,0));
			break;
		case NT_FCTCALL:
			st_computeFctCall(node);
			break;
		case NT_ID:
			ass_ldr(id_getName(node), destination); // error? (from ass.c)
			freeID(node);
			return;
		case NT_EXNB:
			ass_ld(nb_getValue(node), destination);
			freeNb(node);
			return;
		default:
			break; // error
	}
	freeNode(node);
}

void st_computeFctCall(st_Node_t node)
{
	Node* params = (Node*) node_getChild(node,1);
	
	// --- Compute function name
	char* fctName = id_getName(node_getChild(node,0));
	int fctLine = id_getLine(node_getChild(node,0));
	int nbParams = funT_getNbParamsByFunName(fctName);
	if(nbParams == -1)
	{
		errorSymbol(ERR_FATAL, "the function %s is undefined", fctName, fctLine);
	}
	
	// --- Compute params
	for(Node* param = params; param != ST_UNDEFINED;)
	{
		st_computeExpression(node_getChild(param,0), 0);
		node_setChild(param,0,ST_UNDEFINED);
		ass_fctCallParam();
		
		param = (Node*) node_getChild(param,1);
		nbParams--;
	}
	if(nbParams != 0)
		errorSymbol(ERR_FATAL, "wrong number of parameters for the function %s", fctName, fctLine);
	
	// --- Compute function call
	if(!strcmp(fctName, "print"))
	{
		ass_print();
	}
	else
	{
		ass_fctCallJmp(fctName);
		ass_fctCallEnd();
	}
	
	if(params != ST_UNDEFINED)
		freeNodeAll(params);
	freeID(node_getChild(node,0)); //id
}

void st_computeFunction(st_Node_t node) // et prototype
{
	// --- Compute prototype
	Node* prototype = (Node*) node_getChild(node,0);
	// ignore type
	// function name
	char* functionName = id_getName(node_getChild(prototype,1));
	funT_addFunctionToTable(functionName);
	// parameters
	int nbParams = 0;
	Node* params = (Node*) node_getChild(prototype,2);
	while(params != ST_UNDEFINED)
	{
		// --- Compute param
		nbParams++;
		Node* param = (Node*) node_getChild(params,0);
		char* paramName = id_getName(node_getChild(param,1));
		funT_addParamToFunction(functionName, paramName);
		
		params = (Node*) node_getChild(params,1);
	}
	
	// --- Compute corp
	if(node_getChild(node,1) != ST_UNDEFINED)
	{
		ass_fctBegin(functionName, nbParams);
		st_compute(node_getChild(node,1)); // bloc
		node_setChild(node,1,ST_UNDEFINED);
		ass_fctEnd(functionName);
	}
}

void st_computeDeclVar(st_Node_t node)
{
	// ignore type
	// --- Compute all IDs and values
	for(Node* declVar = (Node*) node_getChild(node,1); declVar != ST_UNDEFINED;)
	{
		Node* var = (Node*) node_getChild(declVar,0);
		// --- Compute value
		if(node_getChild(var,1) != ST_UNDEFINED)
		{
			st_computeExpression(node_getChild(var,1), 0);
			node_setChild(var,1,ST_UNDEFINED);
		}
		// --- Compute Arrays
		int arraySize = 1;
		if(node_getChild(var,2) != ST_UNDEFINED)
		{
			arraySize = nb_getValue(node_getChild(var,2));
		}
		
		// --- Compute ID
		char* varName = id_getName(node_getChild(var,0));
		ass_declVar(varName, arraySize);
		
		declVar = (Node*) node_getChild(declVar,1);
	}
}




void st_compute(st_Node_t node)
{
	if(firstCompute)
	{
		st_init();
		firstCompute = 0;
	}
	
	if(node == ST_UNDEFINED)
	{
		if(treeRoot == ST_UNDEFINED)
			return; // error
		node = treeRoot;
	}
	
	switch(getNodeType(node))
	{
		case NT_ROOT:
			for(Node* inst = (Node*) node; inst != ST_UNDEFINED;)
			{
				st_compute(node_getChild(inst,0)); // function
				node_setChild(inst,0,ST_UNDEFINED);
				inst = (Node*) node_getChild(inst,1);
			}
			freeNodeAll(node);
			st_free();
			break;
		case NT_FUNCTION:
			st_computeFunction(node);
			freeNodeAll(node);
			break;
		case NT_BLOC:
			ass_blocBegin();
			// --- Compute belly
			for(Node* inst = (Node*) node_getChild(node,0); inst != ST_UNDEFINED;)
			{
				if(node_getChild(inst,0) != ST_UNDEFINED)
					st_compute(node_getChild(inst,0)); // Instruction
				node_setChild(inst,0,ST_UNDEFINED);
				inst = (Node*) node_getChild(inst,1);
			}
			// --- Compute foot
			if(node_getChild(node,1) != ST_UNDEFINED)
			{
				st_compute(node_getChild(node,1)); // return
				node_setChild(node,1,ST_UNDEFINED);
			}
			ass_blocEnd();
			freeNodeAll(node);
			break;
		case NT_DECLVAR:
			st_computeDeclVar(node);
			freeNodeAll(node);
			break;
		case NT_WHILE:
			ass_whileBegin(labelNumber);
			st_computeExpression(node_getChild(node,0), 0);
			ass_whileDo(labelNumber);
			if(node_getChild(node,1) != ST_UNDEFINED)
				st_compute(node_getChild(node,1));
			ass_whileEnd(labelNumber);
			labelNumber++;
			freeNode(node);
			break;
		case NT_IF:
			ass_ifBegin(labelNumber);
			st_computeExpression(node_getChild(node,0), 0);
			ass_ifThen(labelNumber);
			if(node_getChild(node,1) != ST_UNDEFINED)
				st_compute(node_getChild(node,1));
			ass_ifElse(labelNumber);
			if(node_getChild(node,2) != ST_UNDEFINED)
				st_compute(node_getChild(node,2));
			ass_ifEnd(labelNumber);
			labelNumber++;
			freeNode(node);
			break;
		case NT_RETURN:
			st_computeExpression(node_getChild(node,0), 0);
			ass_return();
			freeNode(node);
			break;
		default:
			st_computeExpression(node, 0);
			break;
	}
}



void st_printTree(st_Node_t node, int indent)
{
	if(node == ST_UNDEFINED)
	{
		if(treeRoot == ST_UNDEFINED)
			printf("arbre vide :(\n");
		node = treeRoot;
	}
	
	for(int i=0; i<indent; i++)
		putchar(' ');
	
	switch(getNodeType(node))
	{
		case NT_TYPE:
			printf("type\n");
			break;
		case NT_ID:
			printf("ID\n");
			break;
		case NT_EXNB:
			printf("NB\n");
			break;
		default:
			printf("%d\n", getNodeType(node));
			for(int i=0; i<NB_CHILDREN_MAX; i++)
			{
				if(node_getChild(node,i) != ST_UNDEFINED)
					st_printTree(node_getChild(node,i), indent+3);
			}
			break;
	}
}






//###################################################
//  OPTIMISATION DE L'ARBRE
//###################################################

st_Node_t st_optimizeSimpleExpression(st_Node_t node)
{
	st_Node_t res;
	int op1, op2;
	
	if(getNodeType(node_getChild(node,0))!=NT_EXNB ||
	(isNodeExpression2Op(node) && getNodeType(node_getChild(node,1))!=NT_EXNB))
		return node;
	op1 = nb_getValue(node_getChild(node,0));
	if(isNodeExpression2Op(node))
		op2 = nb_getValue(node_getChild(node,1));
	
	switch(getNodeType(node))
	{
		case NT_EXADD:
			res = createNb(op1 + op2);
			break;
		case NT_EXMUL:
			res = createNb(op1 * op2);
			break;
		case NT_EXSUB:
			res = createNb(op1 - op2);
			break;
		case NT_EXDIV:
			res = createNb(op1 / op2);
			break;
		case NT_EXAND:
			res = createNb(op1 && op2);
			break;
		case NT_EXOR:
			res = createNb(op1 || op2);
			break;
		case NT_EXINF:
			res = createNb(op1 < op2);
			break;
		case NT_EXINFEQ:
			res = createNb(op1 <= op2);
			break;
		case NT_EXSUP:
			res = createNb(op1 > op2);
			break;
		case NT_EXSUPEQ:
			res = createNb(op1 >= op2);
			break;
		case NT_EXEQU:
			res = createNb(op1 == op2);
			break;
		case NT_EXDIFF:
			res = createNb(op1 != op2);
			break;
		case NT_EXNOT:
			res = createNb(!op1);
			break;
		default:
			return node;
	}
	freeNodeAll(node);
	return res;
}

st_Node_t st_optimizeInstruction(st_Node_t node)
{
	return node;
}

st_Node_t st_optimizeBloc(st_Node_t node)
{
	for(Node* inst = (Node*) node_getChild(node,0); inst != ST_UNDEFINED;)
	{
		st_Node_t newInst = st_optimizeInstruction(node_getChild(inst,0));
		node_setChild(inst,0,newInst);
		inst = (Node*) node_getChild(inst,1);
	}
	return node;
}

st_Node_t st_optimize(st_Node_t node)
{
	if(node == ST_UNDEFINED)
	{
		if(treeRoot == ST_UNDEFINED)
			return ST_UNDEFINED; // error
		node = treeRoot;
	}
	
	if(isNodeExpression2Op(node) || getNodeType(node)==NT_EXNOT)
		node = st_optimizeSimpleExpression(node);
	
	switch(getNodeType(node))
	{
		case NT_BLOC:
			node = st_optimizeBloc(node);
			break;
		default:
			break;
	}
	return node;
}





//###################################################
//  CONSTRUCTION DE L'ARBRE
//###################################################

/* --- Noeuds --- */
st_Node_t st_createNode(st_NodeType type, st_Node_t n1, st_Node_t n2, st_Node_t n3)
{
	st_Node_t children[] = {n1, n2, n3};
	st_Node_t node = createNode(type, children);
	node = st_optimize(node);
	if(type == NT_ROOT)
		treeRoot = node;
	return node;
}



/* --- Feuilles --- */
st_Node_t st_type(int type, int flags, int nbPtr)
{
	return createType(type,flags,nbPtr);
}

st_Node_t st_id(char* id, int line)
{
	return createID(id, line);
}

st_Node_t st_exNb(int val)
{
	return createNb(val);
}








