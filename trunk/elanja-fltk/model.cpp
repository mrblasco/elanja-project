#include "model.h"

model m; // istanza del modello
int t; // counter delle iterazioni

extern bool externAgentOn;
extern bool dinamicProductsOn;
extern int W,H;

void model::init(int agents, int distance, double rho, double epsilon, double friendship, int nFeatures, double threshold){
	int i, j;

	printf("Initializing Model ... \n");	

	/* "this" field of the class model */
	this->agents = agents;
	this->distance = distance;
	this->rho = rho;
	this->m = rho * agents;
	this->epsilon = epsilon;
	this->friendship = friendship;
	this->threshold = threshold;
	this->nFeatures = nFeatures;

	this->features = (double*) malloc(sizeof(double)*agents*nFeatures);
	
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

void model::reinit(int agents, int distance, double rho, double epsilon, double friendship, double threshold){
	int i, j;
	
	printf("Reinitializing Model ... \n");

	this->agents = agents;
	this->distance = distance;
	this->rho = rho;
	this->m = rho * agents;
	this->epsilon = epsilon;
	this->friendship = friendship;
	this->threshold = threshold;
	this->nFeatures = nFeatures;

	
	if(A) free(A);
	this->A = (double*) malloc(sizeof(double)*agents*agents);

	if(features) free(features);
	this->features = (double*) malloc(sizeof(double)*agents*nFeatures);

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
	double threshold;
     double L;
     L = 0.2 * agents;
	
	threshold = newInteraction(L, A, agents);
	update(degree, A, threshold, features);
	
	t += 1;
}

/* void interaction(int agents, int m, double *p, double *q, double *A, double epsilon, double friendship) 
{

	int i, j, count;
     	double random;
	int outDegree[agents];

	for (i=0; i<agents; i++)
	{
		outDegree[i] = 0;
	}

	for(i=0; i<agents; i++)
	{
		for(j=i; j<agents; j++)
		{
	 		random  = (double) (rand() %1000) / (double) 1000;
	     		if( ((random < epsilon) && (A[i*agents + j] == 1)) || (j == i))   
		       	{
				A[i*agents + j] = 1;
				A[j*agents + i] = 1;
				outDegree[i]++;
				outDegree[j]++;
		       	} 
			else 
			{
		 		random  = (double) (rand() %1000) / (double) 1000;
		     		if( (random < p[i] * p[j] ) && ( (j < m) && (i < m) )  )   
			       	{
				    	A[i*agents + j] = 1;
					A[j*agents + i] = 1;
					outDegree[i]++;
					outDegree[j]++;
			       	} 
		     		if( (random < q[i] * p[j] ) &&  ( (j >= m) && (i < m) )  )   
			       	{
				    	A[i*agents + j] = 1;
					A[j*agents + i] = 1;
					outDegree[i]++;
					outDegree[j]++;
			       	} 

		     		if( (random < q[i] * q[j] ) &&  ( (j >= m) && (i >= m) )  )   
			       	{
				    	A[i*agents + j] = 1;
					A[j*agents + i] = 1;
					outDegree[i]++;
					outDegree[j]++;
			       	} 
			}
		}
	}

 
	for(i=0; i<agents; i++)
	{
		count = 0;
		while(outDegree[i] > OUTDEGREE_INIT && count < 2*agents)
		{
			j = rand()%agents;
			if(i != j && A[i*agents + j] == 1 && outDegree[j] > OUTDEGREE_INIT)
			{
				A[i*agents + j] = 0;
				A[j*agents + i] = 0;
				outDegree[i] = outDegree[i] -1;
				outDegree[j] = outDegree[j] -1;
			}	
			count++;
		}

	}
} */


/* compute correlation matrix and finds a threshold */
double newInteraction(double L, double *A, int agents)
{
	int i, j, l, counter, test;
	double upthreshold, downthreshold, threshold;
	double mou = 0.5;
	double featuresTmp2[agents][agents];
	double featuresTmp[agents][m.nFeatures];

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
	for(i=0; i<m.agents; i++)
	{	
		for(j=0; j<m.agents; j++)
		{
			A[i*m.agents+j] = (double) (featuresTmp2[i][j] / (double)sqrt(featuresTmp2[i][i] * featuresTmp2[j][j])); 
		}
	}

     /*New interaction*/
	test = 0;
	upthreshold = 1;
	downthreshold = 0;

	while (test == 0) 
	{
		threshold = (double) ((upthreshold + downthreshold )/ 2);
		counter = 0;
		for(i=0; i<m.agents; i++)
		{    
			for(j=i; j<m.agents; j++)
			{
			    if( A[i*m.agents+j] >= threshold && i != j)
				    counter++;
			}
	    	}
		if(counter <= (L*1.05) &&  counter >= (L*0.95) ) 
		{
		  test = 1;
		}
		if(counter >(L*1.05))
			downthreshold = threshold; 
		if(counter < (L*1.05))
			upthreshold = threshold;    
	}
	printf("%f\n", threshold);
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
void update(int *degree, double *A, double threshold, double *features){

	int i, j, k;

	/* Generates degree vectors */ 
	for(i=0; i<m.agents; i++)
	{
		degree[i] = 0;

		for(j=i; j<m.agents; j++)
		{
			if(m.A[i*m.agents +j] >= threshold && j != i)
			{
				degree[i]++;
			}
	   	}
          /* if degree == 0 reinitizlize all features 
		if(degree[i] <1)
		{
			for(k=0; k<m.nFeatures; k++)
			{
				features[k*m.agents + i] = (double) (rand() %1000) / (double) 1000;
			}
		}*/
          /* if degree == 0 reinitizlize one feature only */
		if(degree[i] <1)
		{
                    k= rand()%(m.nFeatures);
				features[k*m.agents + i] = (double) (rand() %1000) / (double) 1000;
		}

	}
}
