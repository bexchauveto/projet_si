
LEXFILE=source.l
YACCFILE=source.y


all: testyacc


testyacc: y.tab.c lex.yy.c
	gcc y.tab.c lex.yy.c -ll -o $@

y.tab.c: $(YACCFILE)
	yacc -d -v $<

lex.yy.c: $(LEXFILE)
	flex $<

clean:
	rm y.tab.c y.tab.h lex.yy.c
