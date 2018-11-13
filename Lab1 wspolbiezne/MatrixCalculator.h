#ifndef _MATRIXCALCULATOR_H
#define _MATRIXCALCULATOR_H

#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <cstring>

class MatrixCalculator
{
public:
	MatrixCalculator(const int N = 4);
	~MatrixCalculator();
	void show();
	void multiplyMatrixes();
private:	
	int** matrixA;
	int** matrixB;
	int** matrixC;
	int** resultMatrix;
	
	 int N;

	
	std::vector<std::thread> threads;
	
	int** createMatrix( int N);
	void initializeMatrixes();
	void randomiseMatrixValues(int** matrix, int N);
	static void multiplyRow(int** resultMatrix, int** matrixA, int** matrixB, int row, int N);
	void displayMatrix(int** matrix, int N);
	void zeroMatrix(int** matrix, int N);
};


#endif