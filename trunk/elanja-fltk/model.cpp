#include "model.h"

model m; // istanza del modello
int t; // counter delle iterazioni

extern bool externAgentOn;
extern bool dinamicProductsOn;
extern int W,H;

void model::init(int agents, int distance, double Agroup, double epsilon, double friendship){
	int i;

	printf("Initializing Model ... \n");	

	/* "this" field of the class model */
	this->agents = agents;
	this->distance = distance;
	this->m = Agroup * agents;
	this->epsilon = epsilon;
	this->friendship = friendship;
	//this->m = (Agroup*agents)/100;

	this->p = (double*) malloc ((sizeof(double))*agents);
	this->q = (double*) malloc(sizeof(double)*agents);
	this->R = (double*) malloc(sizeof(double)*agents*agents);

	this->A = (int*) malloc(sizeof(int)*agents*agents);
	this->B = (int*) malloc(sizeof(int)*agents*agents);

	this->degree = (int*) malloc(sizeof(int)*agents);
	this->A_degree = (int*) malloc(sizeof(int)*agents);
	this->B_degree = (int*) malloc(sizeof(int)*agents);

	this->composition = (double*) malloc(sizeof(double)*agents);	


	for(i=0; i<agents; i++)	
	{
		p[i] = 0.5; 
		q[i] = 0.5;
	}
     /* inizializza*/
/*	for(i=0; i<agents;i++)
	{
		degree[i] = 10; 
		composition[i] = (double) 0;
		p[i] = 0.0; 
		q[i] = 0.0;
     }*/
	t = 0; /* etichetta che si visualizza ... gli step di simulazione */
}

void model::reinit(int agents, int distance, double Agroup, double epsilon, double friendship){
	int i;
	
	printf("Reinitializing Model ... \n");

	this->agents = agents;
	this->distance = distance;     
	this->m = Agroup * agents;
	this->epsilon = epsilon;
	this->friendship = friendship;
	
	if(p) free(p);
	this->p = (double*) malloc ((sizeof(double))*agents);
	if(q) free(q);
	this->q = (double*) malloc(sizeof(double)*agents);
	if(R) free(R);
	this->R = (double*) malloc(sizeof(double)*agents*agents);
	if(A) free(A);
	this->A = (int*) malloc(sizeof(int)*agents*agents);
	if(B) free(B);
	this->B = (int*) malloc(sizeof(int)*agents*agents);

	if(degree) free(degree);
	this->degree = (int*) malloc(sizeof(int)*agents);
	if(A_degree) free(A_degree);
	this->A_degree = (int*) malloc(sizeof(int)*agents);
	if(B_degree) free(B_degree);
	this->B_degree = (int*) malloc(sizeof(int)*agents);

	if(composition) free(composition);
	this->composition = (double*) malloc(sizeof(double)*agents);
 	t = 0;
} 

void model::step(){

     int i, j;
     /* "interactions" creates adjacency matrix */
	interaction(agents, m,  p, q, A, epsilon, friendship); 
      
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

 			p[i] = 0.2 + (0.5 * (double) A_degree[i] / degree[i] ); 
               q[i] = 0.2 + (0.5 * (double) B_degree[i] / degree[i] ); 
          }
     } 

	multiplyer(agents, A, B);  
//	update(agents, p, q, degree, A_degree, B_degree);

	//printf("Faccio un passo\n");
    /*  externalUpdate(agents, A, p, q, EPSILON, degree);*/

	t += 1;
}

void interaction(int agents, int m, double *p, double *q, int *A, double epsilon, double friendship) {

	int i, j;
	int link;
     double random;

	/* Adjacency matrix */ 
	for(i=0; i<agents; i++)
	{
		for(j=0; j<agents; j++)
		{
               link = 0;
 		     random  = (double) (rand() %1000) / (double) 1000;
     		if( (random < epsilon) )   
               {
                    A[i*agents + j] = 1;
               } else {  
                    A[i*agents +j] = 0;
               }

 		     random  = (double) (rand() %1000) / (double) 1000;
     		if( (random < p[i] * p[j] ) && ( (j < m) && (i < m) )  )   
               {
                    A[i*agents + j] = 1;
               } 

     		if( (random < q[i] * p[j] ) &&  ( (j >= m) && (i < m) )  )   
               {
                    A[i*agents + j] = 1;
               } 

     		if( (random < q[i] * q[j] ) &&  ( (j >= m) && (i >= m) )  )   
               {
                    A[i*agents + j] = 1;
               } 
		}
	}
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
