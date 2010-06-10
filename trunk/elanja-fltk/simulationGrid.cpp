#include "simulationGrid.h"
#include "const.h"

/* Graphical User Interface */
extern int gui_agents;  
extern int gui_distance; 
extern double gui_rho; /* fraction of a-type people over population*/
extern int gui_nFeatures; /* inherited fracion of links  */
extern double gui_friendship; /*  fraction of population met in one iteration */
extern double gui_threshold; 

extern bool restart; 
extern double simSpeed;
extern model m;   /* object of class 'model' is called 'm' */

bool initModel=true;
int W,H;

/*invoca costruttore FL_GL_WINDOW*/
simulationGrid::simulationGrid(int x,int y,int w,int h, priceGenetics *graphic1, const char *l):Fl_Gl_Window(x,y,w,h,l)  
{
/*	grow = true; */
	restart = false; 
	this->graphic1 = graphic1;
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
	gui_nFeatures = FEATURES_INIT;
	gui_friendship = SAMPLE_INIT;
	gui_threshold = THRESHOLD_INIT;
	simSpeed = SIM_SPEED_INIT;
	
	if(initModel)
	{ 
		m.init(AGENTS_INIT,  RHO_INIT , FEATURES_INIT );   
		initModel=false; 
	}
	else
	{		
		restart = true;
	}
}

void simulationGrid::draw() {	
	int i, j, k;
	int nAgentsColumn, nAgentsRow;
	int count;
	
	/*inizializzazione grafica */
	if (!valid())
		init(); 
	
	/* passa al modello i parametri presi dalla gui  e reinit  */
	if((m.agents != gui_agents) || (m.rho != gui_rho) || (m.nFeatures != gui_nFeatures) )
     		m.reinit(gui_agents,  gui_rho,  gui_nFeatures);         

	/* cancella il display */
	glClear(GL_COLOR_BUFFER_BIT);

	nAgentsColumn = (745 - 20)/40;
	//printf("Colonne = %d\n", nAgentsColumn);

	nAgentsRow = m.agents/nAgentsColumn + 1;
	//printf("Righe = %d\n",nAgentsRow);
	
	/* Draw all Agents */
	for(i=0; i<m.agents;i++)
	{
		drawAgents(i);
	}

	//printf("threshold = %f\n", m.threshold);
	/* Draw Friendship links */

	/* passo di simulazione */
	m.step();

}

void drawAgents(int i){
	int k, x;		 	
	

	/* rosso, green, blue, opacity */
	glColor4d(1- m.features[0*m.agents + i],m.features[1*m.agents + i],m.features[2*m.agents + i],0.8);
	
	/* position_x, position_ y, size */
	//circle(rand() % (745 - 10) +10, rand() % (490) + 10, 3.0 * (double) sqrt(m.degree[i]));
	//circle( (i%40) *16+20,  (j%40)*16 +40, 1.0 * (double) m.degree[i]);

	//circle(20 + (10 + 20)*column, 20 + (10 + 20)*row, sqrt(m.degree[i]));
	printf("Agent %d = %f %f, degree = %d\n", i, m.x[i],m.y[i], m.degree[i]);
	circle(m.x[i], m.y[i], sqrt(m.degree[i]));
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

void drawFriendship(int f1, int f2)
{
	glColor4d(170.0, 170.0, 170.0, 0.4);
	glBegin(GL_LINES);
		glVertex2d(30, 100);
		glVertex2d(100, 30);
	glEnd();
}

