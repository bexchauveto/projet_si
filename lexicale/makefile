
INPUT=source.l



all: testlex


testlex: $(INPUT)
	flex $<
	gcc lex.yy.c -ll -o $@

clean:
	rm lex.yy.c
