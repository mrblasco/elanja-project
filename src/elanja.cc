#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>

#define ROW 3 		/* Number of rows */
#define COLUMN 3		/* Number of columns */

using namespace std;

int main()
{
        int i, j = 0;

        int A[ROW][COLUMN];
        int B[ROW][COLUMN];
        int C[ROW][COLUMN];


/*Initialize matrix with value from 0 to 9 */
        for(i=0; i<ROW; i++)
        {
	   for(j=0; j<COLUMN; j++)
	   {
	        A[i][j] = rand() %9;
	        B[i][j] = rand() %9;
	   }
        }
/* Print matrix A and B */
       printf("Matrix A\n");
        for(i=0; i<ROW; i++)
        {
	   for(j=0; j<COLUMN; j++)
	   {
	       printf("%d\t", A[i][j]);
	      cout<<" ";
	   }
	   printf("\n");
        }

        printf("Matrix B\n");
        for(i=0; i<ROW; i++)
        {
	   for(j=0; j<COLUMN; j++)
	   {
	       printf("%d\t", B[i][j]);
	   }
	    printf("\n");
        }

/* Print matrix A*B */
	printf("Matrix C\n");
         for(i=0; i<ROW; i++)
        {
	   for(j=0; j<COLUMN; j++)
	   {
	       C[i][j] = (A[i][j] * B[i][j]) + (A[i][j+1] * B[i+1][j]) + (A[i][j+2] * B[i+2][j]);
	       printf("%d\t", C[i][j]);
	   }
	    printf("\n");
        }
}

