#include "../h/model.h"
#include "../h/const.h"

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

	t = 0; 
}

 
/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%      STEP              %%%%%%%%%%%%%%%%
%%%%%%%%      FUNCTION     %%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
void model::step(){

     int i, j;
 

	for(i=0; i<agents; i++)	
	{
		degree[i] =0;
     	genFeatures(i);
	}

     /* Compute correlation matrix*/
	genCorrMat();

     /* Compute degrees and adjacency matrix*/
	update();

	t += 1;
}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%   GENERATE FEATURES       %%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

void model::genFeatures(int i){
     
     int j, uNum;

	for(i=0; i<agents; i++)	
	{
		for(j=0; j<nFeatures; j++)
		{
               uNum = (rand()%2000) - 1000;
 			features[j*agents + i] = (double) uNum / (double) 1000;
		}
     }	
}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%   COMPUTE CORRELATION     %%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

double model::genCorrMat()
{
	int i, j, l;
     double temp, xx, yy;

     /* Initialize adjacency matrix*/
	for(i=0; i<agents; i++)
	{
	     for(j=0; j<agents; j++)
	     {
		     A[i*agents + j] = 0;	
          }	
	}
	
	for(i=0; i<agents; i++)
	{	
          for(j=0;j<agents;j++)
          {
               xx=0;     
               yy=0;
               temp = 0;
		     for(l=0; l<nFeatures; l++)
		     {
                    temp += features[l*agents + i] * features[l*agents + j];
                    xx +=    pow(features[l*agents + i],2);
                    yy +=    pow(features[l*agents + j],2);
		     }
               A[i*agents+j] = temp / (pow(xx,0.5) *pow(yy,0.5));
          }
	}	
}
 

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%   COMPUTE DEGREES       %%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
void model::update(){

	int i, j, control;
     double rnd;
     double tvalue;
   

	for(i=0; i<agents; i++)
	{
		degree[i] = 0;

     	/* Compute the degree with positive ...  */ 
          if(threshold>=0)
          {
               control = 0;
               tvalue = threshold;
               while(control==0)
               {
                    degree[i]=0;
		          for(j=0; j<agents; j++)
		          {
			          if( A[i*agents +j] > tvalue &&( j != i) )
			          {
				         degree[i]++;
			          }
	             	}


                    if (degree[i]<friends)
                    {
                         control = 1;
                    }
                    tvalue = tvalue + 0.05;
               }
               /* compile Adjacency matrix */
	          for(j=0; j<agents; j++)
	          {
		          if( A[i*agents +j] > tvalue &&( j != i) )
		          {
			         A[i*agents +j] =1;

		          } else {

			         A[i*agents +j] =0;
                    }
             	}

          /* ...  or negative correlation */
          } else {

               control = 0;
               tvalue = threshold;
               while(control==0)
               {
                    degree[i]=0;
		          for(j=0; j<agents; j++)
		          {
			          if( A[i*agents +j] < tvalue &&( j != i) )
			          {
				         degree[i]++;
			          }
	             	}
                    if (degree[i]<friends)
                    {
                         control = 1;
                    }
                    tvalue = tvalue - 0.05;
               }
                    /* compile Adjacency matrix */
		          for(j=0; j<agents; j++)
		          {
			          if( A[i*agents +j] < tvalue &&( j != i) )
			          {
				         A[i*agents +j] =1;

			          } else {

				         A[i*agents +j] =0;
                         }
	             	}
               } 

          /* reinitizlize at random a fraction rho of agents */
               rnd = (rand()%1000) / (double) 1000;
         		if (rnd < rho)
		          genFeatures(i);
	}
}
 
