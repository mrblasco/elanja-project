#include "simulationGrid.h"

extern double gui_agents;
extern double gui_population;
extern double gui_epsilon;

extern int gui_friendship;

extern bool restart;
extern double simSpeed;

extern model m;

bool initModel=true;
int W,H;

simulationGrid::simulationGrid(int x,int y,int w,int h, const char *l):Fl_Gl_Window(x,y,w,h,l) 
{
	grow = true;
	restart = true;
	W=w;
	H=h;
}

void simulationGrid::init(){ 
	valid(1);
	glLoadIdentity();
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glMatrixMode (GL_PROJECTION);     
	glLoadIdentity();
	glOrtho(0, w(), 0, h(), -100, 100);                
	glMatrixMode (GL_MODELVIEW);
	
	// parametri iniziali
	gui_agents = LAMBDA_INIT;
	gui_population = G_COEF_INIT;
	gui_epsilon = C_EXP_INIT;
	gui_friendship = NUM_AGENTS_INIT;
	
	simSpeed = SIM_SPEED_INIT;
	
	if(initModel){
		m.init(10, 1, 50.0, 0.5, 1);
		initModel=false;
	}else{		
		restart = true;
	}
}

void simulationGrid::draw() {	
	int i,j;
	
	//inizializzazione grafica
	if (!valid())
		init();
	
	if (restart)
		m.reinit(gui_agents, gui_population, gui_epsilon, gui_friendship);
	
	// passa al modello i parametri presi dalla gui
	if(m.agents != gui_agents || m.m != gui_population)
		m.reinit(gui_agents, gui_population, gui_epsilon, gui_friendship);

	m.agents = gui_agents;
	m.population = gui_population;
	m.epsilon = gui_epsilon;

	// svuota il display
	glClear(GL_COLOR_BUFFER_BIT);
	
	// passo di simulazione
	m.step();

	for(i=0; i<m.agents; i++)
	{		
		drawAgents(i);	
	}
}

void drawAgents(int i){
	int k, j;		 	

	if (i<m.m)
	{
		glColor4d(1.0,m.composition[i],0.0,0.7);/* La quarta componente e' l'opacita' */
		circle(rand() % (745/2 - 10) +10, rand() % (490) + 10, 3.0 * (double) sqrt(m.degree[i]));
	}
	if (i>=m.m)
	{
		glColor4f(m.composition[i],0.0,1.0,0.7);/* La quarta componente e' l'opacita' */
		circle((745/2 +10) + (rand() % (745/2 - 20)), rand() % (490) + 10, 3.0 * (double) sqrt(m.degree[i]));
	}

	restart = false;
}

void timer_cb(void *p) 
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

