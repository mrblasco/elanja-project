CC= g++
OBJS= *.o

graphic: guiControls widgetWindow
	$(CC) `fltk-config --ldflags --use-gl` -ggdb -lc elanja-fltk.cxx $(OBJS) -L/usr/lib32 -lfltk -o elanja

widgetWindow:
	$(CC) -c widgetWindow.cpp

guiControls: simulationGrid
	$(CC) -c gui_controls.cpp

simulationGrid: graphic1 graphic2 capitalVariation model
	$(CC) -c simulationGrid.cpp

glStats: 
	$(CC) -c glStats.cpp

graphic1: glStats
	$(CC) -c degreeStats.cpp

graphic2: glStats
	$(CC) -c clusteringStats.cpp

capitalVariation: glStats
	$(CC) -c capitalVariation.cpp


	
model:
	$(CC) -c model.cpp

clean:
	rm -f elanja
	rm -f *.o
	rm -f *~
