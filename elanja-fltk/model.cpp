#include "model.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

model m; // istance of the model
int pippo; // counter for iteractions 

extern int w, h;
 
void model::init(int linear_lattice_dimension, int agents, int nFeatures, int pos_traits, int outdegree, double delta, int maxSide){

	printf("Initializing Model ... \n");	

	/* Field of the class model */
	this->linear_lattice_dimension = linear_lattice_dimension;
	this->agents = agents;
	this->link = 0;
	this->nFeatures = nFeatures;
	this->pos_traits = pos_traits; 
	this->outdegree = outdegree;
	this->delta = delta;
	this->maxSide = maxSide;
     
	/* Memory allocation needed */
	if(A) free(A);
    	this->A = (int*) malloc(sizeof(double)*agents*agents); /* adjacency matrix */
	if(k) free(k);
	this->k = (int*) malloc(sizeof(double)*agents); /* degree */
	if(degree_freq) free(degree_freq);
	this->degree_freq = (int*) malloc(sizeof(double)*agents); /* degree histogram */
	if(feature) free(feature);
	this->feature = (int*) malloc(sizeof(double)*(agents*nFeatures)); /* features */
	if(feat_freq) free(feat_freq);
	this->feat_freq = (int*) malloc(sizeof(double)*pos_traits); /* features histogram */
	if(vector) free(vector);
	this->vector = (int*) malloc(sizeof(double)*agents); /* temporary vector for various values */
	if(label) free(label);
	this->label = (int*) malloc(sizeof(double)*agents); /* labels */
	if(reg_size) free(reg_size);
	this->reg_size = (int*) malloc(sizeof(double)*agents); /* labels histogram */
	if(Nlist) free(Nlist);
	this->Nlist = (int*)malloc(sizeof(int)*(linear_lattice_dimension*linear_lattice_dimension*outdegree));
	if(x) free(x);
	this->x = (int*)malloc(sizeof(int)*agents);
	if(y) free(y);
	this->y = (int*)malloc(sizeof(int)*agents);


	/* =========CREATE NETWORK ====================  */

	/* maxSide

	% 0 is no local interactions, i.e., random network
	% 1 is the square of 4 neighbors
	% 2 is the square of 8 neighbors 

	note: outdegree needs to be larger than 8 (or 24) to have long-range shortcuts,i.e., small worlds.
	if maxSide > 2 then outdegree needs to be at least 48 or seg. fault. */
     	
	/* Initialize var and network list */
	int i,j,i2,j2,jj,ii;
	int neighbors, distance;
	double ll,outcome;
	int l, g, n, k, mlinks;

	for (i=0;i<agents;i++)
	{
		for (g=0;g<outdegree;g++)
		{       
			Nlist[i*outdegree +g] = -1;
		}
	}   

	/* create network list -- local neighbors*/
	for (i=0;i<linear_lattice_dimension;i++)
	{
		for(j=0;j<linear_lattice_dimension;j++)
		{
			neighbors=0;

			/* local links */
			for(ii=(i-maxSide); ii<(i+maxSide+1);ii++)
			{
				for (jj=(j-maxSide); jj<(j+maxSide+1); jj++)
				{
					// normalize to torus 
					i2 = ((linear_lattice_dimension + ii) % (linear_lattice_dimension));  
					j2 = ((linear_lattice_dimension + jj) % (linear_lattice_dimension));

					if ( ( (i!=i2) || (j!=j2) ) )
					{
						if( (i==i2) || (j==j2) )
						{
                                   Nlist[(i*linear_lattice_dimension +j)*outdegree + neighbors] = (i2*linear_lattice_dimension +j2);
							neighbors++;
						}
					}
				}
			}

			/* ... then shortcuts are added */
			while (neighbors < outdegree)
			{         
				i2 = (rand()%linear_lattice_dimension);
				j2 = (rand()%linear_lattice_dimension);

				distance =  floor (sqrt(pow(MIN(fabs(i-i2),linear_lattice_dimension-fabs(i-i2)),2) + pow(MIN(fabs(j-j2),linear_lattice_dimension-fabs(j-j2)),2)));

				if(distance > maxSide )
				{   
					mlinks = 0;  /* check to avoid multiple links*/

					outcome =  pow(distance, (- delta) );
					ll = (double) (rand()%1000) / (double) 1000;
					if ( ll < outcome )
					{
						for (k = 0 ; k < neighbors; k++)
						{
							if( Nlist[ (i*linear_lattice_dimension +j)*outdegree + k ] == (i2*linear_lattice_dimension +j2))
								mlinks = 1;
						}
						if(mlinks == 0)
						{
                            				Nlist[ (i*linear_lattice_dimension +j)*outdegree + k ]  = (i2*linear_lattice_dimension +j2);
							neighbors++;
						}
					}
				}
			}
		}  
	}
	
	/* Generates Agents Features */
	genFeatures();
	/* Generates Agents Positions */
	coordinates(x, y, SIMULATION_WIDTH, SIMULATION_HIGH);

	pippo = 0;
}


/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%      STEP              %%%%%%%%%%%%%%%%
%%%%%%%%      FUNCTION     %%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
void model::step(){

	int i, a, j, f, n;
	double p, r, prob;
	int counter;

	/* Dynamic process */
	//t = 0;
	counter = 0;
	for(i=0;i<agents;i++)
	{
		a = rand() % outdegree;
		j = Nlist[i*outdegree +a];
		a = 0;                          
		for(f=0;f<nFeatures;f++)
		{
			if( feature[(i*nFeatures+f)] == feature[(j*nFeatures+f)] )
			{
				a++; 
			}
		}
		prob = (double)  a / (double) nFeatures;
		r = (rand() % 10000) / (double) 10000;
		if( r < prob )
		{
			n = 0;
			a = 0;
			for(f=0;f<nFeatures;f++)
			{
				if( feature[i*nFeatures+f] != feature[j*nFeatures+f] )
				{
					vector[n] = f;
					n++;
				}
				else
				{
					a++;
				}
			}
			if(n > 0 && a > 0)
			{
				a = rand() %n;
				f = vector[a];
				feature[i*nFeatures+f] = feature[j*nFeatures+f];
				counter++;
			}						
		}
	}

	pippo += 1;
}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%   GENERATE FEATURES       %%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
void genFeatures(){
     
     int i, f;

	/* Create features vectors*/
	for(i=0;i<m.agents;i++)
	{
		for(f=0;f<m.nFeatures;f++)
		{
			m.feature[i*m.nFeatures+f] = rand() % m.pos_traits;
		}
	}
}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%   GENERATE COORDINATES %%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
void coordinates(int *x, int *y, int w, int h)
{
int i, j, k;
int tmp, tmp2;
int offset;
	
	offset = (int)(w)/(m.linear_lattice_dimension);
	if(m.linear_lattice_dimension == 20)
	{
		offset -= 1;
	}
	else if(m.linear_lattice_dimension == 10)
	{
		offset -= 6;
	}
	else if(m.linear_lattice_dimension == 15)
	{
		offset -= 3;
	}
	/*else if(m.linear_lattice_dimension == 25)
	{
		offset = (int)(w-15)/(m.linear_lattice_dimension);
	}
	else if(m.linear_lattice_dimension == 30)
	{
		offset -= 3;
	}*/

	printf("offset = %d \n", offset);

	for(i=0; i<m.linear_lattice_dimension; i++)
	{
		for(j=0; j<m.linear_lattice_dimension; j++)
		{		
			tmp = (m.linear_lattice_dimension * i) + j;	
			x[tmp] = (j+1) *offset;	
			y[tmp] = (i+1) *offset;
		}
	}
}
			
 
