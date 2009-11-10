GPPFLAGS= -Wall -Wunused -pedantic -ggdb
LINKERFLAGS= -lm

all: elanja

prova: test

elanja: elanja.o matrices.o 
	gcc -o elanja ${GPPFLAGS} ${LINKERFLAGS} elanja.o matrices.o

elanja.o: src/elanja.c h/matrices.h
	gcc -c ${GPPFLAGS} src/elanja.c

matrices.o: src/matrices.c
	gcc -c ${GPPFLAGS} src/matrices.c

test: test.o util.o
	gcc -o test ${GPPFLAGS} ${LINKERFLAGS} test.o util.o

test.o: src/test.c h/util.h
	gcc -c ${GPPFLAGS} src/test.c

util.o: src/util.c
	gcc -c ${GPPFLAGS} src/util.c



clean:	
	rm -f *.o
	rm -f elanja
	rm -f test
	rm -f *~
