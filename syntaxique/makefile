
SRC=$(wildcard src/*.c)
OBJ:=$(SRC:.c=.o)
OBJ:=$(OBJ:src/%=obj/%)

SRC_AUTO=auto/lex.yy.c auto/y.tab.c
OBJ_AUTO=$(SRC_AUTO:.c=.o)

CFLAGS=-Wall -std=c99


all: testyacc


testyacc: $(OBJ) $(OBJ_AUTO)
	gcc -g $^ -ll -o $@

#### obj
auto/%.o:
	$(MAKE) -C auto/ $($@:auto/%=%)

obj/%.o: src/%.c
	gcc -c $< $(CFLAGS) -o $@


#### clean
clean:
	- rm obj/*
	- $(MAKE) -C auto/ clean
