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
	this->label = (int*) malloc(sizeof(double)*agents); /* labels */
	this->reg_size = (int*) malloc(sizeof(double)*agents); /* labels histogram */
	this->Nlist = (int*)malloc(sizeof(int)*(edge_agents*edge_agents*outdegree));


	/* =========CREATE NETWORK ====================  */

	/* maxSide
	% 0 is no local interactions, i.e., random network
	% 1 is the square of 4 neighbors */
     	
	/* Initialize var and network list */
	int i,j,i2,j2,jj,ii;
	int neighbors, distance;
	double ll,outcome;
	int l, g, n, k, mlinks;
	int friendscount[agents];
	int maxRand;
	
	for(i=0;i<agents;i++)
	{
		friendscount[i] = 0;
	}

	for (i=0;i<agents;i++)
	{
		for (g=0;g<outdegree;g++)
		{       
			Nlist[i*outdegree +g] = -1;
		}
	}   

	/* create network list*/
	if(maxSide == -1)
	{
		for (i=0;i<agents;i++)
		{
			maxRand = 0;
			while(friendscount[i]<outdegree)
			{
				if(maxRand < agents)
				{
					j = (rand() % (agents-i-1)) +i+1;
					if((j != i) && (friendscount[j]<4))
					{
						mlinks = 0;
						for (k = 0 ; k < outdegree; k++)
						{
							if(Nlist[i*outdegree+k]==j)
							mlinks = 1;
						}
						if(mlinks==0)
						{
							Nlist[i*outdegree +friendscount[i]] = j;
							Nlist[j*outdegree +friendscount[j]] = i;
							friendscount[i]++;
							friendscount[j]++;
						}
					}
					maxRand++;
				}
				else
				{
					printf("Prando quello che viene \n");
					for(j=0;j<agents;j++)
					{
						if(friendscount[j]<4)
						{
							if(k != i)
							{
								mlinks = 0;
								for (k = 0 ; k < outdegree; k++)
								{
									if(Nlist[i*outdegree+k]==j)
									mlinks = 1;
								}
								if(mlinks==0)
								{
									Nlist[i*outdegree +friendscount[i]] = j;
									Nlist[j*outdegree +friendscount[j]] = i;
									friendscount[i]++;
									friendscount[j]++;
								}
							}
						}
					}
				}
			}
		}
	}
	else
	{
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
	}
	
	FILE *out;
	out = fopen("list.txt", "w");
	//Print the list
	for(i=0;i<agents;i++)
	{
		fprintf(out,"%d\t",i);
		for(k=0;k<outdegree;k++)
		{
			fprintf(out,"%d\t",Nlist[ i*outdegree + k ]);
		}
		fprintf(out,"\n");
	}

}

 
/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%      STEP              %%%%%%%%%%%%%%%%
%%%%%%%%      FUNCTION     %%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
void model::step(){

        FILE *out2;
	FILE *out3;
	FILE *out4;
	FILE *out5;
        out2 = fopen("dati.txt", "w");     
	out3 = fopen("medie.txt","w");
	out4 = fopen("hist_label.txt","w");
	out5 = fopen("test.txt","w");

	int i,j,n,m,a,b,t,f,s,l,ll, test;
	double p, r, prob, tempo, mean_max_reg, var_max_reg;
	double max_reg[n_iter];
	int counter, counter2;

	//for(pos_features=5;pos_features<=65;pos_features=pos_features+5)
	{
		cout << "pos_features = " << pos_features << endl;

		tempo = 0;
		mean_max_reg = var_max_reg = 0;

		for(s=0;s<n_iter;s++)
		{
			cout << "Simulation " << s+1 << endl;

			/* Create features vectors*/
			for(i=0;i<agents;i++)
			{
				for(f=0;f<nFeatures;f++)
				{
					feature[i*nFeatures+f] = rand() % pos_features;
				}
			}

			/* Dynamic process */
			t = 0;
			control = 0;
			while(control == 0)
			{
				counter = 0;
				for(i=0;i<agents;i++)
				{
					a = rand() % outdegree;
					j = Nlist[i*outdegree +a];
					a = 0;                         
					for(f=0;f<nFeatures;f++)
					{
						if( feature[(i*nFeatures+f)] == feature[(j*nFeatures+f)] )
						{
							a++; 
						}
					}
					prob = (double)  a / (double) nFeatures;
					r = (rand() % 10000) / (double) 10000;
					if( r < prob )
					{
						n = 0;
						a = 0;
						for(f=0;f<nFeatures;f++)
						{
							if( feature[i*nFeatures+f] != feature[j*nFeatures+f] )
							{
								vector[n] = f;
								n++;
							}
							else
							{
								a++;
							}
						}
						if(n > 0 && a > 0)
						{
							a = rand() %n;
							f = vector[a];
							feature[i*nFeatures+f] = feature[j*nFeatures+f];
							counter++;
						}						
					}
				
				}

				//Check if the system is in a freeze state
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
						}
					}
				}

				if( index2 == (outdegree*agents) || t >= agents*agents  )
				{
					control = 1;
				}

				fprintf(out5,"%d %d %d %d \n",pos_features,s+1,t,outdegree*agents-index2,counter);
				if(t % 1000 == 0) {cout << pos_features << "\t" << s+1 << "\t" << t << "\t" << outdegree*agents-index2 << "\t" << counter << endl;}
				t++;
			}
			cout << "Numero di step eseguiti = " << t << endl;
			tempo += t;

			//Labeling
			a = 0;
			label[0]= a;
			for(i=1;i<agents;i++)
			{
				test =1;
				for(j=0;j<i;j++)
				{
					if(feature[i*nFeatures+0]==feature[j*nFeatures+0])
					{
						if(feature[i*nFeatures+1]==feature[j*nFeatures+1])
						{
							if(feature[i*nFeatures+2]==feature[j*nFeatures+2])
							{
								label[i] = label[j];          
								test = 0;
							}                            
						}                        
					}
				}
				if(test==1)
				{
					a++;
					label[i] = a;
				}
			}

			/* Printing needed at the end of each simulation */
			for(i=0;i<agents;i++)
			{
				fprintf(out2,"%d %d\t",pos_features,i);
				for(f=0;f<nFeatures;f++)
				{
					fprintf(out2,"%d\t",feature[i*nFeatures+f]); 
				}
				fprintf(out2,"%d\n",label[i]);
			}

			/* Printing histogram of sizes of region */
                        for(i=0;i<agents;i++)
                        {
                                reg_size[i] = 0;
                        }
                        for(i=0;i<agents;i++)
                        {
                                reg_size[label[i]]++;
                        }
                        for(i=0;i<agents;i++)
                        {
				if( reg_size[i]>0 ) {fprintf(out4,"%d %d %d %d\n",s+1,pos_features,i,reg_size[i]);}
                        }

			max_reg[s] = 0;
			for(i=0;i<agents;i++)
			{
				if( reg_size[i] > max_reg[s] )
				{
					max_reg[s] = reg_size[i];
				}
			}
			max_reg[s] = (double) max_reg[s] / agents;
			mean_max_reg += max_reg[s];
		}
		mean_max_reg = (double) mean_max_reg / (double) n_iter;
		for(i=0;i<n_iter;i++)
		{
			var_max_reg += pow(max_reg[i]-mean_max_reg,2);
		}
		var_max_reg = (double) var_max_reg / (double) n_iter;
		tempo = (double) tempo / (double) n_iter;
		fprintf(out3,"%d %f %f %f\n",pos_features,tempo,mean_max_reg,var_max_reg);
	}

}

 
