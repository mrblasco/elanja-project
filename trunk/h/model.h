#ifndef MODEL_H
#define MODEL_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "const.h"

class model{
public: 
     	/* initialize functions and variables */
	void init(int agents, double rho, int nFeatures, double threshold, int friends); 
	void reinit(int agents, double rho, int nFeatures, double threshold, int friends); 
	void step(); 
	
	int agents;
	double rho;
	int friends;
    
	double threshold;
	int nFeatures;

	double *features;
	int *F;

	double *A;
	double *tvalue;

	int *degree;
	int *A_degree;
	int *B_degree;
	
	double *tvalue;

     void genFeatures(int i);
     double genCorrMat();
     void update();

};

#endif
