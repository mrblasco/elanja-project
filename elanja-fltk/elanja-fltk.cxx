#include <fltk/run.h>
#include <fltk/Window.h>
#include <fltk/Widget.h>
#include <fltk/Slider.h>
#include <fltk/math.h>
#include <fltk/draw.h>
#include <fltk/string.h> // for snprintf
#include <fltk/gl.h>
#include <fltk/compat/FL/Fl.H>
#include <fltk/compat/FL/Fl_Gl_Window.H>
#include <fltk/compat/FL/fl_draw.H>
#include <fltk/math.h>
#include "../h/const.h"

using namespace fltk;

class ShapeWidget : public Widget {
  int sides_;

  void draw() {
	int i, j;

   setcolor(WHITE);
   fillrect(0,0,w(),h());

	for(i=1; i<=sides_; i++){
		for(j=1; j<=sides_; j++){
			setcolor(BLACK);
			fl_arc(31*i, 31*j, 7, 0, 360);
 			fillstrokepath(WHITE);
		}
	}
	
  }

public:

  inline int sides() const {return sides_;}

  void sides(int n) {
    if (sides_ != n) {sides_ = n; redraw();}
  }

  ShapeWidget(int x,int y,int w,int h,const char *l=0) :
    Widget(x,y,w,h,l), sides_(3) {}

};

static void slider_callback(Widget* widget, void* data) {
  ((ShapeWidget*)data)->sides(int(((Slider*)widget)->value()));
}

int main(int argc, char **argv) {

  Window window(500, 500);
  window.begin();

  ShapeWidget sw(10, 10, 480, 480);
  window.resizable(&sw);

  Slider slider(50, 295, window.w()-60, 30, "Sides:");
  slider.clear_flag(ALIGN_MASK);
  slider.set_flag(ALIGN_LEFT);
  slider.callback(slider_callback, &sw);
  slider.value(sw.sides());
  slider.step(1);
  slider.range(3,40);



  window.end();
  window.show(argc,argv);
    
  return run();
}

