#include "widgetWindow.h"

widgetWindow::widgetWindow(int w, int h, glStats *graphic1, const char *label):Fl_Double_Window(w,h,label)
{
	this->add(graphic1);	
}

widgetWindow::widgetWindow(int x,int y,int w, int h, glStats *graphic1, const char *label):Fl_Double_Window(x,y,w,h,label)
{
	this->add(graphic1);	
}
