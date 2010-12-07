#include "regionStats.h"
#include "simulationGrid.h"

extern model m;
extern bool doNextSimulationStep;

regionStats::regionStats(int w, int h, const char *l):glStats(w,h,l) 
{
	
}

void regionStats::paint() 
{	
	int i;	

	int bin_w;
	double bin_h;

	bin_w = (625/m.nRegions);
	//bin_w = (625/m.agents);
	
	printf("bin_w = %d nRegions = %d \n", bin_w, m.nRegions);

	if(doNextSimulationStep){
		glClear(GL_COLOR_BUFFER_BIT);
		
		
		for(i=0; i <m.nRegions; i++)
		{
			
			glColor4d((double)(1+m.reg_size[i*(m.nFeatures+1)+1])/(double)m.pos_traits,(double)(1+m.reg_size[i*(m.nFeatures+1)+2])/(double)m.pos_traits,(double)(1+m.reg_size[i*(m.nFeatures+1)+3])/(double)m.pos_traits,1.0);
				
			bin_h = sqrt((double)m.reg_size[i*(m.nFeatures+1)+0]/(double)m.agents)*300;

			glBegin(GL_POLYGON);
				glVertex2d(0, i*bin_w);
				glVertex2d(0, (i+1)*bin_w);
				glVertex2d(bin_h+3, (i+1)*bin_w);
				glVertex2d(bin_h+3, i*bin_w);
			glEnd();
		}
		
		
	}
}
