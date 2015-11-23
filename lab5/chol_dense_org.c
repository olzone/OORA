#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* for Fortran - j*n + i */
//#define IDX(i, j, n)	(((i) * (n)) + (j))
#define IDX(i, j, n) (((j)+ (i)*(n)))

int
chol(double *A, unsigned int n)
{
	unsigned int i;
	unsigned int j;
	unsigned int k;

	for (j = 0; j < n; j++) {
		for (i = j; i < n; i++) {
			for (k = 0; k < j; ++k) {
				A[IDX(i, j, n)] -= A[IDX(i, k, n)] *
				    A[IDX(j, k, n)];
			}
		}

		if (A[IDX(j, j, n)] < 0.0) {
			return (1);
		}

		A[IDX(j, j, n)] = sqrt(A[IDX(j, j, n)]);
		for (i = j + 1; i < n; i++)
			A[IDX(i, j, n)] /= A[IDX(j, j, n)];
	}

	return (0);
}

int
main()
{
	double *A;
	int i, j, n, ret;

	n = 2000;
	A = (double*)calloc(n*n, sizeof(double));
	assert(A != NULL);

	for(i=0; i<n; i++)
		A[IDX(i, i, n)] = 2;

	chol(A,n);
//	if (!chol(A, n));
//	else
//		fprintf(stderr, "Error: matrix is either not symmetric or not positive definite.\n");

	free(A);
	return 0;
}

