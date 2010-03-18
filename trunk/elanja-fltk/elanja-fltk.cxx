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

class ShapeWidget : public Widget
{

	int agents_;
	int *degree_;    
	double *composition_;
	int m_;


	void draw()
	{
		int l, k;


		for(k=0; k<agents(); k++)
		{
			*(degree_ + k) = rand() %100 +1;
		}

		setcolor(BLACK); // sfondo
		fillrect(0,0,w(),h());

		for(k=0;k<agents();k++) {
			if (k<(m()*agents())/100) 
			{
				fl_color(255,(int)94*exp(*(composition_ + k)),0);
			} 
			else 
			{
				fl_color(0,(int)94*exp(*(composition_ + k)),255);
			}
			fl_arc(rand() %(w()-20) +10, rand() %(w()-20) +10 , 1.5*sqrt( *(degree_ + k) ),0,360);
			fillstrokepath(BLACK);
		}

	}

public:

	inline int agents() const {return agents_;} /* attributo inline ... riferito alla classe... */
	inline int m() const{return m_;}

	void agents(int n)
	{
		int l;
		if (agents_ != n)
		{
		    agents_ = n;

		    free(degree_);
		    degree_ = (int*) malloc(sizeof(int)*agents_);
		    composition_ = (double*) malloc(sizeof(double)*agents_);
		    for(l=0; l<n; l++)
		    {
			*(degree_+l) = 10;
			*(composition_+l) = 1;
		    }
		redraw();
		}
	}

	void m(int n)
	{
		if (m_ != n)	
			m_ = n;
		
		redraw();
	}

	/* Constructor */
	ShapeWidget(int x, int y, int w, int h, int  agents, int *degreeVect, double *compVector, int m, const char *l=0) : Widget(x,y,w,h,l), agents_(agents), degree_(degreeVect), composition_(compVector), m_(m) {}
};

static void slider_callback(Widget* widget, void* data)
{
	((ShapeWidget*)data) -> agents(int( ( (Slider*)widget)-> value()));
}

static void slider_callback2(Widget* widget, void* data)
{
	((ShapeWidget*)data)->m(int(((Slider*)widget)->value()));
}

static void play_callback(Widget* widget, void* data)
{
	int t;
	for(t=0; t<20000; t++)
	{
		ShapeWidget pippo;
		pippo.draw();
	}
}

int main(int argc, char **argv) {

	int l, i, j;
	int agents = 100;
	int m = agents/2;

	double *p = (double*) malloc ((sizeof(double))*agents);
	double *q = (double*) malloc(sizeof(double)*agents);
	double *R = (double*) malloc(sizeof(double)*agents*agents);

	int *A = (int*) malloc(sizeof(int)*agents*agents);
	int *B = (int*) malloc(sizeof(int)*agents*agents);

	int *degree = (int*) malloc(sizeof(int)*agents);
	int *A_degree = (int*) malloc(sizeof(int)*agents);
	int *B_degree = (int*) malloc(sizeof(int)*agents);
	double *composition = (double*) malloc(sizeof(double)*agents);

	/* Initialize random number generator's seed to the current time */
	srand(time(NULL));

	/* Initialize degree vectors */
	for(l=0; l<agents; l++)
	{
		degree[l] = 30;
		A_degree[l] = 10;
		B_degree[l] = 10;
		
	}

	/* Initialize meeting probability vectors */
	for(i=0; i<agents; i++)	
	{
		p[i] = 0.0; 
		q[i] = 0.0;
	}

	/* Initialize composition vector */
	for(i=0; i<agents; i++)
	{
		if(i < m)
		{
			composition[i] = A_degree[i]/degree[i];
		}
		else
		{
			composition[i] = B_degree[i]/degree[i];
		}
	}


	Window window(1000, 690);
	window.begin();

	ShapeWidget sw(5, 5, 680, 680, agents, degree, composition, m);
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
	slider.value(agents);
	slider.callback(slider_callback, &sw);
	slider.align(FL_ALIGN_TOP_LEFT);
	

	Fl_Value_Slider slider2(690, 100, window.w()-690, 50, "Population (%)");
	slider2.type(7);
	slider2.box(FL_EMBOSSED_BOX);
	slider2.color((Fl_Color)246);
	slider2.selection_color((Fl_Color)103);
	slider2.labelfont(HELVETICA_BOLD);
	slider2.labelsize(14);
	slider2.maximum(100);
	slider2.minimum(0);
	slider2.step(1);
	slider2.value(50);
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

	Button playButton(740, 650, 80, 30, "@> Play");
	playButton.callback(play_callback, &sw);
	Button restartButton(870, 650, 80, 30, "@>| Restart");
	//callback

	window.end();
	window.show(argc,argv);

	return run();
}
