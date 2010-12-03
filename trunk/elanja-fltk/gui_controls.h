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

/*void agentsSliderCallback(Fl_Widget*, void* data);
void deltaSliderCallback(Fl_Widget*, void*);
void epsilonSliderCallback(Fl_Widget*, void*);
void friendshipSliderCallback(Fl_Widget*, void*);
void thresholdSliderCallback(Fl_Widget*, void*);
void simSpeedSliderCallback(Fl_Widget*, void*);*/

void latticeCallback(Fl_Check_Button * s,void * data);
void kalinbergCallback(Fl_Check_Button * s,void * data);
void linkCallback(Fl_Check_Button * s,void * data);

void degreeStatsCallback(Fl_Widget*, void*);
void clusteringStatsCallback(Fl_Widget*, void* data);
void capitalVariationCallback(Fl_Widget*, void* data);


#endif
