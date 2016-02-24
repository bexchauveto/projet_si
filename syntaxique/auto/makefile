
DSRC=../src/
SRC_LEX=$(DSRC)source.l
SRC_YACC=$(DSRC)source.y

SRC_AUTO_LEX=lex.yy.c
SRC_AUTO_YACC=y.tab.c
OBJ_AUTO=$(SRC_AUTO_LEX:.c=.o) $(SRC_AUTO_YACC:.c=.o)


all: $(OBJ_AUTO)

#### obj
%.o: %.c
	gcc -c $^ -o $@


#### lex
$(SRC_AUTO_LEX): $(SRC_LEX) $(SRC_AUTO_YACC)
	flex $<


#### yacc
$(SRC_AUTO_YACC): $(SRC_YACC)
	yacc -d -v $<


#### clean
clean:
	rm lex.* y.*
