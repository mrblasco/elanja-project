#include "model.h"

model m; // istanza del modello
int t; // counter delle iterazioni
extern bool externAgentOn;
extern bool dinamicProductsOn;
extern int W,H;

void model::init(int agents, int distance, double population, double epsilon, int friendship){
	int i;
	
	this->agents = agents;
	this->distance = distance;
	this->population = population;
	this->epsilon = epsilon;
	this->friendship = friendship;
	this->m = (population*agents)/100;


	this->p = (double*) malloc ((sizeof(double))*agents);
	this->q = (double*) malloc(sizeof(double)*agents);
	this->R = (double*) malloc(sizeof(double)*agents*agents);

	this->A = (int*) malloc(sizeof(int)*agents*agents);
	this->B = (int*) malloc(sizeof(int)*agents*agents);

	this->degree = (int*) malloc(sizeof(int)*agents);
	this->A_degree = (int*) malloc(sizeof(int)*agents);
	this->B_degree = (int*) malloc(sizeof(int)*agents);

	this->composition = (double*) malloc(sizeof(double)*agents);	

	for(i=0; i<agents;i++)
	{
		degree[i] = rand() % 100 + 1;
		composition[i] = (double) (rand() % 10)/10;
		p[i] = 0.0; 
		q[i] = 0.0;

	}

	t = 0;
}

void model::reinit(double agents, double population, double epsilon, int friendship){
	int i;
	
	this->agents = agents;
	this->population = population;
	this->epsilon = epsilon;
	this->friendship = friendship;
	this->m = (population*agents)/100;


	this->p = (double*) malloc ((sizeof(double))*agents);
	this->q = (double*) malloc(sizeof(double)*agents);
	this->R = (double*) malloc(sizeof(double)*agents*agents);

	this->A = (int*) malloc(sizeof(int)*agents*agents);
	this->B = (int*) malloc(sizeof(int)*agents*agents);

	this->degree = (int*) malloc(sizeof(int)*agents);
	this->A_degree = (int*) malloc(sizeof(int)*agents);
	this->B_degree = (int*) malloc(sizeof(int)*agents);

	this->composition = (double*) malloc(sizeof(double)*agents);

	for(i=0; i<agents;i++)
	{
		degree[i] = rand() % 100 + 1;
		composition[i] = (double) (rand() % 10)/10;
		p[i] = 0.0; 
		q[i] = 0.0;

	}

	t = 0;
}

void model::step(){
	//interaction(agents, m, distance, p, q, A, R, degree, A_degree, B_degree);
	//multiplyer(agents, m, distance, A, A, B, degree, A_degree, B_degree, distance); 
	//update(agents, p, q, degree, A_degree, B_degree);

	//printf("Faccio un passo\n");
    /*  externalUpdate(agents, A, p, q, EPSILON, degree);*/
}

double urand(){
	return (double)(rand()%RAND_MAX)/(double)RAND_MAX;
}

/* Function to compute Adjacency matrices at d<=2 */
void multiplyer(int agents, int m, int distance, int *A, int *B, int *C, int *degree, int *A_degree, int *B_degree, int d) {

	int i, j, l;

	FILE *out_1;

	out_1 = fopen("degree1.dat", "w");
	
	if(distance==2)
	{

		/*  Initialize Am */
		for(i=0; i<agents; i++) 
		{
			for(j=0; j<agents; j++)
			{ 
				*(C + i*agents + j) = 0;
			}
		}

		/* Degree vector distance 1 */ 
		for(i=0; i<agents; i++)
		{
			for(j=0; j<agents; j++)
			{
				*(degree+i) += *(A+(i*agents)+j);
		   	}
			fprintf(out_1,"%d\t",*(degree+i));
		}

		/* Degree of A-type agents vector*/ 
		for(i=0; i<agents; i++)
		{
			for(j=0; j<m; j++)
			{
				*(A_degree+i) += *(A+(i*agents)+j);
		   	}
			fprintf(out_1,"%d\t",*(A_degree+i));
			for(j=m; j<agents; j++)
			{
				*(B_degree+i) += *(A+(i*agents)+j);
		   	}
			fprintf(out_1,"%d\t",*(B_degree+i));
		}
		fprintf(out_1,"\n");		

		/* Product */
		for(i=0; i<agents; i++)
		{	
			for(j=0; j<agents; j++)
			{		
				for (l=0; l<agents;l++) 
					*(C + i*agents +j) += (*(A + i*agents +l) * *(B + j*agents +l)); 
			}	
		} 
		/* Normalize Adjacency matrix adding distance one*/
		for(i=0; i<agents; i++)
		{	
			for(j=0; j<agents; j++)
			{	
				*(C + i*agents +j) += *(A + i*agents +j);
				if (*(C + i*agents +j) > 1 )
						*(C + i*agents +j) = 1;
			}      
		}

		/* Degree vector distance 1 */ 
		for(i=0; i<agents; i++)
		{
			for(j=0; j<agents; j++)
			{
				*(degree+i) += *(C+(i*agents)+j);
		   	}
		}

		/* Degree of A-type agents vector*/ 
		for(i=0; i<agents; i++)
		{
			for(j=0; j<m; j++)
			{
				*(A_degree+i) += *(C+(i*agents)+j);
		   	}
			for(j=m; j<agents; j++)
			{
				*(B_degree+i) += *(C+(i*agents)+j);
		   	}
 		}
 		 
	}
	else if (distance==1)
	{
		/* Degree vector*/ 
		for(i=0; i<agents; i++)
		{
			for(j=0; j<agents; j++)
			{
				*(degree+i) += *(A+(i*agents)+j);
		   	}
		}

		/* Degree of A-type agents vector*/ 
		for(i=0; i<agents; i++)
		{
			for(j=0; j<m; j++)
			{
				*(A_degree+i) += *(A+(i*agents)+j);
		   	}
			for(j=m; j<agents; j++)
			{
				*(B_degree+i) += *(A+(i*agents)+j);
		   	}
		}
	}
	else
		printf("Distance error d = %d\n", distance);
}

