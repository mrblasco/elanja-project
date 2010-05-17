#ifndef GL_STATS
#define GL_STATS

#include <FL/gl.h>
#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>

class glStats : public Fl_Gl_Window
{
public:
	glStats(int w,int h,const char *l=0);
protected:
	void draw();
	virtual void paint();
};

#endif
