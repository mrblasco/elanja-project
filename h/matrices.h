/* Intercation function */
extern void interaction(int agents, int m, int distance, double *p, double *q, int *A, double *R, int *degree, int *A_degree, int *B_degree);

/* Update function */
extern void update(int agents, double *p, double *q, int *degree, int *A_degree, int *B_degree);

/* External Update */
extern void externalUpdate(int agents, int *A, double *p, double *q, double epsilon, int *degree);

/* Multiply function */
extern void multiply(int agents, int m, int distance, int *A, int *B, int *C, int *degree, int *A_degree, int *B_degree, int d, FILE *out_1);
