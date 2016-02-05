
INPUT=source.lex



all: testlex


testlex: $(INPUT)
	flex $<
	gcc lex.yy.c -ll -o $@

clean:
	rm lex.yy.c
