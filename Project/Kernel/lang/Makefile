all: lang

OBJS = code.o lib.o scanner.o parser.o tree.o

lang: $(OBJS)
	$(CC) -o lang $(OBJS)

parser.o: parser.c
	$(CC) -c parser.c

parser.c parser.h: parser.y
	bison -v -d parser.y -o parser.c

scanner.c: parser.c scanner.l
	flex scanner.l
	mv lex.yy.c scanner.c
	 
