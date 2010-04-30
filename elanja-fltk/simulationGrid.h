#ifndef SIMULATION_GRID_H
#define SIMULATION_GRID_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <FL/gl.h>
#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H> 

#include "model.h"
#include "elanja-fltk.h"

extern bool doNextSimulationStep; 
/*extern bool crisis;*/
extern int t;

class simulationGrid : public Fl_Gl_Window
{
public:
	simulationGrid(int x, int y, int w, int h, const char *l=0);
	/*bool grow;
	model m; */
protected: /* non puoi cancellalro */
	void draw();
	void init();
};

void timer_cb(void *p);  /*  delay tra uno step e l'altro della simulazione */
void circle(double x, double y, double radius); /* disegna i pallini */
void drawAgents(int i); /* per gli agenti */

#endif
