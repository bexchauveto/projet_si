#include "st.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
} LeafID;

typedef struct {
	AbstractNode _;
	int type;
	int flags;
} LeafType;

#define NB_CHILDREN_MAX 3
typedef struct {
	AbstractNode _;
	st_Node_t children[NB_CHILDREN_MAX];
} Node;



static int firstCompute = 1;
static st_Node_t treeRoot = ST_UNDEFINED;
static int labelNumber = 0;









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






//******** Nb
st_Node_t createNb(int value)
{
	LeafNb* node = malloc(sizeof(LeafNb));
	if(!node) return node;
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
	if(!node) return node;
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
	if(!node) return node;
	node->id = id;
	return createAN(NT_ID, node);
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

void freeNode(st_Node_t handler)
{
	Node* node = (Node*) handler;
	free(node);
}

void freeNodeAll(st_Node_t handler)
{
	Node* node = (Node*) handler;
	for(int i=0; i<NB_CHILDREN_MAX; i++)
	{
		if(!node->children[i])
			continue;
		switch(getNodeType(node->children[i]))
		{
			case NT_EXNB:
				freeNb(node->children[i]);
				break;
			case NT_TYPE:
				freeType(node->children[i]);
				break;
			case NT_ID:
				freeID(node->children[i]);
				break;
			default:
				freeNodeAll(node->children[i]);
				break;
		}
	}
	free(node);
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

void st_computeExpression(st_Node_t node, int destination)
{
	if(getNodeType(node) == NT_ID) {
		LeafID* id = (LeafID*) node;
		ass_ldr(id->id, destination);
		freeID(node);
	}
	else if(getNodeType(node) == NT_EXNB) {
		LeafNb* nb = (LeafNb*) node;
		ass_ld(nb->value, destination);
		freeNb(node);
	}
	else {
		Node* ex2 = (Node*) node;
		st_compute(ex2);
	}
}

void st_computeFunction(st_Node_t node) // et prototype
{
	Node* father = (Node*) node;
	Node* prototype = (Node*) father->children[0];
	Node* corp = (Node*) father->children[1];
	
	// --- Compute prototype
	// ignore type
	// function name
	LeafID* idFct = (LeafID*) prototype->children[1];
	char* functionName = idFct->id;
	funT_addFunctionToTable(functionName);
	// parameters
	int nbParams = 0;
	Node* params = (Node*) prototype->children[2];
	while(params != ST_UNDEFINED)
	{
		// --- Compute param
		nbParams++;
		Node* param = (Node*) params->children[0];
		LeafID* idParam = (LeafID*) param->children[1];
		char* paramName = idParam->id;
		funT_addParamToFunction(functionName, paramName);
		
		params = (Node*) params->children[1];
	}
	
	// --- Compute corp
	if(corp != ST_UNDEFINED)
	{
		ass_fctBegin(functionName, nbParams);
		st_compute(corp); // bloc
		ass_fctEnd(functionName);
	}
	
	freeNodeAll(prototype);
}

void st_computeBloc(st_Node_t node) // et assimiles
{
	Node* father = (Node*) node;
	Node* belly = (Node*) father->children[0];
	Node* foot  = (Node*) father->children[1];
	
	
	// --- Compute belly
	for(Node* inst = belly; inst != ST_UNDEFINED;)
	{
		st_compute(inst->children[0]); // Instruction
		Node* tmp = (Node*) inst->children[1];
		freeNode(inst);
		inst = tmp;
	}
	
	// --- Compute foot
	if(foot != ST_UNDEFINED)
	{
		st_compute(foot); // return
	}
}

void st_computeDeclVar(st_Node_t node)
{
	Node* father = (Node*) node;
	Node* type = (Node*) father->children[0];
	Node* ids  = (Node*) father->children[1];
	
	// --- Compute type
	freeType(type);
	
	// --- Compute all IDs and values
	for(Node* declVar = ids; declVar != ST_UNDEFINED;)
	{
		Node* var = (Node*) declVar->children[0];
		// --- Compute value
		Node* value = (Node*) var->children[1];
		if(value != ST_UNDEFINED)
			st_computeExpression(value, 0);
		// --- Compute ID
		LeafID* id = (LeafID*) var->children[0];
		char* varName = id->id;
		ass_declVar(varName);
		freeNodeAll(var);
		
		Node* tmp = (Node*) declVar->children[1];
		freeNode(declVar);
		declVar = tmp;
	}
}

void st_computeFctCall(st_Node_t node)
{
	Node* father = (Node*) node;
	Node* params = (Node*) father->children[1];
	LeafID* id = (LeafID*) father->children[0];
	
	// --- Compute function name
	char* fctName = id->id;
	int nbParams = funT_getNbParamsByFunName(fctName);
	if(nbParams == -1)
	{
		return; // TODO error
	}
	
	// --- Compute params
	for(Node* param = params; param != ST_UNDEFINED;)
	{
		st_computeExpression(param->children[0], 0);
		ass_fctCallParam();
		
		Node* tmp = (Node*) param->children[1];
		freeNode(param);
		param = tmp;
		nbParams--;
	}
	if(nbParams != 0)
	{
		return; // TODO error
	}
	
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
	freeID(id);
}

void st_computeOperands(st_Node_t node)
{
	Node* ex = (Node*) node;
	st_NodeType nodeType = getNodeType(ex->children[0]);
	
	st_computeExpression(ex->children[1], 1);
	if(nodeType != NT_ID && nodeType != NT_EXNB)
		ass_pushResult();
	st_computeExpression(ex->children[0], 0);
	if(nodeType != NT_ID && nodeType != NT_EXNB)
		ass_popResult(1);
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
				st_compute(inst->children[0]); // function
				Node* tmp = (Node*) inst->children[1];
				freeNode(inst);
				inst = tmp;
			}
			st_free();
			return;
		case NT_FUNCTION:
			st_computeFunction(node);
			break;
		case NT_BLOC:
			st_computeBloc(node);
			break;
		case NT_DECLVAR:
			st_computeDeclVar(node);
			break;
		case NT_EXADD:
			st_computeOperands(node);
			ass_add();
			break;
		case NT_EXSUB:
			st_computeOperands(node);
			ass_sub();
			break;
		case NT_EXMUL:
			st_computeOperands(node);
			ass_mul();
			break;
		case NT_EXDIV:
			st_computeOperands(node);
			ass_div();
			break;
		case NT_EXOR:
			st_computeOperands(node);
			ass_or();
			break;
		case NT_EXAND:
			st_computeOperands(node);
			ass_and();
			break;
		case NT_EXINF:
			st_computeOperands(node);
			ass_inf();
			break;
		case NT_EXINFEQ:
			st_computeOperands(node);
			ass_sup();
			ass_not();
			break;
		case NT_EXSUP:
			st_computeOperands(node);
			ass_sup();
			break;
		case NT_EXSUPEQ:
			st_computeOperands(node);
			ass_inf();
			ass_not();
			break;
		case NT_EXDIFF:
			st_computeOperands(node);
			ass_equ();
			ass_not();
			break;
		case NT_EXEQU:
			st_computeOperands(node);
			ass_equ();
			break;
		case NT_EXNOT: {
			Node* ex = (Node*) node;
			st_computeExpression(ex->children[0], 0);
			ass_not();
			break; }
		case NT_EXAFFECT: {
			Node* ex = (Node*) node;
			LeafID* id = (LeafID*) ex->children[0];
			st_computeExpression(ex->children[1], 0);
			ass_str(id->id);
			freeID(id);
			break; }
		case NT_FCTCALL:
			st_computeFctCall(node);
			break;
		case NT_WHILE: {
			Node* father = (Node*) node;
			ass_whileBegin(labelNumber);
			st_computeExpression(father->children[0], 0);
			ass_whileDo(labelNumber);
			st_compute(father->children[1]);
			ass_whileEnd(labelNumber);
			labelNumber++;
			break; }
		case NT_IF: {
			Node* father = (Node*) node;
			ass_ifBegin(labelNumber);
			st_computeExpression(father->children[0], 0);
			ass_ifThen(labelNumber);
			st_compute(father->children[1]);
			ass_ifEnd(labelNumber);
			labelNumber++;
			break; }
		case NT_RETURN: {
			Node* ex = (Node*) node;
			st_computeExpression(ex->children[0], 0);
			ass_return();
			break; }
		default:
			return;// error
	}
	freeNode(node);
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
	{
		putchar(' ');
	}
	
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
				Node* father = (Node*) node;
				if(father->children[i] != ST_UNDEFINED)
					st_printTree(father->children[i], indent+3);
			}
			break;
	}
}






//###################################################
//  CONSTRUCTION DE L'ARBRE
//###################################################

/* --- Noeuds --- */
st_Node_t st_createNode(st_NodeType type, st_Node_t n1, st_Node_t n2, st_Node_t n3)
{
	st_Node_t children[] = {n1, n2, n3};
	st_Node_t node = createNode(type, children);
	if(type == NT_ROOT)
		treeRoot = node;
	return node;
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








