#include <stdio.h>
#include <stdlib.h>
#include "../h/const.h"

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