void interaction(int agents, int m, int distance, double *p, double *q, int *A, double *R, int *degree, int *A_degree, int *B_degree) {

	int i, j;
	double link;
	
	/* Initialize matrices */
	for(i=0; i<agents; i++)
        {
	   for(j=0; j<agents; j++)
	   {
	        *(A+(i*agents)+j) = 0; /* adjacency matrix */
	   }
        }

	/* Link formation*/
	/* R has random Upper-triangle and zeros on diagonal */
	for(i=0; i<agents; i++)
     	{
	   	for(j=i; j<agents; j++) 
	   	{
			if(i==j) 
			{
				/* -2 => zero on diagonal (+2 ones) */
				*(R+(i*agents)+j) = -2.0; 
			
			} else {
				*(R+(i*agents)+j) = (double) (rand() %10001) / 10000;
			}
	   	}
	}
	/* R is symmmetric */
	for(j=0; j<agents; j++)
     	{
		for(i=j; i<agents; i++)
		{
			*(R+(i*agents)+j) = *(R+(j*agents)+i);
		}
     	}

	/* Adjacency matrix */ 
	for(i=0; i<agents; i++)
	{
		for(j=i; j<agents; j++)
		{
			if(j < m && i < m ) 
			{	
				link = (double) *(R+(i*agents)+j) - (*(p+i) * *(p+j)); /* provare con il + */
			} else if (j >= m  && i < m ) 
			{
				link = (double) *(R+(i*agents)+j) - (*(q+i) * *(p+j) );  /*  provare con il + */

			} else if (j >= m && i >= m) 
			{		
				link = (double) *(R+(i*agents)+j) - ( *(q+i) * *(q+j) );	
			}
			if (link < 0) 
			{
				*(A+(i*agents)+j) = 1; 		 
			}	 
		}
	}
	/* Am is symmmetric */
	for(j=0; j<agents; j++)
    	{
		for(i=j; i<agents; i++)
		{
			*(A+(i*agents)+j) = *(A+(j*agents)+i);
	   	}
     	}

	/* Initialize degree, A_degree, B_degree vectors to 0 at each iteraction */
	for(i=0; i<agents; i++)
	{
		*(degree+i) = 0;
		*(A_degree+i) = 0;
		*(B_degree+i) = 0;
	}
}

void update(int agents, double *p, double *q, int *degree, int *A_degree, int *B_degree){

	int i;

	/* Calculate the new p and q probabilities */
	/* It is a linear combination of "relative degree" and connection composition*/
	/* Relative degree: degree / total nodes number */

	for(i=0; i<agents; i++)
	{	
		if(*(degree+i) > 0)
		{	 
 			*(p+i) = 0.1 + (0.5 * (double)  *(A_degree + i) / *(degree + i)); 
			*(q+i) = 0.1 + (0.5 * (double) *(B_degree + i) / *(degree + i)); 
		}
	}	
}

void externalUpdate(int agents, int *A, double *p, double *q, double epsilon, int *degree){

	double random;
	int pos;
	int tmp, i, j;

	for(i=0; i<agents; i++)
	{

		if(*(degree+i) != 1)		
		{
			random = (double) (rand() %1000) / 1000;
			if(random < epsilon)
			{

				pos = (rand() %(*(degree+i) -1));
				tmp = 0; 
				for (j=0; j<agents; j++)
				{
					if (tmp != -1 && j != i && *(A+(i*agents)+j) == 1) 
					{	
								tmp++;
							if(tmp == pos)
							{
								*(p+i) = *(p+j);
								*(q+i) = *(q+j);
								tmp = -1;
							}

					}
				}
			}
		}
	}
}
