#include "priceGenetics.h"
#include "simulationGrid.h"

extern model m;
extern bool doNextSimulationStep;

priceGenetics::priceGenetics(int w,int h,const char *l):glStats(w,h,l) 
{

}

void priceGenetics::paint() 
{	
	int i,j, dx, dy;
	
	
	if(doNextSimulationStep){
		glClear(GL_COLOR_BUFFER_BIT);
		
		glColor4d(1, 0, 0,0.7);

		/* Qua disegniamo il nostro grafico per le statistiche */

		glBegin(GL_POLYGON);
		for(i=0; i < 3; i++)
		{
			glVertex2d(50, 50);
			glVertex2d(50, 80);
			glVertex2d(80, 80);
			glVertex2d(80, 50);
		}
		glEnd();
		
	}
}
