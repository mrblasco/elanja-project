#include "simulationGrid.h"
#include "const.h"

#define MAX(a,b)	(a>b?a:b)
#define MIN(a,b)	(a<b?a:b)

/* Graphical User Interface */
extern int gui_linear_lattice_dimension;  
extern double gui_delta; 
extern int gui_pos_traits ; 
extern double gui_threshold; 
extern bool latticeOn;
extern bool kleinbergOn;
extern bool linkVisualization;

extern bool restart; 
extern bool restartB;
extern double simSpeed;
extern model m;   /* object of class 'model' is called 'm' */

bool initModel=true;
int W,H;

simulationGrid::simulationGrid(int x,int y,int w, int h, regionStats *g1, const char *l):Fl_Gl_Window(x,y,w,h,l)  
{

	restart = false; 

     	/* Add statistics windows */
	this->g1 = g1;

	W=w;
	H=h;
}

void simulationGrid::init(){ 

	int i;	

	/* Initialize random number generator's seed to the current time */
	srand(time(NULL));
	
     	/* Initialize Simulation Grid */ 
	valid(1);
	glLoadIdentity(); 
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glMatrixMode (GL_PROJECTION);     
	glLoadIdentity();
	glOrtho(0, w(), 0, h(), -100, 100);                
	glMatrixMode (GL_MODELVIEW);
	glColor4d(0.2,0,1,0.2); 	

	
	/* Initial Parameters */
	gui_linear_lattice_dimension = LINEAR_LATTICE_DIMENSION_INIT;  
	gui_delta = DELTA_INIT;
	gui_pos_traits  = POS_TRAITS_INIT;
	simSpeed = SIM_SPEED_INIT;
	

	if(initModel && latticeOn)
	{ 
		m.init(LINEAR_LATTICE_DIMENSION_INIT, AGENTS, NFEATURES, POS_TRAITS_INIT, OUTDEGREE, DELTA_INIT,1);   
		initModel=false;
		restart = false; 
	}
	else if(initModel && kleinbergOn)
	{ 
		m.init(LINEAR_LATTICE_DIMENSION_INIT, AGENTS, NFEATURES, POS_TRAITS_INIT, OUTDEGREE, DELTA_INIT,0);   
		initModel=false; 
		restart = false;
	}
	else
	{		
		restart = true;
	}
	
}

void simulationGrid::draw() {	

	int i, j, k, tmpAgents;
	
	/* Grafic Initialization */
	if (!valid())
	{
		init(); 
	}
	
	/* If Restart Button is pressed */
	if(restartB)
	{
		tmpAgents = gui_linear_lattice_dimension*gui_linear_lattice_dimension;
     		m.init(gui_linear_lattice_dimension, tmpAgents, NFEATURES, gui_pos_traits, OUTDEGREE, gui_delta, m.maxSide);         
		restartB = false;
		simStepLabel->value(0);
		restart = false;
	}	
	/* Catch parameters from gui and reinit if needed */
	else if((m.delta != gui_delta) || (m.pos_traits != gui_pos_traits ) || (m.linear_lattice_dimension != gui_linear_lattice_dimension) || restart )
	{
		tmpAgents = gui_linear_lattice_dimension*gui_linear_lattice_dimension;
		if(latticeOn)
		{
     			m.init(gui_linear_lattice_dimension, tmpAgents, NFEATURES, gui_pos_traits, OUTDEGREE, gui_delta, 1);
		}
		else
		{
			m.init(gui_linear_lattice_dimension, tmpAgents, NFEATURES, gui_pos_traits, OUTDEGREE, gui_delta, 0);
		}         
		restart = false;
	}

	/* Clear display */
	glClear(GL_COLOR_BUFFER_BIT);
	if(linkVisualization)
	{	
		for (i=0;i<m.agents;i++)
		{
			link(i);
		}
	}

	/* Draws all Agents */
	for(i=0; i<m.agents;i++)
	{
		drawAgents(i);
	}

	/* Simulation Step */
	m.step();

	/* Compute Regions */
	computeRegions();

	g1->redraw();
}

void drawAgents(int i){
	int k, x;		 	

	glColor4d((double)(1+m.feature[i*m.nFeatures + 0])/(double)m.pos_traits,(double)(1+m.feature[i*m.nFeatures + 1])/(double)m.pos_traits,(double)(1+m.feature[i*m.nFeatures + 2])/(double)m.pos_traits,1.0);
	 
	square(m.x[i], m.y[i],20);
}

void timer_cb(void *p) 
{
	simulationGrid *glf = (simulationGrid*)p; 

	if(doNextSimulationStep){
		glf->redraw();
		simStepLabel->value(pippo);
		Fl::repeat_timeout((simSpeed),timer_cb,p);
	}
}

void square(double x, double y, double edge){
	double a, da;
	
	glBegin(GL_TRIANGLE_FAN);
		glVertex2d(x-(edge/2), y+(edge/2));
		glVertex2d(x+(edge/2), y+(edge/2));
		glVertex2d(x+(edge/2), y-(edge/2));
		glVertex2d(x-(edge/2), y-(edge/2));
	glEnd();
}

void link(int i)
{	
	int j, k, z;

	glColor4d(0.9,0.0,1.0,0.2);
	for(j=0; j<m.outdegree;j++)
	{
		glBegin(GL_LINES);
			glVertex2d(m.x[i], m.y[i]);
			glVertex2d(m.x[m.Nlist[i*m.outdegree+j]],m.y[m.Nlist[i*m.outdegree+j]]);	
		glEnd();	
	}
}



