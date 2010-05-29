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

	/* Here we have a problem and this is the best solution I could find right now, please dont change this malloc */
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
			//printf("%f\t", features[j*agents + i]);
		}

		for(j=0; j<agents; j++)
		{
			A[i*agents + j] = 0;		
		}
		//printf("\n");
	}

	/* etichetta che si visualizza ... gli step di simulazione */
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
	
	if(A) free(A);
	this->A = (double*) malloc(sizeof(double)*agents*agents);

	if(features) free(features);
	this->features = (double*) malloc (sizeof(double)*agents*agents);

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
			features[i*agents + j] = (double) (rand() %10) / (double) 10;
		}

		for(j=0; j<agents; j++)
		{
			A[i*agents + j] = 0;		
		}
	}
	
	/* etichetta che si visualizza ... gli step di simulazione */
 	t = 0;
} 

void model::step(){

	int i, j; 
	double threshold;
	
	threshold = newInteraction(10.0, A, agents);
	update(degree, A, threshold, features);
	
	t += 1;
}

void interaction(int agents, int m, double *p, double *q, double *A, double epsilon, double friendship) 
{

	int i, j, count;
     	double random;
	int outDegree[agents];

	/* Initialize outDegree vector */
	for (i=0; i<agents; i++)
	{
		outDegree[i] = 0;
	}

	/* Adjacency matrix */ 
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

	/*for(i=0; i<agents; i++)
	{
		printf(" outdegree %d = %d\n", i, outDegree[i]);
	}*/

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
}

double newInteraction(double L, double *A, int agents)
{
	int i, j, l, counter, test;
	double upthreshold, downthreshold, threshold;
	double mou = 0.5;
	double featuresTmp2[agents][agents];
	double featuresTmp[agents][m.nFeatures];

	for(i=0; i<m.agents; i++)
	{	
		for(j=0; j<m.nFeatures; j++)
		{
			featuresTmp[i][j] = m.features[j*agents + i] - mou;
			//printf("%f\t", featuresTmp[i][j]);
				
		}
		//printf("\n");
	}	
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
				//printf("%f\t", featuresTmp[i][l] * featuresTmp[j][l]);
			}
			//printf("%f\t", featuresTmp2[i][j]);	
			//printf("\n");		
		}	
		//printf("\n");
	}

	for(i=0; i<m.agents; i++)
	{	
		for(j=0; j<m.agents; j++)
		{
			A[i*m.agents+j] = (double) (featuresTmp2[i][j] / (double)sqrt(featuresTmp2[i][i] * featuresTmp2[j][j])); 
			//printf("%f\t", A[i*m.agents+j]);
		}
		//printf("\n");
	}
	test = 0;
	upthreshold = 1;
	downthreshold = 0;
	//printf("Prima del while\n");
	while (test == 0) 
	{
		threshold = (double) ((upthreshold + downthreshold )/ 2);
		//printf("threshold = %f  ", threshold);
		counter = 0;
		for(i=0; i<m.agents; i++)
		{    
			for(j=i; j<m.agents; j++)
			{
			    if( A[i*m.agents+j] >= threshold && i != j)
				    counter++;
			}
	    	}
		//printf("counter = %d", counter);
		if(counter <= (12) &&  counter >= (8) ) 
		{
		  test = 1;
		}
		if(counter > 12)
			downthreshold = threshold; 
		if(counter < 8)
			upthreshold = threshold;    
	}
	//printf("Dopo del while\n");
	printf("%f\n", threshold);
	return threshold;
}

/* Function to compute Adjacency matrices at d<=2 */
void multiplyer(int agents,  int *A, int *C) {

	int i, j, l;
	int temp;

	/* Product of matrices */
	for(i=0; i<agents; i++)
	{	
		for(j=0; j<agents; j++)
		{		
			C[i*agents + j] = 0;
			for (l=0; l<agents;l++) 
				C[i*agents + j] += ( A[i*agents + l] * A[j*agents + l]); 
		}	
	} 
	
	/* Normalize to Adjacency  matrix at distance d=2*/
	for(i=0; i<agents; i++)
	{	
		for(j=0; j<agents; j++)
		{	
			C[i*agents + j]  += A[i*agents + j] ;
			if (C[i*agents + j]  > 1 )
					C[i*agents + j] = 1;
		}      
	}  
}

 
 
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
		//printf("degree[%d] = %d\n", i, degree[i]);
		if(degree[i] == 0)
		{
			for(k=0; k<m.nFeatures; k++)
			{
				features[k*m.agents + i] = (double) (rand() %1000) / (double) 1000;
				//printf("%f\t", features[j*agents + i]);
			}
		}
	}
}
