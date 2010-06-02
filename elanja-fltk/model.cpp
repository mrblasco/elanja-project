#include "model.h"

model m; // istanza del modello
int t; // counter delle iterazioni

extern bool externAgentOn;
extern bool dinamicProductsOn;
extern int W,H;

void model::init(int agents,  double rho, int nFeatures){
	int i, j;

	printf("Initializing Model ... \n");	

	/* "this" field of the class model */
	this->agents = agents;
	this->rho = rho;
	this->m = rho * agents;
	this->nFeatures = nFeatures;
	//this->epsilon = epsilon;
	//this->friendship = friendship;
	//this->distance = distance;


	this->features = (double*) malloc(sizeof(double)*agents*(int)nFeatures);
	
	this->degree = (int*) malloc(sizeof(int)*agents);
	this->A_degree = (int*) malloc(sizeof(int)*agents);
	this->B_degree = (int*) malloc(sizeof(int*)*agents);

	this->A = (double*) malloc(sizeof(double)*agents*agents);

	for(i=0; i<agents; i++)	
	{
		degree[i] = 1;
		for(j=0; j<nFeatures; j++)
		{
			features[j*agents + i] = (double) (rand() %1000) / (double) 1000;
		}

		for(j=0; j<agents; j++)
		{
			A[i*agents + j] = 0;		
		}
	}

	t = 0; 
}

void model::reinit(int agents, double rho,  int nFeatures){
	int i, j;

	printf("Reinitializing Model ... \n");
 
	this->agents = agents;
	this->rho = rho;
//	this->m = rho * agents;
//	this->epsilon = epsilon;
//	this->friendship = friendship;
//	this->threshold = threshold;

	this->nFeatures = nFeatures;


	if(A) free(A);
	this->A = (double*) malloc(sizeof(double)*agents*agents);

	if(features) free(features);
	this->features = (double*) malloc(sizeof(double)*agents*(int)nFeatures);

	if(degree) free(degree);
	this->degree = (int*) malloc(sizeof(int)*agents);
	if(A_degree) free(A_degree);
	this->A_degree = (int*) malloc(sizeof(int)*agents);
	if(B_degree) free(B_degree);
	this->B_degree = (int*) malloc(sizeof(int)*agents);

	for(i=0; i<agents; i++)	
	{
		degree[i] = 1;
		for(j=0; j<nFeatures; j++)
		{
			features[j*agents + i] = (double) (rand() %1000) / (double) 1000;
		}

		for(j=0; j<agents; j++)
		{
			A[i*agents + j] = 0;		
		}
	}
	
 	t = 0;
} 

void model::step(){

	int i, j; 
	double threshold, L;
     
     /* number of available links among all the possible*/
     L = ( rho * agents * (agents - 1) )/ 2;

	threshold = newInteraction(L, A, agents);
	update(L, degree, A, threshold, features);
	
	t += 1;
}

 /* compute correlation matrix and finds a threshold */
double newInteraction(double L, double *A, int agents)
{
	int i, j, l, counter, test;
	double upthreshold, downthreshold, threshold;
	double mou = 0.5;
     double Lmax, Lmin;
	double featuresTmp2[agents][agents];
	double featuresTmp[agents][m.nFeatures];

     Lmax = floor(L) + 1;
     Lmin = floor(L )  -1;
     /* features de-meaned */
	for(i=0; i<m.agents; i++)
	{	
		for(j=0; j<m.nFeatures; j++)
		{
			featuresTmp[i][j] = m.features[j*agents + i] - mou;
		}
	}	
     /*initialize matrix*/
	for(i=0; i<m.agents; i++)
	{	
		for(j=0; j<m.agents; j++)
		{
			featuresTmp2[i][j] = 0;	
		}
	}

	/* Product of matrices */
	for(i=0; i<m.agents; i++)
	{	
		for(j=0; j<m.agents; j++)
		{		
			for (l=0; l<m.nFeatures;l++) 
			{
				featuresTmp2[i][j] = featuresTmp2[i][j] + (featuresTmp[i][l] * featuresTmp[j][l]); 
			}
		}	
	}
     /*correlation matrix */
     //printf("Corr-Matrix\n");
	for(i=0; i<m.agents; i++)
	{	
		for(j=0; j<m.agents; j++)
		{
			A[i*m.agents+j] = (double) (featuresTmp2[i][j] / (double)sqrt(featuresTmp2[i][i] * featuresTmp2[j][j])); 
       //        printf("%2.2f \t",A[i*m.agents+j]);
		}
         // printf("\n");
	}

     /*New interaction*/
	test = 0;
	upthreshold = 1;
	downthreshold = -1;

	while (test == 0) 
	{
		threshold = (double) ((upthreshold + downthreshold )/ 2);
		counter = 0;   
		for(i=0; i<m.agents; i++)
		{    
			for(j=i; j<m.agents; j++)
			{
			    if( A[i*m.agents+j] > threshold && ( i != j) )
				    counter++;
			}
	    	}

		if(counter <= Lmax &&  counter >= Lmin ) 
		{
		  test = 1;
		}
		if(counter >Lmax )
			downthreshold = threshold; 
		if(counter < Lmin)
			upthreshold = threshold;    
	}
	printf("Threshold :%f\n", threshold);
	return threshold;
}

/* Function to compute Adjacency matrices at d<=2 
void multiplyer(int agents,  int *A, int *C) {

	int i, j, l;
	int temp;

	for(i=0; i<agents; i++)
	{	
		for(j=0; j<agents; j++)
		{		
			C[i*agents + j] = 0;
			for (l=0; l<agents;l++) 
				C[i*agents + j] += ( A[i*agents + l] * A[j*agents + l]); 
		}	
	} 
	
	for(i=0; i<agents; i++)
	{	
		for(j=0; j<agents; j++)
		{	
			C[i*agents + j]  += A[i*agents + j] ;
			if (C[i*agents + j]  > 1 )
					C[i*agents + j] = 1;
		}      
	}  
} */
 
 
/* for a given threshold, computes the degree and  if degree==0 reinitilize features */
void update(double L, int *degree, double *A, double threshold, double *features){

	int i, j, k;
     double cc;

     cc=0;
	/* Generates degree vectors */ 
	for(i=0; i<m.agents; i++)
	{
		degree[i] = 0;

		for(j=0; j<m.agents; j++)
		{
			if(m.A[i*m.agents +j] >= threshold &&( j != i) )
			{
				degree[i]++;
			}
	   	}
          /* if degree less than 1, reinitizlize all features */
		if(degree[i] < 0.1* m.agents)
		{
               cc++;
			for(k=0; k<m.nFeatures; k++)
			{
				features[k*m.agents + i] = (double) (rand() %1000) / (double) 1000;
			}
		}
          /* if degree == 0 reinitizlize one feature only 
		if(degree[i] <2)
		{
                    k= rand()%(m.nFeatures);
				features[k*m.agents + i] = (double) (rand() %1000) / (double) 1000;
		}*/
	}
     printf("Fraction - new features : %2.2f\n",cc/m.agents);

}
