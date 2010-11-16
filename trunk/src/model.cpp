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
	this->feature = (int*) malloc(sizeof(double)*(agents*nFeatures)); /* features */
	this->feat_freq = (int*) malloc(sizeof(double)*pos_features); /* features histogram */
	this->vector = (int*) malloc(sizeof(double)*agents); /* temporary vector for various values */
	this->region = (int*) malloc(sizeof(double)*agents); /* labels */
	this->reg_size = (int*) malloc(sizeof(double)*agents); /* labels histogram */
	
	// int list[(edge_agents*edge_agents)][outdegree];
	//int (int*)malloc(sizeof(int)*(edge_agents*edge_agents*outdegree));
	this->Nlist = (int*)malloc(sizeof(int)*(edge_agents*edge_agents*outdegree));


	/* =========CREATE NETWORK ====================  */

	/* maxSide

	% 0 is no local interactions, i.e., random network
	% 1 is the square of 4 neighbors
	% 2 is the square of 8 neighbors 

	note: outdegree needs to be larger than 8 (or 24) to have long-range shortcuts,i.e., small worlds.
	if maxSide > 2 then outdegree needs to be at least 48 or seg. fault. */
     double uNum;

	/* Initialize var and network list */

	int i,j,i2,j2,jj,ii;
	int neighbors, distance;
	double ll,outcome;
	int l, g, n, k, mlinks;

	for (i=0;i<agents;i++)
	{
		for (g=0;g<outdegree;g++)
		{       
               Nlist[i*outdegree +g] = -1;
		}
	}   

     /* create network list -- local neighbors*/
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
					// normalize to torus 
					i2 = ((edge_agents + ii) % (edge_agents));  
					j2 = ((edge_agents + jj) % (edge_agents));

					if ( ( (i!=i2) || (j!=j2) ) )
					//if( (i2==i && j2==j-1) || (i2==i-1 && j2==j) )
					{
						if( (i==i2) || (j==j2) )
						{
                                   Nlist[(i*edge_agents +j)*outdegree + neighbors] = (i2*edge_agents +j2);
							neighbors++;
						}
					}
				}
			}

			/* ... then shortcuts are added */
			while (neighbors < outdegree)
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
							if( Nlist[ (i*edge_agents +j)*outdegree + k ] == (i2*edge_agents +j2))
								mlinks = 1;
						}
						if(mlinks == 0)
						{
                                  Nlist[ (i*edge_agents +j)*outdegree + k ]  = (i2*edge_agents +j2);
							neighbors++;
						}
					}
				}
			}
		}  
     }
          // To test print the list :  seems ok!
          /*for(i=0;i<agents;i++)
          {
		cout << i << "\t";
              for(k=0;k<outdegree;k++)
               {
                   cout << Nlist[ i*outdegree + k ] << "\t";
               }
              cout << endl;
          }*/
     

     /* initialize region and print Adiacency matrix... */
	for(i=0;i<agents;i++)
	{
		region[i] = 0;
		for(j=0;j<agents;j++)
		{
			A[i*agents+j] = 0; 
		}
	}

	for(i=0;i<agents;i++)
	{
		for(g=0;g<outdegree;g++)
		{
			l = Nlist[(i*outdegree +g)]; 
			A[i*agents+l] = 1; 
			link++;
		}
	}
	cout << "Numero di links " << link << endl;

	/*ofstream outfile;
	outfile.open("AdMatrix.txt");
	for(i=0;i<agents;i++)
	{

		for(j=0;j<agents;j++)
		{
			outfile << A[i*agents+j] << "\t";
		} 
		outfile << endl;
	}
	outfile.close();*/
}

 
/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%      STEP              %%%%%%%%%%%%%%%%
%%%%%%%%      FUNCTION     %%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
void model::step(){
	
	int i,j,n,m,a,b,t,f,s,l,ll;
	double p, r, prob;
	//double noise = 0.0005;

	/* Create output file */
	ofstream outfile;
	outfile.open("dati.txt");

	for(pos_features=10;pos_features<=500;pos_features=pos_features+20)
	{
		cout << "pos_features = " << pos_features << endl;

		for(s=0;s<n_iter;s++)
		{
			cout << "Simulation " << s+1 << endl;

			/* Create features vectors*/
			for(i=0;i<agents;i++)
			{
				for(f=0;f<nFeatures;f++)
				{
					feature[i*nFeatures+f] = rand() % pos_features;
      //                  printf("%d \t",feature[i*nFeatures+f]);
				}
        //            printf("\n");
			}
//               exit(0);

			/* Dynamic process */
			t = 0;
			control = 0;
			while(control == 0)
			//for(t=0;t<agents*agents;t++)
			{
				for(i=0;i<agents;i++)
				{
					a = rand() % outdegree;
                         j = Nlist[i*outdegree +a];

                         a =0;                         
					for(f=0;f<nFeatures;f++)
					{
                              l= feature[(i*nFeatures+f)];
                              ll =  feature[(j*nFeatures+f)];
						if( l == ll )
                              {
							a++; 
                              }
					}
					prob = (double)  a / (double) nFeatures;
					r = (rand() % 10000) / (double) 10000;

					if( r <= prob )
					{
						n = 0;
						for(f=0;f<nFeatures;f++)
						{
							if( feature[i*nFeatures+f] != feature[j*nFeatures+f] )
							{
								vector[n] = f;
								n++;
							}
						}
						if(n > 0)
						{
							a = rand() %n;
							f = vector[a];
							feature[i*nFeatures+f] = feature[j*nFeatures+f];
						}						
					}
				}

				//Noise
				/*i = rand() % agents;
				r = (rand() % 1000000) / (double) 1000000;
				if(r<noise)
				{
					f = rand() % nFeatures;
					feature[i*nFeatures+f] = rand() % pos_features;
				}*/

				index2 = 0;
				for(i=0;i<agents;i++)
				{
					for(l=0;l<outdegree;l++)
					{
                              j = Nlist[i*outdegree +l];

						index = 0;
						for(f=0;f<nFeatures;f++)
						{
							if(feature[i*nFeatures+f] == feature[j*nFeatures+f])
							{
								index++;
							}
						}
						if( (index == nFeatures) || (index == 0) )
						{
							index2++;
						} else {
/// prova
//                              printf("Agent %d",i);
//						for(f=0;f<nFeatures;f++)
//						{
//							printf("%d\t",feature[i*nFeatures+f]-feature[j*nFeatures+f]);
//						}
//printf("\n");
                              }

					}
				}

				if( index2 == (outdegree*agents)  )
				{
					control = 1;
				}

				//if(t % 1000 == 0) {cout << t << "\t" << index2 << endl;}
				//if(t % 1000000 == 0) {cout << t << endl;}
				t++;
			}
			cout << "Numero di step eseguiti = " << t << endl;
		
			/* Labeling cultural regions  */
			label = 2;
			for(i=0;i<agents;i++)
			{
				region[i] = 0;
			}
			region[0] = 1;

			for(i=0;i<agents;i++)
			{
				for(j=0;j<agents;j++)
				{
					if(A[i*agents+j] == 1)
					{
						index = 0;
						for(f=0;f<nFeatures;f++)
						{
							if(feature[i*nFeatures+f] == feature[j*nFeatures+f])
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

			int sum;

			/* Printing needed at the end of each simulation */
			for(i=0;i<agents;i++)
			{
				outfile << pos_features << "\t" << i << "\t" << /*region[i] <<*/ "\t";
				sum = 0;
				sum = feature[i*nFeatures+0];
				sum += feature[i*nFeatures+1]*1000;
				sum += feature[i*nFeatures+2]*1000000;
				for(f=0;f<nFeatures;f++)
				{
					outfile << feature[i*nFeatures+f] << "\t"; 
				}
				outfile << sum << endl;
			}
		}
	}
     
}

 
