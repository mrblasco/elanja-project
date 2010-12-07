#include "const.h"
#include "elanja-fltk.h"
#include "gui_controls.h"
#include "widgetWindow.h"
#include "regionCountStats.h"
#include "regionStats.h"
#include "maxRegionStats.h"

static regionStats g1(STATS_W, STATS_H);
static widgetWindow regionStats(STATS_W, STATS_H, &g1, "Region View");

static regionCountStats g1(STATS_W, STATS_H);
static widgetWindow regionCountStats(STATS2_W, STATS2_H, &g2, "Region Count");

static maxRegionStats g1(STATS_W, STATS_H);
static widgetWindow maxRegionStats(STATS2_W, STATS2_H, &g3, "Max Region");

static simulationGrid glf(10,30,SIMULATION_WIDTH,SIMULATION_HIGH, &g1, &g2, &g3); 

/************* Main Window *****************************************/
Fl_Double_Window *elanjaWindow=(Fl_Double_Window *)0;

/************* Play/Stop Buttons ***********************************/
Fl_Button *playButton=(Fl_Button *)0;

Fl_Button *restartButton=(Fl_Button *)0;

/************* Simulation Steps ************************************/
Fl_Value_Output *simStepLabel=(Fl_Value_Output *)0;

/************* Slider's Group **************************************/
Fl_Group *parametersGroup=(Fl_Group *)0;

Fl_Value_Slider *agentsSlider=(Fl_Value_Slider *)0;

Fl_Value_Slider *deltaSlider=(Fl_Value_Slider *)0;

Fl_Value_Slider *pos_traitsSlider=(Fl_Value_Slider *)0;

Fl_Value_Slider *noiseSlider=(Fl_Value_Slider *)0;

Fl_Value_Slider *simSpeedSlider=(Fl_Value_Slider *)0;

/************* Button's Group **************************************/

Fl_Check_Button *latticeButton=(Fl_Check_Button *)0;

Fl_Check_Button *kleinbergButton=(Fl_Check_Button *)0;

Fl_Check_Button *linkButton=(Fl_Check_Button *)0;

