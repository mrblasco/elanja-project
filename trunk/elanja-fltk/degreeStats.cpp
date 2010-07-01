#include "degreeStats.h"
#include "simulationGrid.h"

extern model m;
extern bool doNextSimulationStep;

degreeStats::degreeStats(int w, int h, const char *l):glStats(w,h,l) 
{
	int i,j;

     for(i=0;i<5;i++)
          for(j=0;j<20;j++)  
               degreeHistory[i][j] = 0.0;
}


void degreeStats::paint() 
{	
	int i,j;
     double vector[20];


     for (i=0;i<m.agents;i++)
     {
          vector[m.degree[i]]++;
     }
     /* aggiorna history */
     for(i=0;i<5;i++)
     {
          for(j=0;j<20;j++)
          {  
               degreeHistory[i][j] = degreeHistory[(i+1)][j];
          }
     }
     for(j=0;j<20;j++)
     {  
          vector[j] = vector[j] / m.agents;
          degreeHistory[4][j] = vector[j];
     }

	if(doNextSimulationStep){
		glClear(GL_COLOR_BUFFER_BIT);
		
		for (i=0; i<5; i++)
		{
		     for (j=0; j<20; j++)
		     {
			glColor4f(0.0,1.0,1.0,0.5);
     		glBegin(GL_POLYGON);
			     glVertex2d(70*i, (STATS_H-10)  -j*20);
			     glVertex2d(70*(i+degreeHistory[i][19-j]), (STATS_H-10)  -j*20);
			     glVertex2d(70*(i+degreeHistory[i][19-j]), (STATS_H-10)- (j+1)*20 );
			     glVertex2d(70*i, (STATS_H-10) - (j+1)*20);

			glEnd();
	          }
		}


	}
}
