#include "model.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/* Istance of the Model */
model m;
/* Simulation Counter */
int pippo; 

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
	this->nRegions = 0;
     
	/* Memory allocation needed */
	if(A) free(A);
    	this->A = (int*) malloc(sizeof(double)*agents*agents); /* adjacency matrix */
	if(feature) free(feature);
	this->feature = (int*) malloc(sizeof(double)*(agents*nFeatures)); /* features */
	if(vector) free(vector);
	this->vector = (int*) malloc(sizeof(double)*agents); /* temporary vector for various values */
	if(label) free(label);
	this->label = (int*) malloc(sizeof(double)*agents); /* labels */
	if(reg_size) free(reg_size);
	this->reg_size = (int*) malloc(sizeof(double)*(agents*(nFeatures+1))); /* labels histogram */
	if(Nlist) free(Nlist);
	this->Nlist = (int*)malloc(sizeof(int)*(linear_lattice_dimension*linear_lattice_dimension*outdegree));
	if(x) free(x);
	this->x = (int*)malloc(sizeof(int)*agents);
	if(y) free(y);
	this->y = (int*)malloc(sizeof(int)*agents);


	/* =========CREATE NETWORK ====================  */

     	
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

	/* Compute Regions */
	computeRegions();

	pippo = 0;
}


/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%% STEP %%%%%%%%%%%%%%%%%%%%%
%%%%%%%% FUNCTION %%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
void model::step(){

	int i, a, j, f, n;
	double p, r, prob;
	int counter;

	/* Dynamic process */
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
%%%%% GENERATE FEATURES %%%%%%%%%%%%
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
%%%%%   GENERATE COORDINATES %%%%%%%
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

	for(i=0; i<m.linear_lattice_dimension; i++)
	{
		for(j=0; j<m.linear_lattice_dimension; j++)
		{		
			if(m.linear_lattice_dimension == 25)
			{
				tmp = (m.linear_lattice_dimension * i) + j;	
				x[tmp] = ((j+1) *offset)-5;	
				y[tmp] = ((i+1) *offset)-5;
			}
			else
			{
				tmp = (m.linear_lattice_dimension * i) + j;	
				x[tmp] = (j+1) *offset;	
				y[tmp] = (i+1) *offset;
			}
		}
	}
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%% COMPUTE REGIONS %%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
void computeRegions()
{
	int i, j, k, a, test;

	//Labeling
	a = 0;
	m.label[0]= a;
	for(i=1;i<m.agents;i++)
	{
		test =1;
		for(j=0;j<i;j++)
		{
			if(m.feature[i*m.nFeatures+0]==m.feature[j*m.nFeatures+0])
			{
				if(m.feature[i*m.nFeatures+1]==m.feature[j*m.nFeatures+1])
				{
					if(m.feature[i*m.nFeatures+2]==m.feature[j*m.nFeatures+2])
					{
						m.label[i] = m.label[j];          
						test = 0;
					}                            
				}                        
			}
		}
		if(test==1)
		{
			a++;
			m.label[i] = a;
		}
	}

        for(i=0;i<m.agents;i++)
        {
                m.reg_size[i*(m.nFeatures+1)+0] = 0;
        }
        for(i=0;i<m.agents;i++)
        {
                m.reg_size[m.label[i]*(m.nFeatures+1)+0]++;
		m.reg_size[m.label[i]*(m.nFeatures+1)+1] = m.feature[i*m.nFeatures+0];
		m.reg_size[m.label[i]*(m.nFeatures+1)+2] = m.feature[i*m.nFeatures+1];
		m.reg_size[m.label[i]*(m.nFeatures+1)+3] = m.feature[i*m.nFeatures+2];
        }

	m.nRegions=0;
	for(i=0;i<m.agents;i++)
	{
		if(m.reg_size[i*(m.nFeatures+1)+0] != 0)
			m.nRegions++;
	}
}
			
 
