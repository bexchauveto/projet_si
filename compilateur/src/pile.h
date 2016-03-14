#ifndef PILE_H
#define PILE_H


typedef struct pile
{
	void * data;
	struct pile * prec;
} Pile;

void * pile_pop(Pile ** p_pile);
void pile_push(Pile ** p_pile, void * data);

#endif // PILE_H