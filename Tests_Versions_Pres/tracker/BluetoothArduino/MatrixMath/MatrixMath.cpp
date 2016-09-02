/*
 *  MatrixMath.cpp Library for Matrix Math
 *
 *  Created by Charlie Matlack on 12/18/10.
 *  Modified from code by RobH45345 on Arduino Forums, algorithm from 
 *  NUMERICAL RECIPES: The Art of Scientific Computing.
 */

#include "MatrixMath.h"

#define NR_END 1

MatrixMath Matrix;			// Pre-instantiate

void MatrixMath::Copy(float* A, int n, int m, float* B)
{
	int i, j, k;
	for (i=0;i<m;i++)
		for(j=0;j<n;j++)
		{
			B[n*i+j] = A[n*i+j];
		}
}

//Matrix Addition Routine
void MatrixMath::Add(float* A, float* B, int m, int n, float* C)
{
	// A = input matrix (m x n)
	// B = input matrix (m x n)
	// m = number of rows in A = number of rows in B
	// n = number of columns in A = number of columns in B
	// C = output matrix = A+B (m x n)
	int i, j;
	for (i=0;i<m;i++)
		for(j=0;j<n;j++)
			C[n*i+j]=A[n*i+j]+B[n*i+j];
}
