GPPFLAGS= -Wall -Wunused -pedantic -ggdb
LINKERFLAGS= -lm

all:  elanja 

elanja: elanja.o matrices.o ../h/matrices.h
	g++ -o elanja ${GPPFLAGS} ${LINKERFLAGS} elanja.o 

elanja.o: src/elanja.cc
	g++ -c ${GPPFLAGS} src/elanja.cc

matrices: matrices.o
	g++ -o matrices ${GPPFLAGS} ${LINKERFLAGS} matrices.o

matrices.o: src/matrices.cc
	g++ -c ${GPPFLAGS} src/matrices.cc

clean:	
	rm -f *.o
	rm -f elanja
	rm -f matrices
	rm -f *~
