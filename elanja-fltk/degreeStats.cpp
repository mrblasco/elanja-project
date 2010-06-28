#include "degreeStats.h"
#include "simulationGrid.h"

extern model m;
extern bool doNextSimulationStep;

degreeStats::degreeStats(int w,int h,const char *l):glStats(w,h,l) 
{
	int i;
	degree_avg_history = (double *)malloc(sizeof(double)*w);
	for (i=0; i<w; i++)
	{
		degree_avg_history[i] = 0.0;
		//printf("Degree_avg_history[%d] = %f\n", i, degree_avg_history[i]);
	}
}

void degreeStats::paint() 
{	
	int i,j;
	double avg;
		
	for (i=1; i<w(); i++)
	{
		degree_avg_history[i-1] = degree_avg_history[i];
		printf("Degree_avg_history[%d] = %f\n", i, degree_avg_history[i]);
	}
	
	if(doNextSimulationStep){
		glClear(GL_COLOR_BUFFER_BIT);
		/*// red line
		glColor4f(1.0,0.0,0.0,1.0);
		glBegin(GL_LINES);
			glVertex2d(0, h()/5.0);
			glVertex2d(w(), h()/5.0);
		glEnd();*/
		
		for (i=1; i<w()-1; i++)
		{
			glColor4f(0.0,1.0,1.0,0.5);
			glBegin(GL_LINES);
				glVertex2d(i-1, degree_avg_history[i-1]);
				glVertex2d(i, degree_avg_history[i]);
			glEnd();
	
		}

		avg = 0.0;
		for(j=0; j<m.agents; j++){
			avg += m.degree[j];
		}
		
		avg /= m.agents;
		printf("avg = %f \n", avg);
		degree_avg_history[w()-1] = avg;
	}
}
