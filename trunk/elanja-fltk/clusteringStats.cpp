#include "clusteringStats.h"
#include "simulationGrid.h"

extern model m;
extern bool doNextSimulationStep;

clusteringStats::clusteringStats(int w, int h,const char *l):glStats(w,h,l) 
{
     int j;

          for(j=0;j<STATS_W;  j++)  
          {
               clusteringHistory[j] = 0.0;
          }
}

void clusteringStats::paint() 
{	

	
}
