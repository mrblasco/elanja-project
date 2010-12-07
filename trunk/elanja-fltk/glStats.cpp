#include "glStats.h"

glStats::glStats(int w,int h,const char *l):Fl_Gl_Window(0,0,w,h,l){

}

void glStats::draw(){

	if (!valid()) {
		
		/* Graphic Initialization do not change */
		valid(1);
		glLoadIdentity();
		glEnable(GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glMatrixMode (GL_PROJECTION);     
		glLoadIdentity();
		glOrtho(0, w(), 0, h(), -100, 100);                
		glMatrixMode (GL_MODELVIEW);
	}

	this->paint();

}

void glStats::paint(){

}
