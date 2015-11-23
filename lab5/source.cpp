#include "immintrin.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* for Fortran - j*n + i */
//#define IDX(i, j, n)	(((i) * (n)) + (j))
#define IDX(i, j, n) (((j)+ (i)*(n)))

void printMatAfterChol(double *A, int n)
{
	register int i, j;
	for (i = 0; i < n; i++) 
	{
		for (j = 0; j <= i; j++)
			printf("%2.8lf\t", A[IDX(i, j, n)]);
		printf("\n");
	}
}

int
chol(double *A, unsigned int n)
{
	unsigned int i;
	unsigned int j;
	unsigned int k;

	__m256d a0, b0, a1, b1, a2, b2, a3, b3, c0, c1, c2, c3;
	double out0[4];
	double out1[4];
	double out2[4];
	double out3[4];

	for (j = 0; j < n; j++) {
		for (i = j; i < n; i++) {
			for (k = 0; k < j; ) {
				if(j - k >= 16)
				{
					A[IDX(i, j, n)] -= A[IDX(i, k, n)] * A[IDX(j, k, n)];
				

					a0 = _mm256_set_pd(A[IDX(i, k, n)], A[IDX(i, k+1, n)], A[IDX(i, k+2, n)], A[IDX(i, k+3, n)]);
					b0 = _mm256_set_pd(A[IDX(j, k, n)], A[IDX(j, k+1, n)], A[IDX(j, k+2, n)], A[IDX(j, k+3, n)]);

					a1 = _mm256_set_pd(A[IDX(i, k+4, n)], A[IDX(i, k+5, n)], A[IDX(i, k+6, n)], A[IDX(i, k+7, n)]);
					b1 = _mm256_set_pd(A[IDX(j, k+4, n)], A[IDX(j, k+5, n)], A[IDX(j, k+6, n)], A[IDX(j, k+7, n)]);

					a2 = _mm256_set_pd(A[IDX(i, k+8, n)], A[IDX(i, k+9, n)], A[IDX(i, k+10, n)], A[IDX(i, k+11, n)]);
					b2 = _mm256_set_pd(A[IDX(j, k+8, n)], A[IDX(j, k+9, n)], A[IDX(j, k+10, n)], A[IDX(j, k+11, n)]);

					a3 = _mm256_set_pd(A[IDX(i, k+12, n)], A[IDX(i, k+13, n)], A[IDX(i, k+14, n)], A[IDX(i, k+15, n)]);
					b3 = _mm256_set_pd(A[IDX(j, k+12, n)], A[IDX(j, k+13, n)], A[IDX(j, k+14, n)], A[IDX(j, k+15, n)]);


					c0 = _mm256_mul_pd(a0,b0);
					c1 = _mm256_mul_pd(a1,b1);
					c2 = _mm256_mul_pd(a2,b2);
					c3 = _mm256_mul_pd(a3,b3);

					_mm256_storeu_pd(out0, c0);
					_mm256_storeu_pd(out1, c1);
					_mm256_storeu_pd(out2, c2);
					_mm256_storeu_pd(out3, c3);

					A[IDX(i, j, n)] -= out0[0];
					A[IDX(i, j+1, n)] -= out0[1];
					A[IDX(i, j+2, n)] -= out0[2];
					A[IDX(i, j+3, n)] -= out0[3];

					A[IDX(i, j+4, n)] -= out0[4];
					A[IDX(i, j+5, n)] -= out0[5];
					A[IDX(i, j+6, n)] -= out0[6];
					A[IDX(i, j+7, n)] -= out0[7];

					A[IDX(i, j+8, n)] -= out0[8];
					A[IDX(i, j+9, n)] -= out0[9];
					A[IDX(i, j+10, n)] -= out0[10];
					A[IDX(i, j+11, n)] -= out0[11];

					A[IDX(i, j+12, n)] -= out0[12];
					A[IDX(i, j+13, n)] -= out0[13];
					A[IDX(i, j+14, n)] -= out0[14];
					A[IDX(i, j+15, n)] -= out0[15];
					k+=16;
				}
				else
				{
					A[IDX(i, j, n)] -= A[IDX(i, k, n)] * A[IDX(j, k, n)];
					k++;
				}
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
	A = (double*) calloc(n*n, sizeof(double));
	assert(A != NULL);

	for(i=0; i<n; i++)
		A[IDX(i, i, n)] = 2;

	chol(A,n);
//	printMatAfterChol(A,n);
//	if (!chol(A, n));
//	else
//		fprintf(stderr, "Error: matrix is either not symmetric or not positive definite.\n");

	free(A);
	return 0;
}

