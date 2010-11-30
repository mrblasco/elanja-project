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

}
