#include "capitalVariation.h"
#include "simulationGrid.h"

extern model m;
extern bool doNextSimulationStep;

capitalVariation::capitalVariation(int w,int h,const char *l):glStats(w,h,l) 
{
	
}

void capitalVariation::paint() 
{	
	int i,j;
	double avg;
	
	if(doNextSimulationStep){
		glClear(GL_COLOR_BUFFER_BIT);
		
		glColor4d(1, 0, 0,0.7);

		/* Qua disegniamo il nostro grafico per le statistiche */

		glBegin(GL_POLYGON);
		for(i=0; i < 3; i++)
		{
			glVertex2d(rand()%200, rand()%100);
			glVertex2d(50, 80);
			glVertex2d(80, 80);
			glVertex2d(80, 50);
			glVertex2d(50, 80);
			glVertex2d(rand()%200, rand()%100);
		}
		glEnd();
		
	}
}
