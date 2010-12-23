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
bool latticeOn = false;
bool kleinbergOn = false;
bool randomOn = true;
bool linkVisualization = false;
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
	Fl_Value_Slider * deltaSlider;
	deltaSlider = (Fl_Value_Slider *)data;

	latticeOn=!latticeOn;

	if(kleinbergButton->value())
	{
		kleinbergButton->value(0);
		kleinbergOn=!kleinbergOn;
		deltaSlider->deactivate();
		restart = true;
	}
	else if(randomButton->value())
	{
		randomButton->value(0);
		randomOn=!randomOn;
		deltaSlider->activate();
		restart = true;
	}

	if(deltaSlider->active())
		deltaSlider->deactivate();
}

void kleinbergCallback(Fl_Check_Button *s,void * data){
	Fl_Value_Slider * deltaSlider;
	deltaSlider = (Fl_Value_Slider *)data;

	kleinbergOn=!kleinbergOn;

	if(latticeButton->value())
	{
		latticeButton->value(0);
		latticeOn=!latticeOn;
		restart = true;
	}
	else if(randomButton->value())
	{
		randomButton->value(0);
		randomOn=!randomOn;
		restart = true;
	}
	
	if(!(deltaSlider->active()))
		deltaSlider->activate();
	
}

void randomCallback(Fl_Check_Button *s,void * data){
	Fl_Value_Slider * deltaSlider;
	deltaSlider = (Fl_Value_Slider *)data;

	randomOn=!randomOn;

	if(latticeButton->value())
	{
		latticeButton->value(0);
		latticeOn=!latticeOn;
		deltaSlider->deactivate();
		restart = true;
	}
	else if(kleinbergButton->value())
	{
		kleinbergButton->value(0);
		kleinbergOn=!kleinbergOn;
		deltaSlider->deactivate();
		restart = true;
	}
	
	if(deltaSlider->active())
		deltaSlider->deactivate();
	
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

