#include "model.h"

model m; // istanza del modello
int t; // counter delle iterazioni

extern bool externAgentOn;
extern bool dinamicProductsOn;
extern int W,H;

void model::init(int agents, int distance, double rho, double epsilon, double friendship){
	int i, j;

	printf("Initializing Model ... \n");	

	/* "this" field of the class model */
	this->agents = agents;
	this->distance = distance;
	this->rho = rho;
	this->m = rho * agents;
	this->epsilon = epsilon;
	this->friendship = friendship;
	this->threshold = 0.8;

	this->p = (double*) malloc (sizeof(double)*agents);
	this->q = (double*) malloc (sizeof(double)*agents);
	this->R = (double*) malloc (sizeof(double)*agents*agents);

	this->features = (double*) malloc (sizeof(double)*agents);

	this->A = (double*) malloc(sizeof(double)*agents*agents);
	this->B = (int*) malloc(sizeof(int)*agents*agents);

	this->degree = (int*) malloc(sizeof(int)*agents);
	this->A_degree = (int*) malloc(sizeof(int)*agents);
	this->B_degree = (int*) malloc(sizeof(int)*agents);

	this->composition = (double*) malloc(sizeof(double)*agents);	


	for(i=0; i<agents; i++)	
	{
		p[i] = 0.5; 
		q[i] = 0.5;
		degree[i] = 1;
		composition[i] = 1;
		for(j=0; j<3; j++)
		{
			features[i*agents + j] = (double) (rand()%1000) / 1000;
		}

		for(j=0; j<agents; j++)
		{
			A[i*agents + j] = 0;		
		}
	}
	t = 0; /* etichetta che si visualizza ... gli step di simulazione */
}

void model::reinit(int agents, int distance, double rho, double epsilon, double friendship){
	int i, j;
	
	printf("Reinitializing Model ... \n");

	this->agents = agents;
	this->distance = distance;  
	this->rho = rho;
	this->m = rho * agents;
	this->epsilon = epsilon;
	this->friendship = friendship;
	
	if(p) free(p);
	this->p = (double*) malloc ((sizeof(double))*agents);
	if(q) free(q);
	this->q = (double*) malloc(sizeof(double)*agents);
	if(R) free(R);
	this->R = (double*) malloc(sizeof(double)*agents*agents);
	if(A) free(A);
	this->A = (double*) malloc(sizeof(double)*agents*agents);
	if(B) free(B);
	this->B = (int*) malloc(sizeof(int)*agents*agents);

	if(features) free(features);
	this->features = (double*) malloc (sizeof(double)*agents*3);

	if(degree) free(degree);
	this->degree = (int*) malloc(sizeof(int)*agents);
	if(A_degree) free(A_degree);
	this->A_degree = (int*) malloc(sizeof(int)*agents);
	if(B_degree) free(B_degree);
	this->B_degree = (int*) malloc(sizeof(int)*agents);

	if(composition) free(composition);
	this->composition = (double*) malloc(sizeof(double)*agents);

	for(i=0; i<agents; i++)	
	{
		p[i] = 0.5; 
		q[i] = 0.5;
		degree[i] = 1;
		composition[i] = 1;

		for(j=0; j<agents; j++)
		{
			A[i*agents + j] = 0;		
		}
	}
 	t = 0;
} 

void model::step(){

     int i, j;
     /* "interactions" creates adjacency matrix */
	//interaction(agents, m,  p, q, A, epsilon, friendship); 

	printf("Faccio la nuova interaction\n");
	
	newInteraction(features, threshold, A);

	printf("Finita la nuova interaction\n");
      
	/* Degree, A-type, B-type */ 
	for(i=0; i<agents; i++)
	{
		degree[i] = 0;
		A_degree[i] = 0;
		B_degree[i] = 0;

		for(j=0; j<m; j++)
		{
			A_degree[i] += A[i*agents +j];
			degree[i] += A[i*agents +j];
	   	}
		for(j=m; j<agents; j++)
		{
			B_degree[i] += A[i*agents +j];
			degree[i] += A[i*agents +j];
	   	}
	//printf(" degree %d = %d\n", i, degree[i]);

	}

     /* Composition and p & q vectors*/
	for(i=0; i<agents; i++)
	{
          if( degree[i] > 0)
          {	 
		     if(i<m)
		     {
                    composition[i]  = (double) A_degree[i] / (double) degree[i];

	        	} else {
                    composition[i]  = (double) B_degree[i] / (double) degree[i];
	        	}

 		p[i] = 0.05 + (0.5 * (double) A_degree[i] / degree[i] ); 
                q[i] = 0.05 + (0.5 * (double) B_degree[i] / degree[i] ); 
          }
     }

//	multiplyer(agents, A, B);  
//	update(agents, p, q, degree, A_degree, B_degree);

	//printf("Faccio un passo\n");
    /*  externalUpdate(agents, A, p, q, EPSILON, degree);*/

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

void newInteraction(double *features, double thershold, double *A)
{
	int i, j, l;
	double mou = 0.5;

	printf("Alloco memoria \n");

	double featuresTmp2[m.agents][m.agents];
	double featuresTmp[m.agents][3];

	printf("HO Allocato memoria \n");

	for(i=0; i<m.agents; i++)
	{	
		for(j=0; j<3; j++)
		{
			featuresTmp[i][j] = features[i*m.agents + j] - 0.5;	
				
		}
	}	
	for(i=0; i<m.agents; i++)
	{	
		for(j=0; j<m.agents; j++)
		{
			featuresTmp2[i][j] = 0;	
		}
	}

	printf("Arrivo qua dopo il mou !!\n");
	/* Product of matrices */
	for(i=0; i<m.agents; i++)
	{	
		for(j=0; j<3; j++)
		{		
			for (l=0; l<3;l++) 
				featuresTmp2[i][j] += (featuresTmp[i][l] * featuresTmp[j][l]); 
		}	
	}

	printf("Fatta la trasposta\n");

	for(i=0; i<m.agents; i++)
	{	
		for(j=0; j<m.agents; j++)
		{
			if(featuresTmp2[i][j] / (double)sqrt(featuresTmp2[i][i] * featuresTmp2[j][j]) >= thershold )
				A[i*m.agents+j] = 1;
			else
				A[i*m.agents+j] = 0;
		}
	}

	printf("Calcolata la nuova A\n");


	printf(" Fatta la free \n");
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

 
 
/*void update(int agents, double *p, double *q, int *degree, int *A_degree, int *B_degree){

	int i;

	for(i=0; i<agents; i++)
	{	
		if(degree[i] > 0)
		{	 
 			p[i]= 0.2+ (0.5 * (double)  *(A_degree + i) / *(degree + i)); 
			q[i]= 0.2 + (0.5 * (double) *(B_degree + i) / *(degree + i)); 
		}
	}	
}*/
/*
void externalUpdate(int agents, int *A, double *p, double *q, double epsilon, int *degree){

	double random;
	int pos;
	int tmp, i, j;

	for(i=0; i<agents; i++)
	{

		if(degree[i] != 1)		
		{
			random = (double) (rand() %1000) / 1000;
			if(random < epsilon)
			{

				pos = (rand() %(degree[i] -1));
				tmp = 0; 
				for (j=0; j<agents; j++)
				{
					if (tmp != -1 && j != i && A[i*agents +j]== 1) 
					{	
								tmp++;
							if(tmp == pos)
							{
								p[i]= *(p+j);
								q[i]= *(q+j);
								tmp = -1;
							}

					}
				}
			}
		}
	}
}*/
