
SRC=$(wildcard src/*.c)
OBJ:=$(SRC:src/%.c=obj/%.o)

SRC_LY=src/source.l src/source.y
SRC_AUTO=auto/lex.yy.c auto/y.tab.c
OBJ_AUTO=$(SRC_AUTO:%.c=%.o)

CFLAGS=-Wall -std=c99
LDFLAGS=-ll






all: testyacc

-include $(wildcard dep/*.d)




testyacc: $(OBJ) $(OBJ_AUTO)
	gcc -g $^ $(LDFLAGS) -o $@

#### obj
auto/%.o: $(SRC_LY) src/st.h
	$(MAKE) -C auto/ $($@:auto/%=%)

obj/%.o: src/%.c
	echo $(OBJ)
	gcc -MM $< -MF dep/$*.d -MT $@
	gcc -c $< $(CFLAGS) -o $@



#### clean
clean:
	- rm obj/*.o
	- $(MAKE) -C auto/ clean



