#include "pch.h"
#include "MatrixCalculator.h"

MatrixCalculator::MatrixCalculator( int N)
{
	this->N = N;
	initializeMatrixes();
}

MatrixCalculator::~MatrixCalculator()
{
	for (int i = 0 ; i < N ; ++i)
	{
		delete[] matrixA[i];
	}
	for (int i = 0 ; i < N ; ++i)
	{
		delete[] matrixB[i];
	}
	for (int i = 0 ; i < N ; ++i)
	{
		delete[] matrixC[i];
		delete[] resultMatrix[i];
	}
	
	delete[] matrixA;
	delete[] matrixB;
	delete[] matrixC;
	delete[] resultMatrix;
}

void MatrixCalculator::zeroMatrix(int** matrix,  int N)
{
	for (int i = 0 ; i < N ; ++i)
	{
		for (int j = 0 ; j < N ; ++j)
		{
			matrix[i][j] = 0;
		}
	}
}

int** MatrixCalculator::createMatrix( int N)
{
	int** matrix = new int*[N];
	for (int i = 0 ; i < N ; ++i)
	{
		matrix[i] = new int[N];
	}
	return matrix;
}

void MatrixCalculator::initializeMatrixes()
{
    matrixA = createMatrix(N);
	matrixB = createMatrix(N);
	matrixC = createMatrix(N);
	resultMatrix = createMatrix(N);
	zeroMatrix(resultMatrix, N); 
	randomiseMatrixValues(matrixA, N);
	randomiseMatrixValues(matrixB, N);
	randomiseMatrixValues(matrixC, N);
	
}

void MatrixCalculator::randomiseMatrixValues(int** matrix, int N)
{
	for (int i = 0 ; i < N ; ++i)
	{
		for (int j = 0 ; j < N ; ++j)
		{
			matrix[i][j] = rand() % 5 +1;
		}
	}
}

void MatrixCalculator::multiplyRow(int** resultMatrix, int** matrixA, int** matrixB, int row, int N)
{
	for (int i = 0 ; i < N ; ++i)
	{
		for (int j = 0 ; j < N ; ++j)
		{
			resultMatrix[row][i] += matrixA[row][j] * matrixB[j][i];	
		}
	}
}

void MatrixCalculator::multiplyMatrixes()
{	
	int** temporaryMatrix = createMatrix(N);
	zeroMatrix(temporaryMatrix,N);
	for (int i = 0 ; i < N ; ++i)
	{
		threads.push_back(std::thread(multiplyRow, temporaryMatrix, matrixA, matrixB , i , N));
	}
	
	for (auto thread = threads.begin() ; thread != threads.end() ; ++thread)
	{
		thread->join();
	}
	
	
	for  (int i = 0 ; i < N ; ++i)
	{
		threads[i] = std::thread(multiplyRow, resultMatrix, temporaryMatrix, matrixC , i , N);
	}
	for (auto thread = threads.begin() ; thread != threads.end() ; ++thread)
	{
		thread->join();
	}
	

	for (int i = 0 ; i < N ; ++i)
	{
		delete [] temporaryMatrix[i];
	}
	delete temporaryMatrix;
	
}

void MatrixCalculator::show()
{
	std::cout<<"Matrix A" <<std::endl;
	displayMatrix(matrixA, N);
	
	std::cout<<"Matrix B" <<std::endl;
	displayMatrix(matrixB, N);
	
	std::cout<<"Matrix C" <<std::endl;
	displayMatrix(matrixC, N);
	
	std::cout<<"Result Matrix (A*B)*C :" <<std::endl;
	displayMatrix(resultMatrix, N);
}

void  MatrixCalculator::displayMatrix(int** matrix,  int N)
{
	for (int i = 0 ; i < N ; ++i)
	{
		for (int j = 0 ; j < N ; ++j)
		{
			std::cout<<matrix[i][j]<<'\t';
		}
		std::cout<<std::endl;
	}
}
