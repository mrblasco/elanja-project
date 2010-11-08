#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "const.h"


class model{
public: 
     	/* Initialize functions and variables */
	void init(int edge_agents, int agents, int nFeatures, int pos_features, int n_iter, int outdegree, double delta, int maxSide); 
	/* Step computing the model status */
	void step(); 
	
	int edge_agents; 
	int agents; 
	int link; 
	int nFeatures; 
	int pos_features;
	int control; 
	int index, index2, label;
	int n_iter; 
	int outdegree;
	double delta;
	int maxSide;

	/* matrix/vector pointers */
	int *A, *k, *degree_freq, *feature, *feat_freq, *vector, *region, *reg_size, *Nlist;

};

#endif
