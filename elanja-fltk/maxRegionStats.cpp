#include "maxRegionStats.h"
#include "simulationGrid.h"

extern bool restartS;
extern model m;
extern bool doNextSimulationStep;

maxRegionStats::maxRegionStats(int w, int h, const char *l):glStats(w,h,l) 
{
	int j;

	for(j=0;j<STATS2_W-1;  j++)  
	{
		maxRegionHistory[j] = 0;
	}
	maxRegionHistory[STATS2_W-1] = 0;
}


void maxRegionStats::paint() 
{	
	int i,j,k; 
	int max;

	max = 0;
	for(i=0;i<m.agents;i++)
	{
		if(m.reg_size[i*(m.nFeatures+1)+0] > max)
		{
			max = m.reg_size[i*(m.nFeatures+1)+0];
		}
	}
	
	if(restartS)
	{
		for(j=0;j<STATS2_W-1;  j++)  
		{
			maxRegionHistory[j] = 0;
		}
		maxRegionHistory[STATS2_W-1] = max;
		restartS = false;
	}

     	for(j=0;j<STATS2_W-1;j++)  
	{
          	maxRegionHistory[j] = maxRegionHistory[j+1];
	}

	maxRegionHistory[STATS2_W-1] = max;
	
	if(doNextSimulationStep){
		glClear(GL_COLOR_BUFFER_BIT);
		
		glColor4d(1.0, 1.0, 1.0,0.7);

          	for(j=0;j<STATS2_W;j++)
          	{
			if(maxRegionHistory[j] > 0)
			{
				glBegin(GL_LINES);
					glVertex2d(j,maxRegionHistory[j]);
					glVertex2d(j+1,maxRegionHistory[j+1]);
				glEnd();
			}
          	}
	}
}
