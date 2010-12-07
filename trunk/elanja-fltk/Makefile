CC= g++
OBJS= *.o

graphic: guiControls widgetWindow
	$(CC) `fltk-config --ldflags --use-gl` -ggdb -lc elanja-fltk.cxx $(OBJS) -L/usr/lib32 -lfltk -o elanja

widgetWindow:
	$(CC) -c widgetWindow.cpp

guiControls: simulationGrid
	$(CC) -c gui_controls.cpp

simulationGrid: graphic1 model
	$(CC) -c simulationGrid.cpp

glStats: 
	$(CC) -c glStats.cpp

graphic1: glStats
	$(CC) -c regionStats.cpp

	
model:
	$(CC) -c model.cpp

clean:
	rm -f elanja
	rm -f *.o
	rm -f *~
