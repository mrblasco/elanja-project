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
	void init(int agents, double rho, int nFeatures); 
	void reinit(int agents, double rho, int nFeatures); 
	void step(); 
	
	int agents;
	int distance;
	int m;
	double rho;
	double epsilon;
	double friendship;
	double threshold;
	int nFeatures;

	double *features;

	double *A;
	
	double *x;
	double *y;

	int *degree;
	int *A_degree;
	int *B_degree;
	
};

//void interaction(int agents, int m,  double *p, double *q, double *A, double epsilon, double friendship);
double newInteraction(double L, double *A, int agents);
//void multiplyer(int agents, int *A, int *C);
void update(double L,int *degree, double *A, double threshold, double *features);
void coordinates(double *A, double threshold, double *x, double *y);

#endif
