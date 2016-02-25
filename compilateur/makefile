
SRC=$(wildcard src/*.c)
OBJ:=$(SRC:.c=.o)
OBJ:=$(OBJ:src/%=obj/%)

SRC_LY=src/source.l src/source.y
SRC_AUTO=auto/lex.yy.c auto/y.tab.c
OBJ_AUTO=$(SRC_AUTO:.c=.o)

CFLAGS=-Wall -std=c99
LDFLAGS=-ll


all: testyacc


testyacc: $(OBJ) $(OBJ_AUTO)
	gcc -g $^ $(LDFLAGS) -o $@

#### obj
auto/%.o: $(SRC_LY)
	$(MAKE) -C auto/ $($@:auto/%=%)

obj/%.o: src/%.c
	gcc -c $< $(CFLAGS) -o $@


#### clean
clean:
	- rm obj/*
	- $(MAKE) -C auto/ clean