/************* Menu ************************************************/
Fl_Menu_Item menu_Visualizza[] = {
 {"File", 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 14, 0},
 {"Exit", 0,  (Fl_Callback*)exitCallback, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {"Simulation", 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 14, 0},
 {"@> Play", 0,  (Fl_Callback*)playCallback, (void*)(&glf), 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"@|> Restart", 0,  (Fl_Callback*)restartCallback, (void*)(&glf), 0, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {"View", 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 14, 0},
 {"Region View", 0, (Fl_Callback*)regionStatsCallback, (void*)(&regionStats), 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"Region Count", 0, (Fl_Callback*)regionCountStatsCallback, (void*)(&regionStats), 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"Max Region", 0, (Fl_Callback*)maxRegionCallback, (void*)(&regionStats), 0, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0}
};

int main(int argc, char **argv) 
{
	glf.mode(FL_DOUBLE);
	{	
          /* Main Window */
 		elanjaWindow = new Fl_Double_Window(WINDOW_WIDTH, WINDOW_HIGH, "Elanja");
		elanjaWindow->color(FL_LIGHT3);	
	     	elanjaWindow->selection_color((Fl_Color)53);
      
    		{	/* Button's Group */ 
			Fl_Group* controlGroup = new Fl_Group(710, 465, 232, 255, "Controls");
			controlGroup->box(FL_PLASTIC_UP_FRAME);
			controlGroup->color(FL_FOREGROUND_COLOR);
      			controlGroup->align(FL_ALIGN_TOP_LEFT|FL_ALIGN_INSIDE);
			{	/* Simulation Speed Slider */
				simSpeedSlider = new Fl_Value_Slider(715, 523, 220, 40, "Simulation Speed");
        			simSpeedSlider->type(5);
			        simSpeedSlider->color((Fl_Color)10);
			        simSpeedSlider->selection_color((Fl_Color)136);
			        simSpeedSlider->labelfont(1);
			        simSpeedSlider->labelsize(12);
			        simSpeedSlider->minimum(SIM_SPEED_MIN);
				simSpeedSlider->maximum(SIM_SPEED_MAX);
			        simSpeedSlider->step(0.001);
			        simSpeedSlider->value(SIM_SPEED_INIT);
			        simSpeedSlider->callback((Fl_Callback*)simSpeedSliderCallback);
			        simSpeedSlider->align(FL_ALIGN_TOP_LEFT);      
			}
			{ 	/* Play Button */
				playButton = new Fl_Button(725, 680, 100, 30, "@>");
        			playButton->callback((Fl_Callback*)playCallback, (void*)(&glf));
      			} 
      			{	/* Stop Button */
				restartButton = new Fl_Button(830, 680, 100, 30, "@|>");
        			restartButton->callback((Fl_Callback*)restartCallback, (void*)(&glf));
	      		} 
      			{	/* Simulation Steps */
				simStepLabel = new Fl_Value_Output(740, 620, 172, 25, "Simulation steps:");
				simStepLabel->labelfont(1);
        			simStepLabel->labelsize(12);
        			simStepLabel->maximum(1e+06);
        			simStepLabel->align(FL_ALIGN_TOP_LEFT);
      			} 
      			controlGroup->end();
    		} 
		{	/* Parameters Group */
			parametersGroup = new Fl_Group(710, 30, 232, 430, "Parameters");
      			parametersGroup->box(FL_PLASTIC_UP_FRAME);
      			parametersGroup->color(FL_FOREGROUND_COLOR);
      			parametersGroup->align(FL_ALIGN_TOP_LEFT|FL_ALIGN_INSIDE);
			{ 	/* Agent Slider */
				agentsSlider = new Fl_Value_Slider(715, 70, 220, 40, "Lattice Linear Dimension");
        			agentsSlider->type(5);
        			agentsSlider->color((Fl_Color)10);/* Slider color */
        			agentsSlider->selection_color((Fl_Color)136);/* Cursor color */
        			agentsSlider->labelfont(1);
        			agentsSlider->labelsize(12);
				agentsSlider->minimum(LINEAR_LATTICE_DIMENSION_MIN);
        			agentsSlider->maximum(LINEAR_LATTICE_DIMENSION_MAX);
        			agentsSlider->step(5);
        			agentsSlider->value(LINEAR_LATTICE_DIMENSION_INIT);
        			agentsSlider->callback((Fl_Callback*)agentsSliderCallback);
        			agentsSlider->align(FL_ALIGN_TOP_LEFT);/* Label align*/
      			}
      			{ 	/* Delta Slider */
				deltaSlider = new Fl_Value_Slider(715, 175, 220, 40, "Delta");
        			deltaSlider->type(5);
        			deltaSlider->color((Fl_Color)10);
        			deltaSlider->selection_color((Fl_Color)136);
				deltaSlider->minimum(DELTA_MIN);
        			deltaSlider->maximum(DELTA_MAX);
        			deltaSlider->labelfont(1);
        			deltaSlider->labelsize(12);
        			deltaSlider->value(DELTA_INIT);
				deltaSlider->step(10);
        			deltaSlider->callback((Fl_Callback*)deltaSliderCallback);
        			deltaSlider->align(FL_ALIGN_TOP_LEFT);
      			}
      			{	/* Possible Traits Slider */
		 		pos_traitsSlider = new Fl_Value_Slider(715, 275, 220, 40, "Possible Traits");
        			pos_traitsSlider->type(5);
        			pos_traitsSlider->color((Fl_Color)10);
        			pos_traitsSlider->selection_color((Fl_Color)136);
        			pos_traitsSlider->labelfont(1);
        			pos_traitsSlider->labelsize(12);
        			pos_traitsSlider->minimum(POS_TRAITS_MIN);
        			pos_traitsSlider->maximum(POS_TRAITS_MAX);
        			pos_traitsSlider->step(1);
        			pos_traitsSlider->value(POS_TRAITS_INIT);
        			pos_traitsSlider->callback((Fl_Callback*)pos_traitsSliderCallback);
        			pos_traitsSlider->align(FL_ALIGN_TOP_LEFT);
      			}
			{ 	/* Lattice Network Button */
				latticeButton = new Fl_Check_Button(715, 335, 150, 25, "Lattice Network");
				kleinbergButton = new Fl_Check_Button(715, 365, 150, 25, "Kleinberg Network");
        			latticeButton->down_box(FL_DOWN_BOX);
				latticeButton->labelfont(1);
			        latticeButton->labelsize(12);
				latticeButton->value(1);
        			latticeButton->callback((Fl_Callback*)latticeCallback, (void*)(kleinbergButton));
      			} 
			{ 	/* Kleinberg Network Button */
				
        			kleinbergButton->down_box(FL_DOWN_BOX);
				kleinbergButton->labelfont(1);
			        kleinbergButton->labelsize(12);
        			kleinbergButton->callback((Fl_Callback*)kleinbergCallback, (void*)(latticeButton));
      			} 
      			{ 	/* Link Visualization Button */
				linkButton = new Fl_Check_Button(715, 435, 150, 25, "Link Visualization");
		        	linkButton->down_box(FL_DOWN_BOX);
				linkButton->labelfont(1);
			        linkButton->labelsize(12);
				linkButton->value(1);
        			linkButton->callback((Fl_Callback*)linkCallback);
	      		} 
      			parametersGroup->end();
		}
		{	/* Menu */
			Fl_Menu_Bar* o = new Fl_Menu_Bar(0, 0, 1000, 20, "View");
      			o->menu(menu_Visualizza);
		}
    		elanjaWindow->add(glf);
    		elanjaWindow->end();
	}
	elanjaWindow->show(argc, argv); /* Show me */
	return Fl::run(); 
}
static int x; /* ? */
