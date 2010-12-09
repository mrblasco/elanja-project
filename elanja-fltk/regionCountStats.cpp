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
		
		glColor4d(0.0, 1.0, 1.0,1.0);

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

	glColor4d(1.0, 1.0, 1.0,1.0);

	//Axis
	glBegin(GL_LINES);
		glVertex2d(1,1);
		glVertex2d(1,STATS2_H);
	glEnd();
	glBegin(GL_LINES);
		glVertex2d(1,1);
		glVertex2d(STATS2_W,1);
	glEnd();

	//10
	glBegin(GL_LINES);
		glVertex2d(1,10);
		glVertex2d(3,10);
	glEnd();
	glBegin(GL_LINES);
		glVertex2d(5,6);
		glVertex2d(5,15);
	glEnd();	
	glBegin(GL_LINES);
		glVertex2d(7,6);
		glVertex2d(7,15);
		glVertex2d(7,15);
		glVertex2d(11,14);
		glVertex2d(11,14);
		glVertex2d(11,6);
		glVertex2d(11,6);
		glVertex2d(7,6);
	glEnd();

	//100
	glBegin(GL_LINES);
		glVertex2d(1,100);
		glVertex2d(3,100);
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

	//600
	glBegin(GL_LINES);
		glVertex2d(1,300);
		glVertex2d(3,300);
	glEnd();
	glBegin(GL_LINES);
		glVertex2d(5,304);
		glVertex2d(9,304);
		glVertex2d(9,304);
		glVertex2d(9,296);
		glVertex2d(9,296);
		glVertex2d(5,296);
	glEnd();
	glBegin(GL_LINES);
		glVertex2d(5,300);
		glVertex2d(9,300);	
	glEnd();	
	glBegin(GL_LINES);
		glVertex2d(11,296);
		glVertex2d(11,305);
		glVertex2d(11,305);
		glVertex2d(15,304);
		glVertex2d(15,304);
		glVertex2d(15,296);
		glVertex2d(15,296);
		glVertex2d(11,296);
	glEnd();
	glBegin(GL_LINES);
		glVertex2d(17,296);
		glVertex2d(17,305);
		glVertex2d(17,305);
		glVertex2d(21,304);
		glVertex2d(21,304);
		glVertex2d(21,296);
		glVertex2d(21,296);
		glVertex2d(17,296);
	glEnd();

	//600
	glBegin(GL_LINES);
		glVertex2d(1,600);
		glVertex2d(3,600);
	glEnd();
	glBegin(GL_LINES);
		glVertex2d(5,605);
		glVertex2d(5,596);
		glVertex2d(5,596);
		glVertex2d(9,596);
		glVertex2d(9,596);
		glVertex2d(9,600);
		glVertex2d(9,600);
		glVertex2d(5,600);	
	glEnd();	
	glBegin(GL_LINES);
		glVertex2d(11,596);
		glVertex2d(11,605);
		glVertex2d(11,605);
		glVertex2d(15,604);
		glVertex2d(15,604);
		glVertex2d(15,596);
		glVertex2d(15,596);
		glVertex2d(11,596);
	glEnd();
	glBegin(GL_LINES);
		glVertex2d(17,596);
		glVertex2d(17,605);
		glVertex2d(17,605);
		glVertex2d(21,604);
		glVertex2d(21,604);
		glVertex2d(21,596);
		glVertex2d(21,596);
		glVertex2d(17,596);
	glEnd();

	//t tic
	glBegin(GL_LINES);
		glVertex2d(STATS2_W-5,5);
		glVertex2d(STATS2_W-5,10);
	glEnd();
	glBegin(GL_LINES);
		glVertex2d(STATS2_W-8,10);
		glVertex2d(STATS2_W-3,10);
	glEnd();
}
