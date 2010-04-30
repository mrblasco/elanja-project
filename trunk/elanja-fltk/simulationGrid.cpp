#include "simulationGrid.h"
#include "const.h"

extern int gui_agents; /* graphical user interface ... gui => agenti modificati dalla barra */
extern int gui_distance;
extern double gui_population;
extern double gui_epsilon;

extern double gui_friendship;
extern bool restart;
extern double simSpeed;
extern model m; /* chiami clase model -> m */

bool initModel=true;
int W,H;

simulationGrid::simulationGrid(int x,int y,int w,int h, const char *l):Fl_Gl_Window(x,y,w,h,l)  /*invoca costruttore FLGLWINDOW*/
{
/*	grow = true; */
	restart = true; 
	W=w;
	H=h;
}

void simulationGrid::init(){ 
     /* initializza la simulation grid */ 
	valid(1); /*valido?*/
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
	gui_population = (AGENTS_INIT / 2);
	gui_epsilon = EPSILON_INIT;
	gui_friendship = SAMPLE_INIT;
	
	simSpeed = SIM_SPEED_INIT;
	
if(initModel){ 
		m.init(AGENTS_INIT, DISTANCE_INIT, FRACTION_INIT, EPSILON_INIT, SAMPLE_INIT);  /* chiama la classe model , metodo init()*/ 
		initModel=false; 
	}else{		
		restart = true;
	}
}

void simulationGrid::draw() {	 /*metodo draw ... per disegnare le palline*/
	int i, j;
	
	/*inizializzazione grafica */
	if (!valid())
		init(); 
	
   if (restart)
		m.reinit(gui_agents,gui_distance, gui_population, gui_epsilon, gui_friendship);   
	
	/* passa al modello i parametri presi dalla gui  e reiinit  */
	if(m.agents != gui_agents || m.population != gui_population || m.epsilon != gui_epsilon)
		m.reinit(gui_agents,gui_distance, gui_population, gui_epsilon, gui_friendship); 

	/*m.agents = gui_agents;
	m.population = gui_population;
	m.epsilon = gui_epsilon;*/

	/* cancella il display */
	glClear(GL_COLOR_BUFFER_BIT);
	
	/* passo di simulazione */
	m.step();

	for(i=0; i<m.agents; i++)
	{		
		drawAgents(i);	
	}
}

void drawAgents(int i){
	int k, j;		 	

	if ( i < m.m ) /*modello. m = perc tipo ... */
	{
          /* rosso, green, blue, opacity */
		glColor4d(1 - m.composition[i], 0, m.composition[i],0.7);
          /* position_x, position_ y, size */
		//circle(rand() % (745/2 - 10) +10, rand() % (490) + 10, 3.0 * (double) sqrt(m.degree[i]));
	}
	if (i>=m.m)
	{
          /* rosso, green, blue, opacity */
		glColor4f(m.composition[i],0,(1-m.composition[i]),0.7);
		circle((745/2 +10) + (rand() % (745/2 - 20)), rand() % (490) + 10, 3.0 * (double) sqrt(m.degree[i]));
	}

	restart = false;
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

