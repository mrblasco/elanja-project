#include "model.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

model m; // istance of the model
int t; // counter for iteractions 

extern int w, h;
 
void model::init(int agents,  double rho, int nFeatures, double threshold, int w, int h){

	int i, j;

	printf("Initializing Model ... \n");	

	/* "this" field of the class model */
	this->agents = agents;
	this->rho = rho;
	this->nFeatures = nFeatures;
	this-> threshold = threshold;
//	this->friends = friends;
     
  	this->F = (int*) malloc(sizeof(int)*nFeatures);
	this->features = (double*) malloc(sizeof(double)*agents*(int)nFeatures);
	this->degree = (int*) malloc(sizeof(int)*agents);
	this->A = (double*) malloc(sizeof(double)*agents*agents);
	this->x = (double*) malloc(sizeof(double)*agents);
	this->y = (double*) malloc(sizeof(double)*agents);

	for(i=0; i<agents; i++)	
	{

     	degree[i] =4;
          genFeatures(i);
       
          /* regular lattice */
		//x[i] = (i %40) *18+20;		
		//y[i] =  (i/40)*50 +40;
          /* random graph */
		x[i] = 40+ (double) (rand() %w);		
		y[i] = 40+ (double) (rand() %h);

	}

	t = 0; 
}

void model::reinit(int agents, double rho,  int nFeatures, double threshold, int w, int h){
	int i, j;

	printf("Reinitializing Model ... \n");
 
	this->agents = agents;
	this->friends = friends;
     this->threshold = threshold;
	this->nFeatures = nFeatures;
	this->rho = rho;
     

	if(F) free(F);
	this->F = (int*) malloc(sizeof(int)*nFeatures);
	if(A) free(A);
	this->A = (double*) malloc(sizeof(double)*agents*agents);
	if(features) free(features);
	this->features = (double*) malloc(sizeof(double)*agents*(int)nFeatures);
	if(degree) free(degree);
	this->degree = (int*) malloc(sizeof(int)*agents);
	if(x) free(x);
	this->x = (double*) malloc(sizeof(double)*agents);
	if(y) free(y);
	this->y = (double*) malloc(sizeof(double)*agents);

	
	for(i=0; i<agents; i++)	
	{
     	degree[i] =4;
          genFeatures(i);
              
          /* regular lattice */
	//	x[i] = (i %40) *18+20;		
	//	y[i] =  (i/40)*50 +40;
          /* random graph */
		x[i] = 40+ (double) (rand() %w); 
		y[i] = 30+ (double) (rand() %h); 

	}
 	t = 0;
} 


/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%      STEP              %%%%%%%%%%%%%%%%
%%%%%%%%      FUNCTION     %%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
void model::step(int w, int h){

int i, j;

     /*Initialize adjacency matrix*/
	for(i=0; i<agents; i++)
	{
	     for(j=0; j<agents; j++)
	     {
		     A[i*agents + j] = 0;	
          }	
	}

     /* Compute correlation matrix*/
	genCorrMat();

     /* Compute degrees and adjacency matrix*/
	update();

     /* Coordinates on the plane*/
     coordinates(A, x, y, w, h);

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
           //    m.F[j]=0;
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
	
	double featuresTmp2[m.agents][m.agents];
	double featuresTmp[m.agents][m.nFeatures];

     /* features de-meaned */
	for(i=0; i<m.agents; i++)
	{	
		for(j=0; j<m.nFeatures; j++)
		{
			featuresTmp[i][j] = m.features[j*m.agents + i];
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
				featuresTmp2[i][j] += featuresTmp[i][l] * featuresTmp[j][l]; 
              // printf("%.2f ",featuresTmp2[i][j]);
			}
		}	
	}

     /*correlation matrix */
	for(i=0; i<m.agents; i++)
	{	
		for(j=0; j<m.agents; j++)
		{
			m.A[i*m.agents+j] = (double) (featuresTmp2[i][j] / (double) sqrt( featuresTmp2[i][i] * featuresTmp2[j][j])); 
		}
	}
}
 

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%   COMPUTE DEGREES       %%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
void update(){

	int i, j, control;
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

                    if (m.degree[i]<20)
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
                    if (m.degree[i]<20)
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
          /* if degree less than zero, reinitizlize all features */
        
          printf("m.degre%d \n",m.degree[i]);     

		if ( m.degree[i] < m.rho * m.agents)
		{
               genFeatures(i);
          }
	}
}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%   GENERATE COORDINATES %%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
void coordinates(double *A, double *x, double *y, int w, int h)
{
 	int k, i, j;
          double  dist_x, dist_y, norm_x,norm_y;
	double norm, distance, delta, rep_x, rep_y, spring_x, spring_y, F_x, F_y;
     double avg_x, avg_y;

     delta = 0.01;

     avg_x = avg_y = 0;
	for(k=0; k<0; k++)
	{		
          rep_x = rep_y = spring_x = spring_y = F_x = F_y = 0;
		for(i=0; i<m.agents; i++)
		{
		     for(j=i+1; j<m.agents; j++)
		     {
                    dist_x =  (x[i] - x[j]);
                    dist_y = (y[i] - y[j]);
                    norm_x =  sqrt(pow( (x[i] - x[j]),2));
                    norm_y = sqrt(pow( (y[i] - y[j]),2) );
                    
			     if(A[i*m.agents+j] == 0) 
			     {
                         rep_x +=  (dist_x) / pow(norm_x,3);
                         rep_y +=  (dist_y) / pow(norm_y,3);

			     } else {
				     spring_x += (log(norm_x) - 10) * ( dist_x ) / norm_x;
				     spring_y += (log(norm_y) - 10) * ( dist_y) / norm_y;
			     }
  
			     x[i] = x[i] + delta*(rep_x+spring_x);	
			     y[i]= y[i] + delta*(rep_y+spring_y);
               }     
	     }
     }
 

}				 

