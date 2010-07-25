#include "model.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

model m; // istance of the model
int t; // counter for iteractions 

extern int w, h;
 
void model::init(int agents,  double rho, int nFeatures, double threshold, int friends, int w, int h){

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
		x[i] = 10+ (double) (rand() %w);		
		y[i] = 5 + (double) (rand() %h);

	}

	t = 0; 
}

void model::reinit(int agents, double rho,  int nFeatures, double threshold, int friends, int w, int h){
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
		x[i] = 10+ (double) (rand() %w); 
		y[i] = 5+ (double) (rand() %h); 

	}
 	t = 0;
} 


/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%      STEP              %%%%%%%%%%%%%%%%
%%%%%%%%      FUNCTION     %%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
void model::step(int w, int h){

int i, j;
int rnd;

     /* Compute correlation matrix*/
	genCorrMat();

     /* Compute degrees and adjacency matrix*/
	update();

     /* Coordinates on the plane*/
     coordinates(A, x, y, w, h);

     /* Dynamic: at each step extract one pair of nodes at random then: 
          1. if no link, with probability rho they both copy-paste one feature
          2. if directed link, the pointing node copy-paste one feature
          3. if reciprocal link, they do not change nothing. 
     */
      i = rand()%agents;    
      j = rand()%agents;    
     rnd = rand()%nFeatures;
          
     /* directed from i to j  */
     if( A[i*agents + j] == 0 && A[j*agents + i] ==1 )
     {
          features[rnd*agents + i] = features[rnd*agents + j];
     }

     if (A[i*agents + j] == 1 && A[j*agents + i] == 0 )
     {
          features[rnd*agents + i] = features[rnd*agents + j];
     }
     if (A[i*agents + j] == 0 && A[j*agents + i] == 0)
     {
          if( rand()%1000 / (double) 1000 < rho )
          {
               features[rnd*agents + i] = features[rnd*agents + j];
           }
     }


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

     delta = 0.000001;

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
			
 
