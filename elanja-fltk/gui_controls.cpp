#include "gui_controls.h"

#define MAXDELAY	(0.5)
#define MINDELAY	(0.001)
#define MAX(a,b)	(a>b?a:b)

int gui_agents;
int gui_distance;
double gui_rho;
int gui_nFeatures;
double gui_friendship;
double gui_threshold;

bool doNextSimulationStep;
bool restart;
double simSpeed;
bool perturbationOn, hubsOn;

extern model m;

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

void stopCallback(Fl_Widget* button, void* data){
	restart=true;
	playCallback(button,data);
}
void pauseCallback(Fl_Widget* button, void*){
	doNextSimulationStep=false;
	playButton->label("@>");
	playButton->callback((Fl_Callback*)playCallback);
	playItem->label("@> Play");
	playItem->callback((Fl_Callback*)playCallback);
}
void agentsSliderCallback(Fl_Value_Slider* s, void*){
	Fl_Value_Slider* slider = (Fl_Value_Slider*)s;
  	gui_agents = slider->value();
}
void populationSliderCallback(Fl_Value_Slider* s, void*){
	Fl_Value_Slider* slider = (Fl_Value_Slider*)s;
  	gui_rho = slider->value();
}
void epsilonSliderCallback(Fl_Value_Slider* s, void*){
	Fl_Value_Slider* slider = (Fl_Value_Slider*)s;
  	gui_nFeatures = slider->value();
}
void friendshipSliderCallback(Fl_Value_Slider* s, void*){
	Fl_Value_Slider* slider = (Fl_Value_Slider*)s;
// 	slider->value(slider->value());
  	gui_friendship = slider->value();
  	restart = true;
}
void thresholdSliderCallback(Fl_Value_Slider* s, void*){
	Fl_Value_Slider* slider = (Fl_Value_Slider*)s;
  	gui_threshold = slider->value();
}


void simSpeedSliderCallback(Fl_Value_Slider* s, void*){
	Fl_Value_Slider* slider = (Fl_Value_Slider*)s;
// 	slider->value(slider->value());
  	simSpeed = MAX(MAXDELAY*(1-slider->value()),MINDELAY);
}

/************************* STATISTICS ********************************/
void degreeStatsCallback(Fl_Widget*, void* data)
{
	widgetWindow * w;
	
	w = (widgetWindow *)data;
	w->set_visible();
	w->show();
}

void clusteringStatsCallback(Fl_Widget*, void* data){
	widgetWindow * w;

	w=(widgetWindow *)data;
	w->set_visible();
	w->show();
}

void capitalVariationCallback(Fl_Widget*, void* data){
	widgetWindow * w;

	w=(widgetWindow *)data;
	w->set_visible();
	w->show();
}

