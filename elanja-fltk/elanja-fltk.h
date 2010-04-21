// generated by Fast Light User Interface Designer (fluid) version 1.0109

#ifndef economy5_h
#define economy5_h
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
extern Fl_Double_Window *elanjaWindow;

#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
extern void playCallback(Fl_Button*, void*);
extern Fl_Button *playButton;

extern void stopCallback(Fl_Button*, void*);
extern Fl_Button *stopButton;

#include <FL/Fl_Value_Output.H>
extern Fl_Value_Output *simStepLabel;
extern Fl_Group *parametersGroup;

#include <FL/Fl_Value_Slider.H>
extern void agentsSliderCallback(Fl_Value_Slider*, void*);
extern Fl_Value_Slider *agentsSlider;

extern void populationSliderCallback(Fl_Value_Slider*, void*);
extern Fl_Value_Slider *populationSlider;

extern void epsilonSliderCallback(Fl_Value_Slider*, void*);
extern Fl_Value_Slider *epsilonSlider;

extern void friendshipSliderCallback(Fl_Value_Slider*, void*);
extern Fl_Value_Slider *friendshipSlider;

extern void simSpeedSliderCallback(Fl_Value_Slider*, void*);
extern Fl_Value_Slider *simSpeedSlider;

#include <FL/Fl_Check_Button.H>
extern void perturbationCallback(Fl_Check_Button*, void*);
extern Fl_Check_Button *perturbationButton;

extern void hubsCallback(Fl_Check_Button*, void*);
extern Fl_Check_Button *hubsButton;

#include <FL/Fl_Menu_Bar.H>
extern void exitCallback(Fl_Menu_*, void*);
extern void playCallback(Fl_Menu_*, void*);
extern void stopCallback(Fl_Menu_*, void*);
extern void priceGeneticsCallback(Fl_Menu_*, void*);
extern void capitalDistributionCallback(Fl_Menu_*, void*);
extern void capitalVariationCallback(Fl_Menu_*, void*);
extern Fl_Menu_Item menu_Visualizza[];
#define playItem (menu_Visualizza+4)
#endif