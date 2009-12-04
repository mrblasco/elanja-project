/* Intercation function */
extern void interaction(double *p, double *q, int *A, double *R, int *degree, int *A_degree, int *B_degree);

/* Update function */
extern void update(double *p, double *q, int *degree, int *A_degree, int *B_degree);

/*External Update */
extern void externalUpdate(int *A, double *p, double *q, double epsilon, int *degree);

/* multiply function */
extern void distance(int *A, int *B, int *C, int *degree, int *A_degree, int *B_degree);
