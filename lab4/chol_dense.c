#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define IDX(i, j, n) (((j)+ (i)*(n)))

//inline int IDX(int i, int j, int n)
//{
//	register int res;
//	__asm__ ( "imull %%ebx, %%eax;" : "=a" (res) : "a" (i) , "b" (n) );
//	__asm__ ( "addl %%ebx, %%eax;" : "=a" (res) : "a" (j) , "b" (res) );
		
//	return res;
//}

void printMat(double *A, int n)
{
	register int i, j;
	for(i = 0; i < n; i++) 
	{
		for(j = 0; j < n; j++)
			printf("%2.8lf\t", A[IDX(i, j, n)]); 
	printf("\n");
	}
}

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

int chol(double *A, unsigned int n)
{
	register unsigned int i;
	register unsigned int j;
	register unsigned int k;
	register double res;

	register unsigned int index;
	register unsigned int iindex;
	register unsigned int jindex;


	register unsigned int jjindex;
	register unsigned int jtindex;

	for (j = 0; j < n; j++) 
	{

		index = IDX(j, j, n);
		jindex = IDX(j, 0, n);

		iindex = IDX(j, 0, n);

		for (i = n - j; i--;) 
		{
			for (k = j; k--;) 
			{
				asm ("fmul %2, %y0": "=&t" (res) : "%0" (A[iindex]), "u" (A[jindex]));
				asm ("fsub %2, %y0": "=&t" (A[index]) : "%0" (A[index]), "u" (res));				

				__asm__ ( "addl %%ebx, %%eax;" : "=a" (iindex) : "a" (1) , "b" (iindex) );
				__asm__ ( "addl %%ebx, %%eax;" : "=a" (jindex) : "a" (1) , "b" (jindex) );
			}

			__asm__ ( "addl %%ebx, %%eax;" : "=a" (index) : "a" (n) , "b" (index) );
			__asm__ ( "addl %%ebx, %%eax;" : "=a" (iindex) : "a" (n-j) , "b" (iindex) ); //WTF??!!
		}
		
		jjindex = IDX(j, j, n);
		__asm__ ( "addl %%ebx, %%eax;" : "=a" (jtindex) : "a" (n) , "b" (jjindex) );

		if (A[jjindex] < 0.0) {
			return (1);
		}


		A[jjindex] = sqrt(A[jjindex]);

		for (i = n - j - 1; i--;)
		{
			asm ("fdiv %2, %y0": "=&t" (A[jtindex]) : "%0" (A[jtindex]), "u" (A[jjindex]));
			__asm__ ( "addl %%ebx, %%eax;" : "=a" (jtindex) : "a" (n) , "b" (jtindex) );

		}
	}

	return (0);
}

int
main()
{
	register double *A;
	register int i, j, n, ret;
 
	n = 2000;
	A = calloc(n*n, sizeof(double));
	assert(A != NULL);
	for(i=0; i<n; i++)
		A[IDX(i, i, n)] = 2;

//	printMat(A,n);

	if(chol(A, n))
		fprintf(stderr, "COS NIE DZIALA\n");

//	printMatAfterChol(A,n);		
		

	free(A);
	return 0;
}

