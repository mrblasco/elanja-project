#include <stdio.h>
#include <stdlib.h>
#include "../h/const.h"

void intraction(int *p, int *q, int *A, int *R, int *degree, int *A_degree, int *B_degree) {

	int i, j;

	printf("arrivo qua!!!");
	for(i=0; i<ROW; i++)
     	{
	   	for(j=0; j<COLUMN; j++) 
	   	{
			if(i==j) 
			{
				*(R+(i*sizeof(int)*COLUMN)+(j*sizeof(int))) = 0;
				
			} else {
				*(R+(i*sizeof(int)*COLUMN)+(j*sizeof(int))) = 2;/*rand() %10001) / (double) 10000;*/
			}
	   	}
	}
}
