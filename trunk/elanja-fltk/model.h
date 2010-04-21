#ifndef MODEL_H
#define MODEL_H

#include "elanja-fltk.h"
#include "const.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "const.h"
#include <iostream>

class model{
public:
	void init(int agents, int distance, double population, double epsilon, int friendship);
	void reinit(double lambda, double g_coef, double c_exp, int numAgents);
	void step();
	
	int agents;
	int distance;
	int m;
	double population;
	double epsilon;
	int friendship;

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

double urand();
void multiplyer(int agents, int m, int distance, int *A, int *B, int *C, int *degree, int *A_degree, int *B_degree, int d);
void interaction(int agents, int m, int distance, double *p, double *q, int *A, double *R, int *degree, int *A_degree, int *B_degree);
void update(int agents, double *p, double *q, int *degree, int *A_degree, int *B_degree);
void externalUpdate(int agents, int *A, double *p, double *q, double epsilon, int *degree);

#endif
