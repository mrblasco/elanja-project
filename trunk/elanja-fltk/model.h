#ifndef MODEL_H
#define MODEL_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "elanja-fltk.h"
#include "const.h"

class model{
public: 
     /* initialize functions and variables */
	void init(int agents, int distance, double Agroup, double epsilon, double friendship); 
	void reinit(int agents, int distance, double Agroup, double epsilon, double friendship); 
	void step(); 
	
	int agents;
	int distance;
	int m;
	double rho;
	double epsilon;
	double friendship;

	double *p;
	double *q;
	double *R;

	int *A;
	int *B;

	int *degree;
	int *A_degree;
	int *B_degree;

	double *composition;
	
};

void interaction(int agents, int m,  double *p, double *q, int *A, double epsilon, double friendship);

void multiplyer(int agents, int *A, int *C);

/*void update(int agents, double *p, double *q, int *degree, int *A_degree, int *B_degree);
void externalUpdate(int agents, int *A, double *p, double *q, double epsilon, int *degree);
*/
#endif
