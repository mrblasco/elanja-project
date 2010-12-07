#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
extern Fl_Double_Window *elanjaWindow;

#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
extern void playCallback(Fl_Button*, void*);
extern Fl_Button *playButton;

extern void restartCallback(Fl_Button*, void*);
extern Fl_Button *restartButton;

#include <FL/Fl_Value_Output.H>
extern Fl_Value_Output *simStepLabel;
extern Fl_Group *parametersGroup;

#include <FL/Fl_Value_Slider.H>
extern void agentsSliderCallback(Fl_Value_Slider*, void*);
extern Fl_Value_Slider *agentsSlider;

extern void deltaSliderCallback(Fl_Value_Slider*, void*);
extern Fl_Value_Slider *populationSlider;

extern void pos_traitsSliderCallback(Fl_Value_Slider*, void*);
extern Fl_Value_Slider *epsilonSlider;

extern void simSpeedSliderCallback(Fl_Value_Slider*, void*);
extern Fl_Value_Slider *simSpeedSlider;

#include <FL/Fl_Check_Button.H>
extern void latticeCallback(Fl_Check_Button*, void*);
extern Fl_Check_Button *latticeButton;

extern void kleinbergCallback(Fl_Check_Button*, void*);
extern Fl_Check_Button *kleinbergButton;

#include <FL/Fl_Menu_Bar.H>
extern void exitCallback(Fl_Menu_*, void*);
extern void playCallback(Fl_Menu_*, void*);
extern void stopCallback(Fl_Menu_*, void*);
extern Fl_Menu_Item menu_Visualizza[];
#define playItem (menu_Visualizza+4)

