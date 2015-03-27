// MTC_Lab1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <omp.h>
#include <time.h> 
#include <sstream>
#include <iostream>

using namespace std;

// ќбъ€вл€ем переменные
const int numberOfThreads = 8;
int n = 100; // размер матрицы
__int32 sum;
int _i, _j, _k;

void fillMatrix(int n, __int32 **M);

int _tmain(int argc, _TCHAR* argv[])
{
	__int32 **MatrixA = new __int32*[n];
	__int32 **MatrixB = new __int32*[n];
	__int32 **MatrixC = new __int32*[n];
	
	for (int i = 0; i < n; ++i)
	{
		MatrixA[i] = new __int32[n];
	}
	for (int i = 0; i < n; ++i)
	{
		MatrixB[i] = new __int32[n];
	}
	for (int i = 0; i < n; ++i)
	{
		MatrixC[i] = new __int32[n];
	}

	fillMatrix(n, MatrixA);
	fillMatrix(n, MatrixB);
	fillMatrix(n, MatrixC);

#pragma omp parallel for private(_i,_j,_k)
	for (_i = 0; _i<n; _i++)
	{
		for (_k = 0; _k<n; _k++)
		{
			sum = 0;
			for (_j = 0; _j<n; _j++)
			{
				sum += MatrixA[_i][_j] * MatrixB[_j][_k];
			}
			MatrixC[_i][_k] = sum;
		}
	}

	cout << std::to_string(sum);

	string str = "";
	cin >> str;

	return 0;
}

void fillMatrix(int n, __int32 **M)
{
	srand(time(NULL));

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			M[i][j] = rand() % 100 + 1;
		}
	}
}
