#include "gui_controls.h"

#define MAXDELAY	(0.1)
#define MINDELAY	(0.001)
#define MAX(a,b)	(a>b?a:b)

int gui_agents;
int gui_distance;
double gui_rho;
double gui_epsilon;
double gui_friendship;

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
  	gui_epsilon = slider->value();
}
void friendshipSliderCallback(Fl_Value_Slider* s, void*){
	Fl_Value_Slider* slider = (Fl_Value_Slider*)s;
// 	slider->value(slider->value());
  	gui_friendship = slider->value();
  	restart = true;
}

void simSpeedSliderCallback(Fl_Value_Slider* s, void*){
	Fl_Value_Slider* slider = (Fl_Value_Slider*)s;
// 	slider->value(slider->value());
  	simSpeed = MAX(MAXDELAY*(1-slider->value()),MINDELAY);
}

void perturbationCallback(Fl_Check_Button *,void *data){
	Fl_Value_Slider * slider;

	slider=(Fl_Value_Slider *)data;
	perturbationOn=!perturbationOn;
	if(slider->active()){
		slider->deactivate();
	}else{
		slider->activate();
	}
	
}

void hubsCallback(Fl_Check_Button *,void * data){
	hubsOn=!hubsOn;
}
