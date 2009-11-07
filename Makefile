GPPFLAGS= -Wall -Wunused -pedantic -ggdb
LINKERFLAGS= -lm

all: elanja.exe

prova: test.exe

elanja.exe: elanja.o matrices.o 
	g++ -o elanja.exe ${GPPFLAGS} ${LINKERFLAGS} elanja.o matrices.o

elanja.o: src/elanja.c h/matrices.h
	g++ -c ${GPPFLAGS} src/elanja.c

matrices.o: src/matrices.c
	g++ -c ${GPPFLAGS} src/matrices.c

test.exe: test.o util.o
	g++ -o test ${GPPFLAGS} ${LINKERFLAGS} test.o util.o

test.o: src/test.c h/util.h
	g++ -c ${GPPFLAGS} src/test.c

util.o: src/util.c
	g++ -c ${GPPFLAGS} src/util.c



clean:	
	rm -f *.o
	rm -f elanja
	rm -f test
	rm -f *~
