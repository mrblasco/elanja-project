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
	void init(int agents, double rho, int nFeatures, double threshold, int friends, int w, int h); 
	void reinit(int agents, double rho, int nFeatures, double threshold, int friends,int w, int h); 
	void step(int w, int h); 
	
	int agents;
	int distance;
	int m;
	double rho;
	double epsilon;
	int friends;
	double threshold;
	int nFeatures;

	double *features;
	int *F;

	double *A;
	
	double *x;
	double *y;

	int *degree;
	int *A_degree;
	int *B_degree;
};

void genFeatures(int i);
//void interaction(int agents, int m,  double *p, double *q, double *A, double epsilon, double friendship);
double genCorrMat();
//void multiplyer(int agents, int *A, int *C);
void update();
void coordinates(double *A, double *x, double *y, int w, int h);

#endif
