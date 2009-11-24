#include <stdio.h>
#include <stdlib.h>
#include "../h/const.h"

/* Function to multiply Matrices */
void multiply(int *A, int *B, int *C) {

int i, j, l = 0; 

/*  Initialize */
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
				*(C + i*COLUMN +j) += *(A + i*COLUMN +l) + *(B + j*COLUMN +l); 
		}	
	} 
/* Normalize to Adjacency matrix adding distance one*/
for(i=0; i<ROW; i++)
     {	
		for(j=0; j<COLUMN; j++)
		{	
		*(C + i*COLUMN +j) += *(A + i*COLUMN +j);
		if (*(C + i*COLUMN +j) > 1 )
			{
			*(C + i*COLUMN +j) = 1;
			}
		}      
	} 
}
 
