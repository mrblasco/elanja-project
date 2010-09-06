#!/bin/bash
#soluzione provvisoria

	./main 100 5 20 -0.8 0.10 20
	./main 100 5 20 -0.6 0.10 20
	./main 100 5 20 -0.4 0.10 20
	./main 100 5 20 -0.2 0.10 20
	./main 100 5 20 0 0.10 20
	./main 100 5 20 0.2 0.10 20
	./main 100 5 20 0.4 0.10 20
	./main 100 5 20 0.6 0.10 20
	./main 100 5 20 0.8 0.10 20
	
	agenti 1000 
	friends max 5
	features 5 - 30 step 5
	threshold -0.8 - 0.8 step 0.2
	rho 0
	n_iter 20
	

