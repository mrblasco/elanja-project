#include "../h/model.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

model m; // istance of the model
int t; // counter for iteractions 

extern int w, h;
 
void model::init(int agents,  double rho, int nFeatures, double threshold, int friends){

	int i, j;

	printf("Initializing Model ... \n");	

	/* "this" field of the class model */
	this->agents = agents;
	this->rho = rho;
	this->nFeatures = nFeatures;
	this-> threshold = threshold;
	this->friends = friends;
     
  	this->F = (int*) malloc(sizeof(int)*nFeatures);
	this->features = (double*) malloc(sizeof(double)*agents*(int)nFeatures);
	this->degree = (int*) malloc(sizeof(int)*agents);
	this->A = (double*) malloc(sizeof(double)*agents*agents);

	for(i=0; i<agents; i++)	
	{
     		degree[i] =4;
          	genFeatures(i);
	}

	t = 0; 
}

void model::reinit(int agents, double rho,  int nFeatures, double threshold, int friends){
	int i, j;

	printf("Reinitializing Model ... \n");
 
	this->agents = agents;
     	this->threshold = threshold;
	this->nFeatures = nFeatures;
	this->rho = rho;
	this->friends = friends;     

	if(F) free(F);
	this->F = (int*) malloc(sizeof(int)*nFeatures);
	if(A) free(A);
	this->A = (double*) malloc(sizeof(double)*agents*agents);
	if(features) free(features);
	this->features = (double*) malloc(sizeof(double)*agents*(int)nFeatures);
	if(degree) free(degree);
	this->degree = (int*) malloc(sizeof(int)*agents);
	
	for(i=0; i<agents; i++)	
	{
     		degree[i] =4;
          	genFeatures(i);  
	}
 	t = 0;
} 


/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%      STEP              %%%%%%%%%%%%%%%%
%%%%%%%%      FUNCTION     %%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
void model::step(){

int i, j;

     /* Compute correlation matrix*/
	genCorrMat();

     /* Compute degrees and adjacency matrix*/
	update();

	t += 1;
}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%   GENERATE FEATURES       %%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

void genFeatures(int i){
     
     int j, uNum;

	for(i=0; i<m.agents; i++)	
	{
		for(j=0; j<m.nFeatures; j++)
		{
               uNum = (rand()%2000) - 1000;
 			m.features[j*m.agents + i] = (double) uNum / (double) 1000;
		}
     }	
}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%   COMPUTE CORRELATION     %%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

double genCorrMat()
{
	int i, j, l;
     double temp, xx, yy;

     /* Initialize adjacency matrix*/
	for(i=0; i<m.agents; i++)
	{
	     for(j=0; j<m.agents; j++)
	     {
		     m.A[i*m.agents + j] = 0;	
          }	
	}
	
	for(i=0; i<m.agents; i++)
	{	
          for(j=0;j<m.agents;j++)
          {
               xx=0;     
               yy=0;
               temp = 0;
		     for(l=0; l<m.nFeatures; l++)
		     {
                    temp += m.features[l*m.agents + i] * m.features[l*m.agents + j];
                    xx +=    pow(m.features[l*m.agents + i],2);
                    yy +=    pow(m.features[l*m.agents + j],2);
		     }
               m.A[i*m.agents+j] = temp / (pow(xx,0.5) *pow(yy,0.5));
          }
	}	
}
 

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%   COMPUTE DEGREES       %%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
void update(){

	int i, j, control;
     double rnd;
     double tvalue;
   
	for(i=0; i<m.agents; i++)
	{
		m.degree[i] = 0;

     	/* Compute the degree with positive ...  */ 
          if(m.threshold>=0)
          {
               control = 0;
               tvalue = m.threshold;
               while(control==0)
               {
                    m.degree[i]=0;
		          for(j=0; j<m.agents; j++)
		          {
			          if( m.A[i*m.agents +j] > tvalue &&( j != i) )
			          {
				         m.degree[i]++;
			          }
	             	}

                    if (m.degree[i]<m.friends)
                    {
                         control = 1;
                    }
                    tvalue = tvalue + 0.05;
               }
               /* compile Adjacency matrix */
	          for(j=0; j<m.agents; j++)
	          {
		          if( m.A[i*m.agents +j] > tvalue &&( j != i) )
		          {
			         m.A[i*m.agents +j] =1;

		          } else {

			         m.A[i*m.agents +j] =0;
                    }
             	}

          /* ...  or negative correlation */
          } else {

               control = 0;
               tvalue = m.threshold;
               while(control==0)
               {
                    m.degree[i]=0;
		          for(j=0; j<m.agents; j++)
		          {
			          if( m.A[i*m.agents +j] < tvalue &&( j != i) )
			          {
				         m.degree[i]++;
			          }
	             	}
                    if (m.degree[i]<m.friends)
                    {
                         control = 1;
                    }
                    tvalue = tvalue - 0.05;
               }
                    /* compile Adjacency matrix */
		          for(j=0; j<m.agents; j++)
		          {
			          if( m.A[i*m.agents +j] < tvalue &&( j != i) )
			          {
				         m.A[i*m.agents +j] =1;

			          } else {

				         m.A[i*m.agents +j] =0;
                         }
	             	}
               } 

          /* reinitizlize at random a fraction rho of agents */
               rnd = (rand()%1000) / (double) 1000;
         		if (rnd < m.rho)
		          genFeatures(i);
	}
}
 
