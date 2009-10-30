GPPFLAGS= -Wall -Wunused -pedantic -ggdb
LINKERFLAGS= -lm

all:  elanja

elanja: elanja.o 
	g++ -o elanja ${GPPFLAGS} ${LINKERFLAGS} elanja.o 

elanja.o: src/elanja.cc
	g++ -c ${GPPFLAGS} src/elanja.cc

clean:	
	rm -f *.o
	rm -f elanja
	rm -f *~
