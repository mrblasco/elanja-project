#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include "../h/const.h"

void intraction(double *p, double *q, double *A, double *R, int *degree, int *A_degree, int *B_degree) {

	int i, j;

	printf("Pippo %d\n", sizeof(double));

	for(i=0; i<COLUMN; i++)
	{
		*(p+i) = 2.5;
	}

	for(i=0; i<ROW; i++)
	{
		for(j=0; j<COLUMN; j++)
		{
			if(j<M)
				*(A+i+(j*sizeof(int))) = 5;
			else
				*(A+i+(j*sizeof(int))) = 2;
		}
	}
}
