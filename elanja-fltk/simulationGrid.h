#ifndef SIMULATION_GRID_H
#define SIMULATION_GRID_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <FL/gl.h>
#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H> 
#include "model.h"
#include "const.h"
#include "elanja-fltk.h"

extern bool doNextSimulationStep;
extern bool crisis;
extern int t;

class simulationGrid : public Fl_Gl_Window
{
public:
	simulationGrid(int x,int y,int w,int h,const char *l=0);
	bool grow;
	//model m;
protected:
	void draw();
	void init();
};

void timer_cb(void *p);
void circle(double x, double y, double w, double h, double radius);
int min2(int a, int b);
double distance(int x1, int y1, int x2, int y2, int w, int h);
int get_movx(int i, int w, int h);
int get_movy(int i, int w, int h);
void get_mov(int i, int w, int h, int *mov);
void vector(int i, int j, int w, int h, int *vec);
void versor(int *vect, double *vers);
void moveAgent(int i);
void drawAgent(int i);
void drawTrust(int i, int j);
double hue(int i);
int segno (double n);
void hsl2rgb(float h, float s, float l, GLfloat *color);
float h2v(float v1, float v2, float vH);
#endif
