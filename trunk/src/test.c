#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../h/const.h"
#include "../h/util.h"

int main(){

	
	int i;

	srand(time(NULL));

	for(i=0; i<4; i++)
	{
		printf("Numero casuale: %d\n", rand()%10);
	}

	return 0;
}
