
LEXFILE=source.lex
YACCFILE=source.yacc


all: testyacc


testyacc: $(LEXFILE) $(YACCFILE)
	yacc -d $(YACCFILE)
	flex $(LEXFILE)
	gcc y.tab.c lex.yy.c -ll -o $@

clean:
	rm y.tab.c lex.yy.c
