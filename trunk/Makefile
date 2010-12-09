GPPFLAGS= -Wall -Wunused -pedantic -ggdb
LINKERFLAGS= -lm
OBJS= *.o
CC= g++

textual: modelT elanja
	g++ -o elanja ${GPPFLAGS} ${LINKERFLAGS} elanja.o model.o

elanja: 
	$(CC) -c src/elanja.cpp

modelT: 
	$(CC) -c src/model.cpp

graphic: guiControls widgetWindow
	$(CC) `fltk-config --ldflags --use-gl` -ggdb -lc elanja-fltk/elanja-fltk.cxx $(OBJS) -L/usr/lib32 -lfltk -o elanja

widgetWindow:
	$(CC) -c elanja-fltk/widgetWindow.cpp

guiControls: simulationGrid
	$(CC) -c elanja-fltk/gui_controls.cpp

simulationGrid: graphic2 graphic3 graphic1 modelG
	$(CC) -c elanja-fltk/simulationGrid.cpp

glStats: 
	$(CC) -c elanja-fltk/glStats.cpp

graphic1: glStats
	$(CC) -c elanja-fltk/regionStats.cpp

graphic2: glStats		
	$(CC) -c elanja-fltk/regionCountStats.cpp		
			
graphic3: glStats		
	$(CC) -c elanja-fltk/maxRegionStats.cpp

modelG:
	$(CC) -c elanja-fltk/model.cpp

clean:	
	rm -f *.o
	rm -f elanja
	rm -f main
	rm -f *~
	rm -f *.png
	rm -f *.dat
