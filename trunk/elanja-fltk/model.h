#ifndef MODEL_H
#define MODEL_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "const.h"

class model{
public: 
	/* Initialize functions and variables */
	void init(int linear_lattice_dimension, int agents, int nFeatures, int pos_traits, int outdegree, double delta, int maxSide, int gridW, int gridH); 
	/* Step computing the model status */
	void step(); 
	
	int linear_lattice_dimension; 
	int agents; 
	int link; 
	int nFeatures; 
	int pos_traits;
	int control; 
	int index, index2;
	int outdegree;
	double delta;
	int maxSide;
	int nRegions;
	int gridW;
	int gridH;

	/* matrix/vector pointers */
	int *A, *k, *degree_freq, *feature, *feat_freq, *vector, *label, *reg_size, *Nlist, *x, *y;
};

void genFeatures();
void coordinates(int *x, int *y, int w, int h);
void computeRegions();

#endif
