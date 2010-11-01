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
 
void model::init(int edge_agents, int agents, int nFeatures, int pos_features, int n_iter){

	int i, j;

	printf("Initializing Model ... \n");	

	/* Field of the class model */
	this->edge_agents = edge_agents;
	this->agents = agents;
	this->link = 0;
	this->nFeatures = nFeatures;
	this->pos_features = pos_features;
	this->n_iter = n_iter;
	this->control = 0;
     
	/* Memory allocation needed */
    	this->A = (int*) malloc(sizeof(double)*agents*agents); /* adjacency matrix */
	this->k = (int*) malloc(sizeof(double)*agents); /* degree */
	this->degree_freq = (int*) malloc(sizeof(double)*agents); /* degree histogram */
	this->feature = (int*) malloc(sizeof(double)*agents*(double)nFeatures); /* features */
	this->feat_freq = (int*) malloc(sizeof(double)*pos_features); /* features histogram */
	this->vector = (int*) malloc(sizeof(double)*agents); /* temporary vector for various values */
	this->region = (int*) malloc(sizeof(double)*agents); /* labels */
	this->reg_size = (int*) malloc(sizeof(double)*agents); /* labels histogram */

	/* Initialize degree, region, adjacency matrix */
	for(i=0;i<agents;i++)
	{
		k[i] = 0;
		region[i] = 0;

		for(j=0;j<agents;j++)
		{
			A[j*agents+i] = 0;
		}
	}
	
	/* Making the lattice */
	A[1*agents+0] = A[edge_agents*agents+0] = A[(edge_agents-2)*agents+(edge_agents-1)] = A[(2*edge_agents-1)*agents+(edge_agents-1)] = A[(agents-edge_agents+1)*agents+(agents-edge_agents)] = A[(agents-2*edge_agents)*agents+(agents-edge_agents)] = A[(agents-2)*agents+(agents-1)] = A[(agents-edge_agents-1)*agents+(agents-1)] = 1;
	for(i=1;i<agents-1;i++)
	{
		if(i % edge_agents == 0)
		{
			A[(i+1)*agents+i] = A[(i-edge_agents)*agents+i] = A[(i+edge_agents)*agents+i] = 1;
		}
		else if( ((i+1) % edge_agents == 0) && (i>edge_agents) )
		{
			A[(i-1)*agents+i] = A[(i-edge_agents)*agents+i] = A[(i+edge_agents)*agents+i] = 1;
		}
		else if(i < edge_agents-1)
		{
			A[(i+1)*agents+i] = A[(i-1)*agents+i] = A[(i+edge_agents)*agents+i] = 1;
		}
		else if(i >= agents-edge_agents)
		{
			A[(i+1)*agents+i] = A[(i-1)*agents+i] = A[(i-edge_agents)*agents+i] = 1;
		}
		else if( i != edge_agents-1 )
		{
			A[(i+1)*agents+i] = A[(i-1)*agents+i] = A[(i+edge_agents)*agents+i] = A[(i-edge_agents)*agents+i] = 1;
		}
	}

	/* Computing number of links */
	link = 0;
	for(i=0;i<agents;i++)
	{
		for(j=0;j<agents;j++)
		{
			link += A[j*agents+i];
		}
	}
	cout << link << endl;

	for(i=0;i<agents;i++)
	{
		k[i] = 0;
		
		for(j=0;j<agents;j++)
		{
			if(A[j*agents+i] == 1)
			{
				k[i]++;
			}
		}
	}

	/* Printing histogram of the degree */
 	/*outfile.open("degree.txt");
	for(i=0;i<agents;i++)
	{
		degree_freq[i] = 0;
	}
	for(i=0;i<agents;i++)
	{
		degree_freq[k[i]]++;
	}
	for(i=0;i<agents;i++)
	{
		outfile << i << "\t" << degree_freq[i] << endl;
	}
	outfile.close();*/

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

	for(pos_features=3;pos_features<=18;pos_features=pos_features+3)
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

			/* Printing histogram of features */
		 	/*outfile.open("features.txt");
			for(i=0;i<pos_features;i++)
			{
				feat_freq[i] = 0;
			}
			for(i=0;i<agents;i++)
			{
				for(j=0;j<nFeatures;j++)
				{
					feat_freq[feature[j*agents+i]]++;
				}
			}
			for(i=0;i<pos_features;i++)
			{
				outfile << i << "\t" << feat_freq[i] << endl;
			}
			outfile.close();*/

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

				if(t % 1000 == 0) {cout << t << "\t" << index2 << endl;}
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

 
