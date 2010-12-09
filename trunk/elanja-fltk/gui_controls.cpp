#include "gui_controls.h"

#define MAXDELAY	(0.5)
#define MINDELAY	(0.001)
#define MAX(a,b)	(a>b?a:b)

int gui_linear_lattice_dimension;
double gui_delta;
int gui_pos_traits ;

bool doNextSimulationStep;
bool restart;
bool restartB = false;
bool restartS = false;
double simSpeed;
bool latticeOn = true;
bool kleinbergOn = false;
bool linkVisualization = true;
bool resized = false;

extern model m;

/****************************************************/
/**************Controls Callbacks********************/
/****************************************************/
void exitCallback(Fl_Widget*, void*){
	elanjaWindow->hide();
	exit(0);
}

void playCallback(Fl_Widget*, void* data){
	simulationGrid* glf;
	doNextSimulationStep=true;
	glf=(simulationGrid*)data;
	playButton->label("@||");
	playButton->callback((Fl_Callback*)pauseCallback);
	playItem->label("@|| Pause");
	playItem->callback((Fl_Callback*)pauseCallback);
	Fl::add_timeout(2.0/5,timer_cb,glf);
}

void restartCallback(Fl_Widget* button, void* data){
	restart=true;
	restartB=true;
	doNextSimulationStep=false;
	playButton->label("@>");
	playButton->callback((Fl_Callback*)playCallback);
	playItem->label("@> Play");
	playItem->callback((Fl_Callback*)playCallback);
}
void pauseCallback(Fl_Widget* button, void*){
	doNextSimulationStep=false;
	playButton->label("@>");
	playButton->callback((Fl_Callback*)playCallback);
	playItem->label("@> Play");
	playItem->callback((Fl_Callback*)playCallback);
}

/****************************************************/
/************Parameters Callbacks********************/
/****************************************************/

void agentsSliderCallback(Fl_Value_Slider* s, void*){
	Fl_Value_Slider* slider = (Fl_Value_Slider*)s;
  	gui_linear_lattice_dimension = slider->value();
}
void deltaSliderCallback(Fl_Value_Slider* s, void*){
	Fl_Value_Slider* slider = (Fl_Value_Slider*)s;
  	gui_delta = slider->value();
}
void pos_traitsSliderCallback(Fl_Value_Slider* s, void*){
	Fl_Value_Slider* slider = (Fl_Value_Slider*)s;
  	gui_pos_traits = slider->value();
}

void simSpeedSliderCallback(Fl_Value_Slider* s, void*){
	Fl_Value_Slider* slider = (Fl_Value_Slider*)s;
  	simSpeed = MAX(MAXDELAY*(1-slider->value()),MINDELAY);
}

void latticeCallback(Fl_Check_Button *s, void *data){
	Fl_Check_Button * kleinberg;
	kleinberg = (Fl_Check_Button *)data;
	Fl_Check_Button* lattice = (Fl_Check_Button*)s;

	latticeOn=!latticeOn;

	if(kleinberg->value())
	{
		kleinberg->value(0);
		kleinbergOn=!kleinbergOn;
		restart = true;
	}
	else
	{
		kleinberg->value(1);
		kleinbergOn=!kleinbergOn;
		restart = true;
	}
}

void kleinbergCallback(Fl_Check_Button *s,void * data){
	Fl_Check_Button * lattice;
	lattice = (Fl_Check_Button *)data;
	Fl_Check_Button* kleinberg = (Fl_Check_Button*)s;

	kleinbergOn=!kleinbergOn;

	if(lattice->value())
	{
		lattice->value(0);
		latticeOn=!latticeOn;
		restart = true;
	}
	else
	{
		lattice->value(1);
		latticeOn=!latticeOn;
		restart = true;
	}
	
}

void linkCallback(Fl_Check_Button *s,void * data){
	Fl_Check_Button * link;
	link = (Fl_Check_Button *)data;

	linkVisualization=!linkVisualization;
}

/****************************************************/
/************Statistics Callbacks********************/
/****************************************************/
void regionStatsCallback(Fl_Widget*, void* data)
{
	widgetWindow * w;
	
	w = (widgetWindow *)data;
	w->set_visible();
	w->show();
}

void regionCountStatsCallback(Fl_Widget*, void* data){
	widgetWindow * w;

	w=(widgetWindow *)data;
	w->set_visible();
	w->show();
}

void maxRegionStatsCallback(Fl_Widget*, void* data){
	widgetWindow * w;

	w=(widgetWindow *)data;
	w->set_visible();
	w->show();
}

