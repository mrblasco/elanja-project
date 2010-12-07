#include "regionCountStats.h"
#include "simulationGrid.h"

extern model m;
extern bool doNextSimulationStep;

regionCountStats::regionCountStats(int w, int h,const char *l):glStats(w,h,l) 
{
     int j;

          for(j=0;j<STATS_W;  j++)  
          {
               clusteringHistory[j] = 0.0;
          }
}

void regionCountStats::paint() 
{	
	int i,j,k; 
     int check[20];
     double clustering;


     for(j=0;j<w();j++)  
          clusteringHistory[j] = clusteringHistory[j+1];

    clustering=0;
    for(i=0;i<m.agents;i++)
    {
          if(m.degree[i]>1)
          {   
               /*inizializza */
               for(j=0;j<20;j++)
                    check[j] = -1;

               k=0;
               for(j=0;j<m.agents;j++)
               {
                    if(m.A[i*m.agents +j]==1)
                     {    
                         check[k] = j;
                         k++;
                     }
               }
               for(j=0;j<20;j++)
               {
                   if(check[j]>=0)
                   {
                        for(k=0;k<20;k++)
                        {
                              if(m.A[check[j]*m.agents+check[k]]==1 && check[k]>=0)
                                   clustering = clustering +1;
                         }
                    }
               }
               clustering = clustering / (2*m.degree[i]);
          }               
     }
     clusteringHistory[STATS_W-1] = clustering;

	
	if(doNextSimulationStep){
		glClear(GL_COLOR_BUFFER_BIT);
		
		glColor4d(0.5, 0.5, 0,0.7);

		/* Qua disegniamo il nostro grafico per le statistiche */
          for(j=0;j<STATS_W;j++)
          {
		glBegin(GL_LINE);
			glVertex2d(j,(STATS_H/4)*clusteringHistory[j]);
			glVertex2d(j+1,(STATS_H/4)*clusteringHistory[j-1]);
          }
		glEnd();
		
		printf("Faccio clustering\n");
	}
	
}
