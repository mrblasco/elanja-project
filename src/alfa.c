/*The following two variables have to be decleared at the beginning of the program*/
double alfa;			/*Measure of the non-segregation of the system*/
double T = 20 * N / 100;	/*percentual parameter*/


out3 = fopen("alfa.dat", "w");
/*The following part must be in the time cycle*/
/*Computation of alfa at each time step*/ 
alfa = 0;
for(i=0;i<M;i++)
	{ 
		if *(B_degree+i) >= T 
			alfa++
	}
for(i=M;i<N;i++)
	{	
		if *(A_degree+i) >= T
			alfa++
	}
alfa = alfa / N;	/*Normalization of alfa so that it does not depend on N. alfa now is a number betwen 0 and 1*/
fprintf(out3, "%f\t", alfa);

