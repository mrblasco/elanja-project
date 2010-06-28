#include "clusteringStats.h"
#include "simulationGrid.h"

extern model m;
extern bool doNextSimulationStep;

clusteringStats::clusteringStats(int w,int h,const char *l):glStats(w,h,l) 
{
	grow = true;
}

void clusteringStats::paint() 
{	
	int i,j, dx, dy;
	double max_capital;
	
	
	/*if (!valid()) {
		//tutto questo codice eseguito tutte le volte che la
		//finestra deve essere (re)inizializzata, per esempio a
		//causa di un resize
		
		//inizializzazione grafica, non toccare! serve fatto così per compatibilità con altri sistemi
		valid(1);
		glLoadIdentity();
		//glViewport(0,0,w(),h());
		glEnable(GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glMatrixMode (GL_PROJECTION);     
		glLoadIdentity();
		glOrtho(0, w(), 0, h(), -100, 100);                
		glMatrixMode (GL_MODELVIEW);
	}*/
	
	if(doNextSimulationStep){
		glClear(GL_COLOR_BUFFER_BIT);
		
		glColor4d(1, 0, 0,0.7);

		/* Qua disegniamo il nostro grafico per le statistiche */

		glBegin(GL_POLYGON);
		for(i=0; i<3; i++)
		{
			glVertex2d(rand()%100, rand()%300);
			glVertex2d(50, 80);
			glVertex2d(80, 80);
			glVertex2d(80, 50);
		}
		glEnd();
		
	}
	
}
