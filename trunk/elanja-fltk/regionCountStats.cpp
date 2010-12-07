#include "regionCountStats.h"
#include "simulationGrid.h"

extern model m;
extern bool restartS;
extern bool doNextSimulationStep;

regionCountStats::regionCountStats(int w, int h,const char *l):glStats(w,h,l) 
{
     	int j;

	for(j=0;j<STATS2_W-1;  j++)  
	{
		regionHistory[j] = 0;
	}
	regionHistory[STATS2_W-1] = m.nRegions;
}

void regionCountStats::paint() 
{	
	int i,j,k; 

	if(restartS)
	{
		for(j=0;j<STATS2_W-1;  j++)  
		{
			regionHistory[j] = 0;
		}
		regionHistory[STATS2_W-1] = m.nRegions;
		restartS = false;
	}

     	for(j=0;j<STATS2_W-1;j++)  
	{
          	regionHistory[j] = regionHistory[j+1];
	}

	regionHistory[STATS2_W-1] = m.nRegions;
	
	if(doNextSimulationStep){
		glClear(GL_COLOR_BUFFER_BIT);
		
		glColor4d(1.0, 1.0, 1.0,0.7);

          	for(j=0;j<STATS2_W;j++)
          	{
			if(regionHistory[j] > 0)
			{
				glBegin(GL_LINES);
					glVertex2d(j,regionHistory[j]);
					glVertex2d(j+1,regionHistory[j+1]);
				glEnd();
			}
          	}
	}
	
}
