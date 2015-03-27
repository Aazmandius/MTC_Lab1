#include "stdafx.h"
#include <omp.h>
#include <time.h> 
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

const int numberOfThreads = 8;

int n = 10;
int i, j, k;

void initMatrix(int n, __int32 **M);
void fillMatrix(int n, __int32 **M);
void printMatrix(int n, __int32 **M);
double doCalculations(int n);

int _tmain(int argc, _TCHAR* argv[])
{
	omp_set_num_threads(numberOfThreads);
	string outputStr = "";

	cout	<< "Number of threads: " 
			<< numberOfThreads 
			<< endl << endl;

	for (n = 10; n <= 100; n += 10)
	{
		double duration = 0;
		int repeatCount = 10;
		for (int t = 0; t < repeatCount; ++t)
		{
			duration += doCalculations(n);
		}
		outputStr += n + "\t" + to_string(duration / repeatCount) + "\n";

		cout	<< "[" << n << " x " << n << "]"
				<< endl
				<< "Avg duration: " << duration / repeatCount << " seconds."
				<< endl;
	}
	cout << endl << endl;

	for (n = 100; n <= 1000; n += 100)
	{
		double duration = 0;
		int repeatCount = 5;
		for (int t = 0; t < repeatCount; ++t)
		{
			duration += doCalculations(n);
		}
		outputStr += n + "\t" + to_string(duration / repeatCount) + "\n";

		cout	<< "[" << n << " x " << n << "]"
				<< endl
				<< "Avg duration: " << duration / repeatCount << " seconds."
				<< endl;
	}
	cout << endl << endl;

	ofstream outputFile;
	string fileName = "output" + to_string(numberOfThreads) + ".txt";
	outputFile.open(fileName);
	outputFile << outputStr;
	outputFile.close();

	system("pause");

	return 0;
}

double doCalculations(int n)
{
	__int32 **MatrixA = new __int32*[n];
	__int32 **MatrixB = new __int32*[n];
	__int32 **MatrixC = new __int32*[n];
	__int32 sum;

	double start = 0;
	double end = 0;

	initMatrix(n, MatrixA);
	initMatrix(n, MatrixB);
	initMatrix(n, MatrixC);

	fillMatrix(n, MatrixA);
	fillMatrix(n, MatrixB);

	//printMatrix(n, MatrixA);
	//cout << endl;
	//cout << endl;

	//printMatrix(n, MatrixB);
	//cout << endl;
	//cout << endl;

	start = omp_get_wtime();

#pragma omp parallel for private(i,j,k)
	for (i = 0; i < n; i++)
	{
		for (k = 0; k < n; k++)
		{
			sum = 0;
			for (j = 0; j < n; j++)
			{
				sum += MatrixA[i][j] * MatrixB[j][k];
			}
			MatrixC[i][k] = sum;
		}
	}

	end = omp_get_wtime();

	return end - start;
}

void initMatrix(int n, __int32 **M)
{
	for (int i = 0; i < n; ++i)
	{
		M[i] = new __int32[n];
	}
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

void printMatrix(int n, __int32 **M)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cout << M[i][j] << "\t";
		}
		cout << endl;
	}
}