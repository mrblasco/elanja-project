CC= g++
OBJS= *.o

graphic: guiControls widgetWindow
	$(CC) `fltk-config --ldflags --use-gl` -ggdb -lc elanja-fltk.cxx $(OBJS) -L/usr/lib32 -lfltk -o elanja

widgetWindow:
	$(CC) -c widgetWindow.cpp

guiControls: simulationGrid
	$(CC) -c gui_controls.cpp

simulationGrid: model
	$(CC) -c simulationGrid.cpp
	
model:
	$(CC) -c model.cpp

clean:
	rm -f elanja
	rm -f *.o
	rm -f *~
