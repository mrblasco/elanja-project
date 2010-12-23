#ifndef GUI_CONTROLS_H
#define GUI_CONTROLS_H

#include <stdlib.h>
#include <stdio.h>
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Value_Slider.H>
#include "simulationGrid.h"
#include "elanja-fltk.h"
#include "widgetWindow.h"

void playCallback(Fl_Widget*, void*);
void restartCallback(Fl_Widget*, void*);
void pauseCallback(Fl_Widget*, void*);
void exitCallback(Fl_Widget*, void*);

void latticeCallback(Fl_Check_Button * s,void * data);
void kleinbergCallback(Fl_Check_Button * s,void * data);
void randomCallback(Fl_Check_Button * s,void * data);
void linkCallback(Fl_Check_Button * s,void * data);

void regionStatsCallback(Fl_Widget*, void*);
void regionCountStatsCallback(Fl_Widget*, void*);
void maxRegionStatsCallback(Fl_Widget*, void*);

#endif
