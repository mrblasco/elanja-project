#include <stdio.h>
#include <stdlib.h>
#include "../h/const.h"

/* Function to compute Adjacency Matrices at d<=2 */
void distance(int *A, int *B, int *C, int *degree, int *A_degree, int *B_degree, int d, FILE *out_1) {

	int i, j, l;
	
/*	FILE *out1_2;
	FILE *out1_3;*/
	
	/*out1_2 = fopen("degreeA_1.dat", "w");
	out1_3 = fopen("degreeB_1.dat", "w");	*/

	if(d==2)
	{

		/*  Initialize AM */
		for(i=0; i<COLUMN; i++) 
		{
			for(j=0; j<COLUMN; j++)
			{ 
				*(C + i*COLUMN + j) = 0;
			}
		}

		/* Degree vector distance 1 */ 
		for(i=0; i<COLUMN; i++)
		{
			for(j=0; j<COLUMN; j++)
			{
				*(degree+i) += *(A+(i*COLUMN)+j);
		   	}
			fprintf(out_1,"%d\t",*(degree+i));
		}

		/* Degree of A-type agents vector*/ 
		for(i=0; i<COLUMN; i++)
		{
			for(j=0; j<M; j++)
			{
				*(A_degree+i) += *(A+(i*COLUMN)+j);
		   	}
			fprintf(out_1,"%d\t",*(A_degree+i));
			for(j=M; j<COLUMN; j++)
			{
				*(B_degree+i) += *(A+(i*COLUMN)+j);
		   	}
			fprintf(out_1,"%d\t",*(B_degree+i));
		}
		fprintf(out_1,"\n");		

		/* Product */
		for(i=0; i<COLUMN; i++)
		{	
			for(j=0; j<COLUMN; j++)
			{		
				for (l=0; l<COLUMN;l++) 
					*(C + i*COLUMN +j) += (*(A + i*COLUMN +l) * *(B + j*COLUMN +l)); 
			}	
		} 
		/* Normalize Adjacency matrix adding distance one*/
		for(i=0; i<COLUMN; i++)
		{	
			for(j=0; j<COLUMN; j++)
			{	
				*(C + i*COLUMN +j) += *(A + i*COLUMN +j);
				if (*(C + i*COLUMN +j) > 1 )
						*(C + i*COLUMN +j) = 1;
			}      
		}

		 
	}
	else if (d==1)
	{
		/* Degree vector*/ 
		for(i=0; i<COLUMN; i++)
			{
				for(j=0; j<COLUMN; j++)
				{
					*(degree+i) += *(A+(i*COLUMN)+j);
			   	}
			}

		/* Degree of A-type agents vector*/ 
		for(i=0; i<COLUMN; i++)
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

