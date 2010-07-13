GPPFLAGS= -Wall -Wunused -pedantic -ggdb
LINKERFLAGS= -lm
OBJS= *.o
CC= g++

textual: model elanja
	g++ -o main ${GPPFLAGS} ${LINKERFLAGS} elanja.o model.o

elanja: 
	$(CC) -c src/elanja.cpp

model: 
	$(CC) -c src/model.cpp

clean:	
	rm -f *.o
	rm -f elanja
	rm -f main
	rm -f *~
	rm -f *.png
	rm -f *.dat
