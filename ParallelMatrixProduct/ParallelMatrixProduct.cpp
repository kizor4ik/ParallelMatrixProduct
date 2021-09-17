#include "pch.h"
#include <stdio.h>
#include <omp.h>
#include <iostream>
#include <ctime>

using namespace std;
//Manual filling of the matrix
double** GetMX(int row, int col)
{
	double** a;
	a = new double*[row];
	for (int i = 0; i < row; i++)
	{
		a[i] = new double[col];
		for (int j = 0; j < col; j++)
		{
			cin >> a[i][j];
		}
	}
	return a;
}

//Matrix filling with random numbers modulated by 11 for simplicity
double** GetMXrand(int row, int col)
{
	double** a;
	a = new double*[row];
	for (int i = 0; i < row; i++)
	{
		a[i] = new double[col];
		for (int j = 0; j < col; j++)
		{
			a[i][j] = rand() % 11;
		}
	}
	return a;
}
//Print Matrix a size of row*col
void PrintMX(double** a, int row, int col)
{
	if (a != NULL)
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
				cout << a[i][j] << " ";
			cout << endl;
		}
	}
	else
		cout << "matrix inproductable";
}

//Linear realization of matrix product a * b size of row1*col1 and row2* col2 respectively
double** ProductMX(double** a, double** b, int row1, int row2, int col1, int col2)
{
	if (col1 != row2)
		return NULL;
	double** c;
	c = new double*[row1];
	for (int i = 0; i < row1; i++)
	{
		c[i] = new double[col2];
		for (int j = 0; j < col2; j++)
		{
			c[i][j] = 0;
			for (int k = 0; k < col1; k++)
				c[i][j] += a[i][k] * b[k][j];
		}
	}
	return c;
}

//Parallel realization of matrix product a * b size of row1*col1 and row2* col2 respectively
double** ParallelProductMX(double** a, double** b, int row1, int row2, int col1, int col2)
{
	double** res;
	res = new double*[row1];
	for (int i = 0; i < row1; i++)
	{
		res[i] = new double[col2];
	}

	int threadsNum = 4;
	omp_set_num_threads(threadsNum);

	int i, j, k;
#pragma omp parallel for shared(a,b,res) private(i,j,k)
	for (i = 0; i < row1; i++)
	{
		for (j = 0; j < col2; j++)
		{
			res[i][j] = 0;
			for (k = 0; k < col1; k++)
			{
				res[i][j] += (a[i][k] * b[k][j]);
			}
		}
	}
	return res;
}

int main() {
	double times = 0, timef = 0;

	int row1 = 2, row2 = 2, col1 = 2, col2 = 2;
	cin >> row1 >> col1 >> row2 >> col2;
	double** a, ** b, ** c, ** res;

	a = GetMXrand(row1, col1);
	b = GetMXrand(row2, col2);

	cout << "Matrix a:" << endl;
	PrintMX(a, row1, col1);

	cout << "Matrix b:" << endl;
	PrintMX(b, row2, col2);

	times = clock();
	cout << "Matrix product a.b linear realization:" << endl;
	c = ProductMX(a, b, row1, row2, col1, col2);
	PrintMX(c, row1, col2);
	timef = clock();
	cout << "linear product elapsed time: " << (timef - times) / 1000 << endl;

	times = clock();
	cout << "Matrix product a.b parallel realization:" << endl;
	res = ParallelProductMX(a, b, row1, row2, col1, col2);
	PrintMX(res, row1, col2);
	timef = clock();
	cout << "parallel product elapsed time: " << (timef - times) / 1000;
	return 0;
}


