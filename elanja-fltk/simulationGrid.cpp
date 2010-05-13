#include "simulationGrid.h"
#include "const.h"

/* Graphical User Interface */
extern int gui_agents;  
extern int gui_distance; 
extern double gui_rho; /* fraction of a-type people over population*/
extern double gui_epsilon; /* inherited fracion of links  */
extern double gui_friendship; /*  fraction of population met in one iteration */

extern bool restart; 
extern double simSpeed;
extern model m;   /* object of class 'model' is called 'm' */

bool initModel=true;
int W,H;

/*invoca costruttore FL_GL_WINDOW*/
simulationGrid::simulationGrid(int x,int y,int w,int h, const char *l):Fl_Gl_Window(x,y,w,h,l)  
{
/*	grow = true; */
	restart = false; 
	W=w;
	H=h;
}

void simulationGrid::init(){ 
     /* initializza la simulation grid */ 
	valid(1); /*valido <=> grid inizializzata*/
	glLoadIdentity(); 
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glMatrixMode (GL_PROJECTION);     
	glLoadIdentity();
	glOrtho(0, w(), 0, h(), -100, 100);                
	glMatrixMode (GL_MODELVIEW);
	
	/* parametri iniziali */
	gui_agents = AGENTS_INIT;  
	gui_distance = DISTANCE_INIT;
	gui_rho = RHO_INIT;
	gui_epsilon = EPSILON_INIT;
	gui_friendship = SAMPLE_INIT;
	simSpeed = SIM_SPEED_INIT;
	
	if(initModel)
	{ 
		m.init(AGENTS_INIT, DISTANCE_INIT, RHO_INIT , EPSILON_INIT, SAMPLE_INIT);   
		initModel=false; 
	}
	else
	{		
		restart = true;
	}
}

void simulationGrid::draw() {	
	int i, j;
	
	/*inizializzazione grafica */
	if (!valid())
		init(); 
	
	/* passa al modello i parametri presi dalla gui  e reinit  */
	if((m.agents != gui_agents) || (m.rho != gui_rho) || (m.epsilon != gui_epsilon))
     		m.reinit(gui_agents,gui_distance, gui_rho, gui_epsilon, gui_friendship);         

	/* cancella il display */
	glClear(GL_COLOR_BUFFER_BIT);
	
	for(i=0; i<m.agents; i++)
	{		
		drawAgents(i);	
	}

	/* passo di simulazione */
	m.step();

}

void drawAgents(int i){
	int k, j;		 	

	if (i < m.m ) 
	{
          /* rosso, green, blue, opacity */
		glColor4d(1 - m.composition[i], 0, m.composition[i],0.7);
          /* position_x, position_ y, size */
		circle(rand() % (745/2 - 10) +10, rand() % (490) + 10, 3.0 * (double) sqrt(m.degree[i]));
	}
	if (i >= m.m)
	{
          /* rosso, green, blue, opacity */
		glColor4f(m.composition[i],0,(1-m.composition[i]),0.7);
		circle((745/2 +10) + (rand() % (745/2 - 20)), rand() % (490) + 10, 3.0 * (double) sqrt(m.degree[i]));
	}
}

void timer_cb(void *p) /*delay tra step e altro*/
{
	simulationGrid *glf = (simulationGrid*)p; 

	if(doNextSimulationStep){
		glf->redraw();
		simStepLabel->value(t);
		Fl::repeat_timeout((simSpeed),timer_cb,p);
	}
}

void circle(double x, double y, double radius){
	double a, da;
	
	da = 2.0 * asin(1.0/radius);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(x, y);
	for(a = 0.0; a <= 2 * M_PI; a += da) {
		glVertex2d(x + cos(a) * radius, y + sin(a) * radius);
	}

	glVertex2d(x + radius, y);
	glEnd();
}

