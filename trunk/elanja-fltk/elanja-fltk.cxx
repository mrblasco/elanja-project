// generated by Fast Light User Interface Designer (fluid) version 1.0109
#include "const.h"
#include "elanja-fltk.h"
#include "gui_controls.h"
#include "widgetWindow.h"
#include "degreeStats.h"
#include "clusteringStats.h"
#include "capitalVariation.h"

static degreeStats g1(STATS_W, STATS_H);
static widgetWindow degreeStats(STATS_W, STATS_H, &g1, "Degree Statistics");

static clusteringStats g2(STATS_W,STATS_H); 
static widgetWindow clusteringStats(STATS_W,STATS_H,&g2,"Clustering Statistics"); 

static capitalVariation g3(STATS_W,STATS_H); 
static widgetWindow capitalVariation(STATS_W,STATS_H,&g3,"Capitale medio"); 

static simulationGrid glf(10,30,SIMULATION_WIDTH,SIMULATION_HIGH, &g1, &g2, &g3);  /* classe grafica  */

/************* Main Window *****************************************/
Fl_Double_Window *elanjaWindow=(Fl_Double_Window *)0;
/************* Play/Stop Buttons ***********************************/
Fl_Button *playButton=(Fl_Button *)0;

Fl_Button *stopButton=(Fl_Button *)0;
/************* Simulation Steps ************************************/
Fl_Value_Output *simStepLabel=(Fl_Value_Output *)0;
/************* Slider's Group **************************************/
Fl_Group *parametersGroup=(Fl_Group *)0;

Fl_Value_Slider *agentsSlider=(Fl_Value_Slider *)0;

Fl_Value_Slider *populationSlider=(Fl_Value_Slider *)0;

Fl_Value_Slider *epsilonSlider=(Fl_Value_Slider *)0;

Fl_Value_Slider *friendshipSlider=(Fl_Value_Slider *)0;

Fl_Value_Slider *numProductsSlider=(Fl_Value_Slider *)0;

Fl_Value_Slider *thresholdSlider=(Fl_Value_Slider *)0;

