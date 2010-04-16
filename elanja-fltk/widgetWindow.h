#ifndef WIDGET_WINDOW
#define WIDGET_WINDOW

#include "elanja-fltk.h"

class widgetWindow : public Fl_Double_Window
{
public:
	widgetWindow(int x, int y,int w, int h, const char *label = 0);
	widgetWindow(int w, int h, const char *label = 0);
};


#endif
