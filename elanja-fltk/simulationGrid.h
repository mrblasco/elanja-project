#ifndef SIMULATION_GRID_H
#define SIMULATION_GRID_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <FL/gl.h>
#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H> 

#include "regionStats.h"
#include "model.h"
#include "elanja-fltk.h"

extern bool doNextSimulationStep; 
/* Simulation Counter */
extern int pippo;

class simulationGrid : public Fl_Gl_Window
{
public:
	simulationGrid(int x, int y, int w, int h, regionStats *g1, const char *l=0);
	regionStats *g1;
protected: /* do not delete */
	void draw();
	void init();
};

void timer_cb(void *p);  /*  step delay */
void square(double x, double y, double radius); /* draws square */
void drawAgents(int agent); /* draws agents */
void link(int i); /* draws links */

#endif
