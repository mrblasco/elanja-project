#include "simulationGrid.h"
#include "const.h"

/* Graphical User Interface */
extern int gui_agents;  
extern int gui_distance; 
extern double gui_rho; /* fraction of a-type people over population*/
extern int gui_nFeatures; /* inherited fracion of links  */
extern int gui_friends; /*  fraction of population met in one iteration */
extern double gui_threshold; 

extern bool restart; 
extern double simSpeed;
extern model m;   /* object of class 'model' is called 'm' */

bool initModel=true;
int W,H;

/*invoca costruttore FL_GL_WINDOW*/
simulationGrid::simulationGrid(int x,int y,int w, int h, degreeStats *g1, clusteringStats *g2, capitalVariation *g3, const char *l):Fl_Gl_Window(x,y,w,h,l)  
{
/*	grow = true; */
	restart = false; 
     /* aggiunge le finestre con le statistiche*/
	this->g1 = g1;
	this->g2 = g2;
	this->g3 = g3;
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
	glColor4d(0.2,0,1,0.2); 	

	
	/* parametri iniziali */
	gui_agents = AGENTS_INIT;  
	gui_distance = DISTANCE_INIT;
	gui_rho = RHO_INIT;
	gui_nFeatures = FEATURES_INIT;
	gui_friends = FRIENDS_INIT;
	gui_threshold = THRESHOLD_INIT;
	simSpeed = SIM_SPEED_INIT;
	
	if(initModel)
	{ 
		m.init(AGENTS_INIT,  RHO_INIT, FEATURES_INIT, 0.2, FRIENDS_INIT, w(), h());   
		initModel=false; 
	}
	else
	{		
		restart = true;
	}
}

void simulationGrid::draw() {	
	int i, j, k;
	
	/*inizializzazione grafica */
	if (!valid())
		init(); 
	
	/* passa al modello i parametri presi dalla gui  e reinit  */
	if((m.agents != gui_agents) || (m.rho != gui_rho) || (m.nFeatures != gui_nFeatures) ||  (m.threshold != gui_threshold)||  (m.friends != gui_friends) )
     		m.reinit(gui_agents,  gui_rho,  gui_nFeatures, gui_threshold, gui_friends, w(), h());         


	/* cancella il display */
	glClear(GL_COLOR_BUFFER_BIT);
     for (i=0;i<m.agents;i++)
     {
               for (j=0;j<m.agents;j++)
               {
                    if(m.A[i*m.agents +j]==1)
                    {               
                         link(m.x[i],m.y[i],m.x[j],m.y[j]);
                    }
               }
     }

	/* Draw all Agents */
	for(i=0; i<m.agents;i++)
	{
		drawAgents(i);
	}

	/* passo di simulazione */
	printf("Dimensioni simulation grid: w = %d, h = %d\n", w(), h());
	m.step(w(), h());

	g1->redraw();
	g2->redraw();
	g3->redraw();

}

void drawAgents(int i){
	int k, x;		 	
	

	/* rosso, green, blue, opacity */
	glColor4d(1- m.features[0*m.agents + i],m.features[1*m.agents + i],m.features[2*m.agents + i],0.8);
	 
	circle(m.x[i], m.y[i],2+ m.degree[i]);
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

void link(double x, double y, double xx, double yy)
{	

	glColor4d(0.9,0.0,1.0,0.2); 	
	glBegin(GL_LINES);
		glVertex2d(x, y);
		glVertex2d(xx,yy);	
	glEnd();
}

