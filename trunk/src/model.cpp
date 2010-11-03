#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../h/model.h"
#include "../h/const.h"

using namespace std; 

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

model m; // istance of the model
int t; // counter for iteractions 

extern int w, h;
 
void model::init(int edge_agents, int agents, int nFeatures, int pos_features, int n_iter, int outdegree, double delta, int maxSide){

	printf("Initializing Model ... \n");	

	/* Field of the class model */
	this->edge_agents = edge_agents;
	this->agents = agents;
	this->link = 0;
	this->nFeatures = nFeatures;
	this->pos_features = pos_features;
	this->n_iter = n_iter;
	this->control = 0;
	this->outdegree = outdegree;
	this->delta = delta;
	this->maxSide = maxSide;
     
	/* Memory allocation needed */
    	this->A = (int*) malloc(sizeof(double)*agents*agents); /* adjacency matrix */
	this->k = (int*) malloc(sizeof(double)*agents); /* degree */
	this->degree_freq = (int*) malloc(sizeof(double)*agents); /* degree histogram */
	this->feature = (int*) malloc(sizeof(double)*agents*(double)nFeatures); /* features */
	this->feat_freq = (int*) malloc(sizeof(double)*pos_features); /* features histogram */
	this->vector = (int*) malloc(sizeof(double)*agents); /* temporary vector for various values */
	this->region = (int*) malloc(sizeof(double)*agents); /* labels */
	this->reg_size = (int*) malloc(sizeof(double)*agents); /* labels histogram */
	
	int list[(edge_agents*edge_agents)][outdegree];
	//int list = malloc(sizeof(int)*(edge_agents*edge_agents*outdegree));

	/* =================CREATE NETWORK ====================  */

	/* maxSide

	% 0 is no local interactions, i.e., random network
	% 1 is the square of 4 neighbors
	% 2 is the square of 8 neighbors 

	note: outdegree needs to be larger than 8 (or 24) to have long-range shortcuts,i.e., small worlds.
	if maxSide > 2 then outdegree needs to be at least 48 or seg. fault. */

	/* Initialize network list; first column id of all agents, second, third ... outdegree-th column ids of all linked agents. */

	int i,j,i2,j2,jj,ii;
	int neighbors, distance;
	double ll,outcome;
	int l, g, n, k, mlinks;

	for (i=0;i<edge_agents;i++)
	{
		for (j=0; j<edge_agents;j++)
		{            
			for (g=0;g<outdegree;g++)
			{       
				//*(list + (i*edge_agents +j)*outdegree + g ) = -1;
				list[(i*edge_agents +j)][g] = -1;
			}
		}
	}   

	for (i=0;i<edge_agents;i++)
	{
		for(j=0;j<edge_agents;j++)
		{
			neighbors=0;
			
			/* local links */
			for(ii=(i-maxSide); ii<(i+maxSide+1);ii++)
			{
				for (jj=(j-maxSide); jj<(j+maxSide+1); jj++)
				{
					/* normalize to torus */
					i2 = ((edge_agents + ii) % (edge_agents));  
					j2 = ((edge_agents + jj) % (edge_agents));

					if ( ( (i!=i2) || (j!=j2) ) )
					{
						if( (i==i2) || (j==j2) )
						{
							/* fill the list of neighbors */
							//*(list + (i*edge_agents +j)*outdegree + neighbors ) = (i2*edge_agents +j2);
							list[(i*edge_agents +j)][neighbors] = (i2*edge_agents +j2);
							neighbors++;
						}
					}
				}
			}

			/* then shortcuts are added */
			while (neighbors <= outdegree)
			{         
				i2 = (rand()%edge_agents);
				j2 = (rand()%edge_agents);

				distance =  floor (sqrt(pow(MIN(fabs(i-i2),edge_agents-fabs(i-i2)),2) + pow(MIN(fabs(j-j2),edge_agents-fabs(j-j2)),2)));

				if(distance > maxSide )
				{   
					mlinks = 0;  /* check to avoid multiple links*/

					outcome =  pow(distance, (- delta) );
					ll = (double) (rand()%1000) / (double) 1000;
					if ( ll < outcome )
					{
						for (k = 0 ; k < neighbors; k++)
						{
							//if( *(list + (i*edge_agents +j)*outdegree + k ) == (i2*edge_agents +j2))
							if( list[i*edge_agents +j][ k] == (i2*edge_agents +j2))
								mlinks = 1;
						}
						if(mlinks == 0)
						{
							list[i*edge_agents +j][ k] = (i2*edge_agents +j2);
							neighbors++;
						}
					}
				}
			}
		}  
	}

	for(i=0;i<agents;i++)
	{
		region[i] = 0;
		for(j=0;j<agents;j++)
		{
			A[j*agents+i] = 0;
		}
	}

	k = 0;
	for(i=0;i<edge_agents;i++)
	{
		for(j=0;j<edge_agents;j++)
		{
			for(g=0;g<outdegree;g++)
			{
				l = list[i*edge_agents +j][g]; 
				A[l*agents+k] = 1;
				link++;
			}
			k++;
		}
	}
	cout << link << endl;

	ofstream outfile;
	outfile.open("matrice_di_agiacenza.txt");
	for(i=0;i<agents;i++)
	{
		for(j=0;j<agents;j++)
		{
			outfile << A[j*agents+i] << "\t";
		}
		outfile << endl;
	}
	outfile.close();

}

 
/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%      STEP              %%%%%%%%%%%%%%%%
%%%%%%%%      FUNCTION     %%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
void model::step(){
	
	int i,j,n,m,a,b,t,f,s;
	double p, r, prob;

	/* Create output file */
	ofstream outfile;
	outfile.open("dati.txt");

	//for(pos_features=3;pos_features<=18;pos_features=pos_features+3)
	{
		cout << "pos_features = " << pos_features << endl;

		for(s=0;s<n_iter;s++)
		{
			cout << "Simulation " << s << endl;

			/* Making features */
			for(i=0;i<agents;i++)
			{
				for(j=0;j<nFeatures;j++)
				{
					feature[j*agents+i] = rand() % pos_features;
				}
			}

			/* Dynamic part */
			t = 0;
			control = 0;
			while(control == 0)
			{
				for(i=0;i<agents;i++)
				{
					n = 0;
					for(j=0;j<agents;j++)
					{
						if(A[j*agents+i] == 1)
						{
							vector[n] = j;
							n++;
						}
					}
					a = rand() % n;
					j = vector[a];
					prob = 0;
					for(f=0;f<nFeatures;f++)
					{
						if( feature[f*agents+i] == feature[f*agents+j] )
						{
							prob++;
						}
					}
					prob = prob / (double) nFeatures;
					r = (rand() % 10001) / 10000;
					if( r<prob )
					{
						n = 0;
						for(m=0;m<nFeatures;m++)
						{
							if( feature[m*agents+i] != feature[m*agents+j] )
							{
								vector[n] = m;
								n++;
							}
						}
						if(n != 0)
						{
							a = rand() % n;
							b = vector[a];
							feature[b*agents+j] = feature[b*agents+i];
						}						
					}
				}
				index2 = 0;
				for(i=0;i<agents;i++)
				{
					for(j=0;j<agents;j++)
					{
						if(A[j*agents+i] == 1)
						{
							index = 0;
							for(f=0;f<nFeatures;f++)
							{
								if(feature[f*agents+i] == feature[f*agents+j])
								{
									index++;
								}
							}
							if( (index == nFeatures) || (index == 0) )
							{
								index2++;
							}
						}
					}
				}
				if( index2 == link )
				{
					control = 1;
				}

				if(t % 500 == 0) {cout << t << "\t" << index2 << endl;}
				t++;
			}
			cout << "Numero di step eseguiti = " << t << endl;
		
			/* Labeling cultural regions */
			label = 2;
			for(i=0;i<agents;i++)
			{
				region[i] = 0;
			}
			region[0] = 1;
			for(i=0;i<agents;i++)
			{
				for(j=i+1;j<agents;j++)
				{
					if(A[j*agents+i] == 1)
					{
						index = 0;
						for(f=0;f<nFeatures;f++)
						{
							if(feature[f*agents+i] == feature[f*agents+j])
							{
								index++;
							}
						}
						if( index == nFeatures )
						{
							region[j] = region[i];
						}
						else if( (index == 0) && (region[j] == 0) )
						{
							region[j] = label;
							label++;
						}
					}
				}
			}

                        /* Printing histogram of sizes of region */
                        /*outfile.open("reg_size.txt");
                        for(i=0;i<agents;i++)
                        {
                                reg_size[i] = 0;
                        }
                        for(i=0;i<agents;i++)
                        {
                                reg_size[region[i]]++;
                        }
                        for(i=0;i<agents;i++)
                        {
                                outfile << i << "\t" << reg_size[i] << endl;
                        }
                        outfile.close();*/


			/* Printing needed at the end of each simulation */
			for(i=0;i<agents;i++)
			{
				outfile << i << "\t" << region[i] << "\t";
				for(j=0;j<nFeatures;j++)
				{
					outfile << feature[j*agents+i] << "\t"; 
				}
				outfile << "\n";
			}
		}
	}
     
}

 
