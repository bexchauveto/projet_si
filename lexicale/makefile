
INPUT=source.l



all: testlex


testlex: lex.yy.c
	gcc lex.yy.c -ll -o $@
	
lex.yy.c: $(INPUT)
	flex $<

clean:
	rm lex.yy.c
