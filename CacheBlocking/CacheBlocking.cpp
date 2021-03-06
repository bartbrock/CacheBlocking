// CacheBlocking.cpp 
//

#include "stdafx.h"
#include <time.h>

using namespace std;

//#define WIDTH (1<<8) // took 0.244 seconds
#define WIDTH (1<<10) // took 1.123 seconds

#define STEP (1<<5)

double a[WIDTH][WIDTH];
double b[WIDTH][WIDTH];
double c[WIDTH][WIDTH];

void transposeMatrix();
void multiplyMatrix();
void multiplyMatrixBlock();
void initMatrix();
void printMatrix(double);

int main()
{
	srand(110);
	clock_t start, end, start2, end2;
	double diff = 0, diff2 = 0;
	int count = 0;

	// fill matrix with random values
	initMatrix();
	//printMatrix(diff);

	printf("size of cache: %d,  size of blocking: %d \n\n", WIDTH, STEP);
	//start timer and call transpose function
	start = clock();
	multiplyMatrix();
	end = clock();
	diff = end - start;
	// print matrix c
	printf("cache without blocking \n");
	printMatrix(diff);

	//start timer and call transpose function
	start2 = clock();
	multiplyMatrixBlock();
	end2 = clock();
	diff2 = end2 - start2;
	// print matrix c
	printf("cache with blocking \n");
	printMatrix(diff2);
	return 0;
}


void transposeMatrix()
{
	for (int j = 0; j < WIDTH; j++)
	{
		for (int i = 0; i < WIDTH; i++)
		{
			c[i][j] = a[i][j];
		}
	}
}

void multiplyMatrixBlock()
{
	for (int ii = 0; ii < WIDTH; ii += STEP) {
		for (int jj = 0; jj < WIDTH; jj += STEP) {
			for (int kk = 0; kk < WIDTH; kk += STEP)
			{
				for (int i = ii; i < ii + STEP; i++)
				{
					for (int j = jj; j < jj + STEP; j++)
					{
						for (int k = kk; k < kk + STEP; k++)
						{
							c[i][j] += a[i][k] * b[k][j];
						}
					}
				}
			}
		}
	}
}

void multiplyMatrix()
{
	for (int j = 0; j < WIDTH; j++)
	{
		for (int i = 0; i < WIDTH; i++)
		{
			for (int k = 0; k < WIDTH; k++)
			{
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
}

void initMatrix()
{
	for (int j = 0; j < WIDTH; j++)
	{
		for (int i = 0; i < WIDTH; i++)
		{
			a[i][j] = ((double)rand()) / RAND_MAX;
			b[i][j] = ((double)rand()) / RAND_MAX;
			c[i][j] = 0;
		}
	}
}
void printMatrix(double d)
{
	//printf("START MATRIX \n");
	/*for (int j = 0; j < 10; j++)
	{
		for (int i = 0; i < 10; i++)
		{
			printf("%f", c[i][j]);
		}
		printf("\n");
	}*/
	printf("END MATRIX \n");
	printf("Took %f seconds.  \n\n", d / (double)CLOCKS_PER_SEC);
}
