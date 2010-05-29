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
	void init(int agents, int distance, double Agroup, double epsilon, double friendship, int nFeatures, double threshold); 
	void reinit(int agents, int distance, double Agroup, double epsilon, double friendship, double threshold); 
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

	int *degree;
	int *A_degree;
	int *B_degree;
	
};

void interaction(int agents, int m,  double *p, double *q, double *A, double epsilon, double friendship);
double newInteraction(double L, double *A, int agents);
void multiplyer(int agents, int *A, int *C);
void update(int *degree, double *A, double threshold, double *features);

#endif
