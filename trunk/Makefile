GPPFLAGS= -Wall -Wunused -pedantic -ggdb
LINKERFLAGS= -lm

graphic: 
	g++ `fltk2-config --cxxflags --use-gl` elanja-fltk/elanja-fltk.cxx `fltk2-config --ldflags` -o elanja

model: elanja

elanja: elanja.o matrices.o multiply.o
	g++ -o main ${GPPFLAGS} ${LINKERFLAGS} elanja.o matrices.o multiply.o

elanja.o: src/elanja.cpp h/matrices.h h/multiply.h
	g++ -c ${GPPFLAGS} src/elanja.cpp

matrices.o: src/matrices.cpp
	g++ -c ${GPPFLAGS} src/matrices.cpp

multiply.o: src/multiply.cpp
	g++ -c ${GPPFLAGS} src/multiply.cpp

prova: test

test: test.o util.o
	g++ -o test ${GPPFLAGS} ${LINKERFLAGS} test.o util.o

test.o: src/test.cpp h/util.h
	g++ -c ${GPPFLAGS} src/test.cpp

util.o: src/util.cpp
	g++ -c ${GPPFLAGS} src/util.cpp



clean:	
	rm -f *.o
	rm -f main
	rm -f test
	rm -f *~
	rm -f *.png
