#include "pile.h"

typedef struct
{
	void * data;
	Pile * prec;
} Pile;

//pile_pop
void * pile_pop(Pile ** p_pile)
{
	void * ret = NULL;
	if(*p_pile != NULL)
	{
		Pile * tmp = (*p_pile)->prec;
		ret = (*p_pile)->data;
		free(*p_pile);
		*p_pile = NULL;
		*p_pile = tmp;
	}
	return ret;
}

//pile_push
void pile_push(Pile ** p_pile, void * data)
{
	Pile * p_new = malloc(sizeof *p_new);
	if( p_new != NULL)
	{
		p_new->data = data;
		p_new->prec = *p_pile;
		*p_pile = p_new; 
	}
}