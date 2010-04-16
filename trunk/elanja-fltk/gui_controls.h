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
void stopCallback(Fl_Widget*, void*);
void pauseCallback(Fl_Widget*, void*);
void exitCallback(Fl_Widget*, void*);
void lambdaSliderCallback(Fl_Value_Slider*, void* data);
void gCoefSliderCallback(Fl_Value_Slider*, void* data);
void cExpSliderCallback(Fl_Value_Slider*, void* data);
void numAgentsSliderCallback(Fl_Value_Slider*, void*);
void numProductsSliderCallback(Fl_Value_Slider*, void*);
void initialCapitalSliderCallback(Fl_Value_Slider*, void*);
void velocitySliderCallback(Fl_Value_Slider*, void*);
void priceGeneticsCallback(Fl_Widget*, void*);
void capitalDistributionCallback(Fl_Widget*, void*);
void needGeneticsCallback(Fl_Widget*, void*);
void capitalVariationCallback(Fl_Widget*, void*);
void trustMatrixCallback(Fl_Widget*, void*);
void dinamicProductsCallback(Fl_Check_Button * button,void * data);
void externAgentCallback(Fl_Check_Button * button,void * data);

#endif
