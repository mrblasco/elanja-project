#include "regionCountStats.h"
#include "simulationGrid.h"

extern model m;
extern bool doNextSimulationStep;

regionCountStats::regionCountStats(int w, int h,const char *l):glStats(w,h,l) 
{
     	int j;

		for(j=0;j<STATS2_W;  j++)  
		{
			regionHistory[j] = 0.0;
		}
		regionHistory[STATS2_W] = m.nRegions;
}

void regionCountStats::paint() 
{	
	int i,j,k; 
     	int check[20];
     	double clustering;


     	for(j=0;j<w();j++)  
          	regionHistory[j] = regionHistory[j+1];

	
	if(doNextSimulationStep){
		glClear(GL_COLOR_BUFFER_BIT);
		
		glColor4d(1.0, 1.0, 1.0,1);

          	//for(j=0;j<STATS2_W;j++)
          	//{
			glBegin(GL_LINE);
				glVertex2d(0,0);
				glVertex2d(0,50);
				glVertex2d(50,50);
				glVertex2d(50,0);
				//glVertex2d(j,(STATS2_H/4)*regionHistory[j]);
				//glVertex2d(j+1,(STATS2_H/4)*regionHistory[j-1]);
			glEnd();
          	//}
		
		
	}
	
}
