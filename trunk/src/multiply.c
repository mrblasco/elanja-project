#include <stdio.h>
#include <stdlib.h>
#include "../h/const.h"

/* Function to compute Adjacency Matrices at d<=2 */
void distance(int *A, int *B, int *C, int *degree, int *A_degree, int *B_degree, int d) {

	int i, j, l;

	if(d==2)
	{

		/*  Initialize AM */
		for(i=0; i<ROW; i++) 
		{
			for(j=0; j<COLUMN; j++)
			{ 
				*(C + i*COLUMN + j) = 0;
			}
		}

		/* Product */
		for(i=0; i<ROW; i++)
		{	
			for(j=0; j<COLUMN; j++)
			{		
				for (l=0; l<ROW;l++) 
					*(C + i*COLUMN +j) += *(A + i*COLUMN +l) * *(B + j*COLUMN +l); 
			}	
		} 
		/* Normalize Adjacency matrix adding distance one*/
		for(i=0; i<ROW; i++)
		{	
			for(j=0; j<COLUMN; j++)
			{	
				*(C + i*COLUMN +j) += *(A + i*COLUMN +j);
				if (*(C + i*COLUMN +j) > 1 )
						*(C + i*COLUMN +j) = 1;
			}      
		} 

		/* Initialize degree, A_degree, B_degree vectors to 0 at each iteraction */
		for(i=0; i<COLUMN; i++)
		{
			*(degree+i) = 0;
			*(A_degree+i) = 0;
			*(B_degree+i) = 0;
		}

		/* Degree vector*/ 
		for(i=0; i<ROW; i++)
			{
				for(j=0; j<COLUMN; j++)
				{
					*(degree+i) += *(C+(i*COLUMN)+j);
			   	}
			}

		/* Degree of A-type agents vector*/ 
		for(i=0; i<ROW; i++)
			{
				for(j=0; j<M; j++)
				{
					*(A_degree+i) += *(C+(i*COLUMN)+j);
			   	}
				for(j=M; j<COLUMN; j++)
				{
					*(B_degree+i) += *(C+(i*COLUMN)+j);
			   	}
			}

	}
	else if (d==1)
	{
		/* Degree vector*/ 
		for(i=0; i<ROW; i++)
			{
				for(j=0; j<COLUMN; j++)
				{
					*(degree+i) += *(A+(i*COLUMN)+j);
			   	}
			}

		/* Degree of A-type agents vector*/ 
		for(i=0; i<ROW; i++)
			{
				for(j=0; j<M; j++)
				{
					*(A_degree+i) += *(A+(i*COLUMN)+j);
			   	}
				for(j=M; j<COLUMN; j++)
				{
					*(B_degree+i) += *(A+(i*COLUMN)+j);
			   	}
			}
	}
	else
		printf("Distance error d = %d\n", d);
}

