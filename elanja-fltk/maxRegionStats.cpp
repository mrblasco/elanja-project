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

	axis();

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

		axis();
		
		glColor4d(1.0, 0.0, 1.0,0.7);

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

void axis() 
{
	int i;

	glColor4d(1.0, 1.0, 1.0,1.0);

	//100
	glBegin(GL_LINES);
		glVertex2d(0,100);
		glVertex2d(2,100);
	glEnd();
	glBegin(GL_LINES);
		glVertex2d(5,96);
		glVertex2d(5,105);
	glEnd();	
	glBegin(GL_LINES);
		glVertex2d(7,96);
		glVertex2d(7,105);
		glVertex2d(7,105);
		glVertex2d(11,104);
		glVertex2d(11,104);
		glVertex2d(11,96);
		glVertex2d(11,96);
		glVertex2d(7,96);
	glEnd();
	glBegin(GL_LINES);
		glVertex2d(13,96);
		glVertex2d(13,105);
		glVertex2d(13,105);
		glVertex2d(17,104);
		glVertex2d(17,104);
		glVertex2d(17,96);
		glVertex2d(17,96);
		glVertex2d(13,96);
	glEnd();
	for(i=25;i<STATS2_W;i=i+10)
	{
		glBegin(GL_LINES);
			glVertex2d(i,100);
			glVertex2d(i+5,100);
		glEnd();		
	}

	//225
	glBegin(GL_LINES);
		glVertex2d(0,225);
		glVertex2d(2,225);
	glEnd();
	glBegin(GL_LINES);
		glVertex2d(5,230);
		glVertex2d(9,230);
		glVertex2d(9,230);
		glVertex2d(9,225);
		glVertex2d(9,225);
		glVertex2d(5,225);
		glVertex2d(5,225);
		glVertex2d(5,221);
		glVertex2d(5,221);
		glVertex2d(9,221);
	glEnd();
	glBegin(GL_LINES);
		glVertex2d(11,230);
		glVertex2d(15,230);
		glVertex2d(15,230);
		glVertex2d(15,225);
		glVertex2d(15,225);
		glVertex2d(11,225);
		glVertex2d(11,225);
		glVertex2d(11,221);
		glVertex2d(11,221);
		glVertex2d(15,221);
	glEnd();	
	glBegin(GL_LINES);
		glVertex2d(21,230);
		glVertex2d(17,230);
		glVertex2d(17,230);
		glVertex2d(17,225);
		glVertex2d(17,225);
		glVertex2d(21,225);
		glVertex2d(21,225);
		glVertex2d(21,221);
		glVertex2d(21,221);
		glVertex2d(17,221);
	glEnd();
	for(i=25;i<STATS2_W;i=i+10)
	{
		glBegin(GL_LINES);
			glVertex2d(i,225);
			glVertex2d(i+5,225);
		glEnd();		
	}

	//400
	glBegin(GL_LINES);
		glVertex2d(0,400);
		glVertex2d(2,400);
	glEnd();
	glBegin(GL_LINES);
		glVertex2d(9,405);
		glVertex2d(9,396);
	glEnd();
	glBegin(GL_LINES);
		glVertex2d(5,405);
		glVertex2d(5,400);
		glVertex2d(5,400);
		glVertex2d(9,400);	
	glEnd();	
	glBegin(GL_LINES);
		glVertex2d(11,396);
		glVertex2d(11,405);
		glVertex2d(11,405);
		glVertex2d(15,404);
		glVertex2d(15,404);
		glVertex2d(15,396);
		glVertex2d(15,396);
		glVertex2d(11,396);
	glEnd();
	glBegin(GL_LINES);
		glVertex2d(17,396);
		glVertex2d(17,405);
		glVertex2d(17,405);
		glVertex2d(21,404);
		glVertex2d(21,404);
		glVertex2d(21,396);
		glVertex2d(21,396);
		glVertex2d(17,396);
	glEnd();
	for(i=25;i<STATS2_W;i=i+10)
	{
		glBegin(GL_LINES);
			glVertex2d(i,400);
			glVertex2d(i+5,400);
		glEnd();		
	}

}
