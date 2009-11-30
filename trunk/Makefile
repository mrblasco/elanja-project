GPPFLAGS= -Wall -Wunused -pedantic -ggdb
LINKERFLAGS= -lm

graphic: 
	g++ `fltk2-config --cxxflags` elanja-fltk/elanja-fltk.cxx `fltk2-config --ldflags` -o elanja

model: elanja

elanja: elanja.o matrices.o multiply.o
	gcc -o elanja ${GPPFLAGS} ${LINKERFLAGS} elanja.o matrices.o multiply.o

elanja.o: src/elanja.c h/matrices.h
	gcc -c ${GPPFLAGS} src/elanja.c

matrices.o: src/matrices.c
	gcc -c ${GPPFLAGS} src/matrices.c

multiply.o: src/multiply.c
	gcc -c ${GPPFLAGS} src/multiply.c

prova: test

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
