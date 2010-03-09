#include <fltk/run.h>
#include <fltk/Window.h>
#include <fltk/Widget.h>
#include <fltk/Button.h>
#include <fltk/CheckButton.h>
#include <fltk/math.h>
#include <fltk/draw.h>
#include <fltk/string.h> // for snprintf
#include <fltk/gl.h>
#include <fltk/compat/FL/Fl.H>
#include <fltk/compat/FL/Fl_Gl_Window.H>
#include <fltk/compat/FL/fl_draw.H>
//#include <fltk/compat/Fl_Int_Input.H>
#include <fltk/compat/FL/Fl_Slider.H>
#include <fltk/compat/FL/Fl_Value_Slider.H>
#include <fltk/compat/FL/Fl_Value_Output.H>
#include <fltk/Slider.h>
#include <fltk/math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../h/const.h"

using namespace fltk;

class ShapeWidget : public Widget {
  int agents_;
  double population_;

  void draw() {
	double i, j;
	int k=0;

  int l;

  //Random initialization of degree and composition (to be changed when the file is inserted in the project)
  srand(time(NULL));
 
  int degree[500];
  for(l=0; l<500; l++) {
	degree[l] = (int) ((rand() %100) + 1);
	}

  double composition[500];
  for(l=0; l<500; l++) {
	composition[l] = (double) (rand() %100 + 1) / 100;;
	}

   //Draw agents
   setcolor(BLACK);
   fillrect(0,0,w(),h());

	for(i=1; i<=2*sqrt(agents()); i=i+2){
		for(j=1; j<=2*sqrt(agents()); j=j+2){
			if (k<0.5*agents()) {fl_color(255,(int)94*exp(composition[k]),0);} else {fl_color(0,(int)94*exp(composition[k]),255);}
			fl_arc(0.5*sqrt((w()*w())/agents())*i, 0.5*sqrt((w()*w())/agents())*j, 1.5*sqrt(degree[k]),0,360);
 			fillstrokepath(BLACK);
			k++;
		}
	}
  }

public:

  inline int agents() const {return agents_;}
  inline double population() const {return population_;}

  void agents(int n) {
    if (agents_ != n) {agents_ = n; redraw();}
  }

  void population(double m) {
    if (population_ != m) {population_ = m; redraw();}
  }

  ShapeWidget(int x,int y,int w,int h,const char *l=0) :
    Widget(x,y,w,h,l), agents_(100), population_(0.5) {}

};

static void slider_callback(Widget* widget, void* data) {
  ((ShapeWidget*)data)->agents(int(((Slider*)widget)->value()));
}

static void slider_callback2(Widget* widget, void* data) {
  ((ShapeWidget*)data)->population(double(((Slider*)widget)->value()));
}

int main(int argc, char **argv) {

  Window window(1000, 690);
  window.begin();

  ShapeWidget sw(5, 5, 680, 680);
  window.resizable(&sw); 

  Fl_Value_Slider slider(690, 20, window.w()-690, 50, "Agents");
  slider.type(7);
  slider.box(FL_EMBOSSED_BOX);
  slider.color((Fl_Color)246);
  slider.selection_color((Fl_Color)103);
  slider.labelfont(HELVETICA_BOLD);
  slider.labelsize(14);
  slider.maximum(500);
  slider.minimum(100);
  slider.step(2);
  slider.value(100);
  slider.callback(slider_callback, &sw);
  slider.align(FL_ALIGN_TOP_LEFT);
  //vorrei avere come possibili valori solo 100,144,196,256,324,400,484 (perchè sono quadrati di numeri interi)
  
  Fl_Value_Slider slider2(690, 100, window.w()-690, 50, "Population");
  slider2.type(7);
  slider2.box(FL_EMBOSSED_BOX);
  slider2.color((Fl_Color)246);
  slider2.selection_color((Fl_Color)103);
  slider2.labelfont(HELVETICA_BOLD);
  slider2.labelsize(14);
  slider2.maximum(1);
  slider2.minimum(0);
  slider2.step(0.1);
  slider2.value(0.5);
  slider2.callback(slider_callback2, &sw);
  slider2.align(FL_ALIGN_TOP_LEFT);
	
  Fl_Value_Slider slider3(690, 180, window.w()-690, 50, "Epsilon interaction");
  slider3.type(7);
  slider3.box(FL_EMBOSSED_BOX);
  slider3.color((Fl_Color)246);
  slider3.selection_color((Fl_Color)103);
  slider3.labelfont(HELVETICA_BOLD);
  slider3.labelsize(14);
  slider3.maximum(1);
  slider3.minimum(0);
  slider3.step(0.1);
  //slider3.value();
  //slider3.callback(slider_callback, &sw);
  slider3.align(FL_ALIGN_TOP_LEFT);

  Fl_Value_Slider slider4(690, 260, window.w()-690, 50, "Friendship");
  slider4.type(7);
  slider4.box(FL_EMBOSSED_BOX);
  slider4.color((Fl_Color)246);
  slider4.selection_color((Fl_Color)103);
  slider4.labelfont(HELVETICA_BOLD);
  slider4.labelsize(14);
  slider4.maximum(1);
  slider4.minimum(0);
  slider4.step(0.1);
  //slider4.value();
  //slider4.callback(slider_callback, &sw);
  slider4.align(FL_ALIGN_TOP_LEFT);

  CheckButton checkbutton(690, 320, 50, 50, "Small perturbation");
  checkbutton.clear_flag(ALIGN_MASK);
  checkbutton.set_flag(ALIGN_RIGHT);
  checkbutton.labelsize(14);
  checkbutton.labelfont(HELVETICA_BOLD);
  //inserire callback

  //Da rifare
  /*Button button1(800, 380, 30, 30, "1");
  Button button2(850, 380, 30, 30, "2");*/

  Fl_Value_Output interations(695, 600, 300, 30, "Number of steps");
  interations.maximum(1e+06);
  interations.clear_flag(ALIGN_MASK);
  interations.set_flag(ALIGN_TOP);
  interations.labelsize(14);
  interations.labelfont(HELVETICA_BOLD);

  Button button3(740, 650, 80, 30, "@> Play");
  Button button4(870, 650, 80, 30, "@>| Restart");
  //callback

  window.end();
  window.show(argc,argv);
    
  return run();
}