Fl_Value_Slider *simSpeedSlider=(Fl_Value_Slider *)0;
/************* Menu ************************************************/
Fl_Menu_Item menu_Visualizza[] = {
 {"File", 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 14, 0},
 {"Exit", 0,  (Fl_Callback*)exitCallback, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {"Simulation", 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 14, 0},
 {"@> Play", 0,  (Fl_Callback*)playCallback, (void*)(&glf), 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"@|> Restart", 0,  (Fl_Callback*)stopCallback, (void*)(&glf), 0, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {"View", 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 14, 0},
 {"Degree Statistics", 0, (Fl_Callback*)degreeStatsCallback, (void*)(&degreeStats), 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"Clustering Statistics", 0,  (Fl_Callback*)clusteringStatsCallback, (void*)(&clusteringStats), 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"Capitale medio", 0,  (Fl_Callback*)capitalVariationCallback, (void*)(&capitalVariation), 0, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0}
};


int main(int argc, char **argv) 
{
	glf.mode(FL_DOUBLE); /* glf è la nostra classe */
	{	
          /* Main Window */
	 	elanjaWindow = new Fl_Double_Window(WINDOW_WIDTH, WINDOW_HIGH, "Elanja");
		elanjaWindow->color(FL_LIGHT3);	
	     elanjaWindow->selection_color((Fl_Color)53);
      
    		{	/* Button's Group */ 
			Fl_Group* o = new Fl_Group(585, 660, 172, 65);
			{ 	/* Play Button */
				playButton = new Fl_Button(675, 695, 70, 30, "@>");
        			playButton->callback((Fl_Callback*)playCallback, (void*)(&glf));
      			} 
      			{	/* Stop Button */
				stopButton = new Fl_Button(595, 695, 70, 30, "@|>");
        			stopButton->callback((Fl_Callback*)stopCallback, (void*)(&glf));
	      		} 
      			{	/* Simulation Steps */
				simStepLabel = new Fl_Value_Output(585, 660, 172, 25, "Simulation step:");
        			simStepLabel->maximum(1e+06);
        			simStepLabel->align(FL_ALIGN_TOP_LEFT);
      			} 
      			o->end();
    		} 
		{	/* Parameters Group */
			parametersGroup = new Fl_Group(10, 535, 560, 190, "Parameters");
      			parametersGroup->box(FL_PLASTIC_UP_FRAME);
      			parametersGroup->color(FL_FOREGROUND_COLOR);
      			parametersGroup->align(FL_ALIGN_TOP_LEFT|FL_ALIGN_INSIDE);
			{ 	/* Agent Slider */
				agentsSlider = new Fl_Value_Slider(15, 570, 250, 35, "Agents");
        			agentsSlider->type(5);
        			//agentsSlider->box(FL_THIN_DOWN_BOX);/* Borders dimension */
        			agentsSlider->color((Fl_Color)10);/* Slider color */
        			agentsSlider->selection_color((Fl_Color)136);/* Cursor color */
        			agentsSlider->labelfont(1);
        			agentsSlider->labelsize(12);
				agentsSlider->minimum(2);
        			agentsSlider->maximum(AGENTS_MAX);
        			agentsSlider->step(2);
        			agentsSlider->value(AGENTS_INIT);
        			agentsSlider->callback((Fl_Callback*)agentsSliderCallback);
        			agentsSlider->align(FL_ALIGN_TOP_LEFT);/* Label align*/
      			}
      			{ 	/* Population Slider */
				populationSlider = new Fl_Value_Slider(15, 625, 250, 35, "% Nodes With Renewed Features");
        			populationSlider->type(5);
        			//populationSlider->box(FL_THIN_DOWN_BOX);
        			populationSlider->color((Fl_Color)10);
        			populationSlider->selection_color((Fl_Color)136);
				populationSlider->minimum(0.0);
        			populationSlider->maximum(1.0);
        			populationSlider->labelfont(1);
        			populationSlider->labelsize(12);
        			populationSlider->value(RHO_INIT);
				populationSlider->step(0.05);
        			populationSlider->callback((Fl_Callback*)populationSliderCallback);
        			populationSlider->align(FL_ALIGN_TOP_LEFT);
      			}
      			{	/* Epsilon Slider */
		 		epsilonSlider = new Fl_Value_Slider(290, 570, 250, 35, "Features");
        			epsilonSlider->type(5);
        			//epsilonSlider->box(FL_THIN_DOWN_BOX);
        			epsilonSlider->color((Fl_Color)10);
        			epsilonSlider->selection_color((Fl_Color)136);
        			epsilonSlider->labelfont(1);
        			epsilonSlider->labelsize(12);
        			epsilonSlider->minimum(2.0);
        			epsilonSlider->maximum(20.0);
        			epsilonSlider->step(1.0);
        			epsilonSlider->value(FEATURES_INIT);
        			epsilonSlider->callback((Fl_Callback*)epsilonSliderCallback);
        			epsilonSlider->align(FL_ALIGN_TOP_LEFT);
      			}
      			{	/* Friendship Slider */
				friendshipSlider = new Fl_Value_Slider(290, 625, 250, 35, "Max Number of Friends");
        			friendshipSlider->type(5);
			        //friendshipSlider->box(FL_THIN_DOWN_BOX);
			        friendshipSlider->color((Fl_Color)10);
			        friendshipSlider->selection_color((Fl_Color)136);
			        friendshipSlider->labelfont(1);
			        friendshipSlider->labelsize(12);
        			friendshipSlider->minimum(1);
			        friendshipSlider->maximum(40);
			        friendshipSlider->step(1);
			        friendshipSlider->value(FRIENDS_INIT);
			        friendshipSlider->callback((Fl_Callback*)friendshipSliderCallback);
			        friendshipSlider->align(FL_ALIGN_TOP_LEFT);
			}
      			{	/* Simulation Speed Slider */
				simSpeedSlider = new Fl_Value_Slider(290, 685, 250, 35, "Simulation Speed");
        			simSpeedSlider->type(5);
			        //simSpeedSlider->box(FL_THIN_DOWN_BOX);
			        simSpeedSlider->color((Fl_Color)10);
			        simSpeedSlider->selection_color((Fl_Color)136);
			        simSpeedSlider->labelfont(1);
			        simSpeedSlider->labelsize(12);
			        simSpeedSlider->minimum(0.001);
				simSpeedSlider->maximum(1.000);
			        simSpeedSlider->step(0.001);
			        simSpeedSlider->value(SIM_SPEED_INIT);
			        simSpeedSlider->callback((Fl_Callback*)simSpeedSliderCallback);
			        simSpeedSlider->align(FL_ALIGN_TOP_LEFT);      
			}
			{	/* Threshold Slider */
				thresholdSlider = new Fl_Value_Slider(15, 685, 250, 35, "Threshold");
        			thresholdSlider->type(5);
			        //thresholdSlider->box(FL_THIN_DOWN_BOX);
			        thresholdSlider->color((Fl_Color)10);
			        thresholdSlider->selection_color((Fl_Color)136);
			        thresholdSlider->labelfont(1);
			        thresholdSlider->labelsize(12);
			        thresholdSlider->minimum(-1.0);
				thresholdSlider->maximum(1.0);
			        thresholdSlider->step(0.05);
			        thresholdSlider->value(THRESHOLD_INIT);
			        thresholdSlider->callback((Fl_Callback*)thresholdSliderCallback);
			        thresholdSlider->align(FL_ALIGN_TOP_LEFT);     
			}
      			parametersGroup->end();
		}
		{	/* Menu */
			Fl_Menu_Bar* o = new Fl_Menu_Bar(0, 0, 925, 20, "View");
      			o->menu(menu_Visualizza);
		}
    		elanjaWindow->add(glf);
    		elanjaWindow->resizable(&glf);
    		elanjaWindow->end();
	}
	elanjaWindow->show(argc, argv); /* fammela vedere */
	return Fl::run(); /* se modifica qualcosa ridisegna...  */
}
static int x; /* ? */
